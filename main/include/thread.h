#ifndef THREAD_H
#define THREAD_H
void run();
void* readerThread(void* args);
void* analyzerThread(void* args);
void* printerThread(void* args);
void* watchdogThread(void* args);
void* loggerThread(void* args);

#endif 