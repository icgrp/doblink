#!/usr/bin/python3
import network_generator as ng
import testbench_generator as tg
import subprocess
import pdb
import argparse

# THIS IS THE TOP LEVEL PYTHON SCRIPT FOR AUTOMATED TESTING!
# How it all works: 
 # The first 3 functions below use the testbench_generator.py and
 # network_generator.py file functions to create 
 # 1. a "packet_creator", which is a
 # dummy PE that just sends out packets, 
 # 2. a "testbench" which connects the
 # network to the dummy PEs and counts the packets going into and out of hte
 # network and prints them, 
 # 3. a "network" (gen_nw.v) which is basically the busses and switches that allow the
 # packets to go from one leaf to another. 
 # the "make_simulation_log" function calls Makefile which calls iverilog using 
 # all that Makefile jazz in order to simulate the test bench. 
 # We have the testbench results sent to simulation.log, and if you want to
 # save the simulation via python, just call "save_simulation_log" accordingly. 
 # From there, we can "parse_simulation_log" to get 2 dicts: one of sent
 # packets and one of recieved (see comment below). We can then
 # "verify_simulation" with those dicts as arguments to see if our results make
 # sense (hint: right now they don't). The good thing is, between the code that
 # I have already wrote and using a waveform viewer like gtkwave, you should be
 # in good shape to figure out what I missing. Hint: The common/interface.v
 # file, which is the module that regulates when packets are to be sent into
 # the network, doesn't always know to resend packets. It works fine when there
 # is a small packet injection rate and in high rent parameter networks, but in
 # small p and high injection rates, all goes to hell. In the latter case, the
 # "resend" wire is driven to high many more times, and my interface logic is
 # unable to handle all cases. I should also mention that my subtree modules,
 # which are built recursively, wire through their IO ports through each
 # successively large sub-tree, even if they don't interact with them. e.g. the
 # _111 subtree will have 4 resend wires from left child and 4 resend wires
 # from right child, and will do absolutely nothing with them other than to
 # concanate those buses together into an 8 wire bus and output it outside of
 # the sub-tree to the _1111subtree (for example). That is to say, when a
 # leafless network is constructed, it is blind to the PEs, and vice versa. If
 # I made 8 PEs, I could connect them to a _111subtree or a _211subtree, and
 # they would have no idea which network they are connected to, just that there
 # are 8 PEs total that are addressable. Once you fix this bug that I couldn't,
 # you will have what you need to simulate the network by iterating through
 # different p values, network sizes, injection rates, and addressing schemes.
 # AKA, all the exciting shit that I wanted to do but couldn't. Good luck!
 # Remember to use iverlog version 10.2 and python3, as well as be familiar
 # with git and with Makefile. 

 # My email: nmag@protonmail.com
 # My Phone number: 240-274-9926 (Yes, you can text me). 
 # - Nevo 


def make_packet_creator(injection_rate, traffic_params, num_sent_per_leaf):
    with open('gen_packet_creator.v', 'w') as pc:
        pc.write(tg.create_packet_creator(injection_rate, traffic_params,
                                          num_sent_per_leaf))


def make_testbench(num_leaves, injection_rate, num_sent_per_leaf, addr_width, data_width):  
    tg.make_test_pattern(traffic_params, num_leaves,  num_sent_per_leaf, addr_width, data_width)  
    with open('gen_nw_tb.v', 'w') as tb:
        tb.write(tg.create_tb(traffic_params, num_leaves, injection_rate, 
                     num_sent_per_leaf, addr_width, data_width))

def make_network(num_leaves, p, num_sent_per_leaf, args):
    with open('gen_nw.v', 'w') as nw:
        nw.write(ng.create_leafless_network(num_leaves, p, 
                     num_sent_per_leaf, args))
def make_axi_pe(num_leaves, p, num_sent_per_leaf, args):
    with open('axi_pe.v', 'w') as ap:
        ap.write(ng.generate_axi_pe(num_leaves, p, 
                     num_sent_per_leaf, args))



def make_all_modules(num_leaves, p, num_sent_per_leaf,
                     injection_rate, traffic_params, args):
    make_network(num_leaves, p, num_sent_per_leaf, args)
    make_axi_pe(num_leaves, p, num_sent_per_leaf, args)
    make_packet_creator(injection_rate, traffic_params, num_sent_per_leaf)
    make_testbench(num_leaves, injection_rate, num_sent_per_leaf, addr_width, data_width)

# Messy glue logic between python and Makefile and iverilog...
def make_simulation_log():
    subprocess.call(['make', 'gen_nw.vcd'])

# fyi, this code is relatively dangerous if you put a non-file name for
# filename, e.g., if filename='a && rm -rf *'
def save_simulation_log(filename='saved_simulation.log'):
    subprocess.call(['cp', 'simulation.log', filename])

def parse_simulation_log(num_leaves, num_sent_per_leaf, 
                         filename='simulation.log'):
    """ 
    Parses filename simulation log and returns 2 dicts as a tuple:
    a sent_dict and a received_dict. 
    For both dicts, the key is the packet, and the value is the
    time the packet was sent
    """

    with open(filename, 'r') as f:
        sent_dict={} 
        received_dict={} 
        for i, line in enumerate(f):
            if i > 2:
                data= line.split('\t')
                if (data[0] == 'sent'):
                        start_index= 1 + ng.clog2(num_leaves)
                        end_index= start_index + ng.clog2(num_leaves)
                        src= int(data[2][start_index:end_index], 2)
                        if int(data[1]) == src:
                            sent_dict[data[2]]= int(data[3])
                elif data[0] == 'rcvd':
                    dest= int(data[2][1:1+ng.clog2(num_leaves)], 2)
                    if int(data[1]) == dest:
                        received_dict[data[2]]= int(data[3])
        return sent_dict, received_dict

