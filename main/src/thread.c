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
StoragePrinter* storagePrinter;
Reader* reader;
ProcDate* procDate;
ProcDate* procDatePreviue;
char* wskReader;
char* reciveAnalyzer;
double* allPrec;
char* temp;
double* recivereader;
pthread_t threadTab[THREADS_NUM];
mutexSema readAnalyzerSync, analyzerPrinterSync;

void prepareVariable();
void  setThread();

void signal_exit(const int signum) 
    {
  
        printf(" Signal %d end run\n", signum);
        free(coreSizeV);
        free(analizerSizeV);
        free(wskReader);
        readerCloseSourceFile(reader);
        readerDestroy(reader);
        bufferDestroy(readAnalyzerBuff);
        free(reciveAnalyzer);
        free(allPrec);
        free(temp);
        free(recivereader);
        analyzerDestroy(procDate,procDatePreviue);
        bufferDestroy(analyzerPrinterBuff);
        printerDestroy(storagePrinter);

        pthread_join(threadTab[0],NULL);
        pthread_join(threadTab[1],NULL);
        pthread_join(threadTab[2],NULL);

        sem_destroy(&readAnalyzerSync.semEmptyBuffer);
        sem_destroy(&readAnalyzerSync.semFullBuffer);
        sem_destroy(&analyzerPrinterSync.semEmptyBuffer);
        sem_destroy(&analyzerPrinterSync.semFullBuffer);

        pthread_mutex_destroy(&readAnalyzerSync.mtx);
        pthread_mutex_destroy(&analyzerPrinterSync.mtx);

    } 

void run()
    {
        prepareVariable();
        setThread(); 

    }

void prepareVariable()
    {   

        coreSizeV=(coreSize*)malloc(sizeof(*coreSizeV));
        coreSizeV->amountSign=254;
        coreSizeV->coresNumber=get_nprocs_conf();

        analizerSizeV=(coreSize*)malloc(sizeof(*analizerSizeV));
        analizerSizeV->amountSign=sizeof(double);
        analizerSizeV->coresNumber=get_nprocs_conf();

        readAnalyzerBuff=bufferCreate(coreSizeV,BUFFER_NUM);
        analyzerPrinterBuff=bufferCreate(analizerSizeV,BUFFER_NUM);

    }

void* readerThread(void* args)
    {      
        (void)args;
        int n=0;
    
        reader=readerCreate("/proc/stat");
        reader=readerOpenSourceFile(reader);
   
    while(n<30)
        {

            readerReOpenSourceFile(reader);
            wskReader= readerReadSourceFile(reader,coreSizeV);

            sem_wait(&readAnalyzerSync.semEmptyBuffer);
            pthread_mutex_lock(&readAnalyzerSync.mtx);
    
            bufferSetValue(readAnalyzerBuff,wskReader);
        
            pthread_mutex_unlock(&readAnalyzerSync.mtx);
            sem_post(&readAnalyzerSync.semFullBuffer);

            free(wskReader);
            sleep(1);
            n++;
        }
    
        readerCloseSourceFile(reader);
        readerDestroy(reader);

        return NULL;
   
    }


void* analyzerThread(void* args)
    {       
        (void)args;
        int m=0;

        procDate=analyzerCreate(coreSizeV);
        procDatePreviue=analyzerCreate(coreSizeV);

    while(m<30)
        {
            sem_wait(&readAnalyzerSync.semFullBuffer);
            pthread_mutex_lock(&readAnalyzerSync.mtx);
    
            reciveAnalyzer= bufferGetValue(readAnalyzerBuff);
    
            pthread_mutex_unlock(&readAnalyzerSync.mtx);
            sem_post(&readAnalyzerSync.semEmptyBuffer);
    
    

            for(int i=0;i<=coreSizeV->coresNumber;i++)
                {

                    sscanf((char*)&reciveAnalyzer[i*sizeof(char)*(coreSizeV->amountSign)],"%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",procDate[i].name,&procDate[i].user,&procDate[i].nice,&procDate[i].system,
                    &procDate[i].idle,&procDate[i].iowait,&procDate[i].irq,&procDate[i].softirq,&procDate[i].steal,&procDate[i].guest,&procDate[i].guestNice);

                }
            
            free(reciveAnalyzer);

            allPrec=analyzerCountRate( procDate,procDatePreviue,coreSizeV);
    

   
            sem_wait(&analyzerPrinterSync.semEmptyBuffer);
            pthread_mutex_lock(&analyzerPrinterSync.mtx);
     

            temp=(char*)malloc(sizeof(double)*(coreSizeV->coresNumber+1));
            memcpy(temp,allPrec,sizeof(double)*(coreSizeV->coresNumber+1));
            bufferSetValue(analyzerPrinterBuff,temp);
    
            pthread_mutex_unlock(&analyzerPrinterSync.mtx);
            sem_post(&analyzerPrinterSync.semFullBuffer);
    


            for(int i=0;i<=coreSizeV->coresNumber;i++)
                {
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

        return NULL;

    }

void* printerThread(void* args)
    {   
        (void)args;
        int k=0;
        
        storagePrinter=printerCreate(coreSizeV);
        
    while(k<30)
        {
            sem_wait(&analyzerPrinterSync.semFullBuffer);
            pthread_mutex_lock(&analyzerPrinterSync.mtx);
    
            recivereader= (double*)bufferGetValue(analyzerPrinterBuff);
    
            pthread_mutex_unlock(&analyzerPrinterSync.mtx);
            sem_post(&analyzerPrinterSync.semEmptyBuffer);
            
            memcpy(storagePrinter->allRateValue,recivereader,(sizeof(double)*(coreSizeV->coresNumber+1)));
            free(recivereader);
    
            printerDisplay(storagePrinter);
 
            sleep(1);
            k++;
        }

        bufferDestroy(analyzerPrinterBuff);
        printerDestroy(storagePrinter);
        return NULL;

}


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


        pthread_join(threadTab[0],NULL);
        pthread_join(threadTab[1],NULL);
        pthread_join(threadTab[2],NULL);

        sem_destroy(&readAnalyzerSync.semEmptyBuffer);
        sem_destroy(&readAnalyzerSync.semFullBuffer);
        sem_destroy(&analyzerPrinterSync.semEmptyBuffer);
        sem_destroy(&analyzerPrinterSync.semFullBuffer);

        pthread_mutex_destroy(&readAnalyzerSync.mtx);
        pthread_mutex_destroy(&analyzerPrinterSync.mtx);

        free(coreSizeV);
        free(analizerSizeV);

    }