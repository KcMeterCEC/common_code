#include "queue_list.h"
#include <stdio.h>

typedef struct 
{
    char *name;
    struct list_node node;
}student;
void print_list(struct list_node *head)
{
    student *student_tmp = NULL;
    printf("queue:");
    list_for_each_entry(student_tmp, head, student, node)
    {
        printf("%s,", student_tmp->name);
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    queue_list_str_init();

    struct list_node *queue_head = queue_list.create_obj();
    
    printf("write element:\n");
    student lilei = 
    {
        .name = "lilei",
    };
    queue_list.write(queue_head, &lilei.node);
    print_list(queue_head);
    student may = 
    {
        .name = "may",
    };
    queue_list.write(queue_head, &may.node);
    print_list(queue_head);
    student jack = 
    {
        .name = "jack",
    };
    queue_list.write(queue_head, &jack.node);  
    print_list(queue_head); 

    printf("read element:\n");
    student *student_tmp  = NULL;

    while(queue_list.is_empty(queue_head) == false)
    {
        struct list_node *node_tmp = queue_list.read(queue_head);
        student_tmp = list_first_entry(node_tmp, student, node);
        printf("get : %s\n", student_tmp->name);
        print_list(queue_head); 
    }


    return 0;
}