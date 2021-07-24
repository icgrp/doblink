#include "stdint.h"
#include "system.h"
#include "input1.h"
#include "expected.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>
#include <generated/mem.h>

#include "dma_driver.h"
// #include "axi_lite_driver.h"
#include "config_digit_reg_small.h"

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

#define SEND_LEN 88000
#define RECV_LEN 2000

volatile uint32_t TxBufferPtr[SEND_LEN]  __attribute__((aligned(16)));
volatile uint32_t RxBufferPtr[RECV_LEN]  __attribute__((aligned(16)));


static void digit_test(void) {
  printf("Running digit recognition\n");

  for (int i = 0; i < SEND_LEN; i++) {
    TxBufferPtr[i] = input1[i];
  }

  for(int i = 0; i < RECV_LEN; i++) {
    RxBufferPtr[i] = 0;
  }

  run_dma(TxBufferPtr, SEND_LEN, RxBufferPtr, RECV_LEN);

  printf("Checking Results\n");
  int errors=0;

  for (int i=0; i<RECV_LEN; i++) {
    if (RxBufferPtr[i] != exp_data[i]) {
      errors++;
      printf("%d: We got %d but expected %d\n", i, RxBufferPtr[i], exp_data[i]);
    }
  }

  printf("We should get accuracy rate: 1869 / 2000 \n");
  printf("The real accuracy rate: %d / 2000 \n", (2000-errors));
  printf("SUCCESS\n");
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
  else if(strcmp(token, "digit") == 0)
    digit_test();
  // else if(strcmp(token, "led") == 0)
  //   axi_led_test();
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
  start_start_write(0);
  printf("Begin Configuring BFT!\r\n");
  uart_sync();
  init_regs();
  printf("Configuring BFT Done\r\n");


  while(1) {
    console_service();
  }

	return 0;
}
