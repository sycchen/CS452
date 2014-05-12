#ifndef IO_H
#define IO_H

/*
 * io_setup: int
 *     int channel - The UART to send to.
 *     int state   - The desired state of FIFO.
 *     int speed   - The desired Baud rate.
 * 
 * Initializes the UART with settings and returns a 0 on success 
 * else -1.
 */
int io_setup( int channel, int state, int speed );

/*
 * io_initbuffer: void
 * 
 * Initializes the output buffers.
 */
void io_initbuffer();

/*
 * io_canGet: int
 *     int channel - The UART to check. 
 *
 * Checks to see if UART is ready to read returning 1 if ready else 0.
 *
 * io_getc: int
 *     int channel - The UART to read from.
 *
 * Reads the bytes currently in UART's data register returning 0 on 
 * success else -1;
 */
int io_canGet( int channel );
int io_getc( int channel );

/*
 * io_canPut: int
 *     int channel - The UART to check. 
 *
 * Checks to see if UART is ready to write returning 1 if ready else 0.
 *
 * io_putc: int
 *     int channel - The UART to write to.
 *
 * Adds the bytes to a output buffer returning 0 on success else -1.
 *
 * io_putc_from_buf: char
 *     int channel - The UART to write to.
 *
 * Writes the top item of the output buffer to UART's data register.
 * Returns the character written. 
 */
int io_canPut( int channel );
int io_putc( int channel, char c );
char io_putc_from_buf( int channel );
/* Copied from BWIO but uses io_putc() */
void io_putw( int channel, int n, char fc, char *bf );
void io_printf( int channel, char *fmt, ... );

#endif

