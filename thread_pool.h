// #ifndef __THREAD_POOL_H__


struct scheduler_type *init_scheduler(char *algorithm_type);

struct thread_pool_type *init_thread_pool();

struct thread_arg *init_server_arg(struct thread_pool_type *thread_pool_obj,struct scheduler_type *scheduler_obj, char *algorithm_type);

struct thread_arg * init_server (pthread_t *threads,int threads_number,char *algorithm_type) ;

void consume_requests(void *threadarg);

// #endif

