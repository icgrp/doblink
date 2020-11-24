#!/usr/bin/python3
import argparse


def trace_from_simulation_log(data_package, disp, filename='simulation.log'):

    with open(filename, 'r') as f:
        out_data = open('out.txt', 'w')
        for i, line in enumerate(f):
            if i > 2:
                data= line.split('\t')
                if (data[0] == data_package):
                    out_data.write(line)
                    if disp:
                        print(line)
        return True

if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('-a', '--address', type=str)
    parser.add_argument('-v', '--disp', help="display in terminal", action='store_true')
    #parser.add_argument('-i', '--max_iterations', type=int, default=6, help="max FPGA sizing iterations")
    args = parser.parse_args()
    adress = args.address
    disp = args.disp
    #max_iterations = args.max_iterations
    trace_from_simulation_log(adress, disp, 'simulation.log')
