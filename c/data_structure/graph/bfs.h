#ifndef __BFS_H__
#define __BFS_H__
#include "unidir_list.h"

typedef struct 
{
    char *name;
    bool visited;
    bool has_key;
}vertex_t;
typedef struct 
{
    struct list_node *array;
    int     size;
}map_t;
struct bfs_api
{
    map_t * (*create_map)(vertex_t *v, int size);
    bool (*add_edge)(map_t * map, vertex_t *v, vertex_t *edge);
    void (*print_map)(map_t * map);
    void (*find_key)(map_t * map, vertex_t *start);
};

extern struct bfs_api bfs;
extern void bfs_str_init(void);
#endif
