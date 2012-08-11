#include <stdio.h>
#include <avr/io.h>

#include "serial.h"

#define FOSC 8000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void SerialInit (void)
{
    DDRD = DDRD & 0b11111110; //PORTD (RX on PD0)

    //USART Baud rate: 9600
    UBRR0H = MYUBRR >> 8;
    UBRR0L = MYUBRR;
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve complete interrupt (USART_RXC) 
}

int uart_putchar(char c)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    
    return 0;
}

uint8_t uart_getchar(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}


void serialIsr(char * out)
{
   //char receivedByte;
   //receivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
   //UDR0 = receivedByte; // Echo back the received byte back to the computer
   
   *out = UDR0;	// Return value
} 

int putString(char *inString)
{
	int retVal = 1;
	char tempVal;
	
	while(*inString != 0)
	{
		tempVal = *inString;
		uart_putchar(tempVal);
		inString++;
		retVal++;
	}
	
	return retVal;
}