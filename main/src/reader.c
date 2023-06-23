//#include <stdlib.h>
//#include <stdio.h>
//#include "reader.h"
#include "header.h"

Reader* readerCreate(char*const path)
    {
        if(path==NULL){
            return NULL;
        }

        Reader*const reader = (Reader*const)malloc(sizeof(*reader));
        reader->path=path;

        
        return reader;
    }

Reader* readerOpenSourceFile(Reader*const reader)
    {   
        if(reader==NULL){
            return NULL;
        }

        reader->f=fopen(reader->path,"r");
        if(reader->f==NULL){
            return NULL;
        }

        return reader;
    }
    void readerReOpenSourceFile(Reader*const reader)
    {  
        fclose(reader->f);
        reader->f=fopen(reader->path,"r");
        
        return;
    }

    char* readerReadSourceFile(const Reader*const reader,const coreSize*const coresize)
    {
        
        char*const line=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));
        char*const allSign=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));

        if(line==NULL || allSign==NULL){
            return NULL;
        }

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

    uint8_t readerCloseSourceFile(const Reader*const reader)
    {     
        if(reader==NULL){
            return 1;
        }

        return fclose(reader->f);
    } 

    void    readerDestroy(Reader*const reader)
    {   
        free(reader);
    }    
