#include "stdint.h"
#include "system.h"
#include "input_data.h"
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
#include "config_rendering.h"

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

// static void axi_led_test(void) {
//   axi_led_write(0xffffffff);
// }

// static void axi_sw_test(void) {
//   printf("%#08x\n", axi_sw_read());
//   busy_wait(100);
// }

#define SEND_LEN 9576
#define RECV_LEN 16384

static char frame_buffer_print[256][256];

static void check_results(uint32_t * output)
{

  // read result from the 32-bit output buffer
  for (int i = 0, j = 0, n = 0; n < 16384; n ++ )
  {
    uint32_t temp = output[n];
    //printf("n = %d, val = %#X\n", n, temp);

    frame_buffer_print[i][j++] = (char) (temp & 0x000000ff);
    frame_buffer_print[i][j++] = (char) ((temp & 0x0000ff00) >> 8);
    frame_buffer_print[i][j++] = (char) ((temp & 0x00ff0000) >> 16);
    frame_buffer_print[i][j++] = (char) ((temp & 0xff000000) >> 24);
    if(j == 256)
    {
      i++;
      j = 0;
    }
  }

  // print result
  printf("Image After Rendering: \n\r");
  for (int j = 256 - 1; j >= 0; j -- )
  {
    for (int i = 0; i < 256; i ++ )
    {
      int pix;
        pix = frame_buffer_print[i][j];
        //pix = output[i*256+j];
      if (pix!=0)
        printf("1");
      else
        printf("0");
    }
    printf("\n\r");
  }
}

volatile uint32_t TxBufferPtr[SEND_LEN]  __attribute__((aligned(16)));
volatile uint32_t RxBufferPtr[RECV_LEN]  __attribute__((aligned(16)));

static void rendering_test(void) {
  // printf("Write LED value 3!\r\n");
  // uart_sync();
  // axi_led_write(3);

  busy_wait(1000);
  printf("Begin Configuring BFT!\r\n");
  uart_sync();
  init_regs();
  printf("Configuring BFT Done\r\n");


  for(int i = 0; i < SEND_LEN; i++) {
    TxBufferPtr[i] = input_data[i];
  }

  for(int i = 0; i < RECV_LEN; i++) {
    RxBufferPtr[i] = 0;
  }

  busy_wait(1000);
  printf("Start!\r\n");
  start_start_write(1);

  busy_wait(1000);
  run_dma(TxBufferPtr, SEND_LEN, RxBufferPtr, RECV_LEN);

  printf("Checking Results\n");
  check_results((uint32_t *) RxBufferPtr + 16);
  start_start_write(0);

  // for(int i = 0; i < RECV_LEN; i++) {
  //   printf("got: %d\n", RxBufferPtr[i]);
  // }
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
  else if(strcmp(token, "rendering") == 0)
    rendering_test();
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


  while(1) {
    console_service();
  }

	return 0;
}
