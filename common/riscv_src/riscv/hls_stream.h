
#ifndef _HLS_STREAM_H_
#define _HLS_STREAM_H_

//# include "ap_int.h"
#include <stdint.h>
#define STREAMOUT_BASE 0x10000000

//template <class type>
namespace hls{
  template <class type>
  class stream
  {
      public:
	uint32_t ADDR;
	stream(uint32_t addr){ ADDR = addr; };
	stream(void){ ADDR = STREAMOUT_BASE; };

        uint32_t read(){
	  return *((volatile uint32_t*)ADDR);
        }

        void write(type dout){
	  *((volatile uint32_t*)ADDR) = dout;
        }
 
  };
}

#endif
