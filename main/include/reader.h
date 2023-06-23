#ifndef READER_H
#define READER_H
#include "header.h"
//void fun(int a);

typedef struct Reader
    {
        char *path;
        FILE* f;    
    }Reader;



Reader* readerCreate(char*const path);
Reader* readerOpenSourceFile(Reader*const reader);
void    readerReOpenSourceFile(Reader*const reader);
char*   readerReadSourceFile(const Reader*const reader,const coreSize*const coresize);
uint8_t readerCloseSourceFile(const Reader*const reader);
void    readerDestroy(Reader*const reader);

#endif 

