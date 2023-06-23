#ifndef ANALYZER_H
#define ANALYZER_H

typedef struct ProcDate {
	char name[10];
	long user;
    long nice;
    long system;
    long idle;
    long iowait;
    long irq;
    long softirq;
    long steal;
    long guest;
    long guestNice;

	
}ProcDate;

ProcDate* analyzerCreate(coreSize*const coresize);
double* analyzerCountRate(ProcDate*const procDate,ProcDate*const procDatePreviue,const coreSize*const coresize);
void analyzerDestroy(ProcDate*const procDate,ProcDate*const procDatePreviue);


#endif 

