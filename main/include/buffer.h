#ifndef BUFFER_H
#define BUFFER_H

BufferCircularBuf* bufferCreate(const coreSize*const coresize,const uint8_t numbers_of_buffer);
char* bufferGetValue(BufferCircularBuf*const bufferCircularBuf);
void bufferSetValue(BufferCircularBuf*const bufferCircularBuf,char*const wskSource);
void bufferDestroy(BufferCircularBuf*const BufferCircularBuf);
bool bufferCheckEmptyBuf(const BufferCircularBuf*const bufferCircularBuf);
bool bufferCheckFillBuf(const BufferCircularBuf* bufferCircularBuf);

#endif  

