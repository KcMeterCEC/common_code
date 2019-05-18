#include "bfs.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef struct 
{
    vertex_t vertex;
    struct list_node node;
}list_t;

static void bfs_insert_node(struct list_node *node, const vertex_t *edge)
{
    list_t *new_node = (list_t *)malloc(sizeof(list_t));
    assert(new_node);
    memset(new_node, 0, sizeof(list_t));

    new_node->vertex = *edge;

    undir_list.insert(node, &new_node->node);
}

static map_t * bfs_create_map(vertex_t *v, int size)
{
    map_t *map = (map_t *)malloc(sizeof(map_t));
    assert(map);

    map->array = (struct list_node *)malloc(sizeof(struct list_node) * size);
    assert(map->array);
    
    map->size = size;
    

    for(int i = 0; i < size; i++)
    {
        undir_list.init_obj(&map->array[i]);
        bfs_insert_node(&map->array[i], &v[i]);
    }

    return map;
}
static bool bfs_add_edge(map_t * map, vertex_t *v, vertex_t *edge)
{
    bool ret = false;
    list_t *first;
    for(int i = 0; i < map->size; i++)
    {
        first = unidir_list_first_entry(&map->array[i], list_t, node);

        if(strcmp(first->vertex.name, v->name) == 0)
        {
            bfs_insert_node(map->array[i].next, edge);
            ret = true;
            break;
        }
    }
    if(ret == false)
    {
        printf("can not add edge [%s]\n", edge->name);
    }

    return ret;
}

static void bfs_print_map(map_t * map)
{
    list_t *v;
    for(int i = 0; i < map->size; i++)
    {
        printf("array %d: ", i);

        unidir_list_for_each_entry(v, &map->array[i], list_t, node)
        {
            printf("[%s], ", v->vertex.name);
        }
        printf("\n");
    }
}
static void bfs_find_key(map_t * map, vertex_t *start)
{
    list_t *first;
    for(int i = 0; i < map->size; i++)
    {
        first = unidir_list_first_entry(&map->array[i], list_t, node);

        if(strcmp(first->vertex.name, start->name) == 0)
        {
            break;
        }
    }

    first->vertex.visited = true;

    struct list_node scan;
 
    undir_list.init_obj(&scan);
    undir_list.insert(&scan, &first->node);

    list_t *actually_node;

    struct list_node *head;
    while(undir_list.is_empty(&scan) == false)
    {
        first = unidir_list_first_entry(&scan, list_t, node);
        undir_list.remove_next(&scan);
        for(int i = 0; i < map->size; i++)
        {
            actually_node = unidir_list_first_entry(&map->array[i], list_t, node);

            if(strcmp(actually_node->vertex.name, first->vertex.name) == 0)
            {
                head = &map->array[i];
                printf("head = %p, i = %d\n", head, i);
                break;
            }
        }

        printf("scan start:[%s]\n", actually_node->vertex.name);
        unidir_list_for_each_entry(actually_node, head, list_t, node)
        {
            printf("%s, ", actually_node->vertex.name);
            if(actually_node->vertex.visited == false)
            {
                actually_node->vertex.visited = true;
                if(actually_node->vertex.has_key == true)
                {
                    printf("%s has the key!\n", actually_node->vertex.name);
                    return;
                }
                undir_list.insert(&scan, &actually_node->node);
            }
        }
        printf("\n");
    }
}

struct bfs_api bfs;
void bfs_str_init(void)
{
    unidir_list_str_init();

    bfs.create_map = bfs_create_map;
    bfs.add_edge = bfs_add_edge;
    bfs.print_map = bfs_print_map;
    bfs.find_key = bfs_find_key;
}