proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    } elseif { [info exist ::env(HOST)] } {
      set host $::env(HOST)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}



set part xcu50-fsvh2104-2-e
create_project -in_memory -part $part
add_files ./checkpoint/hw_bb_divided.dcp
add_files ./checkpoint/page.dcp

# set_property SCOPED_TO_CELLS { level0_i/ulp/ydma_1/inst/page2_inst level0_i/ulp/ydma_1/inst/page3_inst level0_i/ulp/ydma_1/inst/page4_inst level0_i/ulp/ydma_1/inst/page5_inst level0_i/ulp/ydma_1/inst/page6_inst level0_i/ulp/ydma_1/inst/page7_inst level0_i/ulp/ydma_1/inst/page8_inst level0_i/ulp/ydma_1/inst/page9_inst level0_i/ulp/ydma_1/inst/page10_inst level0_i/ulp/ydma_1/inst/page11_inst level0_i/ulp/ydma_1/inst/page12_inst level0_i/ulp/ydma_1/inst/page13_inst level0_i/ulp/ydma_1/inst/page14_inst level0_i/ulp/ydma_1/inst/page15_inst level0_i/ulp/ydma_1/inst/page16_inst } [get_files /home/ylxiao/ws_202/rosetta_vitis/ydma/hw_dfx_manual/checkpoint/page.dcp]
set_property SCOPED_TO_CELLS { level0_i/ulp/ydma_1/inst/page2_inst level0_i/ulp/ydma_1/inst/page3_inst level0_i/ulp/ydma_1/inst/page4_inst level0_i/ulp/ydma_1/inst/page5_inst level0_i/ulp/ydma_1/inst/page6_inst level0_i/ulp/ydma_1/inst/page7_inst level0_i/ulp/ydma_1/inst/page8_inst level0_i/ulp/ydma_1/inst/page9_inst level0_i/ulp/ydma_1/inst/page10_inst level0_i/ulp/ydma_1/inst/page11_inst level0_i/ulp/ydma_1/inst/page12_inst level0_i/ulp/ydma_1/inst/page13_inst level0_i/ulp/ydma_1/inst/page14_inst level0_i/ulp/ydma_1/inst/page15_inst level0_i/ulp/ydma_1/inst/page16_inst level0_i/ulp/ydma_1/inst/page17_inst level0_i/ulp/ydma_1/inst/page18_inst  level0_i/ulp/ydma_1/inst/page19_inst level0_i/ulp/ydma_1/inst/page20_inst level0_i/ulp/ydma_1/inst/page21_inst level0_i/ulp/ydma_1/inst/page22_inst level0_i/ulp/ydma_1/inst/page23_inst level0_i/ulp/ydma_1/inst/page24_inst level0_i/ulp/ydma_1/inst/page25_inst level0_i/ulp/ydma_1/inst/page26_inst level0_i/ulp/ydma_1/inst/page27_inst } [get_files ./checkpoint/page.dcp]

add_files ./xdc/sub.xdc
set_property USED_IN {implementation} [get_files ./xdc/sub.xdc]
set_property PROCESSING_ORDER LATE [get_files ./xdc/sub.xdc]
read_xdc ./xdc/impl.xdc
read_xdc ./xdc/dont_partition.xdc
read_xdc -mode out_of_context -cells level0_i/ulp ./xdc//ulp_ooc_copy.xdc
set_property processing_order LATE [get_files ./xdc/ulp_ooc_copy.xdc]



