#include <stdio.h>
#include "stdlib.h"
#include "heap.h"
#include "definations.h"



int get_parent(int index)
{
    return (index-1)/2 ;
}
int left_child(int index)
{
    return (index*2)+1  ;
}
int right_child(int index)
{
    return (index*2)+2 ;
}
void init_minHeap( struct minHeap * heap,int cap)
{
  heap->arr = (struct Pair *)calloc(cap, sizeof(struct Pair));
  heap->capacity=cap ;
  heap->size= 0;

}
void insert_into_heap(struct minHeap * heap ,struct Pair val)
{
    heap->arr[heap->size]=val ;

    int index =heap->size ;
    heap->size++ ;
    while(index>0&&(heap->arr[index].first<heap->arr[get_parent(index)].first))
    {
        struct Pair temp =heap->arr[index] ;
        heap->arr[index] =heap->arr[get_parent(index)] ;
        heap->arr[get_parent(index)]=temp ;
        index =get_parent(index) ;
    }
}
void heapify(struct minHeap * heap ,int index)
{
   int min_index =index ;
   if(left_child(index)<heap->size&& heap->arr[left_child(index)].first<heap->arr[index].first)
   {
       min_index= left_child(index) ;
   }
    if(right_child(index)<heap->size&& heap->arr[right_child(index)].first<heap->arr[index].first)
    {
        min_index= right_child(index) ;
    }
    if(index!=min_index)
    {
        struct Pair temp = heap->arr[index] ;
        heap->arr[index] =heap->arr[min_index] ;
        heap->arr[min_index]=temp ;
        heapify(heap,min_index) ;
    }

}
struct Pair get_min(struct minHeap * heap)
{
   if(heap->size==0)
   {
       return (struct Pair){-1,-1};
   }
   struct Pair mini =heap->arr[0] ;

   heap->arr[0]=heap->arr[heap->size-1] ;
   heap->size-- ;
   heapify(heap,0) ;

   return mini ;
}
