#include "stdint.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>
#include <generated/mem.h>

#define LED AXILITE2LED_BASE+16
#define SW  AXILITE2LED_BASE+8

static void reboot(void) {
	ctrl_reset_write(1);
}

static void led_test(void) {
	int i;
	for(i=0; i<256; i++) {
		//leds_out_write(i);
		busy_wait(100);
	}
}

static void axi_led_write(uint32_t val) {
  uintptr_t Addr = LED;
  volatile uint32_t *LocalAddr = (volatile uint32_t *)Addr;
  *LocalAddr = val;
}

static uint32_t axi_led_read(void) {
  uintptr_t Addr = LED;
  return *(volatile uint32_t *)Addr;
}

static uint32_t axi_sw_read(void) {
  uintptr_t Addr = SW;
  return *(volatile uint32_t *)Addr;
}

static void axi_led_test(void) {
  axi_led_write(0xffffffff);
  busy_wait(200);
  axi_led_write(0x00000000);
  busy_wait(200);
}

static void axi_sw_test(void) {
  printf("%#08x\n", axi_sw_read());
  busy_wait(100);
}

volatile uint32_t RxBufferPtr[16] __attribute__((aligned(16)));
volatile uint32_t TxBufferPtr[16] __attribute__((aligned(16)));

static void dma_test(void) {
  for(int i = 0; i < 16; i++) {
    TxBufferPtr[i] = i;
  }

  for(int i = 0; i < 16; i++) {
    RxBufferPtr[i] = 0;
  }

  flush_cpu_dcache();
  flush_l2_cache();

  mm2s_base_write((uint32_t) &TxBufferPtr);
  mm2s_length_write(16);
  mm2s_start_write(1);
  while (!mm2s_done_read()) {
    printf("Waiting for mm2s to finish\n");
  }

  s2mm_base_write((uint32_t) &RxBufferPtr);
  s2mm_length_write(16);
  s2mm_start_write(1);
  while(!s2mm_done_read()) {
    printf("Waiting for s2mm to finish\n");
  }

  int matching = 1;
  for (int i = 0; i < 16; i++) {
    if (RxBufferPtr[i] != i) {
      printf("Data mismatch at i=%d, expected=%d, actual=%d\n", i, i, RxBufferPtr[i]);
      matching = 0;
    }
  }

  if (!matching) {
    printf("TEST FAILED\n");
  } else {
    printf("TEST PASSED\n");
  }
}

int main(void)
{
#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
#endif
	uart_init();

	puts("\nrvpld - CPU testing software built "__DATE__" "__TIME__"\n");

	printf("led_test...\n");
  dma_test();

	return 0;
}
