#include "heap.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define HEAP_SIZE (10)

#define OP_NORMAL 0
#define OP_PRIORITY_QUEUE  0
#define OP_TOPK     1
#if OP_TOPK
#define TOPN        5
#endif

int main(int argc, char *argv[])
{
    heap_api_init();

    heap_t * hp = heap.create(HEAP_SIZE, false);

    srand(time(NULL));
#if OP_NORMAL
    for(int i = 0; i < HEAP_SIZE; i++)
    {
        heap.insert(hp, rand() % 1000);
    }
    heap.print(hp);
    heap.sort(hp);

    int buf[HEAP_SIZE];
    for(int i = 0; i < HEAP_SIZE; i++)
    {
        buf[i] = rand() % 2000;
    }
    heap.cover(hp, buf, HEAP_SIZE);
    heap.print(hp);
    heap.sort(hp);
#elif OP_PRIORITY_QUEUE
    for(int i = 0; i < HEAP_SIZE; i++)
    {
        heap.insert(hp, rand() % 1000);
    }
    heap.print(hp);
    int val = 0;
    for(int i = 0; i < HEAP_SIZE; i++)
    {
        heap.del_top(hp, &val);
        heap.insert(hp, rand() % 1000);
        printf("priority queue val = %d\n", val);
        heap.print(hp);
    }    
#elif OP_TOPK
    heap_t * top_hp = heap.create(TOPN, true);
    for(int i = 0; i < TOPN; i++)
    {
        heap.insert(top_hp, rand() % 1000);
    }    
    heap.print(top_hp);
    int top_val;
    int del_val;
    for(int i = 0; i < HEAP_SIZE; i++)
    {
        top_val = rand() % 2000;
        printf("generate [%d]\n", top_val);

        if(top_val > top_hp->buf[1])
        {
            heap.del_top(top_hp, &del_val);
            heap.insert(top_hp, top_val);
        }
        heap.print(top_hp);
    }  

    printf("top %d values are :\n", TOPN);
    heap.sort(top_hp);  
#endif


    return 0;
}