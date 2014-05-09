/*
 * Buffer Array
 */
typedef char buffer[128];

int buffer_put(buffer b, char c);

char buffer_get(buffer b);