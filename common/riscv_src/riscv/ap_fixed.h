/*
* Company: IC group, University of Pennsylvania
* Engineer: Yuanlong Xiao
*
* Create Date: 02/02/2021
* Design Name: ap_fixed
* Project Name:
* Versions: 1.0
* Description:
*   This is a manual implementation of ap_fixed to replace ap_fixed.h from Xilinx
*
* Dependencies:
*
* Revision:
* Revision 0.01 - File Created
* Revision 0.02 - add << overloading function
* Revision 0.03 - rename the input argument (data) to din for member function data_to_array. 
*                 avoid shadow variables with data[]. This may help potential deadlock
* Revision 0.04 - Disable floating point operations to accelerate dotProduct in Spam Filter
* Additional Comments:
*/


#ifndef __ap_fixed_H__
#define __ap_fixed_H__


	#include "stdio.h"
template <int _AP_W, int _AP_I>
class ap_fixed{

	// With the proxy struct, the bitwise operations can be overloaded.
	// ap_uint<32> tmp;
	// tmp(7,0) = 0;
	struct Proxy{
		ap_fixed<_AP_W, _AP_I>* parent = nullptr;
		unsigned char hi, lo;

		// When ap_unit is rhs
		Proxy& operator =(unsigned long long u) { parent->set(hi, lo, u); return *this;}

		Proxy& operator =(Proxy u) {parent->set(hi, lo, u); return *this;}

		// When ap_unit is lhs
		operator unsigned int () {return parent->range(hi, lo);}
	};

	public:
		// Define the local variable to store the value
		// Currently, the bitwidth only support multiples of 8 bits.
		unsigned char data[_AP_W/8];

		// constructor
		ap_fixed<_AP_W, _AP_I>(){
			for(int i=0; i<_AP_W/8; i++){
				data[i] = 0;
			}
		}

		// constructor
		//ap_fixed<_AP_W, _AP_I>(unsigned int u) {data = u;}
		ap_fixed<_AP_W, _AP_I>(double f) {
			for(int i=0; i<_AP_W/8; i++){ data[i] = 0; }
			unsigned char i, is_minus;
			long long i_part;
			unsigned char byte_num;;
			unsigned char bit_num;
			is_minus = (f>=0) ? 0 : 1;
			i_part = is_minus ? (unsigned int) (-f) : (unsigned int) f;
			double d_part = is_minus ? -f - i_part : f-i_part;

			// process the decimal parts of the double variables
			for(i=0; i<(_AP_W-_AP_I); i++){
				d_part = d_part * 2;
				//printf("d_part = %.20f |", d_part);
				byte_num = (_AP_W-_AP_I-i-1)>>3;
				bit_num = (_AP_W-_AP_I-i-1)- (byte_num<<3);
				if(d_part >= 1){
					data[byte_num] = set_bit(data[byte_num], bit_num);
					if((i==(_AP_W-_AP_I-1)) && (d_part -1 > 0) && is_minus){ array_add1(data, _AP_W/8); }
					d_part = d_part - 1;

				}else{
					data[byte_num] = clr_bit(data[byte_num], bit_num);
					if((i==(_AP_W-_AP_I-1)) && (d_part > 0) && is_minus){ array_add1(data, _AP_W/8); }
				}
				//print_raw();

			}

			// process the integer parts of the double variables
			for(i=0; i<(_AP_I); i++){
				byte_num = (_AP_W-_AP_I+i)>>3;
				bit_num = (_AP_W-_AP_I+i)- (byte_num<<3);
				if(i_part & 0x01){
					data[byte_num] = set_bit(data[byte_num], bit_num);
				}else{
					data[byte_num] = clr_bit(data[byte_num], bit_num);
				}
				i_part = i_part >> 1;
			}

			// if the variable is a negative double, convert it to 2'complementary value
			if(is_minus){
				array_inv(data, _AP_W/8);
				array_add1(data, _AP_W/8);
			}
		}

