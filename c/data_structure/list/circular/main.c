#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

static struct list_node list_head;

struct student 
{
    uint8_t index;
    struct list_node node;
};

static void print_list(struct list_node *list_head)
{
    struct student *student_tmp;
    list_for_each_entry(student_tmp, list_head, struct student, node)
    {
        printf("%d,", student_tmp->index);
    }
    printf("\n");
}

static struct student * list_looking_for(uint8_t index)
{
    struct student *student_tmp = NULL;
    list_for_each_entry(student_tmp, &list_head, struct student, node)
    {
        if(student_tmp->index == index)
        {
            break;
        }
    }
    if(student_tmp == NULL)
    {
        printf("sorry, i can't find index -> %d\n", index);
        while(1);
    }
    return student_tmp;
}

static void list_demo(void)
{
    printf("\n**********************\n");
    printf("  This is list demo \n");
    printf("\n**********************\n");

    printf("create a list:\n");

    struct student  *new_student = NULL;
    for(uint8_t i = 15; i > 0; i--)
    {
        new_student = (struct student *)malloc(sizeof(struct student));
        assert(new_student);

        new_student->index = i;

        list.add_after(&new_student->node, &list_head);
    }
    for(uint8_t i = 16; i < 30; i++)
    {
        new_student = (struct student *)malloc(sizeof(struct student));
        assert(new_student);

        new_student->index = i;

        list.add_before(&new_student->node, &list_head);
    }    
    print_list(&list_head);

    printf("delete index 16\n");
    struct student *student_tmp = list_looking_for(16);
    list.del(&student_tmp->node);
    free(student_tmp);  
    print_list(&list_head);  

    printf("replace 18 by 99\n");
    new_student = (struct student *)malloc(sizeof(struct student));
    assert(new_student);
    new_student->index = 99;
    student_tmp = list_looking_for(18);
    list.replace(&student_tmp->node, &new_student->node);
    free(student_tmp);    
    print_list(&list_head);    

    printf("move 10 after 27\n");
    student_tmp = list_looking_for(10);
    struct student *student_tmp2 = list_looking_for(27);
    list.move_after(&student_tmp->node, &student_tmp2->node);
    print_list(&list_head);

    printf("move 15 before 9\n");
    student_tmp = list_looking_for(15);
    student_tmp2 = list_looking_for(9);
    list.move_before(&student_tmp->node, &student_tmp2->node);
    print_list(&list_head); 

    printf("rotate left 21\n");
    student_tmp = list_looking_for(21);  
    list.rotate_left(&student_tmp->node);
    print_list(&list_head); 

    printf("rotate right 21\n");
    student_tmp = list_looking_for(21);  
    list.rotate_right(&student_tmp->node);
    print_list(&list_head); 

    printf("cut position 12 ~ 20, including 20 but not including 12\n");
    struct list_node list_head_new;
    list.init_obj(&list_head_new);
    student_tmp = list_looking_for(12);
    student_tmp2 = list_looking_for(20);
    list.cut_position(&list_head_new, &student_tmp->node, &student_tmp2->node);
    print_list(&list_head);
    print_list(&list_head_new);

    // printf("splice new list after 24\n");
    // student_tmp = list_looking_for(24);
    // list.splice_after(&list_head_new, &student_tmp->node);
    // print_list(&list_head);

    printf("splice new list before 7\n");
    student_tmp = list_looking_for(7);
    list.splice_before(&list_head_new, &student_tmp->node);
    print_list(&list_head);    

    printf("free index:\n");
    do
    {
        student_tmp = list_first_entry(&list_head, struct student, node);
        printf("%d,", student_tmp->index);
        list.del(&student_tmp->node);
        free(student_tmp);
    } while (list.is_empty(&list_head) == false);
    printf("\n");
    
    if(list.is_empty(&list_head) == true)
    {
        printf("free list succedded!\n");
    }
}

int main(int argc , char *argv[])
{
    list_str_init();

    list.init_obj(&list_head);

    list_demo();


    return 0;
}