#include "list.h"

struct list_api  list;

static void list_init_obj(struct list_node *node)
{
    node->next = node;
    node->prev = node;
}
static void __list_add(struct list_node *new_node, 
                       struct list_node *prev, 
                       struct list_node *next)
{
    prev->next = new_node;
    new_node ->prev = prev;

    new_node->next = next;
    next->prev = new_node;
}
static void list_add_after(struct list_node *new_node, struct list_node *node)
{
    __list_add(new_node, node, node->next);
}
static void list_add_before(struct list_node *new_node, struct list_node *node)
{
    __list_add(new_node, node->prev, node);
}

static void __list_del(struct list_node *prev, struct list_node *next)
{
    prev->next = next;
    next->prev = prev;
}
static void list_del(struct list_node *node)
{
    __list_del(node->prev, node->next);

    list_init_obj(node);
}
static void list_replace(struct list_node *old_node, struct list_node *new_node)
{
    new_node->next = old_node->next;
    new_node->next->prev = new_node;

    new_node->prev = old_node->prev;
    new_node->prev->next = new_node;

    list_init_obj(old_node);
}
static void list_move_after(struct list_node *node, struct list_node *place)
{
    list_del(node);
    list_add_after(node, place);
}
static void list_move_before(struct list_node *node, struct list_node *place)
{
    list_del(node);
    list_add_before(node, place);
}
static bool list_is_last(struct list_node *node, struct list_node *head)
{
    return node->next == head;
}
static bool list_is_empty(const struct list_node *head)
{
    return head->next == head;
}
static void list_rotate_left(struct list_node *node)
{
    list_move_before(node, node->prev);
}
static void list_rotate_right(struct list_node *node)
{
    list_move_after(node, node->next);
}
static bool list_is_singular(struct list_node *head)
{
    return !list_is_empty(head) && (head->next == head->prev);
}
static void __list_cut_position(struct list_node *new_list_head,
		struct list_node *first_node, struct list_node *next_node)
{
	struct list_node *new_first = next_node->next;

	new_list_head->next = first_node->next;
	new_list_head->next->prev = new_list_head;

	new_list_head->prev = next_node;
	next_node->next = new_list_head;

	first_node->next = new_first;
	new_first->prev = first_node;
}


static void list_cut_position(struct list_node *new_list_head,
		struct list_node *first_node, struct list_node *next_node)
{
	if (next_node == first_node)
		list_init_obj(new_list_head);
	else
		__list_cut_position(new_list_head, first_node, next_node);
}

static void __list_splice(const struct list_node *list,
				 struct list_node *prev,
				 struct list_node *next)
{
	struct list_node *first = list->next;
	struct list_node *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}

static  void list_splice_after(struct list_node *list,
				struct list_node *node)
{
	if (!list_is_empty(list))
    {
        __list_splice(list, node, node->next);
        list_init_obj(list);
    }
		
}
static  void list_splice_before(struct list_node *list,
				struct list_node *node)
{
	if (!list_is_empty(list))
    {
        __list_splice(list, node->prev, node);
        list_init_obj(list);
    }
		
}
static uint32_t list_node_count(struct list_node *head)
{
    struct list_node *node = NULL;
    uint32_t count = 0;
    list_for_each(node, head)
    {
        count += 1;
    }

    return count;
}

void list_str_init(void)
{
    list.init_obj = list_init_obj;
    list.add_after = list_add_after;
    list.add_before = list_add_before;
    list.del = list_del;
    list.replace = list_replace;
    list.move_after = list_move_after;
    list.move_before = list_move_before;
    list.is_last = list_is_last;
    list.is_empty = list_is_empty;
    list.rotate_left = list_rotate_left;
    list.rotate_right = list_rotate_right;
    list.is_singular = list_is_singular;
    list.cut_position = list_cut_position;
    list.splice_after = list_splice_after;
    list.splice_before = list_splice_before;
    list.node_count = list_node_count;
}