		// constructor
		template <int _AP_W_2, int _AP_I_2>
		ap_fixed<_AP_W, _AP_I>(ap_fixed<_AP_W_2, _AP_I_2> op2){
			unsigned char bits_array[_AP_W];
			unsigned char bits_array2[_AP_W_2];
			unsigned char _AP_F, _AP_F_2;
			unsigned int i, j;
			_AP_F =_AP_W-_AP_I;
			_AP_F_2 = _AP_W_2-_AP_I_2;;

			for(i=0; i<_AP_W; i++){
				bits_array[i] = 0;
			}

	    	for(i=0; i<_AP_W_2>>3; i++){
	    		for(j=0; j<8; j++){
	    			bits_array2[(i<<3)+j] = (op2.data[i] >> j) & 0x01;
	    		}
	    	}


			if(_AP_I < _AP_I_2){
				for(i=0; i<_AP_I; i++){ bits_array[i+_AP_F] = bits_array2[i+_AP_F_2];}
			}else{
				for(i=0; i<_AP_I_2; i++){ bits_array[i+_AP_F] = bits_array2[i+_AP_F_2];}
				for(i=0; i<_AP_I-_AP_I_2; i++){ bits_array[_AP_I_2+_AP_F+i] = bits_array2[_AP_W_2-1]; }
			}

			if(_AP_F < _AP_F_2){
				for(i=0; i<_AP_F; i++){   bits_array[_AP_F-1-i] = bits_array2[_AP_F_2-1-i];}
			}else{
				for(i=0; i<_AP_F_2; i++){ bits_array[_AP_F-1-i] = bits_array2[_AP_F_2-1-i];}
			}

	    	for(i=0; i<_AP_W>>3; i++){
	    		for(j=0; j<8; j++){
	    			if(bits_array[(i<<3)+j]){
	    				data[i] = set_bit(data[i], j);
	    			}else{
	    				data[i] = clr_bit(data[i], j);
	    			}
	    		}
	    	}

		}



		unsigned int set_bit(unsigned int din, unsigned char bit_num){
			return (din | (1<<bit_num));
		}

		unsigned int clr_bit(unsigned int din, unsigned char bit_num){
			return (din & (~(1<<bit_num)));
		}

		// reverse the all bits of all the elements in the array
		void array_inv(unsigned char *din, unsigned char len){
			unsigned char i;
			for(i=0; i<len; i++){
				din[i] = ~din[i];
			}
		}

		// assume the array as value
		// eg. data[3], data[2], data[1], data[0]
		//    +                                1
		//---------------------------------------
		//     data[3], data[2], data[1], data[0]
		void array_add1(unsigned char *din, unsigned len){
			unsigned char i;
			unsigned char carry = 1;
			for(i=0; i<len; i++){
				din[i] = din[i] + carry;
				if(din[i] == 0x00){
					carry = 1;
				}else{
					carry = 0;
					return;
				}
			}
		}

		// assume the array as value
		// eg. data[3], data[2], data[1], data[0]
		//    -                                1
		//---------------------------------------
		//     data[3], data[2], data[1], data[0]
		void array_sub1(unsigned char *din, unsigned len){
			unsigned char i;
			unsigned char carry = 1;
			for(i=0; i<len; i++){
				din[i] = din[i] - carry;
				if(din[i] == 0xff){
					carry = 1;
				}else{
					carry = 0;
					return;
				}
			}
		}

