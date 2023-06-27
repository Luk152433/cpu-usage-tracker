#ifndef THREAD_H
#define THREAD_H
void run(void);
void* readerThread(void* args);
void* analyzerThread(void* args);
void* printerThread(void* args);
void signal_exit(const int32_t  signum);

#endif 

