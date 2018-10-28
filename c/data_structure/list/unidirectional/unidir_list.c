#include "unidir_list.h"

struct unidir_list_api undir_list;

static void unidir_list_init_obj(struct list_node *head)
{
    #ifdef RING_LIST
    head->next = head;
    #else
    head->next = NULL;
    #endif
}

static void unidir_list_insert(struct list_node *current_node, struct list_node *new_node)
{
    if(current_node == NULL)
    {
        printf("error:can not insert a node after tail!\n");
    }

    struct list_node *tmp = current_node->next;

    current_node->next = new_node;
    new_node->next = tmp;
}

static void undir_list_remove_next(struct list_node *current_node)
{
    if((current_node == NULL) ||
       (current_node->next == NULL))
    {
        printf("error:can not remove a node after tail!\n");
    }

    struct list_node *tmp = current_node->next->next;

    current_node->next->next = NULL;

    current_node->next = tmp;
}

void unidir_list_str_init(void)
{
    undir_list.init_obj = unidir_list_init_obj;
    undir_list.remove_next = undir_list_remove_next;
    undir_list.insert = unidir_list_insert;
}