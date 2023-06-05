#ifndef THREAD_H
#define THREAD_H
void run(void);
void* readerThread(void* args);
void* analyzerThread(void* args);
void* printerThread(void* args);
void signal_exit(int signum);

#endif 

