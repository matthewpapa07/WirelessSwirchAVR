
#ifndef SERIAL_H
#define SERIAL_H

extern void SerialInit (void);

extern int uart_putchar(char c);

extern uint8_t uart_getchar(void);

extern void serialIsr(char * out);

extern int putString(char *inString);

#endif /* SERIAL_H */