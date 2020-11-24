### config_gen: generate the config.c and config.h files for PrFlow
# Created by: Yuanlong Xiao (yuanlongxiao24@gmail.com)
#         at: University of Pennsylvania
#         in: 2018       
           
#
# The big picture:
#
# config_gen will generate files by using different parameters
#
# How it works (in a nutshell):
#
# Run command "python config_gen.py"
#
# [1] D. Park, Y. Xiao and A. DeHon, "Case for Acceleration of FPGA Compilation using Partial Reconfiguration", FPL2018
#


# This module contains classes needed by config_gen.py 
import xml.etree.ElementTree
import time

class debug_func:
  """ This class can print list and dict decently. """
  def __init__(self):
    pass
    
  def print_list_hex(self, in_list):
    for child in in_list:
      print hex(child)

  def print_dict_hex(self, in_dict):
    for key_var, value_var in in_dict.items():
      print str(key_var) + " -> " + str(hex(value_var))
			
			
class conn_parser:
  """ This class parses the xml file and store the link relations in self.links. """
  def __init__(self, func_conn_filename):
    self.root = xml.etree.ElementTree.parse(func_conn_filename).getroot()
    self.functions = self.root.findall('function')
    self.links = self.root.findall('link')	
    
  def print_all_func(self):
    for child in self.functions:
      print child.get('name')

  def print_all_link(self):
    for child in self.links:
      print child.get('source') + " -> " + child.get('destination')
			
			
			
class loc_parser:
  """ This class pasrses the implementaton file to get the leaf number of each
  functions. The information is stored in self.func_loc_dict. """
  def __init__(self, leaf_num):
  # Initialize the specs
    self.func_loc_dict = {'ARM': '0'}
    for i in range(1, leaf_num):
      self.func_loc_dict['Function'+str(i)] = str(i)
  def print_all_loc(self):
    for child in self.func_loc_dict:
      print child + " -> " + self.func_loc_dict[child] 
			