		double div_2_power(unsigned char power){
			double out_tmp = 1;
			for(unsigned char i=0; i<power; i++){
				out_tmp = out_tmp / 2;
			}
			return out_tmp;
		}

#ifdef FLOAT_ENABLE
		double to_float(){
	    	unsigned char bits_array[_AP_W];
	    	double i_part=0, d_part=0;
	    	unsigned char tmp_data[_AP_W/8];
	    	int i=0, j=0;
	    	unsigned char is_minus = 0;



	    	for(i=0; i<_AP_W/8; i++){ tmp_data[i] = data[i]; }

	    	is_minus = (tmp_data[_AP_W/8-1] >> 7) & 0x01;

	    	if(is_minus){
	    		array_sub1(tmp_data, _AP_W/8);
	    		array_inv(tmp_data,  _AP_W/8);
	    	}
	    	for(i=0; i<_AP_W>>3; i++){
	    		for(j=0; j<8; j++){
	    			bits_array[(i<<3)+j] = (tmp_data[i] >> j) & 0x01;
	    		}
	    	}

	    	//print_array(bits_array, _AP_W);

	    	//calculate integer part
	    	for(i=_AP_W-_AP_I; i<_AP_W; i++){
	    		i_part += (1<<(i-_AP_W+_AP_I))*bits_array[i];
	    	}

	    	//calculate fraction part
	    	for(i=0; i<(_AP_W-_AP_I); i++){
	    		d_part += (double)bits_array[i]*(div_2_power((_AP_W-_AP_I)-i));
	    	}
	    	//printf("d_part = %.20f\n", d_part);
	    	// reverse the bits if the sign flag is minus
	    	return is_minus == 1 ? (-i_part-d_part) : (i_part+d_part);
	    }
#endif
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

