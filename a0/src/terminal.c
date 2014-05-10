#include <terminal.h>
#include <bwio.h>
#include <types.h>
#include <io.h>

/*
 * Function to initialize terminal
 */
void term_print() {
    /* Clear screen and set cursor position to 0,0 and reset scrolling */
    bwprintf( COM2, "\x1b[2J\x1b[H\x1b[r");

    /* Print terminal */
    bwprintf( COM2, "+-------------------------------------------------------------------------+\r" );
    bwprintf( COM2, "| +-------------------+ +-----------------------------------------------+ |\r" );
    bwprintf( COM2, "| | Timer: 00:00:00:0 | |                   Switches                    | |\r" );
    bwprintf( COM2, "| +-------------------+ +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| +-------------------+ | 01: s | 02: s | 03: s | 04: s | 05: s | 06: s | |\r" );
    bwprintf( COM2, "| |      Sensor       | +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| +-------------------+ | 07: s | 09: s | 10: s | 11: s | 12: s | 13: s | |\r" );
    bwprintf( COM2, "| | 00    00    00    | +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| | 00    00    00    | | 07: s | 09: s | 10: s | 11: s | 12: s | 13: s | |\r" );
    bwprintf( COM2, "| | 00    00    00    | +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| | 00    00    00    | | 07: s | 09: s | 10: s | 11: s | 12: s | 13: s | |\r" );
    bwprintf( COM2, "| +-------------------+ +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| ExpressOS >                                                             |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "|                                                                         |\r" );
    bwprintf( COM2, "+-------------------------------------------------------------------------+\r" );

    /* Set up scrolling */
    bwprintf( COM2, "\x1b[13;25r" );

    /* Go to start position */
    bwprintf( COM2, "\x1b[13;15H" );
}

/*
 * Function to add a sensor
 */
void sensor_print() {

}

/*
 * Function to add a input line
 */
void input_print() {
    io_printf( COM2, "\r| ExpressOS > " );
}

/*
 * Function to change a switch display
 */
void switch_print() {

}

/*
 *
 */
void time_print(time_t elapsed_time) {
    /* Time Calculations */
    int milliseconds = (elapsed_time % 10);
    int seconds = (elapsed_time % 600)/10;
    int minutes = (elapsed_time % 3600)/600; 
    int hours = elapsed_time/36000;

    /* Print */
    char *padding_seconds = "";
    if (seconds < 10) {
        padding_seconds = "0";
    }
    char *padding_minutes = "";
    if (minutes < 10) {
        padding_minutes = "0";
    }
    char *padding_hours = "";
    if (hours < 10) {
        padding_hours = "0";
    }

    io_printf( COM2, "\x1b[s\x1b[3;12H%s%u:%s%u:%s%u:%u\x1b[u", 
               padding_hours, hours, padding_minutes, minutes, 
               padding_seconds, seconds, milliseconds);
}
