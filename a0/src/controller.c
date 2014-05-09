#include <ts7200.h>
#include <bwio.h>
#include <controller.h>

/* Sends signal to train console */
static void send(char out) {
    int *flags;
    flags = (int *)( UART1_BASE + UART_FLAG_OFFSET );

    while ( !( *flags & (CTS_MASK)) || ( *flags & (TXBUSY_MASK) ) ) ;
    bwputc( COM1, out );
}

/* Tells the train system to turn on */
void system_on() {
    send((char)0x60);
}

/* Tells the train system to turn off */
void system_off() {
    send((char)0x61);
}

/* Set train speed */
void train_speed(int train_number, int train_speed) {
    send((char)train_speed);
    send((char)train_number);
}

/* Sets switch */
void switch_direction(int switch_number, char switch_direction) { 
    if (switch_direction == 'S' || switch_direction == 's') {
        send((char)0x21);
    } else if (switch_direction == 'C' || switch_direction == 'c') {
        send((char)0x22);
    } else {
        return;
    }
    send((char)switch_number);
    send((char)0x20);
}

/* Status used by main while loop */
static int status;

/* System Initialize Status */
void system_initialize() {
    status = 1;
}

/* Tells the console to quit */
void system_quit() {
    status = 0;;
}

/* Returns wether the system should quit or not */
int system_status() {
    return status;
}
