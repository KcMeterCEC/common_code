#ifndef __QUEUE_LIST__
#define __QUEUE_LIST__

#include <stdint.h>
#include <stdbool.h>
#include "list.h"

struct queue_list_api
{
    struct list_node * (*create_obj)(void);
    bool (*write)(struct list_node *head, struct list_node *new_node);
    struct list_node * (*read)(struct list_node *head);
    bool (*is_empty)(struct list_node *head);
};

extern struct queue_list_api queue_list;
extern void queue_list_str_init(void);
#endif
