//#include "thread.h"
#include "header.h"
coreSize*  coreSizeV;
typedef struct mutexSema
{
    pthread_mutex_t mtx;
    sem_t semEmptyBuffer;
    sem_t semFullBuffer;
}mutexSema;
BufferCircularBuf* readAnalyzerBuff,analyzerPrinterBuff;

pthread_t threadTab[THREADS_NUM];
mutexSema readAnalyzerSync, analyzerPrinterSync;
   

void run(){


     
}
void prepareVariable()
{   coreSizeV=(coreSize*)malloc(sizeof(*coreSizeV));
    coreSizeV->amountSign=254;
    coreSizeV->coresNumber=1;

    readAnalyzerBuff=bufferCreate(coreSizeV,BUFFER_NUM);


}
void* readerThread(void* args)
{
       
    
    Reader* reader=readerCreate("/proc/stat");
    reader=readerOpenSourceFile(reader);
    /////////while
    char*wsk= readerReadSourceFile(reader,coreSizeV);
    sem_wait(&readAnalyzerSync.semEmptyBuffer);
    pthread_mutex_lock(&readAnalyzerSync.mtx);

    printf("%s%s",wsk,&wsk[1*sizeof(char)*(coreSizeV->amountSign)]);
    bufferSetValue(readAnalyzerBuff,wsk);
    
    pthread_mutex_unlock(&readAnalyzerSync.mtx);
    sem_post(&readAnalyzerSync.semFullBuffer);
    free(wsk);
    /////////whileend
    readerCloseSourceFile(reader);
    
    readerDestroy(reader);
    free(coreSizeV);
}
void* analyzerThread(void* args)
{   
    //////////while
    sem_wait(&readAnalyzerSync.semFullBuffer);
    pthread_mutex_lock(&readAnalyzerSync.mtx);
    
   char* reciveAnalyzer= bufferGetValue(readAnalyzerBuff);
    
    pthread_mutex_unlock(&readAnalyzerSync.mtx);
    sem_post(&readAnalyzerSync.semEmptyBuffer);
    //scanf....
    free(reciveAnalyzer);


    /////////whileend


}
void* printerThread(void* args)
{}
void* watchdogThread(void* args)
{}
void* loggerThread(void* args)
{}

void setThread()
{
    pthread_mutex_init(&readAnalyzerSync.mtx,NULL);
    pthread_mutex_init(&analyzerPrinterSync.mtx,NULL);

    sem_init(&readAnalyzerSync.semEmptyBuffer,0,10);
    sem_init(&readAnalyzerSync.semFullBuffer,0,0);
    sem_init(&analyzerPrinterSync.semEmptyBuffer,0,10);
    sem_init(&analyzerPrinterSync.semFullBuffer,0,0);

    pthread_create(&threadTab[0],NULL,&readerThread,NULL);
   // pthread_create(&threadTab[1],NULL,&analyzerThread,NULL);
    //pthread_create(&threadTab[2],NULL,&printerThread,NULL);
    //pthread_create(&threadTab[3],NULL,&loggerThread,NULL);
    //pthread_create(&threadTab[4],NULL,&watchdogThread,NULL);

    pthread_join(threadTab[0],NULL);
   //pthread_join(threadTab[1],NULL);
    //pthread_join(threadTab[2],NULL);
    //pthread_join(threadTab[3],NULL);
    //pthread_join(threadTab[4],NULL);

    sem_destroy(&readAnalyzerSync.semEmptyBuffer);
    sem_destroy(&readAnalyzerSync.semFullBuffer);
    sem_destroy(&analyzerPrinterSync.semEmptyBuffer);
    sem_destroy(&analyzerPrinterSync.semFullBuffer);

    pthread_mutex_destroy(&readAnalyzerSync.mtx);
    pthread_mutex_destroy(&analyzerPrinterSync.mtx);


}