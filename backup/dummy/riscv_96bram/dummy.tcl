add_files -norecurse ../../src/Config_Controls.v
add_files -norecurse ../../src/converge_ctrl.v
add_files -norecurse ../../src/ExtractCtrl.v
add_files -norecurse ../../src/Input_Port_Cluster.v
add_files -norecurse ../../src/Input_Port.v
add_files -norecurse ../../src/leaf_interface.v
add_files -norecurse ../../src/Output_Port_Cluster.v
add_files -norecurse ../../src/Output_Port.v
add_files -norecurse ../../src/read_b_in.v
add_files -norecurse ../../src/Stream_Flow_Control.v
add_files -norecurse ../../src/write_b_in.v
add_files -norecurse ../../src/rise_detect.v
add_files -norecurse ../../src/instr_config.v
add_files -norecurse ../../src/write_b_out.v
add_files -norecurse ../../src/user_kernel.v
set dir "./src/"
set contents [glob -nocomplain -directory $dir *]
foreach item $contents {
  if { [regexp {.*\.tcl} $item] } {
    source $item
  } else {
    add_files -norecurse $item
  }
}
set dir "../../F002_hls_rendering/user_kernel_prj/user_kernel/syn/verilog"
set contents [glob -nocomplain -directory $dir *]
foreach item $contents {
  if { [regexp {.*\.tcl} $item] } {
    source $item
  } else {
    add_files -norecurse $item
  }
}
set_param general.maxThreads  8
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY XPM_FIFO} [current_project]
set logFileId [open ./runLog_user_kernel.log "w"]
set start_time [clock seconds]
set_param general.maxThreads  8 
synth_design -top leaf -part xczu9eg-ffvb1156-2-e -mode out_of_context
write_checkpoint -force page_netlist.dcp
set end_time [clock seconds]
set total_seconds [expr $end_time - $start_time]
puts $logFileId "syn: $total_seconds seconds"
report_utilization -hierarchical > utilization.rpt

