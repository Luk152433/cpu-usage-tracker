//#include "thread.h"
#include "header.h"
coreSize*  coreSizeV;
   

void run(){

   
    
    Reader* reader=readerCreate("/proc/stat");
    reader=readerOpenSourceFile(reader);
    char*wsk= readerReadSourceFile(reader,coreSizeV);
   
    printf("%s%s",wsk,&wsk[1*sizeof(char)*(coreSizeV->amountSign)]);
    readerCloseSourceFile(reader);
    free(wsk);
   
    readerDestroy(reader);
    free(coreSizeV);
     
}
void prepareVariable()
{   coreSizeV=(coreSize*)malloc(sizeof(*coreSizeV));
    coreSizeV->amountSign=254;
    coreSizeV->coresNumber=1;

    

}