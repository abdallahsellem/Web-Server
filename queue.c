
#include "queue.h"
#include "definations.h"
void create_queue( struct queue *pt)
{
    pt->rear = -1;
    pt->front = -1;
    pt->size = 0;
}

void enqueue(int value, struct queue * pt)
{
    pt->arr[++pt->rear%NUM_REQUESTS_BUFFER] = value;
    pt->size++;
    if (pt->front == -1)
    {
        pt->front++;
    }

}

int dequeue(struct queue* pt)
{
    int value_front = pt->arr[pt->front];
    pt->size--;
    pt->front = (pt->front + 1) % NUM_REQUESTS_BUFFER;
    return value_front;
}
int peek(struct queue* pt)
{
    return pt->arr[pt->front];
}
int empty_queue(struct queue *pt)
{
    return !pt->size;
}
int queue_size(struct queue *pt)
{
    return pt->size;
}
int queue_full(struct queue* pt)
{
    return pt->size == NUM_REQUESTS_BUFFER;

}
void clear_queue(struct queue* pt)
{
    pt->size = 0;
    pt->front = -1;
    pt->rear = -1;
}
void Display_queue(struct queue* pt)
{
    int pos = pt->front;

    while (pos != pt->rear)
    {
        printf("%d",pt->arr[pos]);
        pos = pos + 1 % NUM_REQUESTS_BUFFER;
    }
    if (pt->size != 0)
    {
        printf("%d",pt->arr[pos]);
    }

}
