//#include "analyzer.h"
#include "header.h"

ProcDate* analyzerCreate(coreSize* coresize){
 
    ProcDate* procDate=(ProcDate*)malloc(sizeof(*procDate)*(coresize->coresNumber+1));
    for(int i=0;i<=coresize->coresNumber;i++){
    *procDate[i].name=1;
    procDate[i].user=1;
    procDate[i].nice=1;
    procDate[i].system=1;
    procDate[i].idle=1;
    procDate[i].iowait=1;
    procDate[i].irq=1;
    procDate[i].softirq=1;
    procDate[i].steal=1;
    procDate[i].guest=1;
    procDate[i].guestNice=1;
    }

    return procDate;

}

double* analyzerCountRate(ProcDate* procDate,ProcDate* procDatePreviue,coreSize* coresize){

    double* allPercentValue=malloc(sizeof(double)*(coresize->coresNumber+1));
      
    for(int i=0;i<=coresize->coresNumber;i++)
    {
        long PrevIdle = procDatePreviue[i].idle + procDatePreviue[i].iowait;
        long Idle = procDate[i].idle +  procDate[i].iowait;

        long PrevNonIdle = procDatePreviue[i].user + procDatePreviue[i].nice + procDatePreviue[i].system + procDatePreviue[i].irq + procDatePreviue[i].softirq + procDatePreviue[i].steal;  
        long NonIdle = procDate[i].user + procDate[i].nice + procDate[i].system + procDate[i].irq + procDate[i].softirq + procDate[i].steal;

        long PrevTotal = PrevIdle + PrevNonIdle;
        long Total = Idle + NonIdle;

        double totald = (double)Total - (double)PrevTotal;
        double idled = (double)Idle - (double)PrevIdle;
        
 
        allPercentValue[i]=(1000*(totald - idled)/totald+1)/10;
       
    }
  
    return allPercentValue;
}

void analyzerDestroy(ProcDate* procDate,ProcDate* procDatePreviue){

    free(procDate);
    free(procDatePreviue);
}
