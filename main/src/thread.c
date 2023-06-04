//#include "thread.h"
#include "header.h"
coreSize*  coreSizeV,*analizerSizeV;
typedef struct mutexSema
{
    pthread_mutex_t mtx;
    sem_t semEmptyBuffer;
    sem_t semFullBuffer;
}mutexSema;
BufferCircularBuf* readAnalyzerBuff,*analyzerPrinterBuff;

pthread_t threadTab[THREADS_NUM];
mutexSema readAnalyzerSync, analyzerPrinterSync;
   

void run(){
    prepareVariable();
    setThread();
   
     
}
void prepareVariable()
{   coreSizeV=(coreSize*)malloc(sizeof(*coreSizeV));
    coreSizeV->amountSign=254;
    coreSizeV->coresNumber=1;

    analizerSizeV=(coreSize*)malloc(sizeof(*analizerSizeV));
    analizerSizeV->amountSign=sizeof(double);
    analizerSizeV->coresNumber=1;
    readAnalyzerBuff=bufferCreate(coreSizeV,BUFFER_NUM);
    analyzerPrinterBuff=bufferCreate(analizerSizeV,BUFFER_NUM);

}
void* readerThread(void* args)
{
       int n=0;
    
    Reader* reader=readerCreate("/proc/stat");
    reader=readerOpenSourceFile(reader);
    /////////while
    while(n<30){

    readerReOpenSourceFile(reader);
    char*wsk= readerReadSourceFile(reader,coreSizeV);
    sem_wait(&readAnalyzerSync.semEmptyBuffer);
    pthread_mutex_lock(&readAnalyzerSync.mtx);
   // printf("reader");
    //printf("%s%s",wsk,&wsk[1*sizeof(char)*(coreSizeV->amountSign)]);
    bufferSetValue(readAnalyzerBuff,wsk);
    
    pthread_mutex_unlock(&readAnalyzerSync.mtx);
    sem_post(&readAnalyzerSync.semFullBuffer);
    free(wsk);
    sleep(1);
    n++;
    }
    /////////whileend
    readerCloseSourceFile(reader);
    
    readerDestroy(reader);
   
}
void* analyzerThread(void* args)
{   int m=0;
    ProcDate* procDate=analyzerCreate(coreSizeV);
    ProcDate* procDatePreviue=analyzerCreate(coreSizeV);
    while(m<30){
    sem_wait(&readAnalyzerSync.semFullBuffer);
    pthread_mutex_lock(&readAnalyzerSync.mtx);
    
   char* reciveAnalyzer= bufferGetValue(readAnalyzerBuff);
    
    pthread_mutex_unlock(&readAnalyzerSync.mtx);
    sem_post(&readAnalyzerSync.semEmptyBuffer);
    //printf("analyzer");
    //printf("%s%s",reciveAnalyzer,&reciveAnalyzer[1*sizeof(char)*(coreSizeV->amountSign)]);
    

    for(int i=0;i<=coreSizeV->coresNumber;i++)
    {

        sscanf((char*)&reciveAnalyzer[i*sizeof(char)*(coreSizeV->amountSign)],"%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",procDate[i].name,&procDate[i].user,&procDate[i].nice,&procDate[i].system,
        &procDate[i].idle,&procDate[i].iowait,&procDate[i].irq,&procDate[i].softirq,&procDate[i].steal,&procDate[i].guest,&procDate[i].guestNice);

    }
    free(reciveAnalyzer);

    printf("analyzerSSS\n");
    for(int i=0;i<=coreSizeV->coresNumber;i++)
    {
   printf( "%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld \n",procDate[i].name,procDate[i].user,procDate[i].nice,procDate[i].system,
        procDate[i].idle,procDate[i].iowait,procDate[i].irq,procDate[i].softirq,procDate[i].steal,procDate[i].guest,procDate[i].guestNice);
    }
    printf("analyzerSE\n");

   printf("analyzerPREV\n");
       
//   for(int i=0;i<=coreSizeV->coresNumber;i++)
//     {
//         printf( "%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld \n",procDatePreviue[i].name,procDatePreviue[i].user,procDatePreviue[i].nice,procDatePreviue[i].system,
//         procDatePreviue[i].idle,procDatePreviue[i].iowait,procDatePreviue[i].irq,procDatePreviue[i].softirq,procDatePreviue[i].steal,procDatePreviue[i].guest,procDatePreviue[i].guestNice);  
//     }     
        printf("EanalyzerPREV\n");
    // for(int i=0;i<=coreSizeV->coresNumber;i++)
    // {
    //     memcpy(procDatePreviue,procDate,sizeof(*procDate));
    // }
        double* allPrec=analyzerCountRate( procDate,procDatePreviue,coreSizeV);
    

    for(int i=0;i<=coreSizeV->coresNumber;i++)
    {
        printf("%f \n",allPrec[i]);
    }
    printf("A1\n");
    sem_wait(&analyzerPrinterSync.semEmptyBuffer);
    pthread_mutex_lock(&analyzerPrinterSync.mtx);
      printf("A2\n");
/////////////////////
//malloc(sizeof(allPrec)*(coreSizeV->coresNumber+1));
    //char* temp=(char*)allPrec;
    char*temp=(char*)malloc(sizeof(double)*(coreSizeV->coresNumber+1));
    //bufferSetValue(analyzerPrinterBuff,(char*)allPrec);
     memcpy(temp,allPrec,sizeof(double)*(coreSizeV->coresNumber+1));

       printf("A3\n");
     for(int i=0;i<=coreSizeV->coresNumber;i++)
    {
       printf("%f \n",(double)temp[i*8]);
    }

    bufferSetValue(analyzerPrinterBuff,temp);
    pthread_mutex_unlock(&analyzerPrinterSync.mtx);
    sem_post(&analyzerPrinterSync.semFullBuffer);
    


        for(int i=0;i<=coreSizeV->coresNumber;i++){
    *procDatePreviue[i].name=*procDate[i].name;
    procDatePreviue[i].user=procDate[i].user;
    procDatePreviue[i].nice=procDate[i].nice;
    procDatePreviue[i].system=procDate[i].system;
    procDatePreviue[i].idle=procDate[i].idle;
    procDatePreviue[i].iowait=procDate[i].iowait;
    procDatePreviue[i].irq=procDate[i].irq;
    procDatePreviue[i].softirq=procDate[i].softirq;
    procDatePreviue[i].steal=procDate[i].steal;
    procDatePreviue[i].guest=procDate[i].guest;
    procDatePreviue[i].guestNice=procDate[i].guestNice;
    }
        free(temp);
      free(allPrec);

     
        m++;

       sleep(1); 
     }
     
    
bufferDestroy(readAnalyzerBuff);
analyzerDestroy(procDate,procDatePreviue);

    /////////whileend


}
void* printerThread(void* args)
{   
   int k=0;
    while(k<30){
    sem_wait(&analyzerPrinterSync.semFullBuffer);
    pthread_mutex_lock(&analyzerPrinterSync.mtx);
    
   double* recivereader= (double*)bufferGetValue(analyzerPrinterBuff);
    
    pthread_mutex_unlock(&analyzerPrinterSync.mtx);
    sem_post(&analyzerPrinterSync.semEmptyBuffer);

    printf("reader\n");
    printf("%f %f",recivereader[0],recivereader[1]);
     printf("readerKONiec\n");
    free(recivereader);
    sleep(1);
    k++;
    }
    bufferDestroy(analyzerPrinterBuff);

}
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
    pthread_create(&threadTab[1],NULL,&analyzerThread,NULL);
    pthread_create(&threadTab[2],NULL,&printerThread,NULL);
    //pthread_create(&threadTab[3],NULL,&loggerThread,NULL);
    //pthread_create(&threadTab[4],NULL,&watchdogThread,NULL);

    pthread_join(threadTab[0],NULL);
    pthread_join(threadTab[1],NULL);
    pthread_join(threadTab[2],NULL);
    //pthread_join(threadTab[3],NULL);
    //pthread_join(threadTab[4],NULL);

    sem_destroy(&readAnalyzerSync.semEmptyBuffer);
    sem_destroy(&readAnalyzerSync.semFullBuffer);
    sem_destroy(&analyzerPrinterSync.semEmptyBuffer);
    sem_destroy(&analyzerPrinterSync.semFullBuffer);

    pthread_mutex_destroy(&readAnalyzerSync.mtx);
    pthread_mutex_destroy(&analyzerPrinterSync.mtx);
     free(coreSizeV);
    free(analizerSizeV);


}