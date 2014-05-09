/*
 *
 * File containing input and output functions
 *
 */

#include <bwio.h>
#include <ts7200.h>
#include <io.h>

/*
 * Buffers
 */
static buffer COM1_buf;
static buffer COM2_buf;

/*
 * Initialize
 */
int io_setfifo( int channel, int state ) {
    int *line, buf;
    switch( channel ) {
        case COM1:
            line = (int *)( UART1_BASE + UART_LCRH_OFFSET );
            break;
        case COM2:
            line = (int *)( UART2_BASE + UART_LCRH_OFFSET );
            break;
        default:
            return -1;
            break;
    }
    buf = *line;
    buf = state ? buf | FEN_MASK : buf & ~FEN_MASK;
    *line = buf;
    return 0;
}

int io_setspeed( int channel, int speed ) {
    int *high, *low;
    switch( channel ) {
        case COM1:
            high = (int *)( UART1_BASE + UART_LCRM_OFFSET );
            low = (int *)( UART1_BASE + UART_LCRL_OFFSET );
            break;
        case COM2:
            high = (int *)( UART2_BASE + UART_LCRM_OFFSET );
            low = (int *)( UART2_BASE + UART_LCRL_OFFSET );
            break;
        default:
            return -1;
            break;
    }
    switch( speed ) {
        case 115200:
            *high = 0x0;
            *low = 0x3;
            return 0;
        case 2400:
            *high = 0x0;
            *low = 0xbf;
            return 0;
        default:
            return -1;
    }
}

void io_initbuffer() {
    buffer_init(&COM1_buf);
    buffer_init(&COM2_buf);
}

/*
 * Input
 */
int io_canGet( int channel ) {
    int *flags;

    switch( channel ) {
        case COM1:
            break;
        case COM2:
            flags = (int *)( UART2_BASE + UART_FLAG_OFFSET );
            return (*flags & RXFF_MASK );                       
            break;
        default:
            return -1;
            break;
    }
    
    /* Should never get here */
    return -1;
}

int io_getc( int channel ) {
    int *data;

    switch( channel ) {
        case COM1:
            break;
        case COM2:
            data = (int *)( UART2_BASE + UART_DATA_OFFSET );
            break;
        default:
            return -1;
            break;
    }
    
    return *data;
}

/*
 * Output
 */
int io_canPut( int channel ) {
    int *flags;

    switch( channel ) {
        case COM1:
            flags = (int *)( UART1_BASE + UART_FLAG_OFFSET );
            return (!(*flags & TXFF_MASK) && (*flags & CTS_MASK) && !(*flags & TXBUSY_MASK));
            break;
        case COM2:
            flags = (int *)( UART2_BASE + UART_FLAG_OFFSET );
            return (!(*flags & TXFF_MASK));
            break;
        default:
            return -1;
            break;
    }

    return -1;
}

int io_putc_from_buf( int channel ) {
    int *data;
    char c;

    switch( channel ) {
        case COM1:
            data = (int *)( UART1_BASE + UART_DATA_OFFSET );
            c = buffer_get(&COM1_buf);
            break;
        case COM2:
            data = (int *)( UART2_BASE + UART_DATA_OFFSET );
            c = buffer_get(&COM2_buf);
            break;
        default:
            return -1;
            break;
    }

    if (c != (char)0) *data = c;
    return 0;
}

int io_putc( int channel, char c ) {
    switch( channel ) {
        case COM1:
            buffer_put(&COM1_buf, c);
            break;
        case COM2:
            buffer_put(&COM2_buf, c);
            break;
        default:
            return -1;
            break;
    }

    return 0;
}

void bwputw( int channel, int n, char fc, char *bf ) {
    char ch;
    char *p = bf;

    while( *p++ && n > 0 ) n--;
    while( n-- > 0 ) io_putc( channel, fc );
    while( ( ch = *bf++ ) ) io_putc( channel, ch );
}

void io_format ( int channel, char *fmt, va_list va ) {
    char bf[12];
    char ch, lz;
    int w;

    while ( ( ch = *(fmt++) ) ) {
        if ( ch != '%' )
            io_putc( channel, ch );
        else {
            lz = 0; w = 0;
            ch = *(fmt++);
            switch ( ch ) {
            case '0':
                lz = 1; ch = *(fmt++);
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ch = bwa2i( ch, &fmt, 10, &w );
                break;
            }
            switch( ch ) {
            case 0: return;
            case 'c':
                io_putc( channel, va_arg( va, char ) );
                break;
            case 's':
                io_putw( channel, w, 0, va_arg( va, char* ) );
                break;
            case 'u':
                bwui2a( va_arg( va, unsigned int ), 10, bf );
                io_putw( channel, w, lz, bf );
                break;
            case 'd':
                bwi2a( va_arg( va, int ), bf );
                io_putw( channel, w, lz, bf );
                break;
            case 'x':
                bwui2a( va_arg( va, unsigned int ), 16, bf );
                io_putw( channel, w, lz, bf );
                break;
            case '%':
                io_putc( channel, ch );
                break;
            }
        }
    }
}

void io_printf( int channel, char *fmt, ... ) {
    va_list va;

    va_start(va,fmt);
    io_format( channel, fmt, va );
    va_end(va);
}

