import os
import subprocess
from gen_basic import gen_basic


class mbft(gen_basic):

    # modify the project_syn2gen
    # replace the empty pages with real pages
    def return_syn2gen_tcl_list_local(self):
        print("input_src/" + self.prflow_params["benchmark_name"] + "/operators")
        file_list = self.shell.get_file_name(
            "input_src/" + self.prflow_params["benchmark_name"] + "/operators"
        )
        header_file_list = filter(lambda x: x.replace(".h", "") != x, file_list)
        operator_list = [(i.replace(".h", "")) for i in header_file_list]
        # map of reset source for each pages
        # distributed resetting is good for timing
        net_list = self.net_list
        lines_list = []
        lines_list.append(
            "set_property  ip_repo_paths  {./ip_repo ./dirc_ip} [current_project]\n"
        )
        lines_list.append("update_ip_catalog\n")
        # remove empty ip, add real IP and connect the wires
        for fun_name in operator_list:
            HW, page_num = self.pragma.return_pragma(
                "./input_src/"
                + self.prflow_params["benchmark_name"]
                + "/operators/"
                + fun_name
                + ".h",
                "page_num",
            )
            lines_list.append(
                self.tcl.return_create_bd_cell_tcl_str(
                    "user.org:user:leaf_" + page_num + ":1.0", "leaf" + page_num
                )
            )
            lines_list.append(
                self.tcl.return_delete_bd_objs_tcl_str("leaf_empty_" + page_num)
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/clk_bft", "/zynq_ultra_ps_e_0/pl_clk1"
                )
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/clk_user", "/zynq_ultra_ps_e_0/pl_clk0"
                )
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/ap_start",
                    "bft" + str(int(page_num) / 8) + "/ap_start",
                )
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/reset_bft",
                    "bft" + str(int(page_num) / 8) + "/bft_reset",
                )
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/reset", "bft0/user_reset"
                )
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/dout_leaf_interface2bft",
                    "bft"
                    + str(int(page_num) / 8)
                    + "/leaf_"
                    + str(int(page_num) & 7)
                    + "_in",
                )
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/din_leaf_bft2interface",
                    "bft"
                    + str(int(page_num) / 8)
                    + "/leaf_"
                    + str(int(page_num) & 7)
                    + "_out",
                )
            )
            lines_list.append(
                self.tcl.return_connect_bd_net_tcl_str(
                    "leaf" + page_num + "/resend",
                    "bft"
                    + str(int(page_num) / 8)
                    + "/resend_"
                    + str(int(page_num) & 7),
                )
            )

        return lines_list

    # main.sh will be used for local compilation
    def return_main_sh_list_local(self):
        lines_list = []
        lines_list.append("#!/bin/bash -e")
        lines_list.append("source " + self.prflow_params["Xilinx_dir"])
        lines_list.append("vivado -mode batch -source project_syn2gen.tcl")
        lines_list.append("vivado -mode batch -source project_syn2bits.tcl")
        return lines_list

    # qsub_main.sh will be used for qsub compilation
    def return_qsub_main_sh_list_local(self):
        # go through all the files and qsub the ip compilation tasks
        lines_list = self.shell.return_qsub_scan_sh_list("./ip_repo")
        hold_jid = "$file_list"

        # after the ip compilation is done, we can construct the vivado momo bft project
        lines_list.append(
            self.shell.return_qsub_command_str(
                "./qsub_project_syn2gen.sh", hold_jid, "bft_mono_syn2gen"
            )
        )

        # we can accelerate the synthesis by compile each out-of-context modules in parallel
        lines_list.append(
            self.shell.return_qsub_command_str(
                "./qsub_sub_syn.sh", "bft_mono_syn2gen", "bft_mono_sub_syn"
            )
        )
        return lines_list

    # qsub_sub_syn.sh will go through all the out-of-context module directories and qsub each
    # task by executing thn runme.sh, which is generated by vivado
    def return_sub_syn_sh_list_local(self):
        lines_list = self.shell.return_qsub_scan_sh_list(
            "./prj/floorplan_static.runs", "runme.sh"
        )
        hold_jid = "$file_list"

        # after all the out-of-context compilations are done, we reopen the project and compile it to bits.
        lines_list.append(
            self.shell.return_qsub_command_str(
                "./qsub_project_syn2bits.sh", hold_jid, "bft_mono_syn2bits"
            )
        )

        # after the vivado project is implemented to bitstreams, we make an SDK project
        lines_list.append(
            self.shell.return_qsub_command_str(
                "./qsub_project_xsdk.sh", "bft_mono_syn2bits", "bft_mono_sdk"
            )
        )

        return lines_list

    def return_run_sdk_sh_list_local(self, vivado_dir, tcl_file):
        return [
            "#!/bin/bash -e",
            "source " + vivado_dir,
            "xsdk -batch -source " + tcl_file,
            "",
        ]

    # create ip directory for each page
    def create_ip(self):
        self.shell.re_mkdir(self.mono_bft_dir + "/ip_repo")
        for fun_num, fun_name in enumerate(self.prflow_params["syn_fun_list"]):
            if fun_name != "user_kernel":
                page_num = self.prflow_params["page_list"][fun_num].replace(
                    "Function", ""
                )
                input_num = self.prflow_params["input_num_list"][fun_num]
                output_num = self.prflow_params["output_num_list"][fun_num]
                num_bram_addr_bits = int(self.prflow_params["bram_addr_bits"])
                self.shell.re_mkdir(self.mono_bft_dir + "/ip_repo/" + fun_name)
                file_list = [
                    "../../src/Config_Controls.v",
                    "../../src/converge_ctrl.v",
                    "../../src/ExtractCtrl.v",
                    "../../src/Input_Port_Cluster.v",
                    "../../src/Input_Port.v",
                    "../../src/leaf_interface.v",
                    "../../src/Output_Port_Cluster.v",
                    "../../src/Output_Port.v",
                    "../../src/read_b_in.v",
                    "../../src/Stream_Flow_Control.v",
                    "../../src/write_b_in.v",
                    "../../src/write_b_out.v",
                    "../../src/instr_config.v",
                    "../../src/rise_detect.v",
                    "../../src/user_kernel.v",
                ]
                print("=========================================")
                self.shell.write_lines(
                    self.mono_bft_dir + "/ip_repo/" + fun_name + "/ip_page.tcl",
                    self.tcl.return_ip_page_tcl_list(fun_name, page_num, file_list),
                )
                self.shell.write_lines(
                    self.mono_bft_dir + "/ip_repo/" + fun_name + "/run.sh",
                    self.shell.return_run_sh_list(
                        self.prflow_params["Xilinx_dir"], "ip_page.tcl"
                    ),
                    True,
                )
                self.shell.write_lines(
                    self.mono_bft_dir + "/ip_repo/" + fun_name + "/qsub_run.sh",
                    self.shell.return_run_sh_list(
                        self.prflow_params["Xilinx_dir"], "ip_page.tcl"
                    ),
                    True,
                )
                self.shell.write_lines(
                    self.mono_bft_dir
                    + "/ip_repo/"
                    + fun_name
                    + "/leaf_"
                    + str(page_num)
                    + ".v",
                    self.verilog.return_page_v_list(
                        page_num, fun_name, input_num, output_num
                    ),
                    True,
                )

    def create_shell_file(self):
        # local run:
        #   main.sh <- |_ execute each run.sh <- ip_page.tcl
        #              |_ vivado project_syn2gen.tcl
        #              |_ vivado project_syn2bits.tcl
        #
        # qsub run:
        #   qsub_main.sh <-|_ Qsubmit each qsub_run.sh <- ip_page.tcl
        #                  |_ qsub_project_syn2gen.sh <- project_syn2gen.tcl
        #                  |_ qsub_sub_syn.sh <-|_ go through very synthesis directies and Qsubmmit jobs <- runme.sh
        #                                       |_ qsub_project_syn2bits.sh <- project_syn2bits.tcl
        #                                       |_ qsub_project_sdk <- project_xsdk_dma.tcl

        self.shell.cp_dir(
            self.overlay_dir + "/project_syn2gen.tcl",
            self.mono_bft_dir + "/project_syn2gen.tcl",
        )
        self.shell.add_lines(
            self.mono_bft_dir + "/project_syn2gen.tcl",
            "# Create address segments",
            self.return_syn2gen_tcl_list_local(),
        )
        self.shell.write_lines(
            self.mono_bft_dir + "/project_syn2bits.tcl",
            self.tcl.return_syn2bits_tcl_list(self.prflow_params["maxJobs"]),
            False,
        )
        replace_dict = {
            "set Benchmark_name": "set Benchmark_name "
            + self.prflow_params["benchmark_name"]
        }
        self.shell.replace_lines(
            self.mono_bft_dir + "/project_xsdk_core.tcl", replace_dict
        )
        self.shell.write_lines(
            self.mono_bft_dir + "/main.sh", self.return_main_sh_list_local(), True
        )
        self.shell.write_lines(
            self.mono_bft_dir + "/qsub_main.sh",
            self.return_qsub_main_sh_list_local(),
            True,
        )
        self.shell.write_lines(
            self.mono_bft_dir + "/qsub_project_syn2gen.sh",
            self.shell.return_run_sh_list(
                self.prflow_params["Xilinx_dir"], "project_syn2gen.tcl"
            ),
            True,
        )
        self.shell.write_lines(
            self.mono_bft_dir + "/qsub_sub_syn.sh",
            self.return_sub_syn_sh_list_local(),
            True,
        )
        self.shell.write_lines(
            self.mono_bft_dir + "/qsub_project_syn2bits.sh",
            self.shell.return_run_sh_list(
                self.prflow_params["Xilinx_dir"], "project_syn2bits.tcl"
            ),
            True,
        )
        self.shell.write_lines(
            self.mono_bft_dir + "/qsub_project_xsdk.sh",
            self.return_run_sdk_sh_list_local(
                self.prflow_params["Xilinx_dir"], "project_xsdk_core.tcl"
            ),
            True,
        )

    def uncomment_page_empty(self):
        modification_dict = {"/*": "", "*/": ""}

        self.shell.replace_lines(
            self.mono_bft_dir + "/src/leaf_empty.v", modification_dict
        )

    def run(self):
        # mk work directory
        os.system("rm -rf " + self.mono_bft_dir + "/prj")
        self.shell.mkdir(self.mono_bft_dir)

        # copy the hld/xdc files from static dirctory
        self.shell.cp_dir(self.overlay_dir + "/src ", self.mono_bft_dir)

        # copy the hld/xdc files from static dirctory
        self.shell.cp_dir(self.overlay_dir + "/dirc_ip ", self.mono_bft_dir)

        # copy the xsdk tcl to local directory
        self.shell.cp_dir(
            "./common/script_src/project_xsdk_core.tcl ", self.mono_bft_dir
        )

        # enable the logic inside paage, so that vivado can
        # implement it
        self.uncomment_page_empty()

        # clear up the xdc file
        self.shell.write_lines(self.mono_bft_dir + "/src/pblocks_32.xdc", [""])

        # generate shell files for qsub run and local run
        self.create_shell_file()

        # create ip directories for all the pages
        # self.create_ip()

        # go to the local mono_bft directory and run the qsub command
        # os.chdir(self.mono_bft_dir)
        # if self.prflow_params['run_qsub']:
        #  os.system('./qsub_main.sh')
        # os.chdir('../../')
