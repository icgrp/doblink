#include <stdio.h>

static const int STREAM_NUM = 0;

void stream_out(int num) {
    //place stream-out instruction here (stream out to stream STREAM_NUM)
    asm volatile("strmw zero, %[strm_ind], %[value]" : : [strm_ind] "r" (STREAM_NUM), [value] "r" (num));
    printf("Stream out: %d\n", num);
}

int stream_in() {
    int num = -1; //place stream-in instruction here (stream in to stream STREAM_NUM)
    asm volatile("strmw %[dest], %[strm_ind], zero" : [dest] "=r" (num) : [strm_ind] "r" (STREAM_NUM));
    printf("Stream in: %d\n", num);
    return num; 
}

int main() {
#ifdef CONFIG_CPU_HAS_INTERRUPT
	irq_setmask(0);
	irq_setie(1);
#endif
	uart_init();
	puts("\nrvpld - CPU testing software built "__DATE__" "__TIME__"\n");

    int a = 12;
    int b = 10;
    printf("Multiply %d by %d via adds and streams\n", a, b);
    for (int i = 0; i < b; i++) {
        int val;
        if (i == 0) {
            val = 0;
        } else {
            val = stream_in();
        }

        val += a;

        if (i == b - 1) {
            printf("Final value is: %d\n", val);
        } else {
            printf("Current intermittent value is: %d\n", val);
            stream_out(val);
        }
    }

    int as[] = {2, 5, 7};
    b = 3;
    printf("Multiply %d, %d, %d by %d via adds and streams\n", as[0], as[1], as[2], b);
    for (int i = 0; i < b; i++) {
        int vals[3];
        if (i == 0) {
            vals[0] = 0;
            vals[1] = 0;
            vals[2] = 0;
        } else {
            vals[0] = stream_in();
            vals[1] = stream_in();
            vals[2] = stream_in();
        }

        vals[0] = as[0];
        vals[1] = as[1];
        vals[2] = as[2];

        if (i == b - 1) {
            printf("Final values are: %d, %d, %d\n", vals[0], vals[1], vals[2]);
        } else {
            printf("Current intermittent values are: %d, %d, %d\n", vals[0], vals[1], vals[2]);
            stream_out(vals[0]);
            stream_out(vals[1]);
            stream_out(vals[2]);
        }
    }
return 0;

}