def verify_simulation(sent_dict, received_dict):
    total_num_hops= 0;
    for sent_packet, send_time in sent_dict.items():
        # first verify that the packet exists in both dicts
        if sent_packet not in received_dict.keys():
            print("Not all packets sent were recieved")
            print('first-case: ' + sent_packet)
            return False
        # verify received came after sent
        elif received_dict[sent_packet] < send_time:
            print("packet received before it was sent!")
            return False
        # verify valid packet
        elif sent_packet[0] != '1':
            print("non-valid packet")
            return False
        else:
            total_num_hops+= (received_dict[sent_packet] - send_time) / 20
    print(str(total_num_hops/len(sent_dict)))
    return True

def get_latency(sent_dict, received_dict):
    total_num_hops= 0;
    for sent_packet, send_time in sent_dict.items():
        # first verify that the packet exists in both dicts
        if sent_packet not in received_dict.keys():
            print("Not all packets sent were recieved")
            print('first-case: ' + sent_packet)
            return False
        # verify received came after sent
        elif received_dict[sent_packet] < send_time:
            print("packet received before it was sent!")
            return False
        # verify valid packet
        elif sent_packet[0] != '1':
            print("non-valid packet")
            return False
        else:
            total_num_hops+= (received_dict[sent_packet] - send_time) / 20
    return (total_num_hops/len(sent_dict))

def make_clean():
    subprocess.call(['make', 'clean'])

def simulate_more(simulation_num, args):
    i = 0
    latency_sum = 0
    simulation_true = True
    while i<simulation_num:
        i += 1;
        if args.src_gen:
            make_all_modules(num_leaves, p, num_sent_per_leaf,
                     injection_rate, traffic_params, args)
        make_simulation_log()
        sent_dict, received_dict= parse_simulation_log(num_leaves, num_sent_per_leaf)
        true_value = verify_simulation(sent_dict, received_dict)
        save_simulation_log()
        print ('Success: '+str(i)+'!')
        if true_value != True:
            print("Hoops! Something Wrong.")
            simulation_true = False
            break
        latency_sum += get_latency(sent_dict, received_dict)

    if simulation_true:
        return latency_sum/simulation_num
    else:
        return False

def gen_synth_file(num_leaves):
    out_file = open('gen_nw_vivado.v', 'w')
    in_file = open('gen_nw.v', 'r')
    for line in in_file:
        if line.startswith('module gen_nw'):
          out_file.write('module gen_nw' +str(num_leaves) + ' # (\n')
        else:
          out_file.write(line)
    in_file.close()
    in_file = open('./basic/basic.v', 'r')
    for line in in_file:
        out_file.write(line)
    in_file.close()
    out_file.close()

#-------------------  USERSPACE BELOW ------------------------#

# network params
num_leaves=0
p= 0


# testbench params
injection_rate= 0 # as a percent (out of 100) 
num_sent_per_leaf= 10 # how many total packets each pe will send 
addr_width = 0
data_width = 0

traffic_pattern= {}

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-flt', '--flatten', help="flatten the BFT in top module", action='store_true')
    parser.add_argument('-sg', '--src_gen', help="no verilog source generation", action='store_false')
    parser.add_argument('-pp', '--pipeline', type=int, default=0, help="pipeline the network")
    parser.add_argument('-v', '--verbose', help="print parameters for debugging", action='store_true')
    parser.add_argument('-s', '--synth', help="generate synthesizable gen_nw_vivado.v", action='store_true')
    parser.add_argument('-tp', '--traffic_pattern', type=str, choices=["complement", "reverse", 'random', 'manual', 'uniform'],
                           default="complement", help="choose optimization type")
    parser.add_argument('-oft', '--offset', type=int, default=5, help="the offset number for uniform")
    parser.add_argument('-irt', '--injection_rate', type=int, default=5, help="injectoin rate in percentage")
    parser.add_argument('-nspl', '--num_sent_per_leaf', type=int, default=10, help="num_sent_per_leaf")
    parser.add_argument('-pks', '--package_size', type=int, default=11, help="the width for each package")
    #parser.add_argument('-pls', '--payload_size', type=int, default=7, help="the width for each payload")
    parser.add_argument('-nl', '--num_leaves', type=int, default=8, help="the leave number for the BFT")
    parser.add_argument('-p', '--p', type=float, default=0.5, help="the P parameter in rent law")

    
    

    args = parser.parse_args()

    num_leaves = args.num_leaves
    p = args.p
    injection_rate= args.injection_rate
    num_sent_per_leaf= args.num_sent_per_leaf
    addr_width = ng.clog2(args.num_leaves)
    data_width = args.package_size - ng.clog2(args.num_leaves) * 2 - 1
    traffic_params = {'pattern':args.traffic_pattern, 'offset':args.offset}



    if args.synth:
        make_network(num_leaves, p, num_sent_per_leaf, args)
        gen_synth_file(num_leaves)
    else:
        print (simulate_more(2, args))

        
        




   
#    make_clean()
