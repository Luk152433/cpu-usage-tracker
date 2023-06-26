#include "header.h"
#include <assert.h>
#include <unistd.h>
#include <sys/sysinfo.h>

void testBufferCreate(void);
void testBufferCreate(void)
{   
   
    coreSize*const MCoreSize=(coreSize*)malloc(sizeof(*MCoreSize));
    MCoreSize->amountSign=1;
    MCoreSize->coresNumber=1;
    u_int8_t Mnumbers_of_buffer=1;
    BufferCircularBuf* buffer=bufferCreate(MCoreSize, Mnumbers_of_buffer );
    assert(buffer!=NULL);
    bufferDestroy(buffer);

    MCoreSize->amountSign=0;
    MCoreSize->coresNumber=1;
    Mnumbers_of_buffer=1;
    buffer=bufferCreate(MCoreSize, Mnumbers_of_buffer );
    assert(buffer==NULL);

    MCoreSize->amountSign=1;
    MCoreSize->coresNumber=0;
    Mnumbers_of_buffer=1;
    buffer=bufferCreate(MCoreSize, Mnumbers_of_buffer );
    assert(buffer==NULL);

    MCoreSize->amountSign=1;
    MCoreSize->coresNumber=1;
    Mnumbers_of_buffer=0;
    buffer=bufferCreate(MCoreSize, Mnumbers_of_buffer );
    assert(buffer==NULL);

    free(MCoreSize);
    

}

void testBufferSetValue(void);
void testBufferSetValue(void)
{   
   
    coreSize*const MCoreSize=(coreSize*)malloc(sizeof(*MCoreSize));
    MCoreSize->amountSign=1;
    MCoreSize->coresNumber=1;
    u_int8_t Mnumbers_of_buffer=1;
    BufferCircularBuf* buffer=bufferCreate(MCoreSize, Mnumbers_of_buffer );
    assert(buffer!=NULL);
    
    assert(!bufferCheckFillBuf(buffer));
    char MwskSource='A';
    bufferSetValue(buffer, &MwskSource);
    assert(bufferCheckFillBuf(buffer));



    bufferDestroy(buffer);
    free(MCoreSize);
    

}

void testBufferGetValue(void);
void testBufferGetValue(void)
{   
   
    coreSize*const MCoreSize=(coreSize*)malloc(sizeof(*MCoreSize));
    MCoreSize->amountSign=1;
    MCoreSize->coresNumber=1;
    u_int8_t Mnumbers_of_buffer=1;
    BufferCircularBuf* buffer=bufferCreate(MCoreSize, Mnumbers_of_buffer );
    assert(buffer!=NULL);

    assert(!bufferCheckFillBuf(buffer));
    
    char MwskSource='A';
    bufferSetValue(buffer, &MwskSource);
    assert(bufferCheckFillBuf(buffer));

    assert(!bufferCheckEmptyBuf(buffer));

    char* wskGetValue=bufferGetValue(buffer);
    assert(wskGetValue!=NULL);
    assert(bufferCheckEmptyBuf(buffer));


    bufferDestroy(buffer);
    free(MCoreSize);
    free(wskGetValue);
    

} 

void testBuffer(void);
void testBuffer(void)
{
    testBufferCreate();
    testBufferSetValue();
    testBufferGetValue();
}