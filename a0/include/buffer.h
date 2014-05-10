#ifndef BUFFER_H
#define BUFFER_H

/*
 * Buffer Array
 */
#define MAX_BUFFER_SIZE 128

typedef struct {
    int get_index, put_index;
    char buf[MAX_BUFFER_SIZE];
} buffer;

void buffer_init(buffer *b);

void buffer_put(buffer *b, char c);

char buffer_get(buffer *b);

#endif

