#include "header.h"
#include <assert.h>
#include <unistd.h>
#include <sys/sysinfo.h>

void testCreateReader(void)
{
    Reader* reader=readerCreate("/proc/stat");
    assert(reader!=NULL);

    readerDestroy(reader);

}

void testReaderOpenSourceFile(void)
{   Reader Mreader;
    Mreader.path="/proc/stat";
    Reader* reader=readerOpenSourceFile(&Mreader);
    assert(reader!=NULL);


}
void testReaderReadSourceFile(void)
{ 
    Reader* reader=readerCreate("/proc/stat");
    assert(reader!=NULL);

    reader=readerOpenSourceFile(reader);
    assert(reader!=NULL);

    coreSize coresize;
    coresize.amountSign=254;
    coresize.coresNumber=get_nprocs_conf();
    char* TempWsk=readerReadSourceFile(reader,&coresize);
    assert(TempWsk!=NULL);

    free(TempWsk);
    readerDestroy(reader);

} 

void testReaderCloseSourceFile(void)
{  
    Reader* reader=readerCreate("/proc/stat");
    assert(reader!=NULL);

    reader=readerOpenSourceFile(reader);
    assert(reader!=NULL);

   uint8_t TempClose= readerCloseSourceFile(reader);
    assert(TempClose!=1);

    readerDestroy(reader);

}

void testReader(void)
{
    testCreateReader();
    testReaderOpenSourceFile();
    testReaderReadSourceFile();
    testReaderCloseSourceFile();
}