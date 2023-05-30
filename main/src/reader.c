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

void    readerReadSourceFile(const Reader* reader,int amountSign, int coresNumber)
    {
        char* const line=(char*)malloc(sizeof(char)*amountSign);
        char* const allSign=(char*)malloc(sizeof(amountSign*(coresNumber+1)));
    }    

uint8_t readerCloseSourceFile(const Reader* reader)
    {
        return fclose(reader->f);
    } 

void    readerDestroy(Reader* reader)
    {
        free(reader);
    }    
