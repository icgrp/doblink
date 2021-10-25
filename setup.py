import os

from setuptools import setup

setup(
    name="doblink",
    version="0.0.0",
    packages=["do_blink"],
    package_data={
        "do_blink": [
            "edalize/templates/symbiflow/symbiflow-vpr-cmakelists.j2",
            "edalize/templates/symbiflow/symbiflow-vpr-makefile.j2",
            "edalize/templates/vivado/synth.tcl.j2",
            "edalize/templates/vivado/pnr.tcl.j2",
            "edalize/templates/vivado/pnr_abs.tcl.j2",
            "edalize/templates/vivado/vivado.sh.j2",
        ]
    },
    author="IC Group",
    description=("doblink open source fpga linking"),
    license="MIT License",
    keywords=[
        "VHDL",
        "verilog",
        "EDA",
        "hdl",
        "rtl",
        "synthesis",
        "FPGA",
        "simulation",
        "Xilinx",
    ],
    install_requires=[
        # 2.11.0 and .1 introduced an incompatible change in template output,
        # which was fixed in 2.11.2 and later.
        # https://github.com/pallets/jinja/issues/1138
        "Jinja2 >=2.8, !=2.11.0, !=2.11.1",
    ],
    tests_require=["pytest>=3.3.0", "vunit_hdl>=4.0.8"],
    # Supported Python versions: 3.5+
    python_requires=">=3.5, <4",
)