start_step init_design
set ACTIVE_STEP init_design
puts "source ./scripts/_full_init_pre.tcl"
source ./scripts/_full_init_pre.tcl
set_param project.enablePRFlowIPI 1
set_param bd.debug_profile.script ./scripts/debug_profile_automation.tcl
set_param bd.hooks.addr.debug_scoped_use_ms_name 1
set_param ips.enableSLRParameter 2
set_param hd.Visual 0
set_param bd.enable_dpa 1
set_param project.loadTopLevelOOCConstrs 1
set_param project.gatelevelSubdesign 1
set_param chipscope.maxJobs 1
set_param place.ultrathreadsUsed 0
set_param bd.skipSupportedIPCheck 1
set_param hd.enableClockTrackSelectionEnancement 1
set_param bd.ForceAppCoreUpgrade 1
set_param compiler.enablePerformanceTrace 1
set_property design_mode GateLvl [current_fileset]
set_param project.singleFileAddWarning.threshold 0
set_property webtalk.parent_dir ./prj/prj.cache/wt [current_project]
set_property tool_flow SDx [current_project]
set_property parent.project_path ./prj/prj.xpr [current_project]
# link_design -mode default -reconfig_partitions { level0_i/ulp/ydma_1/inst/page2_inst level0_i/ulp/ydma_1/inst/page3_inst level0_i/ulp/ydma_1/inst/page4_inst level0_i/ulp/ydma_1/inst/page5_inst level0_i/ulp/ydma_1/inst/page6_inst level0_i/ulp/ydma_1/inst/page7_inst level0_i/ulp/ydma_1/inst/page8_inst level0_i/ulp/ydma_1/inst/page9_inst level0_i/ulp/ydma_1/inst/page10_inst level0_i/ulp/ydma_1/inst/page11_inst level0_i/ulp/ydma_1/inst/page12_inst level0_i/ulp/ydma_1/inst/page13_inst level0_i/ulp/ydma_1/inst/page14_inst level0_i/ulp/ydma_1/inst/page15_inst level0_i/ulp/ydma_1/inst/page16_inst } -part $part -top level0_wrapper
link_design -mode default -reconfig_partitions { level0_i/ulp/ydma_1/inst/page2_inst level0_i/ulp/ydma_1/inst/page3_inst level0_i/ulp/ydma_1/inst/page4_inst level0_i/ulp/ydma_1/inst/page5_inst level0_i/ulp/ydma_1/inst/page6_inst level0_i/ulp/ydma_1/inst/page7_inst level0_i/ulp/ydma_1/inst/page8_inst level0_i/ulp/ydma_1/inst/page9_inst level0_i/ulp/ydma_1/inst/page10_inst level0_i/ulp/ydma_1/inst/page11_inst level0_i/ulp/ydma_1/inst/page12_inst level0_i/ulp/ydma_1/inst/page13_inst level0_i/ulp/ydma_1/inst/page14_inst level0_i/ulp/ydma_1/inst/page15_inst level0_i/ulp/ydma_1/inst/page16_inst level0_i/ulp/ydma_1/inst/page17_inst level0_i/ulp/ydma_1/inst/page18_inst level0_i/ulp/ydma_1/inst/page19_inst level0_i/ulp/ydma_1/inst/page20_inst level0_i/ulp/ydma_1/inst/page21_inst level0_i/ulp/ydma_1/inst/page22_inst level0_i/ulp/ydma_1/inst/page23_inst level0_i/ulp/ydma_1/inst/page24_inst level0_i/ulp/ydma_1/inst/page25_inst level0_i/ulp/ydma_1/inst/page26_inst level0_i/ulp/ydma_1/inst/page27_inst } -part $part -top level0_wrapper
puts "source ./scripts/_full_init_post.tcl"
source ./scripts/_full_init_post.tcl

start_step opt_design
set ACTIVE_STEP opt_design
puts "source ./scripts/_full_opt_pre.tcl"
source ./scripts/_full_opt_pre.tcl
opt_design 
puts "source ./scripts/_full_opt_post.tcl"
source ./scripts/_full_opt_post.tcl
end_step opt_design
unset ACTIVE_STEP 


start_step place_design
set ACTIVE_STEP place_design
puts "source ./scripts/_full_place_pre.tcl"
source ./scripts/_full_place_pre.tcl
implement_debug_core 
place_design 
puts "source ./scripts/_full_place_post.tcl"
source ./scripts/_full_place_post.tcl
end_step place_design
unset ACTIVE_STEP 
write_checkpoint -force design_place.dcp

start_step phys_opt_design
set ACTIVE_STEP phys_opt_design
phys_opt_design 
end_step phys_opt_design
unset ACTIVE_STEP 


start_step route_design
set ACTIVE_STEP route_design
route_design 
write_checkpoint -force level0_wrapper_routed.dcp
end_step route_desing
unset ACTIVE_STEP 
write_checkpoint -force design_route.dcp


update_design -black_box -cell level0_i/ulp/ydma_1/inst/page2_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page3_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page4_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page5_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page6_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page7_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page8_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page9_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page10_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page11_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page12_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page13_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page14_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page15_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page16_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page17_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page18_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page19_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page20_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page21_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page22_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page23_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page24_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page25_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page26_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page27_inst

lock_design -level routing
write_checkpoint -force ./overlay.dcp
close_project


create_project -in_memory -part $part
open_checkpoint level0_wrapper_routed.dcp
pr_recombine -cell level0_i/ulp
write_bitstream -force -cell level0_i/ulp ./dynamic_region.bit
close_project





create_project -in_memory -part $part
open_checkpoint level0_wrapper_routed.dcp
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page2_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page3_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page4_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page5_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page6_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page7_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page8_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page9_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page10_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page11_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page12_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page13_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page14_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page15_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page16_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page17_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page18_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page19_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page20_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page21_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page22_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page23_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page24_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page25_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page26_inst
update_design -black_box -cell level0_i/ulp/ydma_1/inst/page27_inst

update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page2_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page3_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page4_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page5_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page6_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page7_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page8_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page9_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page10_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page11_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page12_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page13_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page14_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page15_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page16_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page17_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page18_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page19_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page20_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page21_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page22_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page23_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page24_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page25_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page26_inst
update_design -buffer_ports -cell level0_i/ulp/ydma_1/inst/page27_inst

lock_design -level routing
write_checkpoint -force ./overlay_buffer.dcp

close_project









