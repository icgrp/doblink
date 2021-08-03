#ifndef CONFIG_SPAM_FILTER_SMALL_H
#define CONFIG_SPAM_FILTER_SMALL_H

void read_from_fifo(int * ctrl_reg);

void write_to_fifo_simple(int reg3, int reg2, int reg1);

void init_regs(void);

int stream_op(int op_type, int i);

int send_packet(int i);

#endif
