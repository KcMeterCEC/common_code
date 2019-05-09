#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "heap.h"
heap_api_t heap;

#define DBG_EN 0
#if DBG_EN 
#define dbg     printf
#else
#define dbg(...)
#endif

static void swap(int *a, int *b)
{
    dbg("swap [%d] and [%d]\n", *a, *b);

    int tmp = *b;
    *b = *a;
    *a = tmp;
}

static heap_t *heap_create(int size, bool is_small)
{
    heap_t *new_heap = (heap_t *)malloc(sizeof(heap_t));
    assert(new_heap);
    new_heap->buf = (int *)malloc((size + 1) * sizeof(int));
    assert(new_heap->buf);

    new_heap->size = size;
    new_heap->node_cnt = 0;
    new_heap->is_small = is_small;

    dbg("create a [%s] heap, it size is [%d]\n",
    is_small ? "small" : "big",
    size);
    return new_heap;
}
static bool heap_insert(heap_t *hp, int node)
{
    bool ret = true;

    if(hp->node_cnt >= hp->size)
    {
        ret = false;
        printf("heap buffer is overflow!\n");
        goto quick_out;
    }
    hp->buf[++hp->node_cnt] = node;
    dbg("insert node [%d] at [%d]\n", node, hp->node_cnt);

    if(hp->is_small)
    {
        for(int i = hp->node_cnt; i > 1; i /= 2)
        {
            if(hp->buf[i] < hp->buf[i / 2])
            {
                swap(&hp->buf[i], &hp->buf[i / 2]);
            }
            else
            {
                break;
            }
        }
    }
    else 
    {
        for(int i = hp->node_cnt; i > 1; i /= 2)
        {
            if(hp->buf[i] > hp->buf[i / 2])
            {
                swap(&hp->buf[i], &hp->buf[i / 2]);
            }
            else
            {
                break;
            }
        }
    }

quick_out:
    return ret;
}
static bool  heap_cover(heap_t *hp, const int *buf, int size)
{
    bool ret = true;
    if(hp->size < size)
    {
        ret = false;
        printf("heap doesn't have enough buffer.\n");
        goto quick_out;
    }
    memcpy(hp->buf, buf, size * sizeof(int));
    hp->node_cnt = size;
quick_out:
    return ret;
}
static void   do_small_heap(heap_t *hp, int index)
{
    bool is_swap = false;
    for(int j = index; j <= hp->node_cnt / 2; j++)
    {
        if(hp->buf[j] > hp->buf[2 * j])
        {
            swap(&hp->buf[j], &hp->buf[2 * j]);
            is_swap = true;
        }
        if(((2 * j + 1) <= hp->node_cnt) &&
            (hp->buf[j] > hp->buf[2 * j + 1]))
        {
            swap(&hp->buf[j], &hp->buf[2 * j + 1]); 
            is_swap = true;    
        }
        if(is_swap == false)
        {
            break;
        }
    }
}
static void   do_big_heap(heap_t *hp, int index)
{
    bool is_swap = false;
    for(int j = index; j <= hp->node_cnt / 2; j++)
    {
        if(hp->buf[j] < hp->buf[2 * j])
        {
            swap(&hp->buf[j], &hp->buf[2 * j]);
            is_swap = true;
        }
        if(((2 * j + 1) <= hp->node_cnt) &&
            (hp->buf[j] < hp->buf[2 * j + 1]))
        {
            swap(&hp->buf[j], &hp->buf[2 * j + 1]); 
            is_swap = true;    
        }
        if(is_swap == false)
        {
            break;
        }
    }
}
static void   heap_sort(heap_t *hp)
{
    int count = hp->node_cnt;
    if(hp->is_small)
    {
        for(int i = hp->node_cnt / 2; i >= 1; i--)
        {
            do_small_heap(hp, i);
        }
        while(hp->node_cnt > 1)
        {
            swap(&hp->buf[1], &hp->buf[hp->node_cnt]);
            hp->node_cnt--;
            do_small_heap(hp, 1);
        }
    }
    else
    {
        for(int i = hp->node_cnt / 2; i >= 1; i--)
        {
            do_big_heap(hp, i);
        }
        while(hp->node_cnt > 1)
        {
            swap(&hp->buf[1], &hp->buf[hp->node_cnt]);
            hp->node_cnt--;
            do_big_heap(hp, 1);
        }        
    }
    printf("after sort:\n");
    for(int i = 1; i <= count; i++)
    {
        printf("%d,", hp->buf[i]);
    }
    printf("\n");
}

static void heap_print(heap_t *hp)
{
    printf("heap contents are:\n");
    for(int i = 1; i <= hp->node_cnt; i++)
    {
        printf("%d,", hp->buf[i]);
    }
    printf("\n");
}

static bool heap_del_top(heap_t *hp, int *val)
{
    bool ret = true;

    if(hp->node_cnt == 0)
    {
        ret = false;
        printf("heap is empty!\n");
        goto quick_out;
    }
    *val = hp->buf[1];

    hp->buf[1] = hp->buf[hp->node_cnt];
    hp->node_cnt--;
    if(hp->is_small == true)
    {
        do_small_heap(hp, 1);
    }
    else 
    {
        do_big_heap(hp, 1);
    }

quick_out:
    return ret;
}

void heap_api_init(void)
{
    heap.create = heap_create;
    heap.cover = heap_cover;
    heap.sort = heap_sort;
    heap.print = heap_print;
    heap.insert = heap_insert;
    heap.del_top = heap_del_top;
}