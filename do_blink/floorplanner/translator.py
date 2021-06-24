import yaml
import json
import copy
import matplotlib.pyplot as plt
import matplotlib.patches as patches
###############################################################################
# First we read the yaml file
yaml_data = None
with open("draft.yaml", 'r') as yaml_file:
    try:
        yaml_data = yaml.safe_load(yaml_file)

    except yaml.YAMLError as exc:
        print(exc)

###############################################################################
# Next we get the interface information which is common to all pblocks

# Here we get the clocks
clocks = []
for clock in yaml_data["overlay"]["pblocks"]["interface"]["clocks"]:
    clock_dict = {
        "name": clock["name"],
        "type": "clk",
        "data_type": "scalar",
        "side": None
    }
    clocks.append(clock_dict)

# And here we get the ports
ports = []
for port in yaml_data["overlay"]["pblocks"]["interface"]["ports"]:
    port_dict = {
        "name": port["name"],
        "type": port["direction"],
        "data_type": "scalar" if port["width"] == 1 else "bus",
    }

    # Only insert a mapping for msb and lsb if its a bus
    if port_dict["data_type"] == "bus":
        port_dict["msb"] = port["width"]
        port_dict["lsb"] = 0

    port_dict["side"] = None
    ports.append(port_dict)
###############################################################################
# Now we loop through each pblock in the yaml file, create a 
# definition dictionary for it, and add it to a list.

definitions = []
for pblock in yaml_data["overlay"]["pblocks"]["pblocks"]:
    ###########################################################################
    # First we create a definition dictionary and populate it with data
    # from a specific pblock description in the yaml file. Note we don't
    # populate the "ports" list yet
    definition_dict = {
        "info": {
            "name": pblock["name"],
            "pins_per_tile": pblock["pins_per_tile"],
            "GRID_X_MAX": pblock["x_max"],
            "GRID_X_MIN": pblock["x_min"],
            "GRID_Y_MAX": pblock["y_max"],
            "GRID_Y_MIN": pblock["y_min"],
        },
        "synth_tiles_range": None,
        "ports": None
    }
    ###########################################################################
    # Now we make a deep copy of the list of clocks that we got earlier
    # and assign a side to each one, which depends on the specific pblock
    # we are working with.
    pblock_clocks = copy.deepcopy(clocks)
    for clock in pblock_clocks:
        if(pblock["x_max"] < yaml_data["overlay"]["clock_spine_x_coordinate"]):
            clock["side"] = "east"
        elif(pblock["x_min"] > yaml_data["overlay"]["clock_spine_x_coordinate"]):
            clock["side"] = "west"
        else:
            print("Error: pblock crosses the clock spine!")
            exit(1)
    ###########################################################################
    # Now we make a deep copy of the list of ports
    pblock_ports = copy.deepcopy(ports)

    # Then we get the pblock's parent switchbox
    parent = None
    for switchbox in yaml_data["overlay"]["BFT"]:
        if(switchbox["name"] == pblock["parent_switchbox"]):
            parent = switchbox
            break

    ###########################################################################
    def get_synth_tiles(direction, pblock, parent, yaml_data):
        #######################################################################
        # first get some information about how we will expand

        front_dim = None        # the dimension the front spans
        exp_dim = None          # the dimension the front will expand along
        exp_dir = None          # the direction the front will expand along the dimension

        if(direction == "north"):
            front_dim, exp_dim, exp_dir = "x" , "y", -1
        elif(direction == "south"):
            front_dim, exp_dim, exp_dir = "x" , "y", 1
        elif(direction == "east"):
            front_dim, exp_dim, exp_dir = "y" , "x", 1
        elif(direction == "west"):
            front_dim, exp_dim, exp_dir = "y" , "x", -1

        front_dim_min = front_dim + "_min"
        front_dim_max = front_dim + "_max"

        exp_dim_min = exp_dim + "_min"
        exp_dim_max = exp_dim + "_max"

        front_min = pblock[front_dim_min]
        front_max = pblock[front_dim_max]

        front_exp_coord = None
        if(direction == "south" or direction == "east"):
            front_exp_coord = pblock[exp_dim_max]
        else: 
            front_exp_coord = pblock[exp_dim_min]
        #######################################################################
        # then generate a list of potential hazards
        hazards =  [blk for blk in yaml_data["overlay"]["BFT"] if blk["name"] != parent["name"]]
        hazards += [blk for blk in yaml_data["overlay"]["static_blocks"]]
        hazards += [blk for blk in yaml_data["overlay"]["pblocks"]["pblocks"] if blk["name"] != pblock["name"]]
        #######################################################################
        # Now expand the front
        while(True):
            # check each hazard to see if it intersects with the front
            for hazard in hazards:
                # if we have a possible intersection because of the expansion coordinate data
                if(front_exp_coord >= hazard[exp_dim_min] and front_exp_coord <= hazard[exp_dim_max]):
                    # if the hazard completely blocks the front:
                    if(hazard[front_dim_min] <= front_min and hazard[front_dim_max] >= front_max):
                        print("Error: " + pblock["name"] + " has no clear path to " + parent["name"])
                        exit(1)
                    # if the hazard creates a split front (possible to solve, but not supported now)
                    elif(hazard[front_dim_min] > front_min and hazard[front_dim_max] < front_max):
                        print("Error: routing " + pblock["name"] + " to " + parent["name"] + "creates split front")
                        exit(1)
                    # if the hazard blocks the min side of the front
                    elif(hazard[front_dim_min] <= front_min and hazard[front_dim_max] > front_min):
                        # adjust the front if possible
                        front_min = hazard[front_dim_max] + 2
                        if(front_min >= front_max):
                            print("Error: " + pblock["name"] + " has no clear path to " + parent["name"])
                            exit(1)
                    # if hazard blocks the max side of the front
                    elif(hazard[front_dim_max] >= front_max and hazard[front_dim_min] < front_max):
                        # adjust the front if possible
                        front_max = hazard[front_dim_min] - 2
                        if(front_max <= front_min):
                            print("Error: " + pblock["name"] + " has no clear path to " + parent["name"])
                            exit(1)
            # if we're here, the currently the front does not intersect with a hazard
            # so we check to see if it has intersected with the target
            if(front_exp_coord >= parent[exp_dim_min] and front_exp_coord <= parent[exp_dim_max]):
                print("Reached target! front: " + str(front_min) + " " + str(front_max))
                break
            # otherwise we expand the front
            front_exp_coord += exp_dir
        synth_tiles_range = {
            "GRID_" + exp_dim_max.upper(): pblock[exp_dim_max],
            "GRID_" + exp_dim_min.upper(): pblock[exp_dim_min],
            "GRID_" + front_dim_max.upper(): front_max,
            "GRID_" + front_dim_min.upper(): front_min,
        }
        return synth_tiles_range
    ###########################################################################
    # Next we figure out which side of the pblock to assign the ports to
    side = None
    synth_tiles_range = None
    # If the parent's x-range overlaps with the pblock's x-range
    if(parent["x_min"] <= pblock["x_max"] and parent["x_max"] >= pblock["x_min"]):
        if(pblock["y_min"] > parent["y_max"]):
            side = "north"
            synth_tiles_range = get_synth_tiles(side,pblock,parent,yaml_data)
        elif(pblock["y_max"] < parent["y_min"]):
            side = "south"
            synth_tiles_range = get_synth_tiles(side,pblock,parent,yaml_data)

    # Else if the parent's y-range overlaps with the pblock's y-range
    elif(parent["y_min"] <= pblock["y_max"] and parent["y_max"] >= pblock["y_min"]):
        if(pblock["x_max"] < parent["x_min"]):
            side = "east"
            synth_tiles_range = get_synth_tiles(side,pblock,parent,yaml_data)
        elif(pblock["x_min"] > parent["x_max"]):
            side = "west"
            synth_tiles_range = get_synth_tiles(side,pblock,parent,yaml_data)
        else:
            print("Error: pblock intersects with parent switchbox!")
            exit(1)
    # Else if there is no overlap
    else:
        print("Warning: " + pblock["name"] + " has no direct path to " + parent["name"])

    for port in pblock_ports:
        port["side"] = side

    # We now create an interface list, and put it into the definition_dict
    interface_list = pblock_clocks + pblock_ports
    definition_dict["ports"] = interface_list

    definition_dict["synth_tiles_range"] = synth_tiles_range

    # Finally we add our new definition to the definitions list
    definitions.append(definition_dict)
