import glob
import logging
import os
import re
import shutil

import hydra
import pyparsing as pp
from edalize import *
from hydra.core.hydra_config import HydraConfig
from hydra.utils import get_original_cwd
from omegaconf import DictConfig, OmegaConf

from do_blink.edalize.symbiflow import Symbiflow

# A logger for this file
log = logging.getLogger(__name__)

from pathlib import Path


def build_do_blink_designs(cfg):

    project_dir = get_original_cwd()
    total_times = []
    for figure, fig_val in cfg.do_blink.fig.items():
        for num_luts, design_cfg in fig_val.items():
            source_file_dir = os.path.join(
                project_dir,
                "do_blink/symbiflow_benchmark/{}/{}".format(figure, num_luts),
            )
            source_files = glob.glob("{}/*.v".format(source_file_dir))
            user_files = glob.glob("{}/*.dat".format(source_file_dir))
            src_dir = f"{os.getcwd()}/{figure}/{num_luts}/"
            Path(src_dir).mkdir(parents=True, exist_ok=True)
            for filename in [*source_files, *user_files]:
                shutil.copy(filename, src_dir)

            files = [
                {"name": i.split("/")[-1], "file_type": "verilogSource"}
                for i in source_files
            ]
            files.extend(
                [{"name": i.split("/")[-1], "file_type": "user"} for i in user_files]
            )

            tool_options = {
                "doblink_source_dir": project_dir,
                "doblink_build_dir": os.path.join(project_dir, "build"),
                "figure": figure,
                "num_luts": num_luts,
                "arch": design_cfg.arch,
                "device_family": design_cfg.device_family,
                "device_name": design_cfg.device_name,
                "device_speed": design_cfg.device_speed,
                "board": design_cfg.board,
                "vpr_options": """
                --router_heap bucket 
                --clock_modeling route 
                --place_delta_delay_matrix_calculation_method dijkstra 
                --place_delay_model delta 
                --router_lookahead extended_map 
                --check_route quick 
                --strict_checks off 
                --allow_dangling_combinational_nodes on 
                --disable_errors check_unbuffered_edges:check_route 
                --congested_routing_iteration_threshold 0.8 
                --incremental_reroute_delay_ripup off 
                --base_cost_type delay_normalized_length_bounded 
                --bb_factor {} 
                --acc_fac {} 
                --astar_fac {} 
                --initial_pres_fac {} 
                --pres_fac_mult {} 
                --check_rr_graph off 
                --suppress_warnings \${{OUT_NOISY_WARNINGS}},sum_pin_class:check_unbuffered_edges:load_rr_indexed_data_T_values:check_rr_node:trans_per_R:check_route:set_rr_graph_tool_comment:calculate_average_switch
                """.format(
                    cfg.do_blink.vpr_options.bb_factor,
                    cfg.do_blink.vpr_options.acc_fac,
                    cfg.do_blink.vpr_options.astar_fac,
                    cfg.do_blink.vpr_options.initial_pres_fac,
                    cfg.do_blink.vpr_options.pres_fac_mult,
                ),
            }
            build_dir = f"{os.getcwd()}/{figure}/{num_luts}/build"
            Path(build_dir).mkdir(parents=True, exist_ok=True)
            name = "_".join(
                [figure, num_luts, re.sub("\D", "", HydraConfig().get().run.dir)]
            )

            hooks = {
                "pre_run": [
                    {
                        "cmd": ["cmake", "-S", src_dir, "-B", build_dir],
                        "name": "cmake_gen",
                    },
                    {
                        "cmd": [
                            "cmake",
                            "--build",
                            build_dir,
                            "--target",
                            name + "_bit",
                        ],
                        "name": "cmake_build",
                    },
                ]
            }
            edam = {
                "files": files,
                "name": name,
                "tool_options": {"symbiflow": tool_options},
                "toplevel": "top",
                "hooks": hooks,
            }

            backend = Symbiflow(edam=edam, work_root=src_dir)
            backend.configure()
            # backend.run()

    #     curr_build_dir = os.path.join(build_dir, HydraConfig().get().run.dir)
    #     top_synth_log = open(glob.glob("{}/**/top_synth.json.log".format(curr_build_dir), recursive=True)[0], "r").read()
    #     top_eblif_log = open(glob.glob("{}/**/top.eblif.log".format(curr_build_dir), recursive=True)[0], "r").read()
    #     pack_log = open(glob.glob("{}/**/pack.log".format(curr_build_dir), recursive=True)[0], "r").read()
    #     place_log = open(glob.glob("{}/**/place.log".format(curr_build_dir), recursive=True)[0], "r").read()
    #     route_log = open(glob.glob("{}/**/route.log".format(curr_build_dir), recursive=True)[0], "r").read()
    #     fasm_log = open(glob.glob("{}/**/vpr_stdout.log".format(curr_build_dir), recursive=True)[0], "r").read()
    #     bitgen_log = open(glob.glob("{}/**/xcfasm.time".format(curr_build_dir), recursive=True)[0], "r").read()

    #     yosys_pattern = pp.Literal("CPU: user") + pp.Combine(pp.Word(pp.nums) + "." + pp.Word(pp.nums))
    #     vpr_pattern = pp.Literal("The entire flow of VPR took ") + pp.Combine(pp.Word(pp.nums) + "." + pp.Word(pp.nums))
    #     xcfasm_pattern = pp.Combine(pp.Word(pp.nums) + "." + pp.Word(pp.nums)) + pp.Literal('user')

    #     top_synth_time = float(yosys_pattern.searchString(top_synth_log).asList()[-1][-1])
    #     top_eblif_time = float(yosys_pattern.searchString(top_eblif_log).asList()[-1][-1])
    #     pack_time_time = float(vpr_pattern.searchString(pack_log).asList()[-1][-1])
    #     place_log_time = float(vpr_pattern.searchString(place_log).asList()[-1][-1])
    #     route_log_time = float(vpr_pattern.searchString(route_log).asList()[-1][-1])
    #     fasm_log_time = float(vpr_pattern.searchString(fasm_log).asList()[-1][-1])
    #     bitgen_log_time = float(xcfasm_pattern.searchString(bitgen_log).asList()[0][0])

    #     total_time = top_synth_time + top_eblif_time + pack_time_time + place_log_time + route_log_time + fasm_log_time + bitgen_log_time
    #     log.info(f"Total compile time={total_time} seconds (bb_factor={cfg.do_blink.vpr_options.bb_factor}, acc_fac={cfg.do_blink.vpr_options.acc_fac}, astar_fac={cfg.do_blink.vpr_options.astar_fac}, inital_pres_fac={cfg.do_blink.vpr_options.initial_pres_fac}, press_fac_mult={cfg.do_blink.vpr_options.pres_fac_mult})")
    # return total_time


@hydra.main(config_path="conf", config_name="config")
def parse_config(cfg: DictConfig) -> None:
    return build_do_blink_designs(cfg)


if __name__ == "__main__":
    parse_config()
