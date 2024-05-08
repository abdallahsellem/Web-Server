struct Pair {
    int first;
    int second;
};

struct minHeap{
    struct Pair * arr ;
    int capacity ;
    int size  ;

};

void init_minHeap( struct minHeap * heap,int cap);
void insert_into_heap(struct minHeap * heap ,struct Pair val);
struct Pair get_min(struct minHeap * heap);
