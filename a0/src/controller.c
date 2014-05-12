#include <ts7200.h>
#include <io.h>
#include <bwio.h>
#include <controller.h>
#include <terminal.h>

/* Variables global to file */
static int status = 0;
static int sensor_id = 0;
static int sensor_count = 0;
static int count = 0;

static int reverse_time[MAX_REVERSE_QUEUE] = { 0 };
static int reverse_train[MAX_REVERSE_QUEUE] = { 0 };
static int train_speed_array[52] = { 0 };

/* Initialize all */
void system_init() {
    /* Initialize Status so polling loop will run */
    status = 1;

    /* Initialize reverse arrays */
    int i;
    for (i = 0; i < MAX_REVERSE_QUEUE; i++) {
        reverse_time[i] = 0;
        reverse_train[i] = 0;
    }

    /* Initialize sensor variables */
    sensor_id = 0xa00;
    sensor_count = 0;
    count = 0;

    /* Turn System On */
    bwputc( COM1, (char)0x60 );
    
    /* Initialize Trains */
    for (i = 0; i < 52; i++) {
        train_speed_array[i] = 0;
    }
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)43 );
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)45 );
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)47 );
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)48 );
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)49 );
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)50 );
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)51 );

    /* Initialize Switches */
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

/* System functions */
void system_on() {
    io_putc( COM1, (char)0x60 );
}
void system_off() {
    io_putc( COM1, (char)0x61 );
}
void system_quit() {
    status = 0;
    bwputc( COM1, (char)0 );
    bwputc( COM1, (char)43 );
    bwputc( COM1, (char)0 );
    bwputc( COM1, (char)45 );
    bwputc( COM1, (char)0 );
    bwputc( COM1, (char)47 );
    bwputc( COM1, (char)0 );
    bwputc( COM1, (char)48 );
    bwputc( COM1, (char)0 );
    bwputc( COM1, (char)49 );
    bwputc( COM1, (char)0 );
    bwputc( COM1, (char)50 );
    bwputc( COM1, (char)0 );
    bwputc( COM1, (char)51 );
}
int system_status() {
    return status;
}

/* Train functions */
void train_speed(int train_number, int train_speed) {
    io_putc( COM1, (char)train_speed );
    io_putc( COM1, (char)train_number );
    if (train_speed < 15 && train_speed >= 0 && train_number < 52 && train_number >= 0) train_speed_array[train_number] = train_speed;
}
void train_reverse(int train_number) {
    io_putc( COM1, (char)0 );
    io_putc( COM1, (char)train_number );

    /* Throw in queue */
    int i;
    for (i = MAX_REVERSE_QUEUE - 1; i > 0; i--) {
        reverse_time[i] = reverse_time[i-1];
        reverse_train[i] = reverse_train[i-1];
    }
    reverse_train[i] = train_number;
}
void train_reverse_checkQueue(int cur_time) {
    int i;
    for (i = 0; i < MAX_REVERSE_QUEUE; i++) { 
        if (reverse_train[i] == 0) {
            return;
        } else if (reverse_time[i] == 0) {
            reverse_time[i] = cur_time;
        } else if ((reverse_time[i] + 15) < cur_time) {
            train_speed(reverse_train[i], 15);
            train_speed(reverse_train[i], train_speed_array[reverse_train[i]]);
            reverse_time[i] = 0;
            reverse_train[i] = 0;
        }
    }
}

/* Switch functions */
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

/* Sensor */
int sensor_check(char sensor_read) {
    /* read sensor */    
    if (sensor_read & SMASK8) {
        sensor_add(sensor_id + (sensor_count * 8) + 1);  
    } if (sensor_read & SMASK7) {
        sensor_add(sensor_id + (sensor_count * 14) + 2);  
    } if (sensor_read & SMASK6) {
        sensor_add(sensor_id + (sensor_count * 14) + 3);  
    } if (sensor_read & SMASK5) {
        sensor_add(sensor_id + (sensor_count * 14) + 4);  
    } if (sensor_read & SMASK4) {
        sensor_add(sensor_id + (sensor_count * 14) + 5);  
    } if (sensor_read & SMASK3) {
        sensor_add(sensor_id + (sensor_count * 14) + 6);  
    } if (sensor_read & SMASK2) {
        sensor_add(sensor_id + (sensor_count * 14) + 7);  
    } if (sensor_read & SMASK1) {
        sensor_add(sensor_id + (sensor_count * 14) + 8);  
    }

    /* Which sensor is this */
    if (sensor_count == 1) {
        sensor_count = 0;
        sensor_id += 0x100;
    } else {
        sensor_count = 1;
    }
    
    if (sensor_id > 0xe00) {
        sensor_id = 0xa00;
    }

    /* Count for request */
    count++;
    if (count == 10) {
        count = 0;
        io_putc(COM1, (char)133);
        return 1;
    }
    return 0;
}

