#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread_pool.h"
#include "definations.h"
#include "request.h"
#include "queue.h"
struct scheduler_type *init_scheduler(char *algorithm_type)
{
    struct scheduler_type *scheduler_obj = (struct scheduler_type *)malloc(sizeof(struct scheduler_type));
    if (strcmp(algorithm_type, "FIFO") == 0)
    {
        scheduler_obj->BUFFER_QUEUE = (struct queue *)malloc(sizeof(struct queue));
    }
    else if (strcmp(algorithm_type, "SFF") == 0)
    {
    }
    return scheduler_obj;
}
struct thread_pool_type *init_thread_pool()
{
    struct thread_pool_type *thread_pool_obj = (struct thread_pool_type *)malloc(sizeof(struct thread_pool_type));
    return thread_pool_obj;
}

struct thread_arg *init_server_arg(struct thread_pool_type *thread_pool_obj, struct scheduler_type *scheduler_obj, char *algorithm_type)
{
    struct thread_arg *thread_arg_obj = (struct thread_arg *)malloc(sizeof(struct thread_arg));
    thread_arg_obj->scheduler = scheduler_obj;
    thread_arg_obj->pool = thread_pool_obj;
    thread_arg_obj->requests_counter = 0;
    thread_arg_obj->algorithm_type = algorithm_type;
    return thread_arg_obj;
}
struct thread_arg *init_server(pthread_t *threads, int threads_number, char *algorithm_type)
{
    struct thread_pool_type *thread_pool_obj = init_thread_pool();
    struct scheduler_type *scheduler_obj = init_scheduler(algorithm_type);
    struct thread_arg *thread_arg_obj = init_server_arg(thread_pool_obj, scheduler_obj,algorithm_type);
    pthread_mutex_init(&thread_arg_obj->pool->BufferLock, NULL);
    pthread_cond_init(&thread_arg_obj->pool->EMPTY, NULL);
    // Create worker threads
    for (int i = 0; i < threads_number; i++)
    {
        pthread_create(&threads[i], NULL, consume_requests, thread_arg_obj);
    }
    printf(" \n Thread Pool Started with %d  number of Threads \n", threads_number);

    return thread_arg_obj;
}

void consume_requests(void *threadarg)
{
    struct thread_arg *thread_arg_obj = (struct thread_arg *)threadarg;

    while (1)
    {
        pthread_mutex_lock(&thread_arg_obj->pool->BufferLock);

        // Wait until there are requests available
        while (thread_arg_obj->requests_counter == 0)
        {
            pthread_cond_wait(&thread_arg_obj->pool->EMPTY, &thread_arg_obj->pool->BufferLock);
        }

        int request = 0;
        if (strcmp(thread_arg_obj->algorithm_type, "FIFO")==0)
        {
            request=dequeue(thread_arg_obj->scheduler->BUFFER_QUEUE);
        }
        else
        {
            request = thread_arg_obj->scheduler->BUFFER_STACK[thread_arg_obj->requests_counter - 1];
        }
        thread_arg_obj->requests_counter--;
        printf("\n *************************************************************************** \n");
        printf(" (inside thread pool) Served request: %d\n", request);
        printf(" left requests: %d\n", thread_arg_obj->requests_counter);
        printf("\n *************************************************************************** \n");

        pthread_mutex_unlock(&thread_arg_obj->pool->BufferLock);

        sleep(1);
        // Handle the request
        request_handle(request);
    }
}