		// Whenever need () operator, call out the Proxy struct
		Proxy operator() (unsigned char Hi, unsigned char Lo) {
			return {this, Hi, Lo};
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

#ifdef FLOAT_ENABLE
		//  enable arithmetic operator
		operator double() { return this->to_float(); }
#endif

	    void cp_array(unsigned char *d_dest, unsigned char *d_src, unsigned char len){
	    	for(unsigned char i=0; i<len; i++){
	    		d_dest[i] = d_src[i];
	    	}
	    }


	    // convert an array to a long long
		unsigned long long array_to_data (unsigned char *din, unsigned char len){
			unsigned long long tmp_data = 0;
			unsigned char len_local;
			len_local = len > 8 ? 8 : len;

			for(unsigned char i=0; i<len_local; i++){
				tmp_data += (din[i] << (i<<3));
			}

			return tmp_data;
		}

		 // convert a long long to an array
		void data_to_array (unsigned char *dout, unsigned char len, unsigned long long din){
			unsigned long long tmp_data = din;
			unsigned char len_local;
			len_local = len > 8 ? 8 : len;

			for(unsigned char i=0; i<len_local; i++){
				dout[i] = tmp_data & 0xff;
				tmp_data = tmp_data >> 8;
			}
		}

		// shift the array to the left by 1 byte
		void array_lsh(unsigned char *din, unsigned len){
			for(int i=len-1; i>0; i--){
				din[i] = din[i-1];
			}
			din[0] = 0;
		}

		void clr_array(unsigned char *din, unsigned len){
			for(unsigned char i=0; i<len; i++){
				din[i] = 0;
			}
		}
#ifdef FLOAT_ENABLE
		double operator * (int op){
			double tmp;
			tmp = to_float();
			tmp = tmp * (double) op;
			return tmp;
		}
#endif




		ap_fixed<(_AP_W<<1), (_AP_I<<1)> operator *(ap_fixed<_AP_W, _AP_I> op){
			ap_fixed<(_AP_W<<1), (_AP_I<<1)> fix_out;			// final results array for multiplication
			ap_fixed<(_AP_W<<1), (_AP_I<<1)> op_shift;			// shift array intermediate multiplication
			ap_fixed<(_AP_W<<1), (_AP_I<<1)> op_mul;			// results for intermediate multiplication

			unsigned char is_minus_a, is_minus_b, is_minus_out;
			unsigned i,j;

			is_minus_a = ((data[(_AP_W>>3)-1]&0x80)==0x80);
			is_minus_b = ((op.data[(_AP_W>>3)-1]&0x80)==0x80);

	    	if(is_minus_a){
	    		array_sub1(data, _AP_W>>3);
	    		array_inv(data,  _AP_W>>3);
	    	}

	    	if(is_minus_b){
	    		array_sub1(op.data, _AP_W>>3);
	    		array_inv(op.data,  _AP_W>>3);
	    	}

	    	is_minus_out = is_minus_a ^ is_minus_b;

	    	cp_array(op_shift.data, this->data, _AP_W>>3);


			for(i=0; i<_AP_W>>3; i++){
				unsigned char mul1 = op.data[i];
				unsigned int carry = 0;
				for(j=0; j<_AP_W>>2; j++){
					carry = op_shift.data[j] * mul1 + carry;
					op_mul.data[j] = carry & 0xff;
					carry = carry >> 8;
				}
				//printf("op_mul: ");
				//op_mul.print_raw();
				fix_out = fix_out + op_mul;
				//printf("fix_out: ");
				//fix_out.print_raw();
				array_lsh(op_shift.data, _AP_W>>2);
			}

			if(is_minus_out){
				array_inv(fix_out.data,  _AP_W>>2);
				array_add1(fix_out.data, _AP_W>>2);
			}

	    	if(is_minus_a){
	    		array_inv(data,  _AP_W>>3);
	    		array_add1(data, _AP_W>>3);
	    	}

			//printf("before out\n");
			//fix_out.print_raw();

			return fix_out;
		}

		ap_fixed<_AP_W, _AP_I> operator +(ap_fixed<_AP_W, _AP_I> op){
			ap_fixed<_AP_W, _AP_I> fix_out;
			unsigned char i;
			unsigned int carry = 0;
			for(i=0; i<_AP_W/8; i++){
				carry = this->data[i] + op.data[i] + carry;
				fix_out.data[i] = carry & 0xff;
				carry = carry >> 8;
			}

			return fix_out;
		}



#ifdef FLOAT_ENABLE
		double operator +(double op){
			double tmp;
			tmp = to_float();
			tmp = tmp + op;
			return tmp;
		}
#endif
		



		ap_fixed<_AP_W, _AP_I> operator -(ap_fixed<_AP_W, _AP_I> op){
			ap_fixed<_AP_W, _AP_I> fix_out;
			unsigned char i;
			unsigned int carry = 0;
			array_inv(op.data,  _AP_W>>3);
			array_add1(op.data, _AP_W>>3);
			for(i=0; i<_AP_W>>3; i++){
				carry = this->data[i] + op.data[i] + carry;
				fix_out.data[i] = carry & 0xff;
				carry = carry >> 8;
			}


			return fix_out;
		}

		ap_fixed<_AP_W, _AP_I> operator -(){
			ap_fixed<_AP_W, _AP_I> fix_out;
			cp_array(fix_out.data, this->data, _AP_W>>3);
			array_inv(fix_out.data,  _AP_W>>3);
			array_add1(fix_out.data, _AP_W>>3);

			return fix_out;
		}


		ap_fixed<_AP_W, _AP_I> operator <<(unsigned int op){
			ap_fixed<_AP_W, _AP_I> fix_out;
			unsigned char i;
			unsigned char shift_bytes = op >> 3;
			unsigned char shift_bits = op - ((op >> 3) << 3);

			//printf("shift_bytes = %d\n", shift_bytes);
			//printf("shift_bits = %d\n", shift_bits);

			// copy the local array to fix_out.data
			cp_array(fix_out.data, this->data, _AP_W>>3);

			// right shift the array by the unit of bytes
			for(i=0; i<(_AP_W>>3); i++){
				if(i<((_AP_W>>3)-shift_bytes)){
					fix_out.data[(_AP_W>>3)-1-i] = fix_out.data[(_AP_W>>3)-1-i-shift_bytes];
				}else{
					fix_out.data[(_AP_W>>3)-1-i] = 0;
				}
			}

			//printf("raw\n");
			//fix_out.print_raw();

			// right shift the array by the unit of bits
			for(i=0; i<((_AP_W>>3)-shift_bytes); i++){
				fix_out.data[(_AP_W>>3)-1-i] = (fix_out.data[(_AP_W>>3)-1-i] << shift_bits) | (fix_out.data[(_AP_W>>3)-1-i-1] >> (8-shift_bits));
			}
			return fix_out;
		}


#ifdef DEBUG
	    void print_raw() {
			for(int i=0; i<_AP_W/8; i++){
				printf("%02x", data[_AP_W/8-i-1]);
			}
			printf("\n");
	    }
#endif

};

#endif


