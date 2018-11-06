#ifndef __STACK_LIST_H__
#define __STACK_LIST_H__

#include <stdint.h>
#include <stdbool.h>
#include "unidir_list.h"

struct stack_list_api
{
    struct list_node * (*create_obj)(void);
    bool (*push)(struct list_node *head, struct list_node *new_node);
    struct list_node * (*pop)(struct list_node *head);
    bool (*is_empty)(struct list_node *head);
};

extern struct stack_list_api stack_list;
extern void stack_list_str_init(void);
#endif