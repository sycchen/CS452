#include <ts7200.h>
#include <types.h>
#include <bwio.h>

#define TIMER_CLICKS_IN_DAY = 172800000 - 1;

/* 
 * Circular Buffer
 */
typedef struct {
	int size;		/* maximum number of elements */
	int start;		/* read index (oldest) */
	int end;		/* write index (newest) */
	int *elements;	/* pointer to list of elements */
} cbuf;

/*
 * Polling Loop
 */
int main( int argc, const char* argv[] ) {
	/* Initialize Time */
	time_t elapsed_time = 0;

	/* Initialize bwio */
	bwsetfifo( COM2, OFF );

	/* Initialize Timer 1 */
	int *timer_ctrl = (int *)( TIMER3_BASE + CTRL_OFFSET );
	int *timer_load = (int *)( TIMER3_BASE + LDR_OFFSET );
	int *timer_read = (int *)( TIMER3_BASE + VAL_OFFSET );
	*timer_ctrl = 0x00000000;				/* Resets Timer */
	*timer_load |= TIMER_CLICKS_IN_DAY;  	/* Load timer with an hour */
	*timer_ctrl |= ENABLE_MASK + MODE_MASK; /* Start Timer */


	/* Run instruction */
	while (1) {
		/* Check Timer */
		elapsed_time = (time_t)(TIMER_CLICKS_IN_DAY - (int)(*timer_read))/2;

		/* Test - Print Time */
		int milliseconds = (elapsed_time % 86400);
		int seconds = ((elapsed_time % 1440) - milliseconds)/1000;
		int minutes = ((elapsed_time % 24) - milliseconds - seconds)/60000; 
		int hours = (elapsed_time - milliseconds - seconds - minutes)/3600000;
		bwprintf( COM2, "Time: %02d:%02d:%02d:%04d", hours, minutes, seconds, milliseconds );

		/* Check Buffer */


	}

	return 0;
}



