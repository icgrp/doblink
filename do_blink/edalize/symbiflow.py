import logging
import os.path
import platform
import re
import subprocess

from edalize.edatool import *
from edalize.yosys import Yosys
from importlib import import_module
from jinja2 import Environment, PackageLoader

logger = logging.getLogger(__name__)


class Symbiflow(Edatool):

    argtypes = ["vlogdefine", "vlogparam", "generic"]

    def __init__(self, edam=None, work_root="./", eda_api=None, verbose=True):
        super(Symbiflow, self).__init__(edam, work_root, eda_api, verbose)
        self.jinja_env = Environment(
            loader=PackageLoader(__package__, "templates"),
            trim_blocks=True,
            lstrip_blocks=True,
            keep_trailing_newline=True,
        )

    @classmethod
    def get_doc(cls, api_ver):
        if api_ver == 0:
            symbiflow_help = {
                "members": [
                    {
                        "name": "package",
                        "type": "String",
                        "desc": "FPGA chip package (e.g. clg400-1)",
                    },
                    {
                        "name": "part",
                        "type": "String",
                        "desc": "FPGA part type (e.g. xc7a50t)",
                    },
                    {
                        "name": "vendor",
                        "type": "String",
                        "desc": 'Target architecture. Currently only "xilinx" is supported',
                    },
                    {
                        "name": "pnr",
                        "type": "String",
                        "desc": 'Place and Route tool. Currently only "vpr" is supported',
                    },
                    {
                        "name": "vpr_options",
                        "type": "String",
                        "desc": "Additional vpr tool options. If not used, default options for the tool will be used",
                    },
                    {
                        "name": "environment_script",
                        "type": "String",
                        "desc": "Optional bash script that will be sourced before each build step.",
                    },
                ]
            }

            symbiflow_members = symbiflow_help["members"]

            return {
                "description": "The Symbiflow backend executes Yosys sythesis tool and VPR place and route. It can target multiple different FPGA vendors",
                "members": symbiflow_members,
            }

    def get_version(self):
        return "1.0"

    def configure_vpr(self):
        (src_files, incdirs) = self._get_fileset_files(force_slash=True)

        has_vhdl = "vhdlSource" in [x.file_type for x in src_files]
        has_vhdl2008 = "vhdlSource-2008" in [x.file_type for x in src_files]

        if has_vhdl or has_vhdl2008:
            logger.error("VHDL files are not supported in Yosys")
        file_list = []
        user_files = []

        for f in src_files:
            if f.file_type in ["verilogSource"]:
                file_list.append(f.name)
            if f.file_type in ["user"]:
                user_files.append(f.name)

        doblink_source_dir = self.tool_options.get("doblink_source_dir", None)
        doblink_build_dir = self.tool_options.get("doblink_build_dir", None)
        figure = self.tool_options.get("figure", None)
        num_luts = self.tool_options.get("num_luts", None)
        arch = self.tool_options.get("arch", None)
        device_family = self.tool_options.get("device_family", None)
        device_name = self.tool_options.get("device_name", None)
        device_speed = self.tool_options.get("device_speed", None)
        board = self.tool_options.get("board", None)

        vpr_options = self.tool_options.get("vpr_options", None)
        cmake_params = {
            "name": self.name,
            "sources": file_list,
            "user_files": user_files,
            "doblink_source_dir": doblink_source_dir,
            "doblink_build_dir": doblink_build_dir,
            "figure": figure,
            "num_luts": num_luts,
            "arch": arch,
            "device_family": device_family,
            "device_name": device_name,
            "device_speed": device_speed,
            "board": board,
            "vpr_options": vpr_options,
        }

        self.render_template(
            "symbiflow-vpr-cmakelists.j2", "CMakeLists.txt", cmake_params
        )

    def configure_main(self):
        self.configure_vpr()

    def run_main(self):
        logger.info("Done")


