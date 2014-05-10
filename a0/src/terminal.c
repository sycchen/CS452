#include <terminal.h>

/*
 * Function to initialize terminal
 */
void term_print() {
    bwprintf( COM2, "+-----------------------------------------------------------------------------------------------------------+" );
    bwprintf( COM2, "| ExpressOS >                                                                  +------+ +-----------------+ |" );
    bwprintf( COM2, "|                                                                              |      | |                 | |" );
    bwprintf( COM2, "|                                                                              |sensor| |    Switches     | |" );
    bwprintf( COM2, "|                                                                              |      | |                 | |" );
    bwprintf( COM2, "|                                                                              +------+ +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 01:  s | 02:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 03:  s | 04:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 05:  s | 06:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 07:  s | 08:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 09:  s | 10:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 11:  s | 12:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 13:  s | 14:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 15:  s | 16:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 17:  s | 18:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 99:  s | 9A:  s | |" );
    bwprintf( COM2, "|                                                                              |      | +--------+--------+ |" );
    bwprintf( COM2, "|                                                                              |      | | 9C:  s | 9B:  s | |" );
    bwprintf( COM2, "|                                                                              +------+ +--------+--------+ |" );
    bwprintf( COM2, "+-----------------------------------------------------------------------------------------------------------+" );
}
