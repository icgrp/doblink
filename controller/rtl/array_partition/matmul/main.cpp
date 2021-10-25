#include <iostream>
#include "matmul.cpp"
#include "input1.h"
#include "expected.h"

using namespace std;

int main()
{
	cxxrtl_design::p_matmul__partition top;

	top.p_ap__start.set<bool>(true);
	top.p_ap__rst__n.set<bool>(true);
	top.p_Output__1__V__TREADY.set<bool>(true);
	top.p_Input__1__V__TVALID.set<bool>(true);

	for(int i = 0; i < 4; i++) {
		top.p_ap__clk.set<bool>(false);
		top.step();
		top.p_ap__clk.set<bool>(true);
		top.step();
		top.p_ap__clk.set<bool>(false);
		top.step();
		top.p_ap__clk.set<bool>(true);
		top.step();
	}

	for(int i = 0; i < 1024; i++) {
		top.p_ap__clk.set<bool>(false);
		top.step();
		top.p_ap__clk.set<bool>(true);
		top.step();
		top.p_Input__1__V__TDATA.set<uint32_t>(input1[i]);
	}

	for(int i = 0; i < 7; i++) {
		top.p_ap__clk.set<bool>(false);
		top.step();
		top.p_ap__clk.set<bool>(true);
		top.step();
	}

	for(int i = 0; i < 1024; i++){
		top.p_ap__clk.set<bool>(false);
		top.step();
		top.p_ap__clk.set<bool>(true);
		top.step();
		uint32_t output = top.p_Output__1__V__TDATA.get<uint32_t>();
		if (output != exp_data[i]) {
			printf("%d: We got %08x but expected %08x\n", i, output, exp_data[i]);
		}
	}
	printf("Finished simulation.\n");
	
}