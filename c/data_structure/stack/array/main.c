#include "stack_array.h"
#include <stdio.h>
#include <string.h>

struct strack_obj  student;

void print_buf(void)
{
    printf("stack contents:\n");
    for(uint8_t i = 0; i < student.index; i++)
    {
        printf("%d,",*(((int *)student.buf) + i));
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    stack_array_str_init();

    student.element_size = sizeof(int);
    student.count = 5;

    #define BUG_SIZE (6)
    int test_buf[BUG_SIZE];

    for(uint8_t i = 0; i < BUG_SIZE; i++)
    {
        test_buf[i] = i;
    }
    stack_array.create_obj(&student);
    print_buf();

    for(uint8_t i = 0; i < BUG_SIZE; i++)
    {
        printf("push -> %d\n", test_buf[i]);
        stack_array.push(&student, (uint8_t *)&test_buf[i]);
        print_buf();
    }
    memset(test_buf, 0, sizeof(test_buf));
    for(uint8_t i = 0; i < BUG_SIZE; i++)
    {
        stack_array.pop(&student, (uint8_t *)&test_buf[i]);
        print_buf();
        printf("pop -> %d\n", test_buf[i]);
    }    
    return 0;
}