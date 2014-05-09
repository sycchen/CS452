#include <bwio.h>
#include <controller.h>

/* Tells the train system to turn on */
void system_on() {
    bwputc( COM1, (char)0x60);
}

/* Tells the train system to turn off */
void system_off() {
    bwputc( COM1, (char)0x61);
}

/* Tells the console to quit */
int status = 1;
void system_quit() {
    status = 0;;
}

/* Returns wether the system should quit or not */
int system_status() {
    return status;
}
