#ifndef READER_H
#define READER_H
#include "header.h"
//void fun(int a);

typedef struct Reader
    {
        char *path;
        FILE* f;    
    }Reader;



Reader* readerCreate(char* path);
Reader* readerOpenSourceFile(Reader* reader);
char*   readerReadSourceFile(const Reader* reader,coreSize* coresize);
uint8_t readerCloseSourceFile(const Reader* reader);
void    readerDestroy(Reader* reader);

#endif 