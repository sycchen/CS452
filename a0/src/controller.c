#include <bwio.h>
#include <controller.h>

/* Tells the train system to turn on */
void system_on() {
    bwputc( COM2, (char)0x60);
}

/* Tells the train system to turn off */
void system_off() {
    bwputc( COM2, (char)0x61);
}

/* Tells the console to quit */
void system_quit() {
    system_status(1);
}

/* Returns wether the system should quit or not */
int system_status(int command) {
    static int status = 1;

    if (status == 1) {
        status = 0;        
    }

    return status;
}

