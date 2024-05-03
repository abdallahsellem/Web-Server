
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_REQUESTS_BUFFER 100
#define NUM_THREADS 2


struct thread_pool_type
{
pthread_mutex_t BufferLock ;
pthread_cond_t EMPTY ;

};

// Scheduler structure
struct scheduler_type {

    int BUFFER[NUM_REQUESTS_BUFFER];
    int curr_size;

};

// Arguments passed to workder threads
 struct thread_arg {

    struct scheduler_type * scheduler;
    struct thread_pool_type * pool;
    int requests_counter ;

};


#endif
