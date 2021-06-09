package require struct::set

if { $argc != 2 } {
	puts "The gen_vpr_nodes.tcl script requires the path of big_static_routed.dcp and a boolean flag for specifying if to use vivado partition pins."
	puts "For example, vivado -mode batch -source ${DOBLINK_DIR}/do_blink/tcl/gen_vpr_nodes.tcl -tclargs ${DOBLINK_DIR}/do_blink/vivado_benchmark/fig2/F001_static_8_7020_1600/big_static_routed_8_48.dcp 1".
} else {
	open_checkpoint [lindex $argv 0]
}

set use_vivado_part_pins 0
if {[lindex $argv 1] == "1"} {
	set use_vivado_part_pins 1
}

# initialize output file
set file [open "definition.json" "w"]

# get all partition pins in the pblock
set part_pins [get_pins -of_objects [get_cells design_1_i/page_0/inst]]

# get min/max coordinates of the pblock (for checking if a node is inside the pblock or not)
set pblock_tiles [get_tiles -of_objects [get_sites -of_objects [get_pblocks pblock_1]]]
set pblock_tiles_x_max [tcl::mathfunc::max {*}[get_property GRID_POINT_X $pblock_tiles]]
set pblock_tiles_x_min [tcl::mathfunc::min {*}[get_property GRID_POINT_X $pblock_tiles]]
set pblock_tiles_y_max [tcl::mathfunc::max {*}[get_property GRID_POINT_Y $pblock_tiles]]
set pblock_tiles_y_min [tcl::mathfunc::min {*}[get_property GRID_POINT_Y $pblock_tiles]]

# start writing definition.json
puts $file "\{"
puts $file "    \"info\":"
puts $file "        \{"
puts $file "        \"name\": \"pr1\","
puts $file "        \"pins_per_tile\": 5,"
puts $file "        \"GRID_X_MAX\": $pblock_tiles_x_max,"
puts $file "        \"GRID_X_MIN\": $pblock_tiles_x_min,"
puts $file "        \"GRID_Y_MAX\": $pblock_tiles_y_max,"
puts $file "        \"GRID_Y_MIN\": $pblock_tiles_y_min"
puts $file "        \},"
puts $file "    \"ports\": \["

set pin_index -1
foreach pin $part_pins {
	incr pin_index
	set pin_name [lindex [split [get_property NAME [get_pins $pin]] "/"] end]
	set pin_type [get_property TYPE [get_nets -of_objects [get_pins $pin]]]
	set pin_direction [get_property DIRECTION [get_pins $pin]]

	# if nets are GROUND, skip them
	if {[string first "GROUND" $pin_type] != -1} {
		continue
	}

	if {[string first "CLOCK" $pin_type] != -1} {
		set definition_json_pin_type "clk"
	} else {
		if {$pin_direction == "IN"} {
			set definition_json_pin_type "in"
		} else {
			set definition_json_pin_type "out"
		}
	}

	puts $file "        \{"
	puts $file "            \"name\": \"$pin_name\","
	puts $file "            \"type\": \"$definition_json_pin_type\","
	puts $file "            \"data_type\": \"scalar\","
	puts $file "            \"side\": \"west\","

	# set resultant node for vpr as UNASSIGNED by default
	set vpr_node "UNASSIGNED"
	
	# if nets are clock, leave unassigned
	if {[string first "CLOCK" $pin_type] != -1} {
		#puts "Pin: $pin, VPR node: $vpr_node"
		puts $file "            \"node\": \"$vpr_node\""
		if {$pin_index < [expr [llength $part_pins] - 1]} {
			puts $file "        \},"
		} else {
			puts $file "        \}"
		} 
		continue
	} 

	# get the unordered list of nodes associated with the net
	set unordered_nodes [get_nodes -of_objects [get_nets -of_objects $pin]]

	# walk the nodes until we exit out of the pblock
	# start with where vivado assigned the node
	get_pplocs -nets [get_nets -of_objects $pin] -verbose > pplocs.txt
	exec grep -o "Found PartPin: .*" pplocs.txt | tail -1 | sed "s/.*: //" > pin_pploc.txt
	set fp [open "pin_pploc.txt" r]
	set pin_pploc [read $fp]
	close $fp
    set current_node [get_nodes $pin_pploc]

	# set boolean for tracking if walked outside of pblock
	set reached_outside 0

	while {$reached_outside != 1} {
		# get the tiles associated with the current_node
		set current_node_tiles [get_tiles -of_objects $current_node]

		foreach tile $current_node_tiles {
			# get the tile coordinates
			set tile_x [get_property GRID_POINT_X $tile]
			set tile_y [get_property GRID_POINT_Y $tile]
			set tile_name [get_property NAME [get_tiles $tile]]
			#puts $tile_name
			
			# if the coordinates of the current_node is not in the pblock grid
			# then the node is outside and so break.
			if {!($tile_x <= $pblock_tiles_x_max
				&& $tile_x >= $pblock_tiles_x_min
				&& $tile_y <= $pblock_tiles_y_max
				&& $tile_y >= $pblock_tiles_y_min)} {
				# TODO: need something more robust in the following check
				# filter BRKH tiles, they seem to be intermediate loop arounds
				if {[string first "BRKH" $tile_name] == -1} {
					set reached_outside 1
					if {$use_vivado_part_pins == 1} {
						set vpr_node $current_node
					}
					break
				}
			}
		}

		# get all the next nodes to the current_node
		# if the current_node is an input, then use -uphill
		# if it's an output, then use -downhill
		if {$pin_direction == "IN"} {
			set next_nodes [get_nodes -uphill -of_objects $current_node]
		} else {
			set next_nodes [get_nodes -downhill -of_objects $current_node]
		}
		
		# pick the first node from the next_nodes that exists in the unordered_nodes
		# and set it as current_node. Break if none found.
		set candidate_nodes [::struct::set intersect $unordered_nodes $next_nodes]	
		if {[llength $candidate_nodes] == 0} {
			break
		}
		set current_node [get_nodes [get_property NAME [lindex $candidate_nodes end]]]	
	}
	puts $vpr_node
	#puts "\n"
	puts $file "            \"node\": \"$vpr_node\""
	if {$pin_index < [expr [llength $part_pins] - 1]} {
		puts $file "        \},"
	} else {
		puts $file "        \}"
	} 
}

puts $file "    \]"
puts $file "\}"
close $file