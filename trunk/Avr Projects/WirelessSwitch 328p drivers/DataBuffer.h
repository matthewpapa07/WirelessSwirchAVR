#ifndef DATA_BUFFER_H
#define DATA_BUFFER_H

#define BUFFER_LENGTH 25

extern void bufferInit(void);

extern int addByte(char newByte);

extern int isEmpty(void);

extern int isFull(void);

extern void clearBuffer(void);

extern char buffer[];

extern char *bufferPointer;

#endif /* DATA_BUFFER_H */