#ifndef THREAD_H
#define THREAD_H
void run(void);
void* readerThread(void* args);
void* analyzerThread(void* args);
void* printerThread(void* args);
void signal_exit(int signum);
void SemInitProducerConsumerMaxBuff(mutexSema*const producerConsumerSync);
void SemInitProducerConsumerCountBuff(mutexSema*const producerConsumerSync);
void SemDestroyProducerConsumerMaxBuff(mutexSema*const producerConsumerSync);
void SemDestroyProducerConsumerCountBuff(mutexSema*const producerConsumerSync);

#endif 

