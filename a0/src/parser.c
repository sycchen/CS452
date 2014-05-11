#include <bwio.h>
#include <io.h>
#include <parser.h>
#include <controller.h>
#include <terminal.h>

/* Current State */
static state cur_state;

/* Fail state */
static int failState(char in) {
    switch( in ) {
        case '\r':
            input_print(0);
            io_printf(COM2, "Invalid Command")
            return 0;
        default:
            return -1;
    }
}

/* The starting state */
static int initialState(char in) {
    switch( in ) {
        case 'O':
        case 'o':
            return 1;
        case 'Q':
        case 'q':
            return 5;
        case 'T':
        case 't':
            return 6;
        case 'S':
        case 's':
            return 13;
        case 'R':
        case 'r':
            return 20;
        case ' ':
            return 0;
        default:
            return -1;
    }
}

/* O */
static int state1(char in) {
    switch( in ) {
        case 'N':
        case 'n':
            return 2;
        case 'F':
        case 'f':
            return 3;
        default:
            return -1;
    } 
}

/* ON */
static int state2(char in) {
    switch( in ) {
        case ' ':
            return 2;
        case '\r':
            system_on();
            return 0;
        default:
            return -1;
    }
}

/* OF */
static int state3(char in) {
    switch( in ) {
        case 'F':
        case 'f':
            return 4;
        default:
            return -1;
    }
}

/* OFF */
static int state4(char in) {
    switch( in ) {
        case ' ':
            return 4;
        case '\r':
            system_off();
            return 0;
        default:
            return -1;
    }
}

/* Q */
static int state5(char in) {
    switch( in ) {
        case ' ':
            return 5;
        case '\r':
            system_quit();
            return 0;
        default:
            return -1;
    }
}

/* T */
static int state6(char in) {
    switch( in ) {
        case 'R':
        case 'r':
            return 7;
        default:
            return -1;
    }   
}

/* TR */
static int state7(char in) {
    switch( in ) {
        case ' ':
            return 8;
        default:
            return -1;
    }       
}

/* TR_ */
static int state8(char in, int *arg1) {
    switch( in ) {
        case ' ':
            return 8;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg1 = bwa2d( in );
            return 9;
        default:
            return -1;
    }       
}

/* TR_# */
static int state9(char in, int *arg1) {
    switch( in ) {
        case ' ':
            return 10;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg1 = ( *arg1 * 10 ) + bwa2d( in );
            return 9;
        default:
            return -1;
    }
}

/* TR_#_ */
static int statea(char in, int *arg2) {
    switch( in ) {
        case ' ':
            return 10;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg2 = bwa2d( in );
            return 11;
        default:
            return -1;
    }       
}

/* TR_#_# */
static int stateb(char in, int arg1, int *arg2) {
    switch( in ) {
        case ' ':
            return 12;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg2 = ( *arg2 * 10 ) + bwa2d( in );
            return 11;
        case '\r':
            train_speed(arg1, *arg2);
            return 0;
        default:
            return -1;
    }
}

/* TR_#_#_ */
static int statec(char in, int arg1, int arg2) {
    switch( in ) {
        case ' ':
            return 12;
        case '\r':
            train_speed(arg1, arg2);
            return 0;
        default:
            return -1;
    }
}

/* S */
static int stated(char in) {
    switch( in ) {
        case 'W':
        case 'w':
            return 14;
        default:
            return -1;
    }   
}

/* SW */
static int statee(char in) {
    switch( in ) {
        case ' ':
            return 15;
        default:
            return -1;
    }       
}

/* SW_ */
static int statef(char in, int *arg1) {
    switch( in ) {
        case ' ':
            return 15;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg1 = bwa2d( in );
            return 16;
        default:
            return -1;
    }       
}

/* SW_# */
static int stateg(char in, int *arg1) {
    switch( in ) {
        case ' ':
            return 17;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg1 = ( *arg1 * 10 ) + bwa2d( in );
            return 16;
        default:
            return -1;
    }
}