class packets_gen:
  def __init__(self, prflow_params, packet_bits, addr_bits, port_bits, bram_addr_bits,payload_bits, bram_addr, freespace, input_port_offset, output_port_offset):
  # Initialize the specs
    self.prflow_params = prflow_params
    self.packet_bits = packet_bits
    self.addr_bits = addr_bits
    self.port_bits = port_bits
    self.bram_addr_bits = bram_addr_bits
    self.payload_bits = payload_bits
    self.bram_addr = bram_addr
    self.freespace = 2**bram_addr_bits - 1
    self.addr_offset = packet_bits - 1 - addr_bits
    self.port_offset = packet_bits - 1 - addr_bits - port_bits
    self.bram_offset = payload_bits
    self.self_port_offset    = payload_bits - port_bits
    self.dst_src_addr_offset = payload_bits - port_bits - addr_bits
    self.dst_src_port_offset = payload_bits - port_bits - addr_bits - port_bits
    self.bram_addr_offset    = payload_bits - port_bits - addr_bits - port_bits - bram_addr_bits
    self.freespace_offset    = payload_bits - port_bits - addr_bits - port_bits - bram_addr_bits - bram_addr_bits	
    self.input_port_offset = 2;
    self.output_port_offset = 9;

    #This list stores the initial packet to set up links between different leaves
    #src_leaf, type_0, src_port, dst_leaf, dst_port
    #dst_leaf, type_1, dst_port, src_leaf, src_port
    self.init_pkt_arm2leaf_loc_list = []
    
    #This dict stores the acknowledge packet to be sent by ARM
    #As long as ARM receive 64 packets, it send an ack packet to the source ports
    #The hardware free_cnt in the source port increases by 64
    self.ack_pkt_arm2leaf_loc_dict = {}
    
    #This dict stores the acknowledge packet that should be received by ARM
    #As long as the dest receive 64 packets from ARM, it should sent an ack packet
    #the ARM increases its free_cnt after receiving one ack packet	
    self.ack_pkt_leaf2arm_loc_dict = {}
    
    #This dict stores the packet header for ARM.
    self.data_pkt_arm2leaf_loc_dict = {}
    
    #HEX packet corresponded to self.init_pkt_arm2leaf_loc_list
    self.init_pkt_arm2leaf_num_list = []
    
    #HEX packet corresponded to self.ack_pkt_arm2leaf_loc_dict
    self.ack_pkt_arm2leaf_num_dict = {}
    
    #HEX packet corresponded to self.ack_pkt_leaf2arm_loc_dict
    self.ack_pkt_leaf2arm_num_dict = {}
    
    #HEX packet corresponded to self.data_pkt_arm2leaf_loc_dict
    self.data_pkt_arm2leaf_num_dict = {}
    
    #type 0: configuration packet for output ports
    #type 1: configuration packet for input ports
    #type 2: regular data packet
    #type 4: update free_cnt packet
    self.pkt_type = ['0', '1', '2', '3']

  def find_page_num(self, target_val, syn_list, page_list ):
    if target_val == 'DMA':
      return 'Function1'
    elif target_val == 'dirc':
      return 'Function2'
    for num, val in enumerate(syn_list):
      if val == target_val:
        return page_list[num]

    return 'error' 		
		
  def generate_packets_of_loc(self, conn_parser, func_loc_dict):
    """This function make up all the dicts and lists for the packets sent and received by ARM"""
    for link_pair in conn_parser.links:
      source = link_pair.get('source')
      destination = link_pair.get('destination')
      packet_table_line = []
      if link_pair.get('source') == 'ARM':
        [dst_function, dst_port] = link_pair.get('destination').split('.')
        dst_function = self.find_page_num(dst_function, self.prflow_params['syn_fun_list'], self.prflow_params['page_list']) 

        dst_leaf = func_loc_dict[dst_function]
        dst_port =str(int(dst_port) + self.input_port_offset)
        src_leaf = func_loc_dict['ARM']
        src_port = '9'
        self.ack_pkt_leaf2arm_loc_dict[dst_function] = [src_leaf, src_port]
        self.data_pkt_arm2leaf_loc_dict[dst_function] = [dst_leaf, dst_port] 
        self.init_pkt_arm2leaf_loc_list.append([dst_leaf, self.pkt_type[1], dst_port, src_leaf, src_port])
      elif link_pair.get("destination") == 'ARM':
        [src_function, src_port] = link_pair.get('source').split('.')
        src_function = self.find_page_num(src_function, self.prflow_params['syn_fun_list'], self.prflow_params['page_list']) 
        src_leaf = func_loc_dict[src_function]
        src_port = str(int(src_port) + self.output_port_offset)
        dst_leaf =func_loc_dict['ARM']
        dst_port = '2'
        self.ack_pkt_arm2leaf_loc_dict[src_function] = [src_leaf, src_port]
        self.init_pkt_arm2leaf_loc_list.append([src_leaf, self.pkt_type[0], src_port, dst_leaf, dst_port])
      else:
        [src_function, src_port] = link_pair.get('source').split('.')
        src_function = self.find_page_num(src_function, self.prflow_params['syn_fun_list'], self.prflow_params['page_list']) 
        [dst_function, dst_port] = link_pair.get('destination').split('.')
        dst_function = self.find_page_num(dst_function, self.prflow_params['syn_fun_list'], self.prflow_params['page_list']) 
        src_leaf = func_loc_dict[src_function]
        dst_leaf = func_loc_dict[dst_function]
        src_port = str(int(src_port) + self.output_port_offset)
        dst_port = str(int(dst_port) + self.input_port_offset)
        self.init_pkt_arm2leaf_loc_list.append([src_leaf, self.pkt_type[0], src_port, dst_leaf, dst_port])
        self.init_pkt_arm2leaf_loc_list.append([dst_leaf, self.pkt_type[1], dst_port, src_leaf, src_port])

  def generate_packet_of_num(self):
    "Convert physical location format to HEX format"
    for child_list in self.init_pkt_arm2leaf_loc_list:
      packet_value = 0 
      packet_value = packet_value + (int(child_list[0]) << self.addr_offset)
      packet_value = packet_value + (int(child_list[1]) << self.port_offset)
      packet_value = packet_value + (int(child_list[2]) << self.self_port_offset)
      packet_value = packet_value + (int(child_list[3]) << self.dst_src_addr_offset)
      packet_value = packet_value + (int(child_list[4]) << self.dst_src_port_offset)	
      if child_list[1] == self.pkt_type[0]:
        packet_value = packet_value + ((self.bram_addr) << self.bram_addr_offset)	
        packet_value = packet_value + ((self.freespace) << self.freespace_offset)	
      self.init_pkt_arm2leaf_num_list.append(packet_value)
  
    for child_key, child_list in self.ack_pkt_arm2leaf_loc_dict.items():
      packet_value = 0
      packet_value = packet_value + (int(child_list[0]) << self.addr_offset)
      packet_value = packet_value + (int(child_list[1]) << self.port_offset)
      packet_value = packet_value + 1
      self.ack_pkt_arm2leaf_num_dict[child_key] = packet_value
  
    for child_key, child_list in self.ack_pkt_leaf2arm_loc_dict.items():
      packet_value = 0
      packet_value = packet_value + (int(child_list[0]) << self.addr_offset)
      packet_value = packet_value + (int(child_list[1]) << self.port_offset)
      packet_value = packet_value + (1 << (self.packet_bits-1))
      packet_value = packet_value + 1
      self.ack_pkt_leaf2arm_num_dict[child_key] = packet_value
  
    for child_key, child_list in self.data_pkt_arm2leaf_loc_dict.items():
      packet_value = 0
      packet_value = packet_value + (int(child_list[0]) << self.addr_offset)
      packet_value = packet_value + (int(child_list[1]) << self.port_offset)			
      self.data_pkt_arm2leaf_num_dict[child_key] = packet_value


