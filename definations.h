
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <semaphore.h>
#define NUM_REQUESTS_BUFFER 100
#define NUM_THREADS 2



// Thread Pool structure

struct thread_pool_type
{
pthread_mutex_t BufferLock ;
pthread_cond_t EMPTY ;

};

// Scheduler structure
struct scheduler_type {

    int BUFFER_STACK[NUM_REQUESTS_BUFFER];
    struct queue *BUFFER_QUEUE ;
    struct minHeap *BUFFER_HEAP ;
    int curr_size;

};

// Arguments passed to workder threads
 struct thread_arg {

    struct scheduler_type * scheduler;
    struct thread_pool_type * pool;
    char *algorithm_type;
    int requests_counter ;

};



// Generic Functions :

int request_parse_uri(char *uri, char *filename, char *cgiargs);
int get_filesize(int con_fd);



#endif
