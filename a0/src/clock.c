#include <ts7200.h>
#include <types.h>
#include <io.h>
#include <bwio.h>
#include <clock.h>

/* Initialize Timer */
void timer_init() {
    *((int *)( TIMER3_BASE + LDR_OFFSET )) = 0x00000000;                /* Reset */
    *((int *)( TIMER3_BASE + CTRL_OFFSET )) = 0x00000000;               /* Reset */
    *((int *)( TIMER3_BASE + LDR_OFFSET )) |= TIMER_CLICKS_IN_DAY;      /* Load timer with an hour */
    *((int *)( TIMER3_BASE + CTRL_OFFSET )) |= ENABLE_MASK + MODE_MASK; /* Start Timer */
}

/* Reads from the Timer */
time_t timer_getTime() {
    time_t timer = *((time_t *)( TIMER3_BASE + VAL_OFFSET ));
    return (((time_t)TIMER_CLICKS_IN_DAY - timer)/200);
}
time_t timer_getMilli() {
    time_t timer = *((time_t *)( TIMER3_BASE + VAL_OFFSET ));
    return (((time_t)TIMER_CLICKS_IN_DAY - timer)/2);
}
