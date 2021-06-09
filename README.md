# doblink

## Getting Started
#### Setting up the environment
```
git clone https://github.com/icgrp/doblink
cd doblink && git submodule update --init --recursive
cd third_party/symbiflow-arch-defs && make env
cd ../../ && conda env create -f environment.yml
conda activate symbiflow_arch_def_base
cd third_party/vtr-verilog-to-routing && make && cd ../
```

#### Compiling rrgraphs
```
mkdir build && cd build && cmake .. && cd ../
cd build/do_blink/rrgraphs/xc/xc7/archs/artix7_200t/devices
make install
```

#### Compiling benchmarks on rrgraphs
```
conda activate doblink
python do_blink/scripts/run_symbiflow_design.py +experiments/fpt2021=digit_recognition_update_knn1
```

#### Cluster Launches
TODO

## Developer Notes
- Config management done using Hydra: https://hydra.cc/docs/next/intro
