#include "stack_list.h"
#include <stdlib.h>
#include <assert.h>

struct stack_list_api stack_list;

static struct list_node * stack_list_create_obj(void)
{
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    assert(new_node);
    undir_list.init_obj(new_node);
}
static bool stack_list_push(struct list_node *head, struct list_node *new_node)
{
    undir_list.insert(head, new_node);
}
static struct list_node * stack_list_pop(struct list_node *head)
{
    struct list_node *new_node = NULL;
    if(undir_list.is_empty(head) == true)
    {
        goto quick_exit;
    }
    new_node = head->next;
    undir_list.remove_next(head);

quick_exit:
    return new_node;
}
static bool stack_list_is_empty(struct list_node *head)
{
    return undir_list.is_empty(head);
}
void stack_list_str_init(void)
{
    unidir_list_str_init();

    stack_list.create_obj = stack_list_create_obj;
    stack_list.push = stack_list_push;
    stack_list.pop = stack_list_pop;
    stack_list.is_empty = stack_list_is_empty;
}