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
        reader->f=fopen(reader->path,"r");

        return reader;
    }
    void readerReOpenSourceFile(Reader* reader)
    {  
        fclose(reader->f);
        reader->f=fopen(reader->path,"r");

        return;
    }

char*    readerReadSourceFile(const Reader* reader,coreSize* coresize)
    {
        
        char*const line=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));
        char*const allSign=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));
        
        int countLoop=0;
        while (countLoop<=(coresize->coresNumber))
        {  
            fgets(&line[countLoop*sizeof(char)*(coresize->amountSign)],sizeof(char)*(coresize->amountSign),reader->f);
       
            countLoop++;
        }
        memcpy(allSign,line,sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));
      
       
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
