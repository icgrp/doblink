PP		= iverilog -E
VC		= iverilog

# Simulates any testbench and generates waveform, outputs to stdout and logfile
gen_nw.vcd:			gen_nw.vvp
					vvp -l simulation.log $^ > /dev/null 

#-----------# Generated networks Only #---------------------------------------#

gen_nw.vvp:			gen_nw_tb.v gen_nw.ppv
					$(VC) $^ -o $@

gen_nw.ppv:	 		gen_nw.v gen_packet_creator.v \
					common/* t/* pi/*
					$(PP) $^ -o $@

gen_packet_creator.v:				
					echo "must generate packet creator"

gen_nw_tb.v:				
					echo "must generate testbench"

gen_nw.v:				
					echo "must generate network"

#-----------# Non-Generated Modules Below #-----------------------------------#


##-----------# Creates vvp files for testing modules #------------------------#
#
# Note that non-generated testbenches are all contained in tb directory

%.vvp:				tb/%_tb.v %.ppv
					$(VC) $^ -o $@

##-----------# Creates pre-processed modules #--------------------------------#

%_cluster.ppv:		%/*_cluster.v %_switch.ppv
					$(PP) $^ -o $@

%_switch.ppv:		%/*_switch.v direction_determiner.ppv %_arbiter.ppv
					$(PP) $^ -o $@

direction_determiner.ppv:	\
					common/direction_determiner.v common/direction_params.vh
					$(PP) $^ -o $@

%_arbiter.ppv:		%/*_arbiter.v common/direction_params.vh
					$(PP) $^ -o $@

clean:		
			rm -f *.vvp *.ppv *.vcd gen_* simulation.log *.txt *.v

