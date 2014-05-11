#ifndef CONTROLLER_H
#define CONTROLLER_H

void system_init();
void system_on();
void system_off();
void system_initialize();
void system_quit();
int system_status();
void train_speed(int train_number, int train_speed);
void switch_direction(int switch_number, char switch_direction);
void reverse(int train_number);
void reverse_checkQueue(int cur_time);

#endif

