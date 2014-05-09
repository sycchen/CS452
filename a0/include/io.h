#ifndef IO_H
#define IO_H

/*
 * Initialize
 */
int io_setfifo( int channel, int state );
int io_setspeed( int channel, int speed );
void io_initbuffer();

/*
 * Input
 */
int io_canGet( int channel );
int io_getc( int channel );

/*
 * Output
 */
int io_canPut( int channel );
int io_putc_from_buf( int channel );
int io_putc( int channel, char c );
void io_printf( int channel, char *fmt, ... );

#endif

