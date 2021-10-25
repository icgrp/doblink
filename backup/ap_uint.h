/*
* Company: IC group, University of Pennsylvania
* Engineer: Yuanlong Xiao
*
* Create Date: 02/01/2021
* Design Name: ap_uint
* Project Name:
* Versions: 1.0
* Description:
*   This is a manual implementation of ap_uint to replace ap_uinit.h from Xilinx
*
* Dependencies:
*
* Revision:
* Revision 0.01 - File Created
* Revision 0.02 - add overloading ^. Fix this bug for digit recognition
* Revision 0.03 - add #define BYTE_SIZE(X) to define the minimum bytes number
*
* Additional Comments:
*/


#ifndef __AP_UINT_H__
#define __AP_UINT_H__

#include "stdio.h"
#define BYTE_SIZE(X)  ((X>>3)+((X&0x7) ? 1 : 0))

template <int T=32>
class ap_uint{

	// With the proxy struct, the bitwise operations can be overloaded.
	// ap_uint<32> tmp;
	// tmp(7,0) = 0;
	struct Proxy{
		ap_uint<T>* parent = nullptr;
		int hi, lo;

		// When ap_unit is rhs
		Proxy& operator =(unsigned u) {parent->set(hi, lo, u); return *this;}

		Proxy& operator =(Proxy u) {parent->set(hi, lo, u); return *this;}


		// When ap_unit is lhs
		operator unsigned int () {return parent->range(hi, lo);}
	};

	public:
		// Define the local variable to store the value
		// Currently, the bitwidth only support multiples of 8 bits.
		unsigned char data[BYTE_SIZE(T)];

		// constructor
		ap_uint<T>(unsigned int u) {
			unsigned int tmp;
			tmp = u;
			for(unsigned int i=0; i<BYTE_SIZE(T); i++){
				data[i] = tmp & 0xff;
				tmp = tmp >> 8;
			}
		}

		// constructor
		ap_uint<T>(){
			for(unsigned int i=0; i<BYTE_SIZE(T); i++){
				data[i] = 0;
			}
		}


		// set the bit to 1 according to bit number
		unsigned int set_bit(unsigned int din, unsigned char bit_num){
			return (din | (1<<bit_num));
		}

		// clear the bit to 0 according to bit number
		unsigned int clr_bit(unsigned int din, unsigned char bit_num){
			return (din & (~(1<<bit_num)));
		}

		// slice the bit[b:a] out and return the sliced data
		unsigned int range(unsigned char b, unsigned char a){
			unsigned int out_tmp = 0;
			unsigned char byte_num;
			unsigned char bit_num;
			for(unsigned char i=0; i<(b-a+1); i++){
				byte_num = (a+i) >> 3;
				bit_num = (a+i) - (byte_num << 3);
				if((data[byte_num]>>bit_num) & 0x01){ out_tmp = set_bit(out_tmp, i); }
			}
			return out_tmp;
		}



		// manually set bit[b:a] = rhs
		void set(int b, int a, unsigned long long rhs){
			unsigned char i;
			unsigned long long rhs_tmp = rhs;
			unsigned char byte_num;
			unsigned char bit_num;
			for(i=0; i<b-a+1; i++){
				byte_num = (a+i) >> 3;
				bit_num = (a+i) - (byte_num << 3);
				if(rhs_tmp & 1){
					data[byte_num] = set_bit(data[byte_num], bit_num);
				} else {
					data[byte_num] = clr_bit(data[byte_num], bit_num);
				}
				rhs_tmp =  rhs_tmp >> 1;
			}
		}

		// Whenever need () operator, call out the Proxy struct
		Proxy operator() (int Hi, int Lo) {
			return {this, Hi, Lo};
		}

		//Proxy operator = (Proxy op2){
		//	this->data = op2;
		//}


		// enable arithmetic operator
		operator unsigned int() {
			unsigned int tmp;
			tmp = to_int();
			return tmp;
		}

		unsigned int to_int(){
			unsigned int tmp;
			tmp = 0;
			for(char i=BYTE_SIZE(T)-1; i>=0; i--){
				tmp = tmp << 8;
				tmp += data[i];
			}
			return tmp;
		}

		void operator ++(int op){
			unsigned int tmp;
			tmp = 0;
			tmp = to_int();
			tmp = tmp + 1;
			for(unsigned int i=0; i<BYTE_SIZE(T); i++){
				data[i] = tmp & 0xff;
				tmp = tmp >> 8;
			}
		}

		// overload the logic function of xor
		ap_uint<T>  operator ^ (ap_uint<T> op){
			ap_uint<T> out;
			for(unsigned int i=0; i<BYTE_SIZE(T); i++){
				out.data[i] = data[i] ^ op.data[i];
			}
			return out;
		}


		void print_raw(){
			//printf("\n\n\n\nT1 = %d\n", (T>>3)+((T&0x7) ? 1 : 0));
			//printf("T2 = %d\n", (T>>3)-1);
			for(char i=BYTE_SIZE(T)-1; i>=0; i--){
				printf("%02x", data[i]);
			}
			printf("\n");
		}


};

#endif

