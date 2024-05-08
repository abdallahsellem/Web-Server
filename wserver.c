#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <netinet/in.h>
#include "request.h"
#include "io_helper.h"
#include "thread_pool.h"
#include "producer.h"
#include "definations.h"
char default_root[] = ".";


int main(int argc, char *argv[]) {
    int c;
    char *root_dir = default_root;
    int port = 10000;
	int num_threads=10;
    char algorithm_type[100];
    pthread_t threads[num_threads];

    while ((c = getopt(argc, argv, "d:p:t:s:")) != -1) {
        switch (c) {
            case 'd':
                root_dir = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
			case 't':
                num_threads = atoi(optarg);
                break;
            case 's':
                strcpy(algorithm_type, optarg);
                break;
            default:
                fprintf(stderr, "usage: wserver [-d basedir] [-p port]\n");
                exit(1);
        }
    }
    // Start the thread pool
    struct thread_arg *thread_arg_obj=init_server(threads,num_threads,algorithm_type);
    // Change to the specified directory
    chdir_or_die(root_dir);

    // Initialize server
    int listen_fd = open_listen_fd_or_die(port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int conn_fd = accept_or_die(listen_fd, (struct sockaddr *) &client_addr, &client_len);
    
		accept_request(conn_fd,thread_arg_obj);
    }

    return 0;
}