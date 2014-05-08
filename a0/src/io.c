/*
 *
 * File containing input and output functions
 *
 */

#include <ts7200.h>
#include <io.h>

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


/*
 * Input
 */
int io_canGet( int channel ) {
    int *flags;

    switch( channel ) {
    case COM1:
        flags = (int *)( UART1_BASE + UART_FLAG_OFFSET );
        break;
    case COM2:
        flags = (int *)( UART2_BASE + UART_FLAG_OFFSET );
        break;
    default:
        return -1;
        break;
    }
    
    return (*flags & RXFF_MASK );
}

char io_getc( int channel ) {
    int *data;

    switch( channel ) {
    case COM1:
        data = (int *)( UART1_BASE + UART_DATA_OFFSET );
        break;
    case COM2:
        data = (int *)( UART2_BASE + UART_DATA_OFFSET );
        break;
    default:
        return -1;
        break;
    }
    
    int c = (char)(*data);
    return c;
}

