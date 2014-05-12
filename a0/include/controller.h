#ifndef CONTROLLER_H
#define CONTROLLER_H

/* Define */
/* Masks for Sensor parsing */
#define SMASK1 1
#define SMASK2 2
#define SMASK3 4
#define SMASK4 8
#define SMASK5 16
#define SMASK6 32
#define SMASK7 64
#define SMASK8 128
/* Number of trains that can be waiting to reverse */
#define MAX_REVERSE_QUEUE 4

/*
 * system_init: void
 * 
 * Sets all static variables. Initialize speed for trains and
 * switches. 
 */
void system_init();

/*
 * system_on: void
 * system_off: void
 * 
 * Sends the on and off signal to train console.
 */
void system_on();
void system_off();

/*
 * system_quit: void
 * 
 * Sets flag to stop polling loop.
 */
void system_quit();

/*
 * system_status: void
 * 
 * Return the the polling loop flag (Wether system is still running).
 */
int system_status();

/*
 * train_speed: void
 *     int train_number - The ID of the train.
 *     int train_speed  - The speed of the train [0 - 14].
 *
 * Sends train signal to change speed.
 */
void train_speed(int train_number, int train_speed);

/*
 * switch_direction: void
 *     int switch_number     - The ID of the switch.
 *     char switch_direction - The direction of the switch [s/c].
 * 
 * Sends switch signal to change direction.
 */
void switch_direction(int switch_number, char switch_direction);

/*
 * train_reverse: void
 *     int train_number - The ID of the train. 
 *
 * Tells train to stop and change direction and continue.
 */
void train_reverse(int train_number);

/*
 * train_reverse_checkQueue: void
 *     time_t cur_time - The current time in decaseconds.
 * 
 * Checks if there are trains that are waiting to reverse direction
 * and proceeds to change them if timer is up.
 */
void train_reverse_checkQueue(time_t cur_time);

/*
 * sensor_check: int
 *     char sensor_read - The byte containing sensor response. 
 *
 * Parses sensor response and adds triggered sensor to list of
 * sensors to be displayed.
 */
int sensor_check(char sensor_read);

#endif

