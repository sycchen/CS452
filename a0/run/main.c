#include <ts7200.h>
#include <types.h>
#include <bwio.h>

#define TIMER_CLICKS_IN_DAY 172799999

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
		elapsed_time = (TIMER_CLICKS_IN_DAY - (int)(*timer_read))/2;

		/* Test - Print Time */
		int milliseconds = (elapsed_time % 1000);
		int seconds = ((elapsed_time % 60000) - milliseconds)/1000;
		int minutes = ((elapsed_time % 360000) - milliseconds - seconds)/60000; 
		int hours = (elapsed_time - milliseconds - seconds - minutes)/3600000;
		
		if (milliseconds < 10) {
		
		} else if (milliseconds < 100) {

		} else if (milliseconds < 1000) {

		}
		if (second < 10) {

		}
		if (minutes < 10) {
		
		}
		if (hours < 10) {
		
		}


bwprintf( COM2, "Time: %d:%d:%d:%d\n", hours, minutes, seconds, milliseconds);

		/* Check Buffer */


	}

	return 0;
}



