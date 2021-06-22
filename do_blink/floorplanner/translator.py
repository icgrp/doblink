import yaml
import json
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import copy
###############################################################################
# Read the yaml file
yaml_data = None
with open("draft.yaml", 'r') as yaml_file:
    try:
        yaml_data = yaml.safe_load(yaml_file)

    except yaml.YAMLError as exc:
        print(exc)

###############################################################################
# First we get the interface information which is common to all pblocks

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
    ###########################################################################
    # Now we make a deep copy of the list of ports
    pblock_ports = copy.deepcopy(ports)

    # We now create an interface list, and put it into the definition_dict
    interface_list = pblock_clocks + pblock_ports
    definition_dict["ports"] = interface_list

    # We then add our new definition to the definitions list
    definitions.append(definition_dict)
###############################################################################
# Now we can print the json definitions for each pblock:
for definition in definitions:
    print(json.dumps(definition,indent=1))
    print()
###############################################################################
# Plot the pblocks:

# Setup the plot
ax = plt.gca()
plt.xlim([-10, yaml_data["overlay"]["max_x_dimension"] + 10])
plt.ylim([-10, yaml_data["overlay"]["max_y_dimension"] + 10])
plt.gca().invert_yaxis()
ax.set_aspect('equal')
plt.title(yaml_data["overlay"]["name"])
plt.xlabel("Part: " + yaml_data["overlay"]["part"])

# Create the pblock rectangles
for pblock in yaml_data["overlay"]["pblocks"]["pblocks"]:
    rect = patches.Rectangle((pblock["x_min"],pblock["y_min"]),
                              pblock["x_max"] - pblock["x_min"],
                              pblock["y_max"] - pblock["y_min"],
                              fill = False,
                              color = "blue",
                              linewidth = 1)

    # Add pblock rectangle to the plot
    ax.add_patch(rect)

    # Find the center of the pblock rectangle
    rx, ry = rect.get_xy()
    cx = rx + (rect.get_width()/2.0)
    cy = ry + (rect.get_height()/2.0)

    # Lable the pblock rectangle
    ax.annotate(pblock["name"], (cx, cy),
                color = "black",
                fontsize = 6,
                fontfamily = "sans-serif",
                ha = "center",
                va = "center")

# Create a rectangle for the chip's perimeter
rect = patches.Rectangle((0,0),
                          yaml_data["overlay"]["max_x_dimension"],
                          yaml_data["overlay"]["max_y_dimension"],
                          fill = False,
                          color = "red",
                          linewidth = 1)

# Add the perimeter rectangle to the plot
ax.add_patch(rect)

# Display the plot
plt.show()
###############################################################################