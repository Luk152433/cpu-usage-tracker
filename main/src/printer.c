//#include "printer.h"
#include "header.h"

StoragePrinter* printerCreate(coreSize* coresize){

    StoragePrinter* storagePrinter=(StoragePrinter*)malloc(sizeof(*storagePrinter));
    storagePrinter->allRateValue=(double*)malloc(sizeof(double)*(coresize->coresNumber+1));
    storagePrinter->numberLevels=(coresize->coresNumber+1);

    return storagePrinter;
}

void printerDestroy(StoragePrinter* storageprinter){

    free(storageprinter->allRateValue);
    free(storageprinter);

}

void printerDisplay(StoragePrinter* storageprinter){

    for(int i=0;i<storageprinter->numberLevels;i++)
    {
        if(!i)
        {
            printf("total \t%.2f%% \n",storageprinter->allRateValue[i]);
        }else{
            printf("cpu%d \t%.2f%% \n",i-1,storageprinter->allRateValue[i]);
        }

    }
    
    printf("\n");

    return;
}