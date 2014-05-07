#include <ts7200.h>
#include <types.h>
#include <bwio.h>
#include <clock.h>

/*
 * Initialize Timer
 */
void timer_init() {
    *((int *)( TIMER3_BASE + CTRL_OFFSET )) = 0x00000000;               /* Resets Timer */
    *((int *)( TIMER3_BASE + LDR_OFFSET )) |= TIMER_CLICKS_IN_DAY;      /* Load timer with an hour */
    *((int *)( TIMER3_BASE + CTRL_OFFSET )) |= ENABLE_MASK + MODE_MASK; /* Start Timer */
}

/*
 * Reads from the Timer
 */
time_t timer_getTime() {
    return (time_t)TIMER_CLICKS_IN_DAY - (time_t)(*((int *)( TIMER3_BASE + VAL_OFFSET )))/2
}

/*
 * Prints the formatted version of the given time
 */
void timer_printTime(time_t elapsed_time) {
    /* Time Calculations */
    int milliseconds = (elapsed_time % 1000);
    int seconds = (elapsed_time % 60000)/1000;
    int minutes = (elapsed_time % 360000)/60000; 
    int hours = elapsed_time/3600000;

    /* Print */
    char *padding_milliseconds = "";
    if (milliseconds < 10) {
        padding_milliseconds = "00";
    } else if (milliseconds < 100) {
        padding_milliseconds = "0";
    }
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

    bwprintf( COM2, "Time: %s%u:%s%u:%s%u:%s%u", 
              padding_hours, hours, padding_minutes, minutes, 
              padding_seconds, seconds, padding_milliseconds, milliseconds);
}
