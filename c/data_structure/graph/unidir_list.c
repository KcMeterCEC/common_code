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
static void undir_list_reverse(struct list_node *head)
{
    struct list_node new_head;

#ifdef RING_LIST
    new_head.next = head;
#else
    new_head.next = NULL;
#endif

    struct list_node *tmp = head->next;
    struct list_node *node = NULL;
    do
    {
        node = tmp;
        tmp = node->next;

        unidir_list_insert(&new_head, node);
    }while((tmp != NULL) && (tmp != head));
    head->next = new_head.next;
}
struct list_node *undir_list_find_loop(struct list_node *head)
{
    struct list_node *loop = NULL;
    bool   is_loop = false;

    struct list_node *fast, *slow;
    fast = head->next->next;
    slow = head->next;

#ifdef RING_LIST
    while((fast != head) && (fast->next != head))
#else
    while((fast != NULL) && (fast->next != NULL))
#endif    
    {
        fast = fast->next->next;
        slow = slow->next;

        if(fast == slow)
        {
            is_loop = true;
            break;
        }
    }
    if(is_loop == true)
    {
        fast = head;
        while(fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }
        loop = fast;
    }

    return loop;
}
static bool unidir_list_is_empty(struct list_node *head)
{
    #ifdef RING_LIST
    return head->next == head;
    #else 
    return head->next == NULL;
    #endif
}
void unidir_list_str_init(void)
{
    undir_list.init_obj = unidir_list_init_obj;
    undir_list.remove_next = undir_list_remove_next;
    undir_list.insert = unidir_list_insert;
    undir_list.reverse = undir_list_reverse;
    undir_list.find_loop = undir_list_find_loop;
    undir_list.is_empty = unidir_list_is_empty;
}