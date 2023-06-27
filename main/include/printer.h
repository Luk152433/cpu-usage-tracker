#ifndef PRINTER_H
#define PRINTER_H

typedef struct StoragePrinter
{
    double* allRateValue;
	uint8_t numberLevels;
    
}StoragePrinter;

StoragePrinter* printerCreate(const coreSize*const coresize);
void printerDisplay(const StoragePrinter*const storageprinter);
void printerDestroy(StoragePrinter*const storageprinter);

#endif 

