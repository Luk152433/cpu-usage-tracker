//#include "buffer.h"
#include "header.h"


BufferCircularBuf* bufferCreate(const coreSize*const coresize,const uint8_t numbers_of_buffer )
{
    if(coresize==NULL || numbers_of_buffer==0){
        return NULL;
    }
    if(coresize->amountSign==0 || coresize->coresNumber==0){
        return NULL;
    }

    BufferCircularBuf*const bufferCircularBuf=(BufferCircularBuf*const)malloc(sizeof(*bufferCircularBuf));
    bufferCircularBuf->buffer=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1)*numbers_of_buffer);
     bufferCircularBuf->courentFillBuffer=0;
     bufferCircularBuf->head=0;
     bufferCircularBuf->tail=0;
     bufferCircularBuf->maxSize=numbers_of_buffer;
     bufferCircularBuf->sizeOnePacket=(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));

    if(bufferCircularBuf==NULL || bufferCircularBuf->buffer==NULL){
        return NULL;
    }

    return bufferCircularBuf;
}
bool bufferCheckEmptyBuf(const BufferCircularBuf*const bufferCircularBuf)
{
    if(bufferCircularBuf->courentFillBuffer==bufferCircularBuf->maxSize)
    {
        return 0;
    }
    return 1;
}

bool bufferCheckFillBuf(const BufferCircularBuf*const bufferCircularBuf)
{
    if(bufferCircularBuf->courentFillBuffer==0)
    {
        return 0;
    }
    return 1;
}

void bufferSetValue(BufferCircularBuf*const bufferCircularBuf,char*const wskSource)
{
    if(bufferCircularBuf==NULL || wskSource==NULL){
        return ;
    }
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
    if(bufferCircularBuf==NULL){
        return NULL;
    }

    char*const outBufferVal=(char*const)malloc(bufferCircularBuf->sizeOnePacket);
    *outBufferVal='0';
    memcpy(outBufferVal,&bufferCircularBuf->buffer[(bufferCircularBuf->tail)*(bufferCircularBuf->sizeOnePacket)],bufferCircularBuf->sizeOnePacket);
    (bufferCircularBuf->courentFillBuffer)--;
    (bufferCircularBuf->tail)++; 
    if(bufferCircularBuf->tail==bufferCircularBuf->maxSize)
    {
        bufferCircularBuf->tail=0;
    }

    if(outBufferVal==NULL){
        return NULL;
    }

    return outBufferVal;
}

void bufferDestroy(BufferCircularBuf*const bufferCircularBuf)
{   
    if(bufferCircularBuf==NULL){
        return;
    }
    
    free(bufferCircularBuf->buffer);
    free(bufferCircularBuf);

}

void bufferProducerWaitToSetUp( mutexSema*const producerSync)
{
    sem_wait(&producerSync->semEmptyBuffer);
}

void bufferProducerReleased( mutexSema*const producerSync)
{
    sem_post(&producerSync->semFullBuffer);
}

void bufferConsmuerWaitToSetUp( mutexSema*const consumerSync)
{
    sem_wait(&consumerSync->semFullBuffer);
}

void bufferConsmuerReleased( mutexSema*const consumerSync)
{
    sem_post(&consumerSync->semEmptyBuffer);
}