###############################################################################
# Now we can print the json definitions for each pblock:
print()
for definition in definitions:
    print(json.dumps(definition,indent=1))
    print()
###############################################################################
# This function plots a single rectangle 
def plot_rect(axis, x_min, x_max, y_min, y_max, color, fill=False):
    rect = patches.Rectangle((x_min,y_min),
                              x_max - x_min,
                              y_max - y_min,
                              fill = fill,
                              color = color,
                              linewidth = 1)
    axis.add_patch(rect)
    return rect
###############################################################################
# This function plots a set of labeled rectangles, given
# a list of objects from the yaml file
def plot_rects(axis, lst, color, label_color="black"):
    for element in lst:
        rect = plot_rect(axis,element["x_min"],element["x_max"],
                              element["y_min"],element["y_max"],
                              color = color,
                              fill=True)

        axis.add_patch(rect)
        # find the center of the rectangle
        rx, ry = rect.get_xy()
        cx = rx + (rect.get_width()/2.0)
        cy = ry + (rect.get_height()/2.0)

        # Label the switchbox rectangle
        ax.annotate(element["name"], (cx, cy),
                    color = label_color,
                    fontsize = 6,
                    fontfamily = "sans-serif",
                    ha = "center",
                    va = "center")
###############################################################################
# Now we can plot our results

# First we setup the plot
ax = plt.gca()
plt.xlim([-10, yaml_data["overlay"]["max_x_dimension"] + 10])
plt.ylim([-10, yaml_data["overlay"]["max_y_dimension"] + 10])
plt.gca().invert_yaxis()
ax.set_aspect('equal')
plt.title(yaml_data["overlay"]["name"])
plt.xlabel("Part: " + yaml_data["overlay"]["part"])

# Now we plot the BFT, static blocks, and pblocks
plot_rects(ax, yaml_data["overlay"]["BFT"], "darkred")
plot_rects(ax, yaml_data["overlay"]["static_blocks"], "darkgoldenrod")
plot_rects(ax, yaml_data["overlay"]["pblocks"]["pblocks"], "teal")

# Finally we plot an outline of the chip
plot_rect(ax, 0, yaml_data["overlay"]["max_x_dimension"],
              0, yaml_data["overlay"]["max_y_dimension"],
              color = "black")

plt.show()
###############################################################################