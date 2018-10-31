#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>

struct list_node
{
    struct list_node *next, *prev;
};

struct list_api
{
    /**
     *  @brief : this function is used for initialize head node
     */
    void (*init_obj)(struct list_node *node);
    /**
     *  @brief : insert a new_node after node
     */    
    void (*add_after)(struct list_node *new_node, struct list_node *node);
    /**
     *  @brief : insert a new_node before node
     */    
    void (*add_before)(struct list_node *new_node, struct list_node *node);   
    void (*del)(struct list_node *node);
    /**
     *  @brief : replace old_node by new_node
     */     
    void (*replace)(struct list_node *old_node, struct list_node *new_node);
    /**
     *  @brief : move node to place tail
     */    
    void (*move_after)(struct list_node *node, struct list_node *place);
    /**
     *  @brief : move node to place head
     */    
    void (*move_before)(struct list_node *node, struct list_node *place); 
    /**
     *  @brief : move node to the left
     */    
    void (*rotate_left)(struct list_node *node);
    /**
     *  @brief : move node to the right
     */    
    void (*rotate_right)(struct list_node *node);    
     /**
     *  @brief : test whether node is the last node in list head
     */   
    bool (*is_last)(struct list_node *node, struct list_node *head);   
    bool (*is_empty)(const struct list_node *head);
     /**
     *  @brief : test whether a list has just one node
     */     
    bool (*is_singular)(struct list_node *head);
    /**
     *  @brief : list_cut_position - cut a list into two
     *  @par: new_list_head: a new list to add all removed entries
     *  @par: first_node: a list with entries
     *  @par: next_node: an entry within head
     *
     * @note: This helper moves the initial part of @first_node, up to and
     *  including @next_node, from @first_node to @new_list_head. You should
     *  pass on @next_node an element you know is on @first_node. @new_list_head
     *  should be an empty list or a list you do not care about
     *  losing its data.
     *
     */    
    void (*cut_position)(struct list_node *new_list_head,
		struct list_node *first_node, struct list_node *next_node);
    /**
     * @brief : splice @list after @node
     */
    void (*splice_after)(struct list_node *list,
				  struct list_node *node);
    /**
     * @brief : splice @list before @node
     */
    void (*splice_before)(struct list_node *list,
				struct list_node *node);                
};

extern struct list_api  list;
extern void list_str_init(void);

#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ( \
        (type *)((char *)ptr - offsetof(type, member)))

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_node pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_node within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @head:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(head, type, member) \
	list_entry((head)->next, type, member) 
/**
 * list_last_entry - get the last element from a list
 * @head:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(head, type, member) \
	list_entry((head)->prev, type, member)       

/**
 * list_next_entry - get the next element in list
 * @pos:	the type * to cursor
 * @type:	the type of the struct this is embedded in. 
 * @member:	the name of the list_head within the struct.
 */
#define list_next_entry(pos, type, member) \
	list_entry((pos)->member.next, type, member)

/**
 * list_prev_entry - get the prev element in list
 * @pos:	the type * to cursor
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_prev_entry(pos, type, member) \
	list_entry((pos)->member.prev, type, member)  
/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)  
/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)  
/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry(pos, head, type, member)				\
	for (pos = list_first_entry(head, type, member);	            \
	     &(pos->member) != (head);					                \
	     pos = list_next_entry(pos, type, member))  

/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry_reverse(pos, head, type, member)			\
	for (pos = list_last_entry(head, type, member);		                \
	     &pos->member != (head); 					                    \
	     pos = list_prev_entry(pos, type, member))

/**
 * list_prepare_entry - prepare a pos entry for use in list_for_each_entry_continue()
 * @pos:	the type * to use as a start point
 * @head:	the head of the list
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Prepares a pos entry for use as a start point in list_for_each_entry_continue().
 */
#define list_prepare_entry(pos, head, type, member) \
	((pos) ? : list_entry(head, type, member)) 
/**
 * list_for_each_entry_continue - continue iteration over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 */
#define list_for_each_entry_continue(pos, head, type, member) 		\
	for (pos = list_next_entry(pos, type, member);			        \
	     &pos->member != (head);					                \
	     pos = list_next_entry(pos, type, member))  

/**
 * list_for_each_entry_continue_reverse - iterate backwards from the given point
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Start to iterate over list of given type backwards, continuing after
 * the current position.
 */
#define list_for_each_entry_continue_reverse(pos, head, type, member)		\
	for (pos = list_prev_entry(pos, type, member);			                \
	     &pos->member != (head);					                        \
	     pos = list_prev_entry(pos, type, member))   

/**
 * list_for_each_entry_from - iterate over list of given type from the current point
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Iterate over list of given type, continuing from current position.
 */
#define list_for_each_entry_from(pos, head, type, member) 			\
	for (; &pos->member != (head);					\
	     pos = list_next_entry(pos, type, member))

/**
 * list_for_each_entry_from_reverse - iterate backwards over list of given type
 *                                    from the current point
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 *
 * Iterate backwards over list of given type, continuing from current position.
 */
#define list_for_each_entry_from_reverse(pos, head, type, member)		\
	for (; &pos->member != (head);					\
	     pos = list_prev_entry(pos, type, member))

#endif
