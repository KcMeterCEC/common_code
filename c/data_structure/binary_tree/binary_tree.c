#include <stdlib.h>
#include <assert.h>
#include "binary_tree.h"

#define DEBUG

#ifdef DEBUG
#define dbg 	printf 
#else 
#define dbg(...)
#endif

struct tree_api tree;

static struct tree_node * tree_init(int data)
{
	struct tree_node *node = (struct tree_node *)malloc(sizeof(struct tree_node));
	assert(node != NULL);
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}
static bool tree_insert(struct tree_node *root, int data)
{
	bool ret = true;
	if(root == NULL)
	{
		ret = false;
		goto quick_out;
	}

	struct tree_node *node = tree_init(data);

	dbg("insert data = %d\n", data);
	while(1)
	{
		if(node->data < root->data)
		{
			dbg("%d is smaller than %d\n", node->data, root->data);
			if(root->left == NULL)
			{
				dbg("put it at left\n");
				root->left = node;
				ret = true;
				break;
			}
			else
			{
				root = root->left;
			}
		}
		else
		{
			dbg("%d is larger or equal than %d\n", node->data, root->data);
			if(root->right == NULL)
			{
				dbg("put it at right\n");
				root->right = node;
				ret = true;
				break;
			}
			else 
			{
				root = root->right;
			}
		}
	}


quick_out:
	return ret;	
}
static struct tree_node * tree_find(struct tree_node *root, int data)
{
	if(root == NULL)
	{
		goto quick_out;
	}	
	
	bool ret = false;
	do
	{
		if(data < root->data)
		{
			dbg("%d is smaller than %d\n", data, root->data);
			root = root->left;
		}
		else if(data > root->data)
		{
			dbg("%d is larger than %d\n", data, root->data);
			root = root->right;
		}
		else 
		{
			dbg("I have found this node");
			ret = true;
		}
	}while((root != NULL) && (ret == false));	



quick_out:
	return root;
}
static bool tree_delete(struct tree_node *root, int data)
{
	bool ret = false;

	struct tree_node *parent = NULL;

	dbg("delete %d\n", data);
	do
	{
		if(data < root->data)
		{
			parent = root;
			root = root->left;
		}
		else if(data > root->data)
		{
			parent = root;
			root = root->right;
		}
		else
		{
			ret = true;
		}
	}while((root != NULL) && (ret == false));
	if(ret == false)
	{
		goto quick_out;
	}

	struct tree_node *free_node = NULL;
	if((root->left != NULL) && (root->right != NULL))
	{
		dbg("this node have 2 child node\n");
		struct tree_node *sub_parent = NULL;
		struct tree_node *tmp_node = root->right;
		while(tmp_node->left != NULL)
		{
			sub_parent = tmp_node;
			tmp_node = tmp_node->left;
		}
		free_node = tmp_node;
		if(sub_parent != NULL)
		{
			sub_parent->left = NULL;
		}
		else
		{
			root->right = tmp_node->right;
		}
		
		root->data = tmp_node->data;
	}
	else 
	{
		free_node = root;
		struct tree_node *child_node = NULL;
		if(root->left != NULL)
		{
			child_node = root->left;
		}
		else if(root->right != NULL)
		{
			child_node = root->right;
		}
		else 
		{
			child_node = NULL;
		}
		if(parent->left == root)
		{
			parent->left = child_node;
		} 
		else
		{
			parent->right = child_node;
		}		
		dbg("free node %d\n", free_node->data);

		free(free_node);
	}

quick_out:
	return ret;
}
static void tree_pre_order(struct tree_node *node)
{
	if(node == NULL)
	{
		return;
	}
	
	printf("%d,", node->data);
	tree_pre_order(node->left);
	tree_pre_order(node->right);
}
static void tree_in_order(struct tree_node *node)
{
	if(node == NULL)
	{
		return;
	}
	tree_in_order(node->left);	
	printf("%d,", node->data);
	tree_in_order(node->right);
}
static void tree_post_order(struct tree_node *node)
{
	if(node == NULL)
	{
		return;
	}
	
	tree_post_order(node->left);
	tree_post_order(node->right);
	printf("%d,", node->data);
}

void tree_str_init(void)
{
	tree.init_obj = tree_init;
	tree.find = tree_find;
	tree.insert = tree_insert;
	tree.del = tree_delete;
	tree.traverse_pre_order = tree_pre_order;
	tree.traverse_in_order = tree_in_order;
	tree.traverse_post_order = tree_post_order;
}