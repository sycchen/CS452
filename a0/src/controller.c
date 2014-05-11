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