class c_source_gen:
  """ This class generates the config.c and config.h files. """
  def __init__(self, output_source_file_name, output_header_file_name):
    # Initialize the specs
    self.source_file_name = output_source_file_name
    self.header_file_name = output_header_file_name
    
  def generate(self, init_pkt_arm2leaf_num_list, ack_pkt_arm2leaf_num_dict, ack_pkt_leaf2arm_num_dict, data_pkt_arm2leaf_num_dict,board):
  								
    config_c_file = open(self.source_file_name, 'w')
    config_h_file = open(self.header_file_name, 'w')
    self.generate_common_func(config_c_file, init_pkt_arm2leaf_num_list, board)
    for src_function in ack_pkt_arm2leaf_num_dict.keys():	
      for dst_function in ack_pkt_leaf2arm_num_dict.keys():
        self.generate_stream_operation_for_each_leaf(src_function,dst_function, config_c_file, ack_pkt_arm2leaf_num_dict[src_function], ack_pkt_leaf2arm_num_dict[dst_function], data_pkt_arm2leaf_num_dict[dst_function])
    config_h_file.write("void read_from_fifo(int * ctrl_reg);\n\n")
    config_h_file.write("void write_to_fifo_simple(int reg3, int reg2, int reg1);\n\n")
    config_h_file.write("void init_regs();\n\n")
    config_h_file.write("int stream_op(int op_type, int i);\n\n")
    config_h_file.write("int send_packet(int i);\n\n")

    config_c_file.close()
    config_h_file.close()
		
  def generate_common_func(self, config_c_file, init_pkt_arm2leaf_num_list, board):
    """ This function generates all files. """

    config_c_file.write("#include \"xaxidma.h\"\n")
    config_c_file.write("#include \"xparameters.h\"\n")
    config_c_file.write("#include \"xdebug.h\"\n")
    config_c_file.write("\n")
    config_c_file.write("\n")
    config_c_file.write("//width of a packet is 49 bits\n")
    config_c_file.write("//bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}\n")
    config_c_file.write("//arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}\n")
    config_c_file.write("//input fifo empty = SLV_REG3[1]\n")
    config_c_file.write("//output fifo full = SLV_REG3[0]\n")
    config_c_file.write("//input fifo rd_en = SLV_REG7[1]\n")
    for i in range(8):
      if (board == 'u96'):
        config_c_file.write("#define SLV_REG"+str(i)+" XPAR_BFT_AXILITE2BFT_V2_0_0_BASEADDR+"+str(i*4)+"\n")
      else:
        config_c_file.write("#define SLV_REG"+str(i)+" XPAR_AXI_LEAF_AXILITE2BFT_V2_0_0_BASEADDR+"+str(i*4)+"\n")
    config_c_file.write("\n")
    config_c_file.write("\n")
    config_c_file.write("#define WRITE_OP 0\n")
    config_c_file.write("#define READ_OP 1\n")
    config_c_file.write("#define CHECK_ACK 2\n")
    config_c_file.write("void read_from_fifo(int * ctrl_reg)\n")
    config_c_file.write("{\n")
    config_c_file.write("   int rev_0, rev_1;\n")
    config_c_file.write("\n")
    config_c_file.write("    //check if the input fifo is empty\n")
    config_c_file.write("    while((Xil_In32(SLV_REG3)>>1)&&1);\n")
    config_c_file.write("\n")
    config_c_file.write("    //toggle the rd_en bits to start one reading\n")
    config_c_file.write("   *ctrl_reg = (*ctrl_reg) ^ 0x00000002;\n")
    config_c_file.write("    //input fifo rd_en = SLV_REG7[1]\n")
    config_c_file.write("    Xil_Out32(SLV_REG7, *ctrl_reg);\n")
    config_c_file.write("\n")
    config_c_file.write("    //bft2arm_packet = {1'b1, SLV_REG1[15:0], SLV_REG0[31:0]}\n")
    config_c_file.write("    rev_0 = Xil_In32(SLV_REG0);\n")
    config_c_file.write("    rev_1 = Xil_In32(SLV_REG1);\n")
    config_c_file.write("\n")
    config_c_file.write("   //xil_printf( \"The received data is %08x_%08d \\n\", rev_1, rev_0);\n")
    config_c_file.write("\n")
    config_c_file.write("}\n")
    config_c_file.write("\n")
    config_c_file.write("\n")
    config_c_file.write("void write_to_fifo(int high_32_bits, int low_32_bits, int * ctrl_reg)\n")
    config_c_file.write("{\n")
    config_c_file.write("    //arm2bft_packet = {SLV_REG5[16:0], SLV_REG4[31:0]}\n")
    config_c_file.write("    Xil_Out32(SLV_REG5, high_32_bits);\n")
    config_c_file.write("    Xil_Out32(SLV_REG4, low_32_bits);\n")
    config_c_file.write("    *ctrl_reg = (*ctrl_reg) ^ 0x00000001;\n")
    config_c_file.write("    Xil_Out32(SLV_REG7, *ctrl_reg);\n")
    config_c_file.write("}\n")
    config_c_file.write("\n")
    config_c_file.write("\n")
    config_c_file.write("void init_regs()\n")
    config_c_file.write("{\n")
    config_c_file.write("   int i = 0;\n")
    config_c_file.write("   static int ctrl_reg = 0;\n")
    config_c_file.write("\n")
    config_c_file.write("   for (i=4; i<8; i++) {Xil_Out32(SLV_REG0+i*4, 0x00000000);}\n")
    config_c_file.write("\n")


    for packet_value in init_pkt_arm2leaf_num_list:
      
      packet_value_0 = packet_value & 0xffffffff
      packet_value_1 = (packet_value >> 32) & 0xffffffff
      packet_value_2 = (packet_value >> 64) & 0xffffffff
      config_c_file.write("      write_to_fifo(" + str(hex(packet_value_1)).replace('L', '') + ', ' + str(hex(packet_value_0)).replace('L', '') + ", &ctrl_reg);\n")
    config_c_file.write("\n")
    config_c_file.write("\n")
    config_c_file.write("}\n")
		
  def generate_stream_operation_for_each_leaf(self, src_function, dst_function, config_c_file, ack_pkt_arm2leaf_num, ack_pkt_leaf2arm_num, data_pkt_arm2leaf_num):	
    
    config_c_file.write("int stream_" + src_function +"_ARM_" + dst_function + "(int op_type, int i){\n")
    config_c_file.write("   static int free_cnt = 127;\n")
    config_c_file.write("   static int update_cnt = 0;\n")
    config_c_file.write("   static int ctrl_in = 0;\n")
    config_c_file.write("   static int addr = 0;\n")
    config_c_file.write("   static int cnt = 0;\n")
    config_c_file.write("   int low_32_bits, high_32_bits;\n")
    config_c_file.write("\n")
    config_c_file.write("   if(op_type == WRITE_OP){\n")
    config_c_file.write("           if(free_cnt > 0){\n")
    value_var_0 = data_pkt_arm2leaf_num & 0xffffffff
    value_var_1 = (data_pkt_arm2leaf_num >> 32) & 0xffffffff
    value_var_2 = (data_pkt_arm2leaf_num >> 64) & 0xffffffff
    config_c_file.write("                   write_to_fifo(" + str(hex(value_var_1)).replace('L', '') + '+addr, '+ str(hex(value_var_0)).replace('L', '') + "+i);\n")
    config_c_file.write("                   addr++;\n")
    config_c_file.write("                   //xil_printf( \"cnt = %d\\n\",cnt);\n")
    config_c_file.write("                   cnt++;\n")
    config_c_file.write("                   if (addr == 128) addr = 0;\n")
    config_c_file.write("                   free_cnt -= 1;\n")
    config_c_file.write("           }\n")
    config_c_file.write("   }\n")
    config_c_file.write("\n")
    config_c_file.write("\n")
    config_c_file.write("   if(op_type == READ_OP){\n")
    config_c_file.write("           read_from_fifo(&ctrl_in);\n")
    config_c_file.write("           low_32_bits = Xil_In32(SLV_REG0);\n")
    config_c_file.write("           high_32_bits = Xil_In32(SLV_REG1);\n")
    value_var_0 = ack_pkt_leaf2arm_num & 0xffffffff
    value_var_1 = (ack_pkt_leaf2arm_num >> 32) & 0xffffffff
    value_var_2 = (ack_pkt_leaf2arm_num >> 64) & 0xffffffff
    config_c_file.write("           if((high_32_bits == " + str(hex(value_var_1)).replace('L', '') + ") && (low_32_bits == " + str(hex(value_var_0)).replace('L', '') + ")){\n")
    config_c_file.write("                   free_cnt = free_cnt + 64;\n")
    config_c_file.write("                   read_from_fifo(&ctrl_in);\n")
    config_c_file.write("                   low_32_bits = Xil_In32(SLV_REG0);\n")
    config_c_file.write("                   high_32_bits = Xil_In32(SLV_REG1);\n")
    config_c_file.write("                   update_cnt += 1;\n")
    config_c_file.write("           }else{\n")
    config_c_file.write("                   update_cnt += 1;\n")
    config_c_file.write("           }\n")
    config_c_file.write("\n")
    config_c_file.write("           if(update_cnt == 64){\n")
    value_var_0 = ack_pkt_arm2leaf_num & 0xffffffff
    value_var_1 = (ack_pkt_arm2leaf_num >> 32) & 0xffffffff
    value_var_2 = (ack_pkt_arm2leaf_num >> 64) & 0xffffffff	
    config_c_file.write("                   write_to_fifo(" + str(hex(value_var_1)).replace('L', '') + ", (" + str(hex(value_var_0)).replace('L', '') + "));\n")
    config_c_file.write("                   update_cnt = 0;\n")
    config_c_file.write("           }\n")
    config_c_file.write("   }\n")
    config_c_file.write("\n")
    config_c_file.write("   if(op_type == CHECK_ACK){\n")
    config_c_file.write("           read_from_fifo(&ctrl_in);\n")
    config_c_file.write("           low_32_bits = Xil_In32(SLV_REG0);\n")
    config_c_file.write("           high_32_bits = Xil_In32(SLV_REG1);\n")
    value_var_0 = ack_pkt_leaf2arm_num & 0xffffffff
    value_var_1 = (ack_pkt_leaf2arm_num >> 32) & 0xffffffff
    value_var_2 = (ack_pkt_leaf2arm_num >> 64) & 0xffffffff
    config_c_file.write("           if((high_32_bits == " + str(hex(value_var_1)).replace('L', '') + ") && (low_32_bits == " + str(hex(value_var_0)).replace('L', '') + ")){\n")
    config_c_file.write("                   free_cnt = free_cnt + 64;\n")
    config_c_file.write("           }\n")
    config_c_file.write("   }\n")
    config_c_file.write("   return low_32_bits;\n")
    config_c_file.write("}\n")



