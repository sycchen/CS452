#include <buffer.h>
#include <bwio.h>

/* Initialize the buffer */
void buffer_init(buffer *b) {
    b->put_index = 0;
    b->get_index = 0;
    
    int i;
    for (i = 0; i < MAX_BUFFER_SIZE; i++) {
        b->buf[i] = (char)0;
    }
}

/* Put a character in the buffer */
void buffer_put(buffer *b, char c) {
    /* Set character */
    b->buf[b->put_index] = c;
 
    /* Increment */
    b->put_index++;
    if (b->put_index == MAX_BUFFER_SIZE) b->put_index = 0;

    /* Checks if buffer is full */
    if (b->put_index == b->get_index) bwprintf(COM2, "BUFFER FULL \n");
}

/* Checks if buffer is empty */
int buffer_isEmpty(buffer *b) {
    if (b->get_index == b->put_index) return 1;
    return 0;
}

/* Get a character from the buffer */
char buffer_get(buffer *b) {
    char c = b->buf[b->get_index];

    /* Increment */
    b->get_index++;
    if (b->get_index == MAX_BUFFER_SIZE) b->get_index = 0;

    return c;
}

