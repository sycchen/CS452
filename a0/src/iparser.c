/* Run's the state giving it a char.
 * Will return the next state */
void runState(char in, struct state *curState) {
    struct state new_state;

    if (curState == NULL) {
        curState = {initialState, NULL };
    }

    if (in == '\n') {
        curState->func(in);
        new_state = { initialState, NULL };
    } else {
        new_state = { curState->func(in), curState };
    }
    
    return new_state;
}

/* The starting state */
int *intialState(char in) {
    switch( in ) {
        case 'o':
            return state1;
        case 'q':
            return state5;
        case ' ':
            return initialState;
        default:
            return failState;
    }
}

/* State where it can't lead to another command */
int failState(char in) {
    return failState;
}

/* O */
int state1(char in) {
    switch( in ) {
        case 'n':
            return state2;
        case 'f':
            return state3;
        default:
            return failState;
    }    
}

/* ON */
int state2(char in) {
    switch( in ) {
        case ' ':
            return state2;
        case '\n':
            system_on();
            return 0;
        default:
            return failState;
    }
}

/* OF */
int state3(char in) {
    switch( in ) {
        case 'f':
            return state4;
        default:
            return failState;
    }
}

/* OFF */
int state4(char in) {
    switch( in ) {
        case ' ':
            return stat4;
        case '\n':
            system_off();
            return 0;
        default:
            return failState;
    }
}

/* Q */
int state5(char in) {
    switch( in ) {
        case ' ':
            return state5;
        case '\n':
            system_quit();
            return 0;
        default:
            return failState;
    }
}