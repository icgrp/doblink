#include "stdint.h"
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
	puts("led                             - led test");
}

static void reboot(void)
{
	ctrl_reset_write(1);
}

static void led_test(void)
{
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

static void axi_led_test(void)
{
  axi_led_write(0xffffffff);
  //printf("1: %#08x\n", axi_led_read());
  //busy_wait(100);
  //axi_led_write(0x00000000);
  //printf("0: %#08x\n", axi_led_read());
}

static void axi_sw_test(void)
{
  printf("%#08x\n", axi_sw_read());
  busy_wait(100);
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
	else if(strcmp(token, "led") == 0)
		led_test();
	prompt();
}

int main(void)
{
#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
#endif
	uart_init();

	puts("\nLab004 - CPU testing software built "__DATE__" "__TIME__"\n");
	help();
	prompt();

	printf("led_test...\n");
	while(1) {
    //led_test();
    axi_led_test();
	}

	return 0;
}
