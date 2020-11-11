#include "stdint.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>
#include <generated/mem.h>

#define LED AXILITE2LED_BASE+16
#define SW  AXILITE2LED_BASE+8

typedef struct b128 {
  uint64_t a;
  uint64_t b;
} b128_t;

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = readchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					putsnonl("\x08 \x08");
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				putsnonl("\n");
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				putsnonl(c);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}

	return NULL;
}

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("RUNTIME>");
}

static void help(void)
{
	puts("Available commands:");
	puts("help                            - this command");
	puts("reboot                          - reboot CPU");
	puts("display                         - display test");
	puts("led                             - led test");
}

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

static volatile uint32_t TxBufferPtr[100]  __attribute__((aligned(16)));
static volatile uint32_t RxBufferPtr[100]  __attribute__((aligned(16)));

static void dma_test(void) {

  for(int i = 0; i < 100; i++) {
    TxBufferPtr[i] = i+1;
  }

  for(int i = 0; i < 100; i++) {
    RxBufferPtr[i] = 0;
  }

  flush_l2_cache();

  printf("TxBufferPtr = %#8X\n", (uint32_t)TxBufferPtr);
  printf("RxBufferPtr = %#8X\n", (uint32_t)RxBufferPtr);

  mm2s_base_write((uint32_t)TxBufferPtr);
  mm2s_length_write(25);
  mm2s_start_write(1);
  printf("Waiting for mm2s to finish\n");
  while (!mm2s_done_read());

  busy_wait(1000);

  s2mm_base_write((uint32_t) RxBufferPtr);
  s2mm_length_write(25);
  s2mm_start_write(1);
  printf("Waiting for s2mm to finish\n");
  while(!s2mm_done_read());

  busy_wait(1000);

  int matching = 1;
  for (int i = 0; i < 100; i++) {
    if (RxBufferPtr[i] != TxBufferPtr[i]) {
      printf("Data mismatch at i=%d, expected=%d, actual=%d\n", i, TxBufferPtr[i], RxBufferPtr[i]);
      matching = 0;
    }
  }

  if (!matching) {
    printf("TEST FAILED\n");
  } else {
    printf("TEST PASSED\n");
  }
}

static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot();
	prompt();
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

  while(1) {
   console_service(); 
  }

	return 0;
}