class auto_config:
  """ This class generates the config.c and config.h files. """
  def __init__(self, prflow_params):
  # Initialize the specs
    self.prflow_params = prflow_params
    self.source_file_name = './output/config.c'
    self.header_file_name = './output/config.h'
  def generate(self):
    #define the parameters for interface
    packet_bits = int(self.prflow_params['packet_bits'])
    leaf_num = int(self.prflow_params['nl'])
    addr_bits = 0
    while leaf_num !=0:
      leaf_num = leaf_num / 2
      addr_bits = addr_bits + 1
    addr_bits = addr_bits - 1
    port_bits = int(self.prflow_params['port_bits'])
    bram_addr_bits = int(self.prflow_params['bram_addr_bits'])
    payload_bits = int(self.prflow_params['payload_bits'])
    bram_addr = int(self.prflow_params['bram_addr'])
    freespace = 2**bram_addr_bits - 1
    #we got 16 ports, port 0 is to configure the output ports regs
    #port 1 is to configure the input ports regs
    #input ports: 2-8
    #output prots: 9-15
    input_port_offset = int(self.prflow_params['input_port_offset'])
    output_port_offset = int(self.prflow_params['output_port_offset'])

    #define hte paramters for input and output files
    func_conn_filename = self.prflow_params['input_file_name']
    output_source_file_name = self.prflow_params['workspace']+'/F007_mono_bft_'+self.prflow_params['benchmark_name']+'/config_'+self.prflow_params['benchmark_name']+'.cc'
    output_header_file_name = self.prflow_params['workspace']+'/F007_mono_bft_'+self.prflow_params['benchmark_name']+'/config_'+self.prflow_params['benchmark_name']+'.h'

    # Record start time
    total_start_time = time.time()


    # Create debug instance to print list and dict
    debug_inst = debug_func()

    #Create this instance to generate c program files
    c_gen_inst = c_source_gen(output_source_file_name, output_header_file_name)

    #Create this instance to parse the conncetion between the C functions
    conn_parser_inst = conn_parser(func_conn_filename)

    #Create this instance to parse the hardware mapping of C functions
    loc_parser_inst = loc_parser(int(self.prflow_params['nl']))

    #This instance is to do some bits calculation of the packets sent and received by ARM
    packets_gen_inst = packets_gen(self.prflow_params, packet_bits, addr_bits, port_bits, bram_addr_bits, payload_bits, bram_addr, freespace, input_port_offset, output_port_offset)

    #use the physical locations (leaf location and port numbers) to represend the packet
    packets_gen_inst.generate_packets_of_loc(conn_parser_inst, loc_parser_inst.func_loc_dict)
    #convert the packets represent by the physical locations to HEX format
    packets_gen_inst.generate_packet_of_num()

    #generate config.c and config.h files
    c_gen_inst.generate(packets_gen_inst.init_pkt_arm2leaf_num_list, packets_gen_inst.ack_pkt_arm2leaf_num_dict, packets_gen_inst.ack_pkt_leaf2arm_num_dict, packets_gen_inst.data_pkt_arm2leaf_num_dict, self.prflow_params['board'])
	
    # Record end time
    total_end_time = time.time()
    total_time_elapsed = total_end_time - total_start_time
    total_hours_elapsed = int(total_time_elapsed/3600)
    total_minutes_elapsed = int((total_time_elapsed-3600*total_hours_elapsed)/60)
    total_seconds_elapsed = int(total_time_elapsed - 3600*total_hours_elapsed - 60*total_minutes_elapsed)
    print "Config_gen completed!"
    print "Total time elapsed: " + str(total_hours_elapsed) + " hours " + str(total_minutes_elapsed) + " minutes " + str(total_seconds_elapsed) + " seconds\n" 

    #print packets_gen_inst.ack_pkt_arm2leaf_loc_dict
    #print packets_gen_inst.ack_pkt_leaf2arm_loc_dict
    #print packets_gen_inst.data_pkt_arm2leaf_loc_dict
    #print packets_gen_inst.init_pkt_arm2leaf_num_list
    #debug_inst.print_dict_hex(packets_gen_inst.ack_pkt_arm2leaf_loc_dict)
    #debug_inst.print_dict_hex(packets_gen_inst.ack_pkt_leaf2arm_loc_dict)
    #debug_inst.print_dict_hex(packets_gen_inst.data_pkt_arm2leaf_loc_dict)
    #debug_inst.print_list_hex(packets_gen_inst.init_pkt_arm2leaf_num_list)
