set page_num [lindex $argv 0]
set operator [lindex $argv 1]
set benchmark [lindex $argv 2]
set bit_name "../../F005_bits_${benchmark}/${operator}.bit"
set place_dcp "./page${page_num}_design_place.dcp"
set route_dcp "./page${page_num}_design_route.dcp"
set logFileId [open ./runLogImpl_${operator}.log "w"]
set_param general.maxThreads 8 

#####################
## read_checkpoint ##
#####################

set start_time [clock seconds]
open_checkpoint ../../F001_overlay/overlay.dcp
update_design -cell floorplan_static_i/leaf_empty_$page_num/inst -black_box
read_checkpoint -cell floorplan_static_i/leaf_empty_$page_num/inst ../../F003_syn_$benchmark/$operator/page_netlist.dcp
set end_time [clock seconds]
set total_seconds [expr $end_time - $start_time]
puts $logFileId "read_checkpoint: $total_seconds seconds"


# opt design
set start_time [clock seconds]
reset_timing
opt_design
set end_time [clock seconds]
set total_seconds [expr $end_time - $start_time]
puts $logFileId "opt: $total_seconds seconds"

# place design
set start_time [clock seconds]
place_design 
set end_time [clock seconds]
set total_seconds [expr $end_time - $start_time]
puts $logFileId "place: $total_seconds seconds"
write_checkpoint -force $place_dcp

# route design
set start_time [clock seconds]
route_design
set end_time [clock seconds]
set total_seconds [expr $end_time - $start_time]
puts $logFileId "route: $total_seconds seconds"
write_checkpoint -force $route_dcp

# generate bistream
set start_time [clock seconds]
set_param bitstream.enablePR 2341
write_bitstream -force -cell floorplan_static_i/leaf_empty_$page_num/inst $bit_name
set end_time [clock seconds]
set total_seconds [expr $end_time - $start_time]
puts $logFileId "bitgen: $total_seconds seconds"
report_timing_summary > timing_page${page_num}.rpt

