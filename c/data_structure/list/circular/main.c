#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

static struct list_node list_head;

#define LIST_TEST (0)

#if !LIST_TEST
#define LIST_LRU  (0)
#endif

#if !LIST_TEST && !LIST_LRU
#define LIST_PALINDROME (1)
#endif

#if LIST_TEST
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
    printf("node count = %d\n", list.node_count(&list_head));

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
    printf("node count = %d\n", list.node_count(&list_head));
}
#endif

#if LIST_LRU
#define LRU_SIZE (5)
struct lru_member
{
    char member;
    struct list_node node;
};

static void print_lru(struct list_node *list_head)
{
    struct lru_member *lru;
    list_for_each_entry(lru, list_head, struct lru_member, node)
    {
        printf("%c,", lru->member);
    }
    printf("\n");
}
static struct lru_member * lru_looking_for(char member)
{
    bool is_same = false;
    struct lru_member *lru_node = NULL;

    if(list.is_empty(&list_head) == true)
    {
        goto quick_exit;
    }
    list_for_each_entry(lru_node, &list_head, struct lru_member, node)
    {
        if(lru_node->member == member)
        {
            is_same = true;
            break;
        }
    }

quick_exit:
    if(is_same == false)
    {
        lru_node = NULL;
    }
    return lru_node;
}

static void insert_member(char member)
{
    printf("insert member [%c]\n", member);
    struct lru_member *lru_node = NULL;

    if((lru_node = lru_looking_for(member)) != NULL)
    {
        list.move_after(&lru_node->node, &list_head);
    }
    else
    {
        if(list.node_count(&list_head) < LRU_SIZE)
        {
            lru_node = (struct lru_member *)malloc(sizeof(struct lru_member));
            assert(lru_node);
            lru_node->member = member;
            list.add_after(&lru_node->node, &list_head);
        }
        else
        {
            lru_node = list_last_entry(&list_head, struct lru_member, node);
            list.del(list_head.prev);
            lru_node->member = member;
            list.add_after(&lru_node->node, &list_head);
        }
    }
    
    print_lru(&list_head);
}
#endif

#if LIST_PALINDROME
#include <string.h>
struct str_member
{
    char member;
    struct list_node node;
};
static void print_str(struct list_node *list_head)
{
    struct str_member *str;
    list_for_each_entry(str, list_head, struct str_member, node)
    {
        printf("%c,", str->member);
    }
    printf("\n");
}
static void palindrome(char *str)
{
    printf("create list:\n");
    for(uint16_t i = 0; i < strlen(str); i++)
    {
        struct str_member *str_node = (struct str_member *)malloc(sizeof(struct str_member));
        assert(str_node);
        str_node->member = str[i];
        list.add_before(&str_node->node, &list_head);
    }
    print_str(&list_head);

    printf("parse string:\n");
    while(1)
    {
        struct str_member *str_first = list_first_entry(&list_head, struct str_member, node);
        struct str_member *str_last = list_last_entry(&list_head, struct str_member, node);
        if(str_first->member == str_last->member)
        {
            list.del(&str_first->node);
            list.del(&str_last->node);

            free(str_first);
            free(str_last);
        }
        else
        {
            printf("this string is not a palindrome!\n");
            break;
        }
        if((list.is_empty(&list_head) == true) ||
        (list.is_singular(&list_head) == true))
        {
            printf("this string is a palindrome!\n");
            break;
        }
    }

    if(list.is_empty(&list_head) == false)
    {
        struct str_member *str_first = NULL;
        do
        {
            str_first = list_first_entry(&list_head, struct str_member, node);
            list.del(&str_first->node);
            free(str_first);
        } while (list.is_empty(&list_head) == false);
        
        if(list.is_empty(&list_head) == true)
        {
            printf("free list succedded!\n");
        } 
    }
   
}
#endif

int main(int argc , char *argv[])
{
    list_str_init();

    list.init_obj(&list_head);

#if LIST_TEST
    list_demo();
#elif LIST_LRU
    insert_member('A');
    insert_member('B');
    insert_member('C');
    insert_member('A');
    insert_member('E');
    insert_member('D');
    insert_member('B');
    insert_member('F');
    insert_member('G');
#elif LIST_PALINDROME
    if(argc != 2)
    {
        printf("usage : list <string>\n");
        return 1;
    }
    palindrome(argv[1]);
#endif


    return 0;
}