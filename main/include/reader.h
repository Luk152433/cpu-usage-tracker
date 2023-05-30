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
void    readerReadSourceFile(const Reader* reader,int amountSign, int coresNumber);
uint8_t readerCloseSourceFile(const Reader* reader);
void    readerDestroy(Reader* reader);

#endif 