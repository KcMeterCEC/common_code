#include "stack_list.h"
#include <stdio.h>

typedef struct 
{
    char *name;
    struct list_node node;
}student;
void print_list(struct list_node *head)
{
    student *student_tmp = NULL;
    printf("stack:");
    unidir_list_for_each_entry(student_tmp, head, student, node)
    {
        printf("%s,", student_tmp->name);
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    stack_list_str_init();

    struct list_node *stack_head = stack_list.create_obj();
    
    printf("push element:\n");
    student lilei = 
    {
        .name = "lilei",
    };
    stack_list.push(stack_head, &lilei.node);
    print_list(stack_head);
    student may = 
    {
        .name = "may",
    };
    stack_list.push(stack_head, &may.node);
    print_list(stack_head);
    student jack = 
    {
        .name = "jack",
    };
    stack_list.push(stack_head, &jack.node);  
    print_list(stack_head); 

    printf("pop element:\n");
    student *student_tmp  = NULL;

    while(stack_list.is_empty(stack_head) == false)
    {
        struct list_node *node_tmp = stack_list.pop(stack_head);
        student_tmp = unidir_list_entry(node_tmp, student, node);
        printf("get : %s\n", student_tmp->name);
        print_list(stack_head); 
    }


    return 0;
}