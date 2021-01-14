#include "stdint.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>
#include <generated/mem.h>

#include "axi_lite_driver.h"

#define LED AXILITE2LED_BASE+16
#define SW  AXILITE2LED_BASE+8

void lx_write32(uintptr_t addr, uint32_t val) {
  volatile uint32_t *LocalAddr = (volatile uint32_t *)addr;
  *LocalAddr = val;
}

uint32_t lx_read32(uintptr_t addr) {
  return *(volatile uint32_t *)addr;
}

void axi_led_write(uint32_t val) {
  lx_write32(LED, val);
}

uint32_t axi_led_read(void) {
  return lx_read32(LED);
}

uint32_t axi_sw_read(void) {
  return lx_read32(SW);
}

