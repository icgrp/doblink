import logging
from omegaconf import DictConfig, OmegaConf
import hydra
from hydra.utils import get_original_cwd
from hydra.core.hydra_config import HydraConfig
import os
import glob
import re
import shutil
import pyparsing as pp
import tempfile
import numpy as np

from edalize import *
from do_blink.edalize.symbiflow import SymbiflowMake

# A logger for this file
log = logging.getLogger(__name__)

from pathlib import Path

def build_do_blink_designs(cfg):
  project_dir = get_original_cwd()
  
  for figure, fig_val in cfg.do_blink.fig.items():
    for num_luts, design_cfg in fig_val.items():
      verilog_src_dir = os.path.join(project_dir, f"do_blink/symbiflow_benchmark/{figure}/{num_luts}/src")
      verilog_out_dir = os.path.join('/tmp', f"do_blink/symbiflow_benchmark/{figure}/{num_luts}/")
      device_files_dir = os.path.join(project_dir, f"{cfg.do_blink.rrgraph_install_dir}/{design_cfg.device_family}-{design_cfg.device_name}_test")
      device_files_out_dir = os.path.join('/tmp', f"symbiflow")

      xdc_path = os.path.join(verilog_src_dir, "output_fun/nexys_video.xdc")
      input_xdc_file = "nexys_video.xdc" if os.path.isfile(xdc_path) else ""

      name = "_".join([figure, num_luts, re.sub("\D", "", os.getcwd())])
      work_root = tempfile.mkdtemp(prefix=name + "_")

      tool_options = {
        "input_xdc_file": f"{input_xdc_file}",
        "top_pcf": f"{device_files_out_dir}/{design_cfg.device_family}-{design_cfg.device_name}_test/top.pcf",
        "place_delay_bin": f"{device_files_out_dir}/{design_cfg.device_family}-{design_cfg.device_name}_test/rr_graph_{design_cfg.device_family}-{design_cfg.device_name}_test.place_delay.bin",
        "lookahead_bin": f"{device_files_out_dir}/{design_cfg.device_family}-{design_cfg.device_name}_test/rr_graph_{design_cfg.device_family}-{design_cfg.device_name}_test.lookahead.bin",
        "rrgraph_bin": f"{device_files_out_dir}/{design_cfg.device_family}-{design_cfg.device_name}_test/rr_graph_{design_cfg.device_family}-{design_cfg.device_name}_test.rr_graph.real.bin",
        "arch_xml": f"{device_files_out_dir}/{design_cfg.device_family}-{design_cfg.device_name}_test/arch.timing.xml",
        "pinmap_csv": f"{device_files_out_dir}/{design_cfg.device_family}-{design_cfg.device_name}_test/{design_cfg.device_family}{design_cfg.device_speed}/pinmap.csv",
        "doblink_source_dir": project_dir,
        "verilog_src_dir": f"{verilog_out_dir}src",
        "figure": figure,
        "num_luts": num_luts,
        "arch": design_cfg.arch,
        "device_family": design_cfg.device_family,
        "device_name": design_cfg.device_name,
        "device_speed": design_cfg.device_speed,
        "board": design_cfg.board,
        "vpr_options": f"--bb_factor {cfg.do_blink.vpr_options.bb_factor} \
                        --acc_fac {cfg.do_blink.vpr_options.acc_fac} \
                        --astar_fac {cfg.do_blink.vpr_options.astar_fac} \
                        --initial_pres_fac {cfg.do_blink.vpr_options.initial_pres_fac} \
                        --pres_fac_mult {cfg.do_blink.vpr_options.pres_fac_mult} \
                        --place_algorithm {cfg.do_blink.vpr_options.place_algorithm} \
                        --max_criticality {cfg.do_blink.vpr_options.max_criticality} \
                        --target_ext_pin_util {cfg.do_blink.vpr_options.target_ext_pin_util.input},{cfg.do_blink.vpr_options.target_ext_pin_util.output}"
      }
      build_dir = f"/{work_root}/{os.getcwd()}/{figure}/{num_luts}/build"
      Path(build_dir).mkdir(parents=True, exist_ok=True)
      
      hooks = {'pre_run' : [{'cmd': ['mkdir', '-p', verilog_out_dir], 'name': 'mkdir'},
                            {'cmd': ['rsync', '-a', device_files_dir, device_files_out_dir], 'name': 'get device files'},
                            {'cmd': ['rsync', '-a', verilog_src_dir, verilog_out_dir], 'name': 'get verilog files'},
                            {'cmd': ['mkdir', 'output_fun'], 'name': 'mkdir output_fun'},
                            {'cmd': ['make', 'output_fun/top.bit'], 'name': 'make', 'timeout': design_cfg.timeout}]}
      edam = {
        "name": name,
        "tool_options": {"symbiflowmake": tool_options},
        "toplevel" : 'top',
        'hooks': hooks
      }
      
      backend = SymbiflowMake(edam=edam, work_root=build_dir)
      backend.configure()
      try:
        backend.run()

        curr_build_dir = os.path.join(build_dir, "output_fun")
        top_synth_log = open(glob.glob("{}/**/top_synth.json.time".format(curr_build_dir), recursive=True)[0], "r").read()
        top_eblif_log = open(glob.glob("{}/**/out.eblif.time".format(curr_build_dir), recursive=True)[0], "r").read()
        pack_log = open(glob.glob("{}/**/out.net.time".format(curr_build_dir), recursive=True)[0], "r").read()
        io_place_log = open(glob.glob("{}/**/top_io.place.time".format(curr_build_dir), recursive=True)[0], "r").read()
        place_log = open(glob.glob("{}/**/out.place.time".format(curr_build_dir), recursive=True)[0], "r").read()
        route_log = open(glob.glob("{}/**/out.route.time".format(curr_build_dir), recursive=True)[0], "r").read()
        fasm_log = open(glob.glob("{}/**/top.fasm.time".format(curr_build_dir), recursive=True)[0], "r").read()
        bitgen_log = open(glob.glob("{}/**/top.bit.time".format(curr_build_dir), recursive=True)[0], "r").read()

        time_pattern = pp.Combine(pp.Word(pp.nums) + "." + pp.Word(pp.nums)) + pp.Literal('user')

        top_synth_time = float(time_pattern.searchString(top_synth_log).asList()[0][0])
        top_eblif_time = float(time_pattern.searchString(top_eblif_log).asList()[0][0])
        pack_time_time = float(time_pattern.searchString(pack_log).asList()[0][0])
        io_place_log_time = float(time_pattern.searchString(io_place_log).asList()[0][0])
        place_log_time = float(time_pattern.searchString(place_log).asList()[0][0])
        route_log_time = float(time_pattern.searchString(route_log).asList()[0][0])
        fasm_log_time = float(time_pattern.searchString(fasm_log).asList()[0][0])
        bitgen_log_time = float(time_pattern.searchString(bitgen_log).asList()[0][0])
        
        total_time = top_synth_time + top_eblif_time + pack_time_time + io_place_log_time + place_log_time + route_log_time + fasm_log_time + bitgen_log_time
        log.info(f"{design_cfg.device_family},{int(top_synth_time+top_eblif_time)},{int(pack_time_time)},{int(io_place_log_time+place_log_time)},{int(route_log_time)},{int(fasm_log_time+bitgen_log_time)},{int(total_time)}")
        return total_time
      except RuntimeError as e:
        log.info(e)
        total_times = [float(_design_cfg.timeout) for _figure, _fig_val in cfg.do_blink.fig.items() for _num_luts, _design_cfg in _fig_val.items()]
        log.info(f"Experiment failed! Setting total_time to {np.sum(total_times)} seconds.")
        return np.sum(total_times)

@hydra.main(config_path="../../conf", config_name="config")
def parse_config(cfg: DictConfig) -> None:
    return build_do_blink_designs(cfg)

if __name__ == '__main__':
  parse_config()