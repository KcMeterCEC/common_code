#include "queue_list.h"
#include <stdlib.h>
#include <assert.h>

struct queue_list_api queue_list;

static struct list_node * queue_list_create_obj(void)
{
    struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
    assert(new_node);
    list.init_obj(new_node);
}
static bool queue_list_write(struct list_node *head, struct list_node *new_node)
{
    list.add_before(new_node, head);
}
static struct list_node * queue_list_read(struct list_node *head)
{
    struct list_node *new_node = NULL;

    if(list.is_empty(head) == true)
    {
        goto quick_exit;
    }

    new_node = head->next;
    list.del(new_node);

quick_exit:
    return new_node;
}
static bool queue_list_is_empty(struct list_node *head)
{
    return list.is_empty(head);
}

void queue_list_str_init(void)
{
    list_str_init();
    queue_list.create_obj = queue_list_create_obj;
    queue_list.write = queue_list_write;
    queue_list.read = queue_list_read;
    queue_list.is_empty = queue_list_is_empty;
}