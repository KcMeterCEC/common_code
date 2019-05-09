#ifndef __HEAP_H__
#define __HEAP_H__
#include <stdbool.h>
#include <stdint.h>

typedef struct 
{
    int *buf;
    int size;
    int node_cnt;
    bool is_small;
}heap_t;

typedef struct 
{
    heap_t *(*create)(int size, bool is_small);
    bool    (*insert)(heap_t *hp, int node);
    bool    (*cover)(heap_t *hp, const int *buf, int size);
    void    (*sort)(heap_t *hp);
    void    (*print)(heap_t *hp);
    bool    (*del_top)(heap_t *hp, int *val);
}heap_api_t;

extern heap_api_t heap;
extern void heap_api_init(void);
#endif