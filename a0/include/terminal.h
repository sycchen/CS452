#ifndef TERMINAL_H
#define TERMINAL_H

    void term_init();
    void term_kill();

    void sensor_init();
    void sensor_print();
    void sensor_add(int sensor);
    
    void input_print();
    
    void switch_print(int switch_number, char switch_direction);
    
    void time_print();
    
#endif


