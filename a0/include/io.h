#ifndef IO_H
#define IO_H

/*
 * Initialize
 */
int io_setfifo( int channel, int state );

int io_setspeed( int channel, int speed );


/*
 * Input
 */
int io_canGet( int channel );
int io_getc( int channel );

#endif

