#ifndef CLOCK_H
#define CLOCK_H

    /* Includes */
    #include <types.h>

    /* Defines */
    #define TIMER_CLICKS_IN_DAY 172799999   /* Number of timer ticks which make up 24 hours */

    /*
     * Initialize Timer
     */
    void timer_init();

    /*
     * Reads from the Timer
     */
    time_t timer_getTime();
    time_t timer_getMilli();

#endif

