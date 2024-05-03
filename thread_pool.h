// #ifndef __THREAD_POOL_H__


struct thread_arg * init_thread_pool (pthread_t *threads,int threads_number) ;
void consume_requests(void *threadarg);

// #endif

