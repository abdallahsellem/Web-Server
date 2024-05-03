#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread_pool.h"
#include "definations.h"
#include "request.h"
struct thread_arg *init_thread_pool(pthread_t *threads,int threads_number) 
{
    struct thread_pool_type *thread_pool_obj = (struct thread_pool_type*)malloc(sizeof(struct thread_pool_type));
    struct scheduler_type *scheduler_obj = (struct scheduler_type*)malloc(sizeof(struct scheduler_type));
    struct thread_arg *thread_arg_obj = (struct thread_arg*)malloc(sizeof(struct thread_arg));
    thread_arg_obj->scheduler=scheduler_obj;
    thread_arg_obj->pool=thread_pool_obj;
    thread_arg_obj->requests_counter=0 ;
    pthread_mutex_init(&thread_arg_obj->pool->BufferLock, NULL);
    pthread_cond_init(&thread_arg_obj->pool->EMPTY, NULL);



    // Create worker threads
    for (int i = 0; i < threads_number; i++) {
        pthread_create(&threads[i], NULL, consume_requests, thread_arg_obj);
    }
    printf(" \n Thread Pool Started with %d  number of Threads \n",threads_number);

    return thread_arg_obj ;

}

void consume_requests(void *threadarg) {
	struct thread_arg  * thread_arg_obj = (struct thread_arg *)threadarg ;
    while (1) {
        pthread_mutex_lock(&thread_arg_obj->pool->BufferLock);

        // Wait until there are requests available
        while (thread_arg_obj->requests_counter == 0) {
            pthread_cond_wait(&thread_arg_obj->pool->EMPTY, &thread_arg_obj->pool->BufferLock);
        }
        
        int request = thread_arg_obj->scheduler->BUFFER[thread_arg_obj->requests_counter- 1];
        thread_arg_obj->requests_counter--;
        printf("\niam inside thread pool Number of requests available now : %d\n", thread_arg_obj->requests_counter);
        printf("Served request: %d\n", request);

        pthread_mutex_unlock(&thread_arg_obj->pool->BufferLock);

		sleep(1);
        // Handle the request
        request_handle(request);
    }
}


