#ifndef IPARSER_H
#define IPARSER_H

/*
 * Using Finite State Machine:
 *
 *      initialState  -(o)>  state1  -(n)>  state2
 *                                   -(f)>  state3  -(f)>  state4
 *                    -(q)>  state5
 *
 *      failState : All States can go to fail state?
 */

/* State */
struct state {
    /* Function to use to get to next struct */
    int (*func)(char);

    /* Pointer to the last state for backspacing */
    struct state *last_state;   
};

void runState(char in, struct state *curState);
int *intialState(char in);
int failState(char in);
int state1(char in);
int state2(char in);
int state3(char in);
int state4(char in);
int state5(char in);

#endif

