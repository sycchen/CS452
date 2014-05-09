#ifndef IO_H
#define IO_H

/*
 * Buffer Array
 */
#define MAX_BUFFER_SIZE 128

typedef struct {
    int get_index, put_index;
    char buf[MAX_BUFFER_SIZE];
} buffer;

int buffer_put(buffer b, char c);

char buffer_get(buffer b);

#endif

