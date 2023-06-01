//#include "thread.h"
#include "header.h"

void run(){
    
    coreSize* coreSizeV=(coreSize*)malloc(sizeof(*coreSizeV));
   
    coreSizeV->amountSign=254;
    coreSizeV->coresNumber=1;
    Reader* reader=readerCreate("/proc/stat");
    reader=readerOpenSourceFile(reader);
    char*wsk= readerReadSourceFile(reader,coreSizeV);
   
     printf("%s%s",wsk,&wsk[1*sizeof(char)*(coreSizeV->amountSign)]);
    readerCloseSourceFile(reader);
    free(wsk);
    free(coreSizeV);
    readerDestroy(reader);
    
}