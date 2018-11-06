#include "stack_array.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct stack_array_api stack_array;

static bool stack_array_create_obj(struct stack_obj *obj)
{
    bool ret = true;

    obj->size = obj->element_size * obj->count;
    obj->buf = (uint8_t *)malloc(obj->size);
    assert(obj->buf);
    obj->index = 0;

    return ret;
}
static bool stack_array_push(struct stack_obj *obj, uint8_t *buf)
{
    bool ret = true;
    if(obj->index >= obj->count)
    {
        printf("error: stack is full!\n");
        ret = false;
        goto quick_exit;
    }
    obj->index += 1;

    memcpy(obj->buf + (obj->index - 1) * obj->element_size,
    buf, obj->element_size);

quick_exit:
    return ret;
}
static bool stack_array_pop(struct stack_obj *obj, uint8_t *buf)
{
    bool ret = true;
    if(obj->index == 0)
    {
        printf("error: stack is empty!\n");
        ret = false;
        goto quick_exit;
    }
    obj->index -= 1;

    memcpy(buf, obj->buf + obj->index * obj->element_size, 
    obj->element_size);

quick_exit:
    return ret;
}

void stack_array_str_init(void)
{
    stack_array.create_obj = stack_array_create_obj;
    stack_array.push = stack_array_push;
    stack_array.pop = stack_array_pop;
}