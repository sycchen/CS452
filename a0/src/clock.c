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
    time_t timer = *((time_t *)( TIMER3_BASE + VAL_OFFSET));
    return (((time_t)TIMER_CLICKS_IN_DAY - timer)/200);
}

/*
 * Debugging
 */ 
void printTime() {
    time_t timer = *((time_t *)( TIMER3_BASE + VAL_OFFSET));
    io_printf(COM2, "%u::%u\r", (time_t)TIMER_CLICKS_IN_DAY, timer);
}