class SymbiflowMake(Edatool):

    argtypes = ["vlogdefine", "vlogparam", "generic"]

    def __init__(self, edam=None, work_root="./", eda_api=None, verbose=True):
        super(SymbiflowMake, self).__init__(edam, work_root, eda_api, verbose)
        self.jinja_env = Environment(
            loader=PackageLoader(__package__, "templates"),
            trim_blocks=True,
            lstrip_blocks=True,
            keep_trailing_newline=True,
        )

    @classmethod
    def get_doc(cls, api_ver):
        if api_ver == 0:
            symbiflow_help = {
                "members": [
                    {
                        "name": "package",
                        "type": "String",
                        "desc": "FPGA chip package (e.g. clg400-1)",
                    },
                    {
                        "name": "part",
                        "type": "String",
                        "desc": "FPGA part type (e.g. xc7a50t)",
                    },
                    {
                        "name": "vendor",
                        "type": "String",
                        "desc": 'Target architecture. Currently only "xilinx" is supported',
                    },
                    {
                        "name": "pnr",
                        "type": "String",
                        "desc": 'Place and Route tool. Currently only "vpr" is supported',
                    },
                    {
                        "name": "vpr_options",
                        "type": "String",
                        "desc": "Additional vpr tool options. If not used, default options for the tool will be used",
                    },
                    {
                        "name": "environment_script",
                        "type": "String",
                        "desc": "Optional bash script that will be sourced before each build step.",
                    },
                ]
            }

            symbiflow_members = symbiflow_help["members"]

            return {
                "description": "The Symbiflow backend executes Yosys sythesis tool and VPR place and route. It can target multiple different FPGA vendors",
                "members": symbiflow_members,
            }

    def get_version(self):
        return "1.0"

    def configure_vpr(self):
        (src_files, incdirs) = self._get_fileset_files(force_slash=True)

        has_vhdl = "vhdlSource" in [x.file_type for x in src_files]
        has_vhdl2008 = "vhdlSource-2008" in [x.file_type for x in src_files]

        if has_vhdl or has_vhdl2008:
            logger.error("VHDL files are not supported in Yosys")

        input_xdc_file = self.tool_options.get("input_xdc_file", None)
        top_pcf = self.tool_options.get("top_pcf", None)
        place_delay_bin = self.tool_options.get("place_delay_bin", None)
        lookahead_bin = self.tool_options.get("lookahead_bin", None)
        rrgraph_bin = self.tool_options.get("rrgraph_bin", None)
        arch_xml = self.tool_options.get("arch_xml", None)
        pinmap_csv = self.tool_options.get("pinmap_csv", None)

        doblink_source_dir = self.tool_options.get("doblink_source_dir", None)
        verilog_src_dir = self.tool_options.get("verilog_src_dir", None)
        leaf_int_src_dir = self.tool_options.get("leaf_int_src_dir", None)
        use_roi = self.tool_options.get("use_roi", None)
        figure = self.tool_options.get("figure", None)
        num_luts = self.tool_options.get("num_luts", None)
        arch = self.tool_options.get("arch", None)
        device_family = self.tool_options.get("device_family", None)
        device_name = self.tool_options.get("device_name", None)
        device_speed = self.tool_options.get("device_speed", None)
        board = self.tool_options.get("board", None)

        vpr_options = self.tool_options.get("vpr_options", None)
        make_params = {
            "input_xdc_file": input_xdc_file,
            "top_pcf": top_pcf,
            "place_delay_bin": place_delay_bin,
            "lookahead_bin": lookahead_bin,
            "rrgraph_bin": rrgraph_bin,
            "arch_xml": arch_xml,
            "pinmap_csv": pinmap_csv,
            "doblink_source_dir": doblink_source_dir,
            "verilog_src_dir": verilog_src_dir,
            "leaf_int_src_dir": leaf_int_src_dir,
            "use_roi": use_roi,
            "figure": figure,
            "num_luts": num_luts,
            "arch": arch,
            "device_family": device_family,
            "device_name": device_name,
            "device_speed": device_speed,
            "board": board,
            "vpr_options": vpr_options,
        }

        template_dir = "symbiflow"
        template = self.jinja_env.get_template(
            "/".join([template_dir, "symbiflow-vpr-makefile.j2"])
        )
        file_path = os.path.join(self.work_root, "Makefile")
        with open(file_path, "w") as f:
            f.write(template.render(make_params))

    def configure_main(self):
        self.configure_vpr()

    def _run_scripts(self, scripts, hook_name):
        for script in scripts:
            _env = self.env.copy()
            if "env" in script:
                _env.update(script["env"])
            logger.info("Running {} script {}".format(hook_name, script["name"]))
            logger.debug("Environment: " + str(_env))
            logger.debug("Working directory: " + self.work_root)
            try:
                cp = run(
                    script["cmd"],
                    cwd=self.work_root,
                    env=_env,
                    capture_output=True,
                    check=True,
                    timeout=script.get("timeout"),
                )
            except subprocess.TimeoutExpired as e:
                msg = "Unable to run {} script '{}': {}"
                raise RuntimeError(msg.format(hook_name, script["name"], str(e)))
            except FileNotFoundError as e:
                msg = "Unable to run {} script '{}': {}"
                raise RuntimeError(msg.format(hook_name, script["name"], str(e)))
            except subprocess.CalledProcessError as e:
                msg = "{} script '{}': {} exited with error code {}".format(
                    hook_name, script["name"], e.cmd, e.returncode
                )
                logger.debug(msg)
                if e.stdout:
                    logger.info(e.stdout.decode())
                if e.stderr:
                    logger.error(e.stderr.decode())
                    logger.debug("=== STDERR ===")
                    logger.debug(e.stderr)
                raise RuntimeError(msg)

    def run_main(self):
        logger.info("Done!")
