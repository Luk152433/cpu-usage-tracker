#ifndef BUFFER_H
#define BUFFER_H

BufferCircularBuf* bufferCreate(coreSize* coresize,int numbers_of_buffer);
char* bufferGetValue(BufferCircularBuf* bufferCircularBuf);
void bufferSetValue(BufferCircularBuf* bufferCircularBuf,char* wskSource);
void bufferDestroy(BufferCircularBuf* BufferCircularBuf);
void bufferCheckEmptyBuf(BufferCircularBuf* bufferCircularBuf);
void bufferCheckFillBuf(BufferCircularBuf* bufferCircularBuf);

#endif  

