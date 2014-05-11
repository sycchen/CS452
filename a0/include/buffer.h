#ifndef BUFFER_H
#define BUFFER_H

/*
 * BUFFER.H
 * The buffer file contrains all functions to interact with buffer.
 * We use a circular buffer where reading and writing just keeps
 * using the next position. We do this for fast and easy access to
 * data.
 */

/*
 * Max buffer size (in bytes)
 */
#define MAX_BUFFER_SIZE 256

/*
 * Simpled wrapper struct containing an array and get/put indices.
 */
typedef struct {
    int get_index, put_index;
    char buf[MAX_BUFFER_SIZE];
} buffer;

/*
 * buffer_init: void
 *     buffer *b - Buffer to initialize.
 *
 * This function will set all elements of the buffer to 0.
 */
void buffer_init(buffer *b);

/*
 * buffer_put: void
 *     buffer *b - Buffer to add to.
 *     char c    - Character to be put on buffer.
 *
 * Puts a character on the buffer.
 */
void buffer_put(buffer *b, char c);

/*
 * buffer_init: int
 *     buffer *b - Buffer to check.
 *
 * Checks to see if the buffer is empty. Will return 1 if empty else
 * 0.
 */
int buffer_isEmpty(buffer *b);

/*
 * buffer_init: char
 *     buffer *b - Buffer to read from.
 *
 * Pops the top character from the buffer and returns it.
 */
char buffer_get(buffer *b);

#endif

