#ifndef PRINTER_H
#define PRINTER_H

typedef struct StoragePrinter
{
    double* allRateValue;
	int numberLevels;
    
}StoragePrinter;

StoragePrinter* printerCreate(coreSize* coresize);
void printerDisplay(StoragePrinter* storageprinter);
void printerDestroy(StoragePrinter* storageprinter);

#endif 