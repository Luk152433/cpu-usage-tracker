#ifndef BUFFER_H
#define BUFFER_H

BufferCircularBuf* bufferCreate(const coreSize*const coresize,const int numbers_of_buffer);
char* bufferGetValue(BufferCircularBuf*const bufferCircularBuf);
void bufferSetValue(BufferCircularBuf*const bufferCircularBuf,char*const wskSource);
void bufferDestroy(BufferCircularBuf*const BufferCircularBuf);
void bufferCheckEmptyBuf(const BufferCircularBuf*const bufferCircularBuf);
void bufferCheckFillBuf(const BufferCircularBuf* bufferCircularBuf);

#endif  

