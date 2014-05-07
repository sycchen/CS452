#include <ts7200.h>
#include <types.h>
#include <bwio.h>
#include <clock.h>

// /*
//  * Circular Buffer
//  */
// typedef struct {
//     int size;		/* maximum number of elements */
//     int start;		 read index (oldest) 
//     int end;		/* write index (newest) */
//     int *elements;	/* pointer to list of elements */
// } cbuf;

/*
 * Polling Loop
 */
int main( int argc, const char* argv[] ) {
    /* Initialize Time and Timer */
    time_t elapsed_time = 0;
    timer_init();

    /* Initialize bwio */
    bwsetfifo( COM2, OFF );

    /* Hide cursor, clear screen, set cursor to home */
    bwprintf( COM2, "\x1b[?25l \x1b[2J \x1b[H");

    /* Run instructions (Polling Loop) */
    while (1) {
        /* Check Timer */
        elapsed_time = timer_getTime();

        /* Print Time */
        bwprintf( COM2, "\x1b[H");
        timer_printTime(elapsed_time);

        /* Check Buffer */

    }

    return 0;
}
