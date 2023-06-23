//#include "thread.h"
#include "header.h"
static coreSize*  coreSizeV;
static coreSize*  analizerSizeV;

typedef struct mutexSema
    {
        pthread_mutex_t mtx;
        sem_t semEmptyBuffer;
        sem_t semFullBuffer;

    }mutexSema;

static BufferCircularBuf* readAnalyzerBuff,*analyzerPrinterBuff;
static StoragePrinter* storagePrinter;
static Reader* reader;
static ProcDate* procDate;
static ProcDate* procDatePreviue;
static char* wskReader;
static char* reciveAnalyzer;
static double* allPrec;
static char* temp;
static double* recivePrinter;
static pthread_t threadTab[THREADS_NUM];
static mutexSema readAnalyzerSync;
static mutexSema analyzerPrinterSync;
static int FlagawskReader;
static int FlagareciveAnalyzer;
static int FlagaallPrec;
static int Flagatemp;
static int FlagarecivePrinter;

void prepareVariable(void);
void  setThread(void);

void signal_exit(const int signum) 
    {
  
        printf(" Signal %d end run\n", signum);
        free(coreSizeV);
        free(analizerSizeV);
        if(FlagawskReader==1)
        free(wskReader);
        readerCloseSourceFile(reader);
        readerDestroy(reader);
        bufferDestroy(readAnalyzerBuff);
        if(FlagareciveAnalyzer==1)
        free(reciveAnalyzer);
        if(FlagaallPrec==1)
        free(allPrec);
        if(Flagatemp==1)
        free(temp);
        if(FlagarecivePrinter==1)
        free(recivePrinter);
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
            FlagawskReader=1;
            sem_wait(&readAnalyzerSync.semEmptyBuffer);
            pthread_mutex_lock(&readAnalyzerSync.mtx);
    
            bufferSetValue(readAnalyzerBuff,wskReader);
        
            pthread_mutex_unlock(&readAnalyzerSync.mtx);
            sem_post(&readAnalyzerSync.semFullBuffer);

            free(wskReader);
            FlagawskReader=0;
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
            FlagareciveAnalyzer=1;
            pthread_mutex_unlock(&readAnalyzerSync.mtx);
            sem_post(&readAnalyzerSync.semEmptyBuffer);
    
    

            for(int i=0;i<=coreSizeV->coresNumber;i++)
                {

                    sscanf((char*)&reciveAnalyzer[i*sizeof(char)*(coreSizeV->amountSign)],"%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",procDate[i].name,&procDate[i].user,&procDate[i].nice,&procDate[i].system,
                    &procDate[i].idle,&procDate[i].iowait,&procDate[i].irq,&procDate[i].softirq,&procDate[i].steal,&procDate[i].guest,&procDate[i].guestNice);

                }
            
            free(reciveAnalyzer);
            FlagareciveAnalyzer=0;

            allPrec=analyzerCountRate( procDate,procDatePreviue,coreSizeV);
            FlagaallPrec=1;

   
            sem_wait(&analyzerPrinterSync.semEmptyBuffer);
            pthread_mutex_lock(&analyzerPrinterSync.mtx);
     

            temp=(char*)malloc(sizeof(double)*(coreSizeV->coresNumber+1));
            Flagatemp=1;
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
            Flagatemp=0;
            free(allPrec);
             FlagaallPrec=0;
           
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
    
            recivePrinter= (double*)bufferGetValue(analyzerPrinterBuff);
            FlagarecivePrinter=1;
            pthread_mutex_unlock(&analyzerPrinterSync.mtx);
            sem_post(&analyzerPrinterSync.semEmptyBuffer);
            
            memcpy(storagePrinter->allRateValue,recivePrinter,(sizeof(double)*(coreSizeV->coresNumber+1)));
            free(recivePrinter);
            FlagarecivePrinter=0;
    
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

