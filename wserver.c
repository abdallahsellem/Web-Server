#include <stdio.h>
#include "request.h"
#include "io_helper.h"
#include <pthread.h>

# define NUM_REQUESTS_BUFFER 100 
# define NUM_THREADS 4
pthread_mutex_t BufferLock=PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t Cond = PTHREAD_COND_INITIALIZER;

int requests_counter=0 ;
int BUFFER[NUM_REQUESTS_BUFFER];

char default_root[] = ".";
//
// ./wserver [-d <basedir>] [-p <portnum>] 
// 
void thread_function()
{
	printf("Mahmoud \n");
   while(1)
   {
	pthread_mutex_lock(&BufferLock);

	while (requests_counter == 0) {
        pthread_cond_wait(&Cond, &BufferLock);
    }
	int request =BUFFER[requests_counter-1];
	requests_counter-- ;
	pthread_mutex_unlock(&BufferLock);
	printf(" counter %d \n",request);
	request_handle(request);
	
   }
}
void init_thread_pool(pthread_t *threads)
{
	printf("ahmedInside \n");
    // Create worker threads
    for (int i = 0; i < NUM_THREADS; i++) {
		printf("SAID \n");
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }
}

int main(int argc, char *argv[]) {
	// define Variables and datastructres 
    int c;
    char *root_dir = default_root;
    int port = 10000;
    pthread_t threads[NUM_THREADS];
	printf("\n \n \n \n ana zha222t \n \n");
	pthread_mutex_init(&BufferLock, NULL);


    while ((c = getopt(argc, argv, "d:p:")) != -1)
	{

	switch (c) {
	case 'd':
	    root_dir = optarg;
	    break;
	case 'p':
	    port = atoi(optarg);
	    break;
	default:
	    fprintf(stderr, "usage: wserver [-d basedir] [-p port]\n");
	    exit(1);
	}
	}
	// start the thread Pool 
	printf("Ahmed \n");
	init_thread_pool(threads) ;

    // run out of this directory
    chdir_or_die(root_dir);

    // now, get to work
    int listen_fd = open_listen_fd_or_die(port);
    while (1) {

	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	int conn_fd = accept_or_die(listen_fd, (sockaddr_t *) &client_addr, (socklen_t *) &client_len);

	// if the buffer is full , replay to the client with "try again later"
	if(requests_counter==100)
	{
		send(conn_fd, "Please Try Again Later", strlen("Please Try Again Later "), 0);
	}
	else{
	pthread_mutex_lock(&BufferLock);
	BUFFER[requests_counter]=conn_fd ;
	printf("%d \n",conn_fd);
	requests_counter++ ;
	pthread_cond_broadcast(&Cond);
	pthread_mutex_unlock(&BufferLock);
	}
	// close_or_die(conn_fd);
    }
    return 0;
}


    


 
