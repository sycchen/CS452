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
//        bwgetc(COM2);
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
    
    /* Initialize parcer */
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
    if (io_canGet( COM1 ) > 0) io_getc( COM1 );
    io_putc(COM1, (char)192);
    io_putc(COM1, (char)133);
    errorCheck();

    /* Run instructions (Polling Loop) */
    //int test = 0; //1500-1600 cycles through polling loop
    //time_t test = 0; //9000-10000 clock cycles through polling loop
    //time_t test1 = 0;
    //time_t test2 = 0; 5ms
    //time_t test3 = 0;
    //time_t test4 = 0;
    //time_t test5 = 0; < 1ms
    while (system_status()) {
        /* Test */
        //test++;        
        //test1 = timer_getMilli();
        //if (test2 < test1 - test3) test2 = test1 - test3;
        //test3 = test1;            
        //test4++;
        //test5 += test1 - test3;


        /* Check Timer */
        if (elapsed_time != timer_getTime()) {
            elapsed_time = timer_getTime();
            
            /* Update screen */
            time_print(elapsed_time);
            sensor_print();

            /* Check to see if any trains need to reverse */
            train_reverse_checkQueue(elapsed_time);

            /* Test */
            //io_printf(COM2, "\x1b[s\x1b[H%d::%d\x1b[u", test2, test5/test4);
            //io_printf(COM2, "\x1b[s\x1b[H%d\x1b[u", test);
            //test = 0;
        }
        
        /* Read Check */
        if (io_canGet( COM1 ) > 0) {
            sensor_read = (char)io_getc( COM1 );
            if (sensor_check(sensor_read)) {
                //io_printf(COM2, "\x1b[s\x1b[H%d\x1b[u", test);
                //test = 0;
            }
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

