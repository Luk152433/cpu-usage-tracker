#ifndef HEADER_H
#define HEADER_H
#define  _POSIX_C_SOURCE  200809L
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/sysinfo.h>


typedef struct coreSize
{
    uint16_t amountSign;
    uint8_t coresNumber;
}coreSize;

typedef struct BufferCircularBuf {
	char*  buffer;
	size_t head;
	size_t tail;
	size_t courentFillBuffer;
	size_t maxSize;
	size_t sizeOnePacket;
	pthread_mutex_t mutex; 	
}BufferCircularBuf;

typedef struct mutexSema
    {
        pthread_mutex_t mtx;
        sem_t semEmptyBuffer;
        sem_t semFullBuffer;

    }mutexSema;


#define THREADS_NUM 5
#define BUFFER_NUM 10
#include "analyzer.h"
#include "buffer.h"
#include "printer.h"
#include "reader.h"
#include "thread.h"




#endif

