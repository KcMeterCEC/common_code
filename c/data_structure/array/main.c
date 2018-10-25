#include "array.h"
#include <stdio.h>

void print_buf(struct array_obj * obj)
{
    printf("contents of buffer is:\n");
    for(uint32_t i = 0; i < obj->count; i++)
    {
        printf("%d,", *(int *)(obj->addr + obj->size * i));
    }
    printf("\n");
}
int main(int argc, char *argv[])
{
    int ret = 0;

    printf("**** This is array test projext ****\n");

    array_str_init();
    array.init();

    struct array_obj buf_obj = 
    {
        .size = sizeof(int),
        .count = 10,
    };
    int *buf = (int *)array.create(&buf_obj);
    for(uint8_t i = 0; i < buf_obj.count; i++)
    {
        buf[i] = i;
    }
    print_buf(&buf_obj);

    int val = -1;
    array.insert(&buf_obj, 3, (uint8_t *)&val);
    print_buf(&buf_obj);

    val = -2;
    array.insert(&buf_obj, buf_obj.count, (uint8_t *)&val);
    print_buf(&buf_obj);

    val = -3;
    array.insert(&buf_obj, buf_obj.count + 3, (uint8_t *)&val);
    print_buf(&buf_obj);

    array.delete(&buf_obj, 2);
    print_buf(&buf_obj);

    array.delete(&buf_obj, 10);
    print_buf(&buf_obj);

    array.delete(&buf_obj, 20);
    print_buf(&buf_obj);

    val = -4;
    array.insert(&buf_obj, 5, (uint8_t *)&val);
    print_buf(&buf_obj);    

    array.destory(&buf_obj);

    return ret;
}
