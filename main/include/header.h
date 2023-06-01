#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>


typedef struct coreSize
{
    int amountSign;
    int coresNumber;
}coreSize;

typedef struct BufferCircularBuf {
	char* buffer;
	size_t head;
	size_t tail;
	size_t courentFillBuffer;
	size_t maxSize;
	size_t sizeOnePacket;
	pthread_mutex_t mutex; 
	
}BufferCircularBuf;

#include "analyzer.h"
#include "buffer.h"
#include "printer.h"
#include "reader.h"
#include "thread.h"




#endif