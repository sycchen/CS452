#include <bwio.h>
#include <iparser.h>
#include <controller.h>

/* Run's the state giving it a char.
 * Will return the next state */
struct state runState(char in, struct state *curState) {
    bwputc( COM2, in );
    bwputc( COM2, (char)(curState->fnid + 48) );

    struct state new_state;

    int new_fnid = -1;
    switch(curState->fnid) {
        case 0:
    bwputc( COM2, '0' );
            new_fnid = initialState(in);
            break;
        case 1:
    bwputc( COM2, '1' );
            new_fnid = state1(in);
            break;
        case 2:
    bwputc( COM2, '2' );
            new_fnid = state2(in);
            break;
        case 3:
    bwputc( COM2, '3' );
            new_fnid = state3(in);
            break;
        case 4:
    bwputc( COM2, '4' );
            new_fnid = state4(in);
            break;
        case 5:
    bwputc( COM2, '5' );
            new_fnid = state5(in);
            break;
        default:
    bwputc( COM2, '-' );
            break;
    }

    if (in == '\n') {
        new_state = (struct state){ 0, 0 };
    } else {
        new_state = (struct state){ new_fnid, curState };
    }
    
    return new_state;
}

/* The starting state */
int initialState(char in) {
    bwputc( COM2, 'i' );
    switch( in ) {
        case 'o':
            return 1;
        case 'q':
            return 5;
        case ' ':
            return 0;
        default:
            return -1;
    }
}

/* State where it can't lead to another command */
int failState(char in) {
    bwputc( COM2, '-' );
    return -1;
}

/* O */
int state1(char in) {
    bwputc( COM2, 'o' );
    switch( in ) {
        case 'n':
            return 2;
        case 'f':
            return 3;
        default:
            return -1;
    } 
}

/* ON */
int state2(char in) {
    bwputc( COM2, 'n' );
    switch( in ) {
        case ' ':
            return 2;
        case '\n':
            system_on();
            return 0;
        default:
            return -1;
    }
}

/* OF */
int state3(char in) {
    bwputc( COM2, 'f' );
    switch( in ) {
        case 'f':
            return 4;
        default:
            return -1;
    }
}

/* OFF */
int state4(char in) {
    bwputc( COM2, 'f' );
    switch( in ) {
        case ' ':
            return 4;
        case '\n':
            system_off();
            return 0;
        default:
            return -1;
    }
}

/* Q */
int state5(char in) {
    bwputc( COM2, 'q' );
    switch( in ) {
        case ' ':
            return 5;
        case '\n':
            system_quit();
            return 0;
        default:
            return -1;
    }
}

