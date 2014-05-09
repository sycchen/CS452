/*
 * 
 */
void buffer_init(buffer *b) {
    b->put_index = 0;
    b->get_index = 0;
}

void buffer_put(buffer *b, char c) {
    b->buf[b->put_index] = c;

    b->put_index++;
    if (b->put_index == MAX_BUFFER_SIZE) b->put_index = 0;
}

char buffer_get(buffer *b) {
    if (b->get_index == b->put_index) {
        return (char)0;
    }

    char c = b->buf[b->get_index];

    b->get_index++;
    if (b->get_index == MAX_BUFFER_SIZE) b->get_index = 0;

    return c;
}