

class stream_inst{

public:

	unsigned int status_reg;
	unsigned int ctrl_reg;

	stream_inst(int STATUS_REG, unsigned int CTRL_REG);


	void ap_start();

	void stream1_write(unsigned int data);
	void stream2_write(unsigned int data);
	void stream3_write(unsigned int data);
	void stream4_write(unsigned int data);
	void stream5_write(unsigned int data);
	void stream6_write(unsigned int data);
	void stream7_write(unsigned int data);

	unsigned int stream1_read(unsigned int * data);
	unsigned int stream2_read(unsigned int * data);
	unsigned int stream3_read(unsigned int * data);
	unsigned int stream4_read(unsigned int * data);
	unsigned int stream5_read(unsigned int * data);
	unsigned int stream6_read(unsigned int * data);
	unsigned int stream7_read(unsigned int * data);

	void print_status();


private:





};
