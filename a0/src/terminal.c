#include <terminal.h>
#include <bwio.h>
#include <types.h>
#include <io.h>

/*
 * Function to initialize terminal
 */
void term_init() {
    /* Clear screen and set cursor position to 0,0 and reset scrolling and show cursor */
    bwprintf( COM2, "\x1b[2J\x1b[H\x1b[r\x1b[?25h");

    /* Print terminal */
    bwprintf( COM2, "+-------------------------------------------------------------------------+\r" );
    bwprintf( COM2, "| +-------------------+ +-----------------------------------------------+ |\r" );
    bwprintf( COM2, "| | Timer: 00:00:00:0 | |                   Switches                    | |\r" );
    bwprintf( COM2, "| +-------------------+ +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| +-------------------+ | 01: s | 02: s | 03: s | 04: s | 05: s | 06: s | |\r" );
    bwprintf( COM2, "| |      Sensor       | +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| +---------+---------+ | 07: s | 08: s | 09: s | 10: s | 11: s | 12: s | |\r" );
    bwprintf( COM2, "| |   00    |   00    | +-------+-------+-------+-------+-------+-------+ |\r" );
    bwprintf( COM2, "| |   00    |   00    | | 13: s | 14: s | 15: s | 16: s | 17: s | 18: s | |\r" );
    bwprintf( COM2, "| |   00    |   00    | +-------+---+---+-------+-------+---+---+-------+ |\r" );
    bwprintf( COM2, "| |   00    |   00    | | 0x99: s   | 0x9a: s   | 0x9b: s   | 0x9c: s   | |\r" );
    bwprintf( COM2, "| +-------------------+ +-----------+-----------+-----------+-----------+ |\r" );
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
 * Function to reset terminal
 */
void term_kill() {
    bwprintf( COM2, "\x1b[H\x1b[J\x1b[r" );
}

/*
 * Function to add a sensor
 */
static int sensor_display[8] = {0};
static int sensor_flag = 1;
void sensor_init(int sensor) {
    sensor_display[0] = 0;
    sensor_display[1] = 0;
    sensor_display[2] = 0;
    sensor_display[3] = 0;
    sensor_display[4] = 0;
    sensor_display[5] = 0;
    sensor_display[6] = 0;
    sensor_display[7] = 0;
    sensor_flag = 1;
}
void sensor_print() {
    if (sensor_flag) {
        char *padding[8];

        int i;
        for (i = 0; i < 8; i++) {
            if (sensor_display[i] < 16) padding[i] = "0";
            else padding[i] = "";
        }

        io_printf( COM2, "\x1b[s" );
        io_printf( COM2, "\x1b[8;7H%s%x\x1b[9;7H%s%x\x1b[10;7H%s%x\x1b[11;7H%s%x",
                   padding[0], sensor_display[0], 
                   padding[1], sensor_display[1], 
                   padding[2], sensor_display[2], 
                   padding[3], sensor_display[3] ); 
        io_printf( COM2, "\x1b[8;17H%s%x\x1b[9;17H%s%x\x1b[10;17H%s%x\x1b[11;17H%s%x",
                   padding[4], sensor_display[4],
                   padding[5], sensor_display[5],
                   padding[6], sensor_display[6],
                   padding[7], sensor_display[7] ); 
        io_printf( COM2, "\x1b[u" );
        sensor_flag = 0;
    }
}
void sensor_add(int sensor) {
    if (sensor == sensor_display[0]) return;

    int i;
    for (i = 7; i > 0; i--) {
       sensor_display[i] = sensor_display[i-1]; 
    }
    sensor_display[0] = sensor;
    sensor_flag = 1;
}

/*
 * Function to add a input line
 */
void input_print() {
    io_printf( COM2, "\r| ExpressOS > \x1b[60C|\x1b[61D" );
}

/*
 * Function to change a switch display
 */
void switch_print(int switch_number, char switch_direction) {
    io_printf( COM2, "\x1b[s" );
    
    switch( switch_number ) {
        case 1:
            io_printf( COM2, "\x1b[5;31H" );
            break;
        case 2:
            io_printf( COM2, "\x1b[5;39H" );
            break;
        case 3:
            io_printf( COM2, "\x1b[5;47H" );
            break;
        case 4:
            io_printf( COM2, "\x1b[5;55H" );
            break;
        case 5:
            io_printf( COM2, "\x1b[5;63H" );
            break;
        case 6:
            io_printf( COM2, "\x1b[5;71H" );
            break;
        case 7:
            io_printf( COM2, "\x1b[7;31H" );
            break;
        case 8:
            io_printf( COM2, "\x1b[7;39H" );
            break;
        case 9:
            io_printf( COM2, "\x1b[7;47H" );
            break;
        case 10:
            io_printf( COM2, "\x1b[7;55H" );
            break;
        case 11:
            io_printf( COM2, "\x1b[7;63H" );
            break;
        case 12:
            io_printf( COM2, "\x1b[7;71H" );
            break;
        case 13:
            io_printf( COM2, "\x1b[9;31H" );
            break;
        case 14:
            io_printf( COM2, "\x1b[9;39H" );
            break;
        case 15:
            io_printf( COM2, "\x1b[9;47H" );
            break;
        case 16:
            io_printf( COM2, "\x1b[9;55H" );
            break;
        case 17:
            io_printf( COM2, "\x1b[9;63H" );
            break;
        case 18:
            io_printf( COM2, "\x1b[9;71H" );
            break;
        case 153:
            io_printf( COM2, "\x1b[11;33H" );
            break;
        case 154:
            io_printf( COM2, "\x1b[11;45H" );
            break;
        case 155:
            io_printf( COM2, "\x1b[11;57H" );
            break;
        case 156:
            io_printf( COM2, "\x1b[11;69H" );
            break;
    }
    io_putc( COM2, switch_direction );
    io_printf( COM2, "\x1b[u" );
}

/*
 * Print time
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
