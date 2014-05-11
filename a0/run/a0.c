#include <ts7200.h>
#include <types.h>
#include <bwio.h>
#include <io.h>
#include <clock.h>
#include <parser.h>
#include <controller.h>
#include <buffer.h>
#include <terminal.h>

/*
 * Error Check
 */
void errorReset() {
    int *error = (int *)( UART1_BASE + UART_RSR_OFFSET );
    *error = 0;
}
void errorCheck() {
    int *error = (int *)( UART1_BASE + UART_RSR_OFFSET );
    int isError = 0;

    if (*error & OE_MASK) {
        bwprintf(COM2, "Overrun Error\r");
        system_quit();
        isError = 1;
    }
    if (*error & BE_MASK) {
        bwprintf(COM2, "Break Error\r");
        system_quit();
        isError = 1;
    }
    if (*error & PE_MASK) {
        bwprintf(COM2, "Parity Error\r");
        system_quit();
        isError = 1;
    }
    if (*error & FE_MASK) {
        bwprintf(COM2, "Framing Error\r");
        system_quit();
        isError = 1;
    }
    
    if (isError == 1) {
        bwgetc(COM2);
        errorReset();
    }
}

/*
 * Polling Loop
 */
int main( int argc, const char* argv[] ) {
    errorReset();

    /* Initialize io */
    char data_read, sensor_read;
    io_initbuffer();
    io_setup( COM1, OFF, 2400 );
    io_setup( COM2, OFF, 115200 );
    bwprintf( COM2, "ExpressOS Starting.\r" );
    
    /* Initialize parcer.c */
    state_init();

    /* Initialize Trains and switches and sensor settings */
    bwprintf(COM2, "Initializing train and switches and sensors.\r");
    system_init();

    /* Initialize Terminal Screen */
    term_init();
    
    /* Initialize Time and Timer */
    time_t elapsed_time = 0;
    timer_init();

    /* Starting Sensors */
    io_putc(COM1, (char)192);
    io_putc(COM1, (char)133);
    errorCheck();

    /* Run instructions (Polling Loop) */
    while (system_status()) {
        /* Check Timer */
        if (elapsed_time != timer_getTime()) {
            elapsed_time = timer_getTime();
            
            /* Update screen */
            time_print(elapsed_time);
            sensor_print();

            /* Check to see if any trains need to reverse */
            train_reverse_checkQueue(elapsed_time);
        }
        
        /* Read Check */
        if (io_canGet( COM1 ) > 0) {
            sensor_read = (char)io_getc( COM1 );
            checkSensors(sensor_read);
        }
        if (io_canGet( COM2 ) > 0) {
            data_read = (char)io_getc( COM2 );
            runState(data_read);
        }
        
        /* Write Check */
        if (io_canPut( COM1 ) > 0) {
            io_putc_from_buf( COM1 );
        }
        if (io_canPut( COM2 ) > 0) {
            io_putc_from_buf( COM2 );
        }

        /* Error Checking */
        errorCheck();
    }

    /* Clear screen */
    term_kill();
    
    return 0;
}

