#include <stdint.h>
#include <stdio.h>
#include <generated/csr.h>
#include <generated/mem.h>

#include "dma_driver.h"

void run_dma(volatile uint32_t *send_buffer, uint32_t send_len,
    volatile uint32_t *recv_buffer, uint32_t recv_len) {
  flush_l2_cache();
  
  printf("TxBufferPtr = %#8X\n", (uint32_t) send_buffer);
  printf("RxBufferPtr = %#8X\n", (uint32_t) recv_buffer);

  mm2s_base_write((uint32_t) send_buffer);
  mm2s_length_write(4 * send_len);
  mm2s_start_write(1);
  printf("Waiting for mm2s to finish\n");
  //while(!mm2s_done_read());

  s2mm_base_write((uint32_t) recv_buffer);
  s2mm_length_write(4 * recv_len);
  s2mm_start_write(1);
  printf("Waiting for s2mm to finish\n");
  while(!s2mm_done_read());
  printf("DMA done\n");

  flush_l2_cache();
}
