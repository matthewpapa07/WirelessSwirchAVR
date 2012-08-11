#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <stdint.h> 
#include <avr/interrupt.h>

#include "serial.h"
#include "DataBuffer.h"

//Define functions
//======================
void delay_ms(uint16_t x); //General purpose delay
int CheckCode(void);
void blinkLed(void);
//======================

char PreAmble []	= "ning";
char OpenGate [] 	= "OpenGate";
char CloseGate [] 	= "CloseGate";
char StopGate [] 	= "StopGate";

//
// Example message ning_OpenGate
//

int main (void)
{
	//
	// Default all pins to outputs
	// 1 = output, 0 = input
	//
	DDRB = 0b11111111;
    DDRC = 0b11111111;
    DDRD = 0b11111110;
	
	PORTD = 0b00000000;
	PORTC = 0b00000000;
	
	blinkLed();
	
    SerialInit();
	sei();
	putString("POWERED UP!!!");

	//
	// Service Loop
	//
	while(1)
	{
		if(!isEmpty())
		{
			CheckCode();
			clearBuffer();
		}
		delay_ms(1000);		//Every second check
		//clearBuffer();
	}
	
    return(0);
}

int CheckCode(void)
{
	char *tempPnt = buffer;
	
	putString("\r\nChecking Code: ");
	putString(buffer);
	putString(" \r\n");
	
	if(strncmp(tempPnt, PreAmble, 4) == 0)
	{
		tempPnt += 5;
	
		putString("\nPreample Passed\r\n");
		if(strncmp(tempPnt, OpenGate, 8) == 0)
		{
			PORTC = PORTC & 0xF8;
			PORTC = PORTC | 0x04;
			putString("Opened Gate!\r\n");
			delay_ms(2000);
			PORTC = PORTC & 0xF8;
			return 0;
		}
		if(strncmp(tempPnt, CloseGate, 9) == 0)
		{
			PORTC = PORTC & 0xF8;
			PORTC = PORTC | 0x02;
			putString("Closed Gate!\r\n");
			delay_ms(2000);
			PORTC = PORTC & 0xF8;
			return 0;
		}
		if(strncmp(tempPnt, StopGate, 8) == 0)
		{
			PORTC = PORTC & 0xF8;
			PORTC = PORTC | 0x01;
			putString("Stopped Gate!\r\n");
			delay_ms(2000);
			PORTC = PORTC & 0xF8;
			return 0;
		}
		
		putString("Failed the check after the preamble\r\n");
		return -1;
	}
	putString("No Match!");
	return -1;
}

//General short delays
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 20 ; z++){
        asm volatile ("nop");
      }
    }
  }
}

void blinkLed(void)
{
	if((PORTC & 0x20) == 0)
	{
		PORTC = PORTC | 0x20;
	}
	else
	{
		PORTC = PORTC & 0xDF;
	}
}

/**
	Serial receive data interrupt handler
**/
ISR(USART_RX_vect)
{
	char rx = 0;
	
	serialIsr(&rx);
	//uart_putchar(rx);
	addByte(rx);
	blinkLed();
}
