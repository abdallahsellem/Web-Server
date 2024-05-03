#include "definations.h"
#include "producer.h"
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void accept_request(int conn_fd ,struct thread_arg *thread_arg_obj)
{


	    // Lock the buffer
        pthread_mutex_lock(&thread_arg_obj->pool->BufferLock);
        // If the buffer is full, reply to the client with "try again later"
        if (thread_arg_obj->requests_counter>= NUM_REQUESTS_BUFFER) {
            send(conn_fd, "Please Try Again Later", strlen("Please Try Again Later"), 0);
        } else {

            // Add the connection to the buffer
            thread_arg_obj->scheduler->BUFFER[thread_arg_obj->requests_counter] = conn_fd;
            thread_arg_obj->requests_counter++;
            printf("\nNumber of requests available now: %d\n", thread_arg_obj->requests_counter);
            // Signal the condition variable to wake up worker threads
            pthread_cond_signal(&thread_arg_obj->pool->EMPTY);

        }

        // Unlock the buffer
        pthread_mutex_unlock(&thread_arg_obj->pool->BufferLock);

}