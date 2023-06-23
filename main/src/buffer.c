//#include "buffer.h"
#include "header.h"


BufferCircularBuf* bufferCreate(const coreSize*const coresize,const int numbers_of_buffer )
{
    BufferCircularBuf*const bufferCircularBuf=(BufferCircularBuf*const)malloc(sizeof(*bufferCircularBuf));
    bufferCircularBuf->buffer=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1)*numbers_of_buffer);
     bufferCircularBuf->courentFillBuffer=0;
     bufferCircularBuf->head=0;
     bufferCircularBuf->tail=0;
     bufferCircularBuf->maxSize=numbers_of_buffer;
     bufferCircularBuf->sizeOnePacket=(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));

    return bufferCircularBuf;
}
void bufferCheckEmptyBuf(const BufferCircularBuf*const bufferCircularBuf)
{
    if(bufferCircularBuf->courentFillBuffer==bufferCircularBuf->maxSize)
    {
        printf("Buffer is full!");
    }
}

void bufferCheckFillBuf(const BufferCircularBuf*const bufferCircularBuf)
{
    if(bufferCircularBuf->courentFillBuffer==0)
    {
        printf("Buffer is empty!");
    }
}

void bufferSetValue(BufferCircularBuf*const bufferCircularBuf,char*const wskSource)
{
    
    memcpy(&bufferCircularBuf->buffer[(bufferCircularBuf->head)*(bufferCircularBuf->sizeOnePacket)],wskSource,bufferCircularBuf->sizeOnePacket);
   
   (bufferCircularBuf->courentFillBuffer)++;
   (bufferCircularBuf->head)++; 
   if(bufferCircularBuf->head==bufferCircularBuf->maxSize)
    {
        bufferCircularBuf->head=0;
    }
}
char* bufferGetValue(BufferCircularBuf*const bufferCircularBuf)
{
    char*const outBufferVal=(char*const)malloc(bufferCircularBuf->sizeOnePacket);
    *outBufferVal='0';
    memcpy(outBufferVal,&bufferCircularBuf->buffer[(bufferCircularBuf->tail)*(bufferCircularBuf->sizeOnePacket)],bufferCircularBuf->sizeOnePacket);
    (bufferCircularBuf->courentFillBuffer)--;
    (bufferCircularBuf->tail)++; 
    if(bufferCircularBuf->tail==bufferCircularBuf->maxSize)
    {
        bufferCircularBuf->tail=0;
    }

    return outBufferVal;
}

void bufferDestroy(BufferCircularBuf*const bufferCircularBuf)
{   
    
    free(bufferCircularBuf->buffer);
    free(bufferCircularBuf);

}

