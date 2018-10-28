#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "unidir_list.h"

#define NAME_LEN    (10)

#define JOSEPHUS_PROBLEM

#ifdef JOSEPHUS_PROBLEM
typedef struct 
{
    uint16_t index;
    struct list_node node;
}people_obj;

static struct list_node  people_head;
#else
typedef struct 
{
    char        name[NAME_LEN];
    uint8_t     age;
    struct list_node   node;
}student_obj;

static struct list_node student_head; 
#endif

static void print_list(void)
{
#ifdef JOSEPHUS_PROBLEM
    people_obj   *obj;

    printf("people index is :\n");
    unidir_list_for_each_entry(obj, &people_head, people_obj, node)
    {
        printf("%d,", obj->index);
    }
    printf("\n");
#else    
    student_obj   *obj;

    unidir_list_for_each_entry(obj, &student_head, student_obj, node)
    {
        printf("Hi, my name is %s, and I'm %d years old\n", 
        obj->name, obj->age);
    }
#endif    
}

int main(int argc, char *argv[])
{
    unidir_list_str_init();

#ifdef JOSEPHUS_PROBLEM
    undir_list.init_obj(&people_head);
    printf("create list:\n");

    for(uint16_t i = 7; i > 0; i--)
    {
        people_obj   *obj = (people_obj *)malloc(sizeof(people_obj));
        assert(obj != NULL);
        obj->index = i;
        undir_list.insert(&people_head, &obj->node);
    }
    print_list();

    people_obj   *obj = unidir_list_first_entry(&people_head, people_obj, node);
    uint8_t      count = 0;
    struct list_node *prev_node = &people_head;
    #define  JOSEPHUS_STEP (2)
    while(1)
    {
        printf("sweep->index = %d,", obj->index);
        if((obj->node.next == &people_head) &&
           (people_head.next == &(obj->node)))
           {
               printf("[survive]\n");
               break;
           }
        else if(++count >= JOSEPHUS_STEP)
        {
            count = 0;
            printf("[kill]\n");
            undir_list.remove_next(prev_node); 
            
            print_list();
        }
        else 
        {
            prev_node = &obj->node;
            printf("[skip]\n");
        }

        if(prev_node->next == &people_head)
        {
            prev_node = &people_head;
            obj = unidir_list_first_entry(&people_head, people_obj, node);
        } 
        else
        {
            obj = unidir_list_entry(prev_node, people_obj, node);
            obj = unidir_list_next_entry(obj, people_obj, node);
        }         
    }
    
#else
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
#endif    

    return 0;
}