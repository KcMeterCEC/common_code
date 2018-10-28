#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "unidir_list.h"

#define NAME_LEN    (10)

typedef struct 
{
    char        name[NAME_LEN];
    uint8_t     age;
    struct list_node   node;
}student_obj;

static struct list_node student_head; 

static void print_list(void)
{
    student_obj   *obj;

    unidir_list_for_each_entry(obj, &student_head, student_obj, node)
    {
        printf("Hi, my name is %s, and I'm %d years old\n", 
        obj->name, obj->age);
    }
}

int main(int argc, char *argv[])
{
    unidir_list_str_init();

    undir_list.init_obj(&student_head);

    printf(">>>insert students!\n");

    student_obj lilei = 
    {
        .name = "lilei",
        .age = 32,
    };
    undir_list.insert(&student_head, &lilei.node);

    student_obj wq = 
    {
        .name = "wuqing",
        .age = 28,
    };   
    undir_list.insert(&student_head, &wq.node);

    student_obj may = 
    {
        .name = "may",
        .age = 15,
    };   
    undir_list.insert(&student_head, &may.node);    
    print_list();   

    printf(">>> delete students: wuqing\n");
    undir_list.remove_next(&may.node);
    print_list(); 

    return 0;
}