#ifndef CONTROLLER_H
#define CONTROLLER_H

void system_on();
void system_off();
void system_initialize();
void system_quit();
int system_status();
void train_speed(int train_number, int train_speed);
void switch_direction(int switch_number, char switch_direction);

#endif

