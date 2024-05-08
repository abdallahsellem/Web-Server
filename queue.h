#include "definations.h"

// Queue  structure

struct queue
{
    int arr[NUM_REQUESTS_BUFFER];
    int rear;
    int front;
    int size;
};

void create_queue( struct queue *pt);

void enqueue(int value, struct queue* pt);

int dequeue(struct queue* pt);
int peek(struct queue* pt);
int empty_queue(struct queue *pt);
int queue_size(struct queue *pt);
int queue_full(struct queue* pt);
void clear_queue(struct queue* pt);
void Display_queue(struct queue* pt);