#include <ts7200.h>
#include <types.h>
#include <bwio.h>
#include <io.h>
#include <clock.h>
#include <parser.h>
#include <controller.h>
#include <buffer.h>

/*
 * Polling Loop
 */
int main( int argc, const char* argv[] ) {
    
    /* Initialize Loop */
    system_initialize();

    /* Initialize io */
    char data_read;
    io_initbuffer();
    io_setfifo( COM1, OFF );
    io_setspeed( COM1, 2400 );
    io_setfifo( COM2, OFF );

    /* Initialize Time and Timer */
    time_t elapsed_time = 0;
    timer_init();


    /* Initialize Scren */
    bwprintf( COM2, "\x1b[2J \x1b[H");
//    bwprintf( COM2, "\x1b[?25l \x1b[2J \x1b[H");

    /* Run instructions (Polling Loop) */
    while (system_status()) {
        /* Check Timer */
        if (elapsed_time != timer_getTime()) {
            bwprintf( COM2, "\x1b[?25l\x1b[H");
            timer_printTime(elapsed_time);
            bwprintf( COM2, "\x1b[?25h");
        }
        
        /* Write Check */
        if (io_canPut( COM1 ) > 0) {
            io_putc_from_buf( COM1 );
        }
        if (io_canPut( COM2 ) > 0) {
            int io_putc_from_buf( COM2 );
        }

        /* Read Check */
        /*
        if (io_canGet( COM2 ) > 0) {
            ???
            io_getc( COM2 );
        }
        */
        if (io_canGet( COM2 )) {
            data_read = (char)io_getc( COM2 );
            runState(data_read);
        }
    }

    return 0;
}
