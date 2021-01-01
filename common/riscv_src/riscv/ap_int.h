
#ifndef __AP_UINT_H__
#define __AP_UINT_H__

#include <iostream>

template <int T=32>
class ap_uint{

	struct Proxy{
		ap_uint<T>* parent = nullptr;
		int hi, lo;

		// When ap_unit is rhs
		Proxy& operator =(unsigned u) {parent->set(hi, lo, u); return *this;}

		Proxy& operator =(Proxy u) {parent->set(hi, lo, u); return *this;}

		// When ap_unit is lhs
		operator unsigned int () const {return parent->range(hi, lo);}
	};

	public:
		#if(T==8)
			unsigned char data = 0;
		#elif(T==16)
			unsigned short data = 0;
		#elif(T==32)
			unsigned int data = 0;
		#else
			unsigned int data = 0;
		#endif

		// constructor
		ap_uint<T>(unsigned u) {data = u;}
		ap_uint<T>(){ data = 0;}

		// slice the bit[b:a] out and return the sliced data
		unsigned int range(int b, int a) const {
			unsigned tmp1 = 0;
			unsigned tmp2 = 0;
			tmp1 = data >> a;
			for(int i=0; i<(b-a+1); i++) tmp2 = (tmp2<<1)+1;
			return tmp1&tmp2;
		}

		// manually set bit[b:a] = rhs
		void set(int b, int a, unsigned int rhs){
			unsigned or_mask = 0xffffffff;
			unsigned or_data = 0;
			int i;
			for(i=0; i<b-a+1; i++) or_mask = (or_mask << 1);
			for(i=0; i<a; i++) or_mask = (or_mask << 1)+1;
			or_data = data & or_mask;
			data = or_data | (rhs << a);
		}

		// Whenever need () operator, call out the Proxy struct
		Proxy operator() (int Hi, int Lo) {
			return {this, Hi, Lo};
		}

		Proxy operator = (Proxy op2){
			this->data = op2;
		}


		// enable arithmetic operator
		operator unsigned int() const { return data; }

		unsigned int to_int(){
			return data;
		}

		void operator ++(int op){
			data = data + 1;
		}

};

#endif

