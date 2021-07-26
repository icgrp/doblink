#ifndef AXI_LITE_DRIVER_H
#define AXI_LITE_DRIVER_H

#include <stdint.h>

void lx_write32(uintptr_t addr, uint32_t val);

uint32_t lx_read32(uintptr_t addr);

void axi_led_write(uint32_t val);

uint32_t axi_led_read(void);

uint32_t axi_sw_read(void);

#endif
