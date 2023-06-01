//#include "buffer.h"
#include "header.h"


BufferCircularBuf* bufferCreate(coreSize* coresize,int numbers_of_buffer )
{
    BufferCircularBuf* bufferCircularBuf=(BufferCircularBuf*)malloc(sizeof(*bufferCircularBuf));
    bufferCircularBuf->buffer=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1)*numbers_of_buffer);
     bufferCircularBuf->courentFillBuffer=0;
     bufferCircularBuf->head=0;
     bufferCircularBuf->tail=0;
     bufferCircularBuf->maxSize=numbers_of_buffer;
     bufferCircularBuf->sizeOnePacket=(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));

    return bufferCircularBuf;
}
void bufferCheckEmptyBuf(BufferCircularBuf* bufferCircularBuf)
{
    if(bufferCircularBuf->courentFillBuffer==bufferCircularBuf->maxSize)
    {
        printf("Buffer is full!");
    }
}

void bufferCheckFillBuf(BufferCircularBuf* bufferCircularBuf)
{
    if(bufferCircularBuf->courentFillBuffer==0)
    {
        printf("Buffer is empty!");
    }
}

void bufferSetValue(BufferCircularBuf* bufferCircularBuf,char* wskSource)
{
    
    memcpy(bufferCircularBuf->buffer[(bufferCircularBuf->head)*(bufferCircularBuf->sizeOnePacket)],wskSource,bufferCircularBuf->sizeOnePacket);
   (bufferCircularBuf->courentFillBuffer)++;
   (bufferCircularBuf->head)++; 
   if(bufferCircularBuf->head==bufferCircularBuf->maxSize)
    {
        bufferCircularBuf->head=0;
    }
}
char* bufferGetValue(BufferCircularBuf* bufferCircularBuf)
{
    char* outBufferVal=malloc(bufferCircularBuf->sizeOnePacket);
    memcpy(outBufferVal,bufferCircularBuf->buffer[(bufferCircularBuf->tail)*(bufferCircularBuf->sizeOnePacket)],bufferCircularBuf->sizeOnePacket);
    (bufferCircularBuf->courentFillBuffer)--;
    (bufferCircularBuf->tail)++; 
    if(bufferCircularBuf->tail==bufferCircularBuf->maxSize)
    {
        bufferCircularBuf->tail=0;
    }

    return outBufferVal;
}

void bufferDestroy(BufferCircularBuf* bufferCircularBuf)
{   
    
    free(bufferCircularBuf->buffer);
    free(bufferCircularBuf);

}

