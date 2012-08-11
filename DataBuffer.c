#include "DataBuffer.h"

char buffer[BUFFER_LENGTH + 1];	//byte buffer
char *bufferPointer;

void bufferInit(void)
{
	bufferPointer = buffer;
	clearBuffer();
}

int addByte(char newByte)
{
	if(isFull() == 1)
		return -1;
		
	*bufferPointer = newByte;
	bufferPointer++;
	
	return 0;
}

int isEmpty(void)
{
	if(bufferPointer == buffer)
		return 1;
	else
		return 0;
}

int isFull(void)
{
	if(bufferPointer >= &buffer[BUFFER_LENGTH - 2])
		return 1;
	else
		return 0;
}

void clearBuffer(void)
{
	for(int i=0; i < (BUFFER_LENGTH -1); i++)
	{
		buffer[i] = 0;
	}
	bufferPointer = buffer;
}