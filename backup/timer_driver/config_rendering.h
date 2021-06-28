void read_from_fifo(int * ctrl_reg);

void write_to_fifo_simple(int reg3, int reg2, int reg1);

void init_regs();

int stream_op(int op_type, int i);

int send_packet(int i);

