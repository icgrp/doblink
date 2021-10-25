#!/bin/bash

vivado_prj=$1
dest_dir=$2
name=$3
top=$4

mkdir $dest_dir/symbiflow_build
mkdir $dest_dir/symbiflow_source
mkdir $dest_dir/symbiflow_source/$name
pushd $vivado_prj; find . \( -name "*.v" -o -name "*.vh" -o -name "*.dat" \) ! -name "*sim*" ! -name "*stub*" ! -path "*sim*" -exec cp {}  $dest_dir/symbiflow_source/$name \;; popd
pushd $dest_dir/symbiflow_source/$name
rm processing_system7_vip_v1_0_8_*
rm fifo_gen*
touch top.pcf
sed -i '/(\* use_clock_enable/d' axi_register_slice_v2_1_vl_rfs.v
echo -e \
	"module BIBUF (\n" \
"    IO,\n" \
"    PAD\n" \
");\n" \
"    inout IO;\n" \
"    inout PAD;\n" \
"    assign PAD = IO;\n" \
"endmodule\n" > bibuf.v
mv ${top}.v top.v
sed -i 's/^module.*/module top/' top.v
popd
echo "src=${dest_dir}/symbiflow_source" > $dest_dir/symbiflow_build/Makefile
cat Makefile >> $dest_dir/symbiflow_build/Makefile
cp synth.tcl $dest_dir/symbiflow_build

