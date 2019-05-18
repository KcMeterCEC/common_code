#ifndef __UNIDIR_LIST_H__
#define __UNIDIR_LIST_H__

#include <stdbool.h>
#include <stdio.h>

struct list_node
{
    struct list_node *next;
};

// #define RING_LIST

#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ( \
        (type *)((char *)ptr - offsetof(type, member)))

#define unidir_list_entry(ptr, type, member) \
        container_of(ptr, type, member)

/**
 * unidir_list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_node within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define unidir_list_first_entry(ptr, type, member) \
        unidir_list_entry((ptr)->next, type, member)

/**
 * unidir_list_next_entry - get the next element in list
 * @pos:	the type * to cursor
 * @type:   the type of the struct 
 * @member:	the name of the list_node within the struct.
 */
#define unidir_list_next_entry(pos, type, member) \
	unidir_list_entry((pos)->member.next, type, member)

/**
 * unidir_list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @type:   the type of the struct 
 * @member:	the name of the list_node within the struct.
 */
#ifdef RING_LIST
#define unidir_list_for_each_entry(pos, head, type, member)	\
	for (pos = unidir_list_first_entry(head, type, member);	\
        &((pos)->member) != head;                           \
	     pos = unidir_list_next_entry(pos, type, member))
#else
#define unidir_list_for_each_entry(pos, head, type, member)	\
	for (pos = unidir_list_first_entry(head, type, member);	\
	     &((pos)->member) != NULL;					        \
	     pos = unidir_list_next_entry(pos, type, member))
#endif         


struct unidir_list_api
{
    void (*init_obj)(struct list_node *head);
    void (*insert)(struct list_node *current_node, struct list_node *new_node);
    void (*remove_next)(struct list_node *current_node);
    void (*reverse)(struct list_node *head);
    bool (*is_empty)(struct list_node *head);
    struct list_node *(*find_loop)(struct list_node *head);
};

extern struct unidir_list_api undir_list;
extern void unidir_list_str_init(void);
#endif