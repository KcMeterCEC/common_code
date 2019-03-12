#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdbool.h>
#include <stdio.h>

struct tree_node
{
	int 	data;
	struct tree_node *left, *right;
};
struct tree_api
{
	struct tree_node * (*init_obj)(int data);
	bool (*insert)(struct tree_node *root, int data);
	bool (*del)(struct tree_node *root, int data);
	struct tree_node *(*find)(struct tree_node *root, int data);
	void (*traverse_pre_order)(struct tree_node *node);
	void (*traverse_in_order)(struct tree_node *node);
	void (*traverse_post_order)(struct tree_node *node);
};

extern struct tree_api tree;
extern void tree_str_init(void);

#endif
