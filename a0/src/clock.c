#include <ts7200.h>
#include <types.h>
#include <io.h>
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
    return ((((time_t)TIMER_CLICKS_IN_DAY - (time_t)(*((int *)( TIMER3_BASE + VAL_OFFSET ))))/2)/100);
}

/*
 * Prints the formatted version of the given time
 */
void timer_printTime(time_t elapsed_time) {
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

    io_printf( COM2, "Time: %s%u:%s%u:%s%u:%u", 
               padding_hours, hours, padding_minutes, minutes, 
               padding_seconds, seconds, milliseconds);
}

