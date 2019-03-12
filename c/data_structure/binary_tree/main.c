#include <stdio.h>
#include <stdint.h>
#include "binary_tree.h"

#define NODE_COUNT  (10)

static int obj[NODE_COUNT];
struct tree_node *root;

static void obj_init(void)
{
    for(uint8_t i = 0; i < NODE_COUNT / 2; i++)
    {
        obj[2 * i] = 6 * i;
        obj[2 * i + 1] = i + 1;
    }
    printf("obj contents is:\n");
    for(uint8_t i = 0; i < NODE_COUNT; i++)
    {
        printf("%d,", obj[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    tree_str_init();
    obj_init();
    
    root = tree.init_obj(15);

    for(uint8_t i = 0; i < NODE_COUNT; i++)
    {
        tree.insert(root, obj[i]);
    }
    printf("pre order:\n");
    tree.traverse_pre_order(root);
    printf("\nin order:\n");
    tree.traverse_in_order(root);
    printf("\npost order:\n");
    tree.traverse_post_order(root);printf("\n");

    tree.del(root, 1);
    tree.traverse_in_order(root);printf("\n");
    tree.del(root, 4);
    tree.traverse_in_order(root);printf("\n");
    tree.del(root, 5);
    tree.traverse_in_order(root);printf("\n");    
    tree.del(root, 15);
    tree.traverse_in_order(root);printf("\n");  
    tree.del(root, 13);
    tree.traverse_in_order(root);printf("\n");   

    if(tree.find(root, 5) == NULL)
    {
        printf("can not find node!\n");
    }
    if(tree.find(root, 2) == NULL)
    {
        printf("can not find node!\n");
    }            

    return 0;
}