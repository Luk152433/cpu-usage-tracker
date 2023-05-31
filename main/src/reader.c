//#include <stdlib.h>
//#include <stdio.h>
//#include "reader.h"
#include "header.h"

Reader* readerCreate(char* path)
    {
        Reader* reader = (Reader*)malloc(sizeof(*reader));
        reader->path=path;

        return reader;
    }

Reader* readerOpenSourceFile(Reader* reader)
    {
        reader->f=fopen(reader->path,'r');

        return reader;
    }

char*    readerReadSourceFile(const Reader* reader,coreSize* coresize)
    {
        char* const line=(char*)malloc(sizeof(char)*(coresize->amountSign));
        char* const allSign=(char*)malloc(sizeof((coresize->amountSign)*((coresize->coresNumber)+1)));
        int countLoop=0;
        while (countLoop<=(coresize->coresNumber))
        {
            fgets(line,coresize->amountSign,reader->f);

            memcpy(allSign[countLoop*coresize->coresNumber],line,coresize->coresNumber);
            memset(line,0,coresize->coresNumber);
            countLoop++;
        }
        
        free(line);
        return allSign;
    }    

uint8_t readerCloseSourceFile(const Reader* reader)
    {
        return fclose(reader->f);
    } 

void    readerDestroy(Reader* reader)
    {
        free(reader);
    }    
