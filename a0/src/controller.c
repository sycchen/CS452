#include <bwio.h>
#include <controller.h>

/* Sends signal to train console */
void send(char out) {
    int *flags;
    flags = (int *)( UART1_BASE + UART_FLAG_OFFSET );

    while ( ( *flags & (CTS_MASK + TXBUSY_MASK) ) ) ;
    bwputc( COM1, out );
}

/* Tells the train system to turn on */
void system_on() {
    send((char)0x60);
}

/* Tells the train system to turn off */
void system_off() {
    send(char)0x61);
}

/* Set train speed */
void train_speed() {
    send((char)0x20);
    send((char)0x2f);
}

/* Status used by main while loop */
int status = 1;

/* Tells the console to quit */
void system_quit() {
    status = 0;;
}

/* Returns wether the system should quit or not */
int system_status() {
    return status;
}