/* SW_#_ */
static int stateh(char in) {
    switch( in ) {
        case ' ':
            return 17;
        case 'S':
        case 's':
            return 18;
        case 'C':
        case 'c':
            return 19;
        default:
            return -1;
    }       
}

/* SW_#_s */
static int statei(char in, int arg1) {
    switch( in ) {
        case ' ':
            return 18;
        case '\r':
            switch_direction(arg1, 's');
            return 0;
        default:
            return -1;
    }
}

/* SW_#_c */
static int statej(char in, int arg1) {
    switch( in ) {
        case ' ':
            return 19;
        case '\r':
            switch_direction(arg1, 'c');
            return 0;
        default:
            return -1;
    }
}

/* R */
static int statek(char in) {
    switch( in ) {
        case 'V':
        case 'v':
            return 21;
        default:
            return -1;
    }
}

/* RV */
static int statel(char in) {
    switch( in ) {
        case ' ':
            return 22;
        default:
            return -1;
    }   
}

/* RV_ */
static int statem(char in, int *arg1) {
    switch( in ) {
        case ' ':
            return 22;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg1 = bwa2d( in );
            return 23;
        default:
            return -1;
    }       
}

/* RV_# */
static int staten(char in, int *arg1) {
    switch( in ) {
        case ' ':
            return 24;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            *arg1 = ( *arg1 * 10 ) + bwa2d( in );
            return 23;
        case '\r':
            train_reverse(*arg1);
            return 0;
        default:
            return -1;
    }
}

/* RV_#_ */
static int stateo(char in, int arg1) {
    switch( in ) {
        case ' ':
            return 24;
        case '\r':
            train_reverse(arg1);
            return 0;
        default:
            return -1;
    }
}


/* Initializer */
void state_init() {
    cur_state = 0;
}

/* Parse a character */
state runState(char in) {
    static int arg1 = 0;
    static int arg2 = 0;

    if (in == '\x1b') return cur_state;
    else if (in == char(0x8)) return cur_state;
   
    switch(cur_state) {
        case 0:
            arg1 = 0;
            arg2 = 0;
            cur_state = initialState(in);
            break;
        case 1:
            cur_state = state1(in);
            break;
        case 2:
            cur_state = state2(in);
            break;
        case 3:
            cur_state = state3(in);
            break;
        case 4:
            cur_state = state4(in);
            break;
        case 5:
            cur_state = state5(in);
            break;
        case 6:
            cur_state = state6(in);
            break;
        case 7:
            cur_state = state7(in);
            break;
        case 8:
            cur_state = state8(in, &arg1);
            break;
        case 9:
            cur_state = state9(in, &arg1);
            break;
        case 10:
            cur_state = statea(in, &arg2);
            break;
        case 11:
            cur_state = stateb(in, arg1, &arg2);
            break;
        case 12:
            cur_state = statec(in, arg1, arg2);
            break;
        case 13:
            cur_state = stated(in);
            break;
        case 14:
            cur_state = statee(in);
            break;
        case 15:
            cur_state = statef(in, &arg1);
            break;
        case 16:
            cur_state = stateg(in, &arg1);
            break;
        case 17:
            cur_state = stateh(in);
            break;
        case 18:
            cur_state = statei(in, arg1);
            break;
        case 19:
            cur_state = statej(in, arg1);
            break;
        case 20:
            cur_state = statek(in);
            break;
        case 21:
            cur_state = statel(in);
            break;
        case 22:
            cur_state = statem(in, &arg1);
            break;
        case 23:
            cur_state = staten(in, &arg1);
            break;
        case 24:
            cur_state = stateo(in, arg1);
            break;
        default:
            cur_state = failState(in);
            break;
    }

    if (in == '\r') {
        input_print(1);
        cur_state = 0; 
    } else {
        io_putc( COM2, in );
    }

    return cur_state;
}

