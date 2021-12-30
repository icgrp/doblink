# -*- coding: utf-8 -*-
# Company: IC group, University of Pennsylvania
# Engineer: Yuanlong Xiao
#
# Create Date: 02/23/2021
# Design Name: overlay
# Project Name: DIRC
# Versions: 1.0
# Description: This is a python script to prepare the script for static region
#              compile for PRflow.
# Dependencies: python2, gen_basic
# Revision:
# Revision 0.01 - File Created
#
# Additional Comments:


import os
import subprocess

from gen_basic import gen_basic


class overlay(gen_basic):
    def __init__(self, prflow_params):
        gen_basic.__init__(self, prflow_params)

    # create dummy directory for each empty block
    def create_place_holder(self):
        fun_name = "user_kernel"
        self.shell.mkdir(self.overlay_dir + "/dummy_repo")
        self.shell.mkdir(self.overlay_dir + "/dummy_repo/" + fun_name)
        file_list = [
            "../../src/Config_Controls.v",
            "../../src/converge_ctrl.v",
            "../../src/ExtractCtrl.v",
            "../../src/Input_Port_Cluster.v",
            "../../src/Input_Port.v",
            "../../src/InterfaceWrapper.v",
            "../../src/leaf_interface.v",
            "../../src/Output_Port_Cluster.v",
            "../../src/Output_Port.v",
            "../../src/ram0.v",
            "../../src/read_b_in.v",
            "../../src/single_ram.v",
            "../../src/Stream_Flow_Control.v",
            "../../src/SynFIFO.v",
            "../../src/user_kernel.v",
            "../../src/user_kernel_regslice_both.v",
            "../../src/write_b_in.v",
            "../../src/write_b_out.v",
            "./leaf.v",
        ]
        self.shell.write_lines(
            self.overlay_dir + "/dummy_repo/" + fun_name + "/dummy.tcl",
            self.tcl.return_syn_page_tcl_list(fun_name, file_list),
        )
        self.shell.write_lines(
            self.overlay_dir + "/dummy_repo/" + fun_name + "/run.sh",
            self.shell.return_run_sh_list(
                self.prflow_params["Xilinx_dir"],
                "dummy.tcl",
                self.prflow_params["back_end"],
            ),
            True,
        )
        self.shell.write_lines(
            self.overlay_dir + "/dummy_repo/" + fun_name + "/" + "leaf.v",
            self.verilog.return_page_v_list(0, fun_name, 1, 1, True),
        )

    # main.sh will be used for local compilation
    def return_main_sh_list_local(self):
        lines_list = []
        lines_list.append("#!/bin/bash -e")
        # if(self.prflow_params['back_end'] == 'slurm'):
        #   lines_list.append('module load '+self.prflow_params['Xilinx_dir'])
        # else:
        lines_list.append("source " + self.prflow_params["Xilinx_dir"])

        lines_list.append("cd ./dummy_repo/user_kernel")
        lines_list.append("./run.sh&")
        lines_list.append("cd -")
        lines_list.append("vivado -mode batch -source project_syn2gen.tcl")
        lines_list.append("vivado -mode batch -source project_syn2dcp.tcl")
        lines_list.append("vivado -mode batch -source mk_overlay.tcl")
        return lines_list

    def create_tcl_shell_file(self):
        # local run:
        #   main.sh <- |_ vivado each dummy.tcl
        #              |_ vivado project_syn2gen.tcl
        #              |_ vivado project_syn2dcp.tcl
        #              |_ vivado mk_overlay.tcl

        # we use existed files instead
        # generating tcl file to create the overlay region vivado project
        self.shell.cp_dir(
            "./common/script_src/project_syn_gen_"
            + self.prflow_params["board"]
            + ".tcl ",
            self.overlay_dir + "/project_syn2gen.tcl",
        )

        self.shell.write_lines(
            self.overlay_dir + "/project_syn2dcp.tcl",
            self.tcl.return_syn2dcp_tcl_list(self.prflow_params["back_end"]),
            False,
        )
        self.shell.write_lines(
            self.overlay_dir + "/mk_overlay.tcl",
            self.tcl.return_mk_overlay_tcl_list(),
            False,
        )
        self.shell.write_lines(
            self.overlay_dir + "/run.sh", self.return_main_sh_list_local(), True
        )
        self.shell.write_lines(
            self.overlay_dir + "/main.sh",
            self.shell.return_main_sh_list(
                "./run.sh",
                self.prflow_params["back_end"],
                "NONE",
                "overlay",
                self.prflow_params["grid"],
                self.prflow_params["email"],
                self.prflow_params["mem"],
                "8",
            ),
            True,
        )
        # self.prflow_params['node']), True)

    def run(self):
        # make work directory
        self.shell.mkdir(self.prflow_params["workspace"])
        self.shell.re_mkdir(self.overlay_dir)

        # copy the hld/xdc files from input source directory
        self.shell.cp_dir("./do_blink/vivado_benchmark/overlay/top/", self.overlay_dir + "/src")
        self.shell.cp_dir("./do_blink/vivado_benchmark/overlay/leaf_interface/*", self.overlay_dir + "/src")


        # copy the verilog file for the BFT from bft generate directory
        # self.shell.cp_file('./workspace/F000_bft_gen/gen_nw_vivado.v', self.overlay_dir+'/src')

        # create a bft wrapper
        # self.shell.write_lines(self.overlay_dir+'/src/bft.v', self.verilog.return_bft_wrapper_v_list(int(self.prflow_params['nl']), int(self.prflow_params['addr_bits']), int(self.prflow_params['packet_bits'])))

        # generate tcl and shell files for local run
        self.create_tcl_shell_file()

        # create dummy logic place and route the overlay.dcp
        self.create_place_holder()
