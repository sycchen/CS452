#ifndef PARSER_H
#define PARSER_H

/*
 * Using Finite State Machine:
 *
 *      initialState  -(o)>  state1  -(n)>  state2
 *                                   -(f)>  state3  -(f)>  state4
 *                    -(q)>  state5
 *                    -(t)>  state6  -(r)>  state7  -(_)>  state8  -(#)>  state9  -(_)>  statea  -(#)>  stateb  -(_)>  statec
 *                    -(s)>  stated  -(w)>  statee  -(_)>  statef  -(#)>  stateg  -(_)>  stateh  -(s)>  statei
 *                                                                                               -(c)>  statej
 *                    -(r)>  statek  -(v)>  statel  -(_)>  statem  -(#)>  staten  -(_)>  stateo
 *
 *      failState : All States can go to fail state?
 */

/* State */
typedef int state;

/* State to include backspace in future */
//struct state {
//    /* Function to use to get to next struct */
//    int fnid;
//
//    /* Pointer to the last state for backspacing */
//    struct state *last_state;   
//};

/*
 * state_init: void
 * 
 * Initializes the class variables.
 */
void state_init();

/*
 * runState: state
 *     char in - The character to parse.
 * 
 * Travels to the next state using input.
 */
state runState(char in);

#endif

