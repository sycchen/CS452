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
 * Sensor
 */
#define SMASK1 1
#define SMASK2 2
#define SMASK3 4
#define SMASK4 8
#define SMASK5 16
#define SMASK6 32
#define SMASK7 64
#define SMASK8 128

static int sensor_id = 0;
static int sensor_count = 0;
static int sensor_temp = 0;
static int count = 0;
void checkSensors(char sensor_read) {
    /* read sensor */    
    if (sensor_read & SMASK8) {
        sensor_add(sensor_id + sensor_count + 1);  
    } if (sensor_read & SMASK7) {
        sensor_add(sensor_id + sensor_count + 2 + sensor_temp);  
    } if (sensor_read & SMASK6) {
        sensor_add(sensor_id + sensor_count + 3 + sensor_temp);  
    } if (sensor_read & SMASK5) {
        sensor_add(sensor_id + sensor_count + 4 + sensor_temp);  
    } if (sensor_read & SMASK4) {
        sensor_add(sensor_id + sensor_count + 5 + sensor_temp);  
    } if (sensor_read & SMASK3) {
        sensor_add(sensor_id + sensor_count + 6 + sensor_temp);  
    } if (sensor_read & SMASK2) {
        sensor_add(sensor_id + sensor_count + 7 + sensor_temp);  
    } if (sensor_read & SMASK1) {
        sensor_add(sensor_id + sensor_count + 8 + sensor_temp);  
    }

    /* Which sensor is this */
    if (sensor_count == 8) {
        sensor_temp = 0;
        sensor_count = 0;
        sensor_id += 0x100;
    } else {
        sensor_temp = 6;
        sensor_count = 8;
    }
    
    if (sensor_id > 0xe00) {
        sensor_id = 0xa00;
    }

    count++;
    if (count == 10) {
        count = 0;
        io_putc(COM1, (char)133);
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
    bwprintf( COM2, "System ExpressOS Starting.\r" );
    
    /* Initialize Loop */
    bwprintf( COM2, "Setting loop de loop.\r" );
    system_initialize();
   
    /* Initialize Parser */
    bwprintf( COM2, "Initialize Parser.\r" );
    state_init();

    /* Initialize Trains and switches and sensors*/
    bwprintf(COM2, "Initializing train and switches and sensors.\r");
    system_init();
    sensor_id = 0xe00;
    sensor_count = 8;
    sensor_temp = 6;
    count = 0;

    /* Initialize Screen */
    bwprintf( COM2, "I CAN SEE.\r" );
    sensor_init();
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
            time_print(elapsed_time);
            sensor_print();
            reverse_checkQueue(elapsed_time);
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

