#ifndef CONTROLLER_H
#define CONTROLLER_H

#define SMASK1 1
#define SMASK2 2
#define SMASK3 4
#define SMASK4 8
#define SMASK5 16
#define SMASK6 32
#define SMASK7 64
#define SMASK8 128

#define MAX_REVERSE_QUEUE 4

void system_init();
void system_on();
void system_off();
void system_quit();
int system_status();
void train_speed(int train_number, int train_speed);
void switch_direction(int switch_number, char switch_direction);
void train_reverse(int train_number);
void train_reverse_checkQueue(int cur_time);
void sensor_check(char sensor_read);

#endif

