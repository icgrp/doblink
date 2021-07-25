#ifndef DMA_DRIVER_H
#define DMA_DRIVER_H

#include <stdint.h>

void run_dma(volatile uint32_t *send_buffer, uint32_t send_len,
    volatile uint32_t *recv_buffer, uint32_t recv_len);

#endif
