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


class Vivado(Edatool):

    argtypes = ["vlogdefine", "vlogparam", "generic"]

    def __init__(self, edam=None, work_root='./', eda_api=None, verbose=True):
        super(Vivado, self).__init__(edam, work_root, eda_api, verbose)
        self.jinja_env = Environment(
            loader = PackageLoader(__package__, 'templates'),
            trim_blocks = True,
            lstrip_blocks = True,
            keep_trailing_newline = True,
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
                        "name" : "environment_script",
                        "type" : "String",
                        "desc" : "Optional bash script that will be sourced before each build step."
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

    def configure_vivado(self):
        (src_files, incdirs) = self._get_fileset_files(force_slash=True)

        has_vhdl = "vhdlSource" in [x.file_type for x in src_files]
        has_vhdl2008 = "vhdlSource-2008" in [x.file_type for x in src_files]

        if has_vhdl or has_vhdl2008:
            logger.error("VHDL files are not supported in Yosys")

        make_params = {
            "common_src_dir":  self.tool_options.get('common_src_dir', None),
            "src_dir":  self.tool_options.get('src_dir', None),
			"overlay_dir":  self.tool_options.get('overlay_dir', None),
            "part":  self.tool_options.get('part', None),
			"load_vivado": self.tool_options.get('load_vivado', None),
        }

        template_dir = 'vivado'
        template = self.jinja_env.get_template('/'.join([template_dir, "synth.tcl.j2"]))
        file_path = os.path.join(self.work_root, "synth.tcl")
        with open(file_path, 'w') as f:
            f.write(template.render(make_params))
        pnr_script = "pnr_abs" if self.tool_options.get('use_abs', None) else "pnr"
        template = self.jinja_env.get_template('/'.join([template_dir, f"{pnr_script}.tcl.j2"]))
        file_path = os.path.join(self.work_root, f"{pnr_script}.tcl")
        with open(file_path, 'w') as f:
            f.write(template.render(make_params))
        template = self.jinja_env.get_template('/'.join([template_dir, "vivado.sh.j2"]))
        file_path = os.path.join(self.work_root, "vivado.sh")
        with open(file_path, 'w') as f:
            f.write(template.render(make_params))


    def configure_main(self):
        self.configure_vivado()

    def _run_scripts(self, scripts, hook_name):
        for script in scripts:
            _env = self.env.copy()
            if 'env' in script:
                _env.update(script['env'])
            logger.info("Running {} script {}".format(hook_name, script['name']))
            logger.debug("Environment: " + str(_env))
            logger.debug("Working directory: " + self.work_root)
            try:
                cp = run(script['cmd'],
                                    cwd = self.work_root,
                                    env = _env,
				    capture_output=not self.verbose,
                                    check = True,
                                    timeout = script.get('timeout'))
            except subprocess.TimeoutExpired as e:
                msg = "Unable to run {} script '{}': {}"
                raise RuntimeError(msg.format(hook_name, script['name'], str(e)))
            except FileNotFoundError as e:
                msg = "Unable to run {} script '{}': {}"
                raise RuntimeError(msg.format(hook_name, script['name'], str(e)))
            except subprocess.CalledProcessError as e:
                msg = "{} script '{}': {} exited with error code {}".format(hook_name, script['name'], e.cmd, e.returncode)
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