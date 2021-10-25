#!/usr/bin/env python
import sys
import os
import xml.etree.ElementTree
import argparse
import re
import math


def load_prflow_params(filename):
    prflow_params = {}

    # parse the common specifications
    root = xml.etree.ElementTree.parse(filename).getroot()
    specs = root.findall("spec")
    network = root.findall("network")
    clock = root.findall("clock")

    for child in specs:
        prflow_params[child.get("name")] = child.get("value")

    for child in clock:
        prflow_params[child.get("name")] = child.get("period")

    #  hls_fun_list = []
    #  syn_fun_list = []
    #  input_num_list = []
    #  output_num_list = []
    #  page_list = []
    #  ram_type_list = ['block']
    #  for child in functions:
    #    hls_fun_list.append(child.get('name'))
    #    syn_fun_list.append(child.get('name'))
    #    input_num_list.append(child.get('inputs'))
    #    output_num_list.append(child.get('outputs'))
    #    page_list.append(child.get('page'))
    #    ram_type_list.append(child.get('ramtype'))
    #
    #
    #
    #
    #
    #  prflow_params['hls_fun_list'] = hls_fun_list
    #  prflow_params['syn_fun_list'] = syn_fun_list
    #  prflow_params['input_num_list'] = input_num_list
    #  prflow_params['output_num_list'] = output_num_list
    #  prflow_params['page_list'] = page_list
    #  prflow_params['ram_type_list'] = ram_type_list

    return prflow_params
