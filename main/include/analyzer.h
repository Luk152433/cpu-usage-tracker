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

ProcDate* analyzerCreate(coreSize* coresize);
double* analyzerCountRate(ProcDate* procDate,ProcDate* procDatePreviue,coreSize* coresize);
void analyzerDestroy(ProcDate* procDate,ProcDate* procDatePreviue);


#endif 