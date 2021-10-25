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
from do_blink.edalize.vivado import Vivado

# A logger for this file
log = logging.getLogger(__name__)

from pathlib import Path


def build_do_blink_designs(cfg):
    project_dir = get_original_cwd()
    verilog_common_src_dir = os.path.join(
        project_dir, f"do_blink/{cfg.do_blink.backend}_benchmark/hdl/common/"
    )
    verilog_common_out_dir = os.path.join(
        "/tmp", f"do_blink/{cfg.do_blink.backend}_benchmark/hdl/common"
    )
    verilog_src_dir = os.path.join(
        project_dir,
        f"do_blink/{cfg.do_blink.backend}_benchmark/hdl/{cfg.do_blink.num_luts}/src/",
    )
    verilog_out_dir = os.path.join(
        "/tmp",
        f"do_blink/{cfg.do_blink.backend}_benchmark/hdl/{cfg.do_blink.num_luts}/src",
    )

    overlay_dir = os.path.join(
        project_dir,
        f"do_blink/{cfg.do_blink.backend}_benchmark/overlay/{cfg.do_blink.figure}_{cfg.do_blink.sub_figure}/{cfg.do_blink.bft}/{cfg.do_blink.num_luts}/{cfg.do_blink.device}/",
    )
    overlay_out_dir = os.path.join(
        "/tmp",
        f"do_blink/{cfg.do_blink.backend}_benchmark/overlay/{cfg.do_blink.figure}_{cfg.do_blink.sub_figure}/{cfg.do_blink.bft}/{cfg.do_blink.num_luts}/{cfg.do_blink.device}",
    )

    name = "_".join(
        [
            cfg.do_blink.backend,
            cfg.do_blink.figure,
            cfg.do_blink.sub_figure,
            str(cfg.do_blink.device),
            str(cfg.do_blink.num_luts),
            cfg.do_blink.bft,
            re.sub("\D", "", os.getcwd()),
        ]
    )
    work_root = tempfile.mkdtemp(prefix=name + "_")

    tool_options = {
        "common_src_dir": verilog_common_out_dir,
        "src_dir": verilog_out_dir,
        "overlay_dir": overlay_out_dir,
        "part": cfg.do_blink.part,
        "load_vivado": cfg.do_blink.load_vivado,
        "use_abs": cfg.do_blink.get("use_abs", False),
    }
    pnr_script = "pnr_abs.tcl" if cfg.do_blink.get("use_abs", False) else "pnr.tcl"
    hooks = {
        "pre_run": [
            {"cmd": ["mkdir", "-p", verilog_common_out_dir], "name": "mkdir"},
            {"cmd": ["mkdir", "-p", verilog_out_dir], "name": "mkdir"},
            {"cmd": ["mkdir", "-p", overlay_out_dir], "name": "mkdir"},
            {
                "cmd": ["rsync", "-a", verilog_common_src_dir, verilog_common_out_dir],
                "name": "get common verilog files",
            },
            {
                "cmd": ["rsync", "-a", verilog_src_dir, verilog_out_dir],
                "name": "get verilog files",
            },
            {
                "cmd": ["rsync", "-a", overlay_dir, overlay_out_dir],
                "name": "get overlay files",
            },
            {
                "cmd": ["sh", "vivado.sh", "-mode", "batch", "-source", "synth.tcl"],
                "name": "run synth.tcl",
            },
            {
                "cmd": ["sh", "vivado.sh", "-mode", "batch", "-source", pnr_script],
                "name": "run pnr.tcl",
            },
        ]
    }
    edam = {
        "name": name,
        "tool_options": {"vivado": tool_options},
        "toplevel": "top",
        "hooks": hooks,
    }

    backend = Vivado(edam=edam, work_root=work_root)
    backend.configure()
    try:
        backend.run()
        run_synth_log = open(
            glob.glob("{}/**/run_synth.log".format(work_root), recursive=True)[0], "r"
        ).read()
        run_log_name = "run_abs" if cfg.do_blink.get("use_abs", False) else "run"
        run_log = open(
            glob.glob("{}/**/{}.log".format(work_root, run_log_name), recursive=True)[
                0
            ],
            "r",
        ).read()

        syn_time_pattern = pp.Literal("syn:") + pp.Word(pp.nums) + pp.Literal("seconds")
        rdchk_time_pattern = (
            pp.Literal("read_checkpoint:") + pp.Word(pp.nums) + pp.Literal("seconds")
        )
        opt_time_pattern = pp.Literal("opt:") + pp.Word(pp.nums) + pp.Literal("seconds")
        place_time_pattern = (
            pp.Literal("place:") + pp.Word(pp.nums) + pp.Literal("seconds")
        )
        route_time_pattern = (
            pp.Literal("route:") + pp.Word(pp.nums) + pp.Literal("seconds")
        )
        bit_gen_time_pattern = (
            pp.Literal("bit_gen:") + pp.Word(pp.nums) + pp.Literal("seconds")
        )

        syn_time = float(syn_time_pattern.searchString(run_synth_log).asList()[0][1])
        rdchk_time = float(rdchk_time_pattern.searchString(run_log).asList()[0][1])
        opt_time = float(opt_time_pattern.searchString(run_log).asList()[0][1])
        place_time = float(place_time_pattern.searchString(run_log).asList()[0][1])
        route_time = float(route_time_pattern.searchString(run_log).asList()[0][1])
        bit_gen_time = float(bit_gen_time_pattern.searchString(run_log).asList()[0][1])
        total_time = (
            syn_time + rdchk_time + opt_time + place_time + route_time + bit_gen_time
        )
        log.info(
            f"{cfg.do_blink.device},{int(syn_time)},{int(rdchk_time)},{int(opt_time)},{int(place_time)},{int(route_time)},{int(bit_gen_time)},{int(total_time)}"
        )
        return total_time
    except RuntimeError as e:
        log.info(e)
        log.info(f"Experiment failed!")
        total_time = 10000
        return total_time


@hydra.main(config_path="../../conf", config_name="config")
def parse_config(cfg: DictConfig) -> None:
    return build_do_blink_designs(cfg)


if __name__ == "__main__":
    parse_config()
