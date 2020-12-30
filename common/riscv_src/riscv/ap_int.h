
#ifndef __AP_UINT_H__
#define __AP_UINT_H__

template <int T>
class ap_uint
{


struct Proxy
{
    ap_uint<T>* parent = nullptr;
    int hi;
    int lo;
    Proxy& operator =(unsigned u) {
     parent->set(hi, lo, u);
     return *this;
    }

    operator unsigned int () const {
        return parent->range(hi, lo);
    }
};


public:
    unsigned int data = 0;

    // constructor
    ap_uint<T>(unsigned u) {data = u;}
    ap_uint<T>(){ data = 0;}

    // slice the bit[b:a]
    unsigned int range(int b, int a) const {
        unsigned tmp1 = 0;
        unsigned tmp2 = 0;
        tmp1 = data >> a;
        for(int i=0; i<(b-a+1); i++) tmp2 = (tmp2<<1)+1;
        return tmp1&tmp2;
    }

    // overloading () with range() function
    unsigned operator() (int Hi, int Lo) const {
        return this->range(Hi, Lo);
    }
    Proxy operator() (int Hi, int Lo) {
        return {this, Hi, Lo};
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

    // enable arithmetic operator
    operator unsigned int() const { return data; }

    unsigned int to_int(){
    	return data;
    }

    void operator ++(int op){
    	data = data + 1;
    }

    // enable arithmetic operator
    //void operator = (ap_uint<T> & op1){
    //	data = op1.data;
    //}
};

#endif

