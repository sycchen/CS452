#include <ts7200.h>
#include <io.h>
#include <bwio.h>
#include <controller.h>
#include <terminal.h>

/* Initialize all */
void system_init() {
    /* Turn System On */
    bwputc( COM1, (char)0x60 );
    
    /* Initialize Switches */
    int i;
    for (i = 1; i <= 18; i++) {
        bwputc( COM1, (char)0x21 );
        bwputc( COM1, (char)i );
        bwputc( COM1, (char)0x20 );
    }

    bwputc( COM1, (char)0x21 );
    bwputc( COM1, (char)0x99 );
    bwputc( COM1, (char)0x20 );

    bwputc( COM1, (char)0x21 );
    bwputc( COM1, (char)0x9a );
    bwputc( COM1, (char)0x20 );

    bwputc( COM1, (char)0x21 );
    bwputc( COM1, (char)0x9b );
    bwputc( COM1, (char)0x20 );

    bwputc( COM1, (char)0x21 );
    bwputc( COM1, (char)0x9c );
    bwputc( COM1, (char)0x20 );
}

/* Tells the train system to turn on */
void system_on() {
    io_putc( COM1, (char)0x60 );
}

/* Tells the train system to turn off */
void system_off() {
    io_putc( COM1, (char)0x61 );
}

/* Set train speed */
void train_speed(int train_number, int train_speed) {
    io_putc( COM1, (char)train_speed );
    io_putc( COM1, (char)train_number );
}

/* Reverse */
#define MAX_REVERSE_QUEUE 4;
static int reverse_time[MAX_REVERSE_QUEUE] = { 0 };
static int reverse_train[MAX_REVERSE_QUEUE] = { 0 };
void reverse(int train_number) {
    train_speed(train_number, 0);

    /* Throw in queue */
    int i;
    for (i = MAX_REVERSE_QUEUE - 1; i > 0; i++) {
        reverse_time[i] = reverse_time[i-1];
        reverse_train[i] = reverse_train[i-1];
    }
    reverse_train[i] = train_number;
}

/* Run reversed trains */
void reverse_checkQueue(int cur_time) {
    int i;
    for (i = 0; i < MAX_REVERSE_QUEUE; i++) { 
        if (reverse_train[i] == 0) {
            return;
        } else if (reverse_time[i] == 0) {
            reverse_time[i] = cur_time;
        } else if ((reverse_time[i] + 10) < cur_time) {
            io_putc( COM1, (char)15);
            reverse_time[i] = 0;
            reverse_train[i] = 0;
        }
    }
}

/* Sets switch */
void switch_direction(int switch_number, char switch_direction) { 
    if (switch_direction == 'S' || switch_direction == 's') {
        io_putc( COM1, (char)0x21 );
    } else if (switch_direction == 'C' || switch_direction == 'c') {
        io_putc( COM1, (char)0x22 );
    } else {
        return;
    }
    io_putc( COM1, (char)switch_number );
    io_putc( COM1, (char)0x20 );

    switch_print( switch_number, switch_direction );
}

/* Status used polling loop */
static int status = 0;

/* System Initialize Status */
void system_initialize() {
    status = 1;

    int i;
    for (i = 0; i < MAX_REVERSE_QUEUE; i++) {
        reverse_time[i] = 0;
        reverse_train[i] = 0;
    }
}

/* Tells the console to quit */
void system_quit() {
    status = 0;;
}

/* Returns wether the system should quit or not */
int system_status() {
    return status;
}
