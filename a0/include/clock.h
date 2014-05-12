#ifndef CLOCK_H
#define CLOCK_H

/* Includes */
#include <types.h>

/* Defines */
#define TIMER_CLICKS_IN_DAY 172799999   /* Number of timer ticks which make up 24 hours */

/*
 * timer_init: void
 * 
 * This sets settings for TIMER3 and starts it.
 */
void timer_init();

/*
 * timer_getTime: time_t
 *
 * Returns the time in Decaseconds.
 */
time_t timer_getTime();

/*
 * timer_getMilli: time_t
 *
 * Returns the time in Milliseconds.
 */
time_t timer_getMilli();

#endif

