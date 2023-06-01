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
//     if( reader->f == NULL ) {
//     fprintf( "Couldn't open %s\n", reader->path);
//    return EXIT_FAILURE;
// }
        return reader;
    }

char*    readerReadSourceFile(const Reader* reader,coreSize* coresize)
    {
        char*const line=(char*)malloc(sizeof(char)*(coresize->amountSign));
        char*const line2=(char*)malloc(sizeof(char)*(coresize->amountSign));
        char*const line3=(char*)malloc(sizeof(char)*(coresize->amountSign)*(coresize->coresNumber+1));
        int countLoop=0;
        while (countLoop<=(coresize->coresNumber))
        {   //if(countLoop<1){
            //fgets(line,coresize->amountSign,reader->f);}
            fgets(&line3[countLoop*sizeof(char)*(coresize->amountSign)],sizeof(char)*(coresize->amountSign),reader->f);
            //else
             //fgets(line2,coresize->amountSign,reader->f);
            //char* i=&line[0];
            //char* j=&allSign[countLoop*(coresize->amountSign)];
            //while(i!='\n')
           // {
               // *(j++)=*(i++);
            //}
            //strcpy(&allSign[countLoop*(coresize->amountSign)],&line[0]);
           // memcpy(&allSign[countLoop*(coresize->amountSign)],line,coresize->amountSign);
            //memset(line,0,coresize->amountSign);
            countLoop++;
        }
        printf("%s%s",line3,&line3[1*sizeof(char)*(coresize->amountSign)]);
         free(line);
         free(line2);
        //free(line3);
         
       
        
        return line3;
    }    

uint8_t readerCloseSourceFile(const Reader* reader)
    {   
       // fflush (reader->f);
        return fclose(reader->f);
    } 

void    readerDestroy(Reader* reader)
    {
        
        free(reader);
    }    
