#include <ts7200.h>
#include <types.h>
#include <bwio.h>
#include <io.h>
#include <clock.h>
#include <iparser.h>
#include <controller.h>

/*
 * Polling Loop
 */
int main( int argc, const char* argv[] ) {
    /* Initialize IO variables */
    char data_read;
    state cur_state = 0;


    /* Initialize Time and Timer */
    time_t elapsed_time = 0;
    timer_init();

    /* Initialize bwio */
    bwsetfifo( COM2, OFF );
    bwsetspeed( COM1, 2400 );
    bwsetfifo( COM1, OFF );

    /* Hide cursor, clear screen, set cursor to home */
//    bwprintf( COM2, "\x1b[?25l \x1b[2J \x1b[H");

    /* Run instructions (Polling Loop) */
    while (system_status()) {
        /* Check Timer */
        elapsed_time = timer_getTime();

        /* Print Time */
//        bwprintf( COM2, "\x1b[?25l\x1b[H");
//        timer_printTime(elapsed_time);
//        bwprintf( COM2, "\x1b[?25h");

        /* Read Check */
//        if (io_canGet( COM2 )) {
//            data_read = io_getc( COM2 );
	    data_read = 0;
	    data_read = (char)bwgetc( COM2 );
        cur_state = runState(data_read, cur_state);

//        }
    }

    return 0;
}
