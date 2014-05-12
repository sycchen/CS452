#ifndef TERMINAL_H
#define TERMINAL_H

/* Include */
#include <clock.h>

/*
 * term_init: void
 * 
 * Initializes required variables and prints the start screen.
 *
 * term_kill: void
 *
 * Resets the terminal.
 */
void term_init();
void term_kill();

/*
 * sensor_print: void
 * 
 * Prints sensor in proper position.
 *
 * sensor_add: void
 *     int sensor - The sensor's ID.
 *
 * Adds a sensor to be printed.
 */
void sensor_print();
void sensor_add(int sensor);

/*
 * input_print: void
 * 
 * Prints the decoration required to look good while scrolling on
 * newline.
 */
void input_print();

/*
 * switch_print: void
 *     int switch_number     - The switch ID.
 *     char switch_driection - The direction of switch.
 * 
 * Updates the switch table.
 */
void switch_print(int switch_number, char switch_direction);

/*
 * time_print: int
 *     int elapsed_time - Current time
 * 
 * Updates the displayed time.
 */
void time_print(time_t elapsed_time);
    
#endif


