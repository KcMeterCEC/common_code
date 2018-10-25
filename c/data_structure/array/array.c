#include "array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define DBG_PRINT

#ifdef DBG_PRINT
#define DEBUG  printf
#else
#define DEBUG(...)
#endif

struct array_api array;

static bool array_init(void)
{

}
static void * array_create(struct array_obj * obj)
{
    DEBUG("request [%d] bytes from memory\n", obj->size * obj->count);
    obj->addr = malloc(obj->size * obj->count);
    assert(obj->addr);

    return obj->addr;
}
static void  array_destory(struct array_obj * obj)
{
    free(obj->addr);
}
static void array_insert(struct array_obj *obj, uint16_t index, uint8_t *val)
{

    DEBUG("insert value at index [%d]\n", index);
    uint32_t add_count = 1;

    if(index > obj->count)
    {
        add_count = index - obj->count;
    }
    DEBUG("add array [%d] bytes memory\n", (obj->size *  add_count));

    void *new_addr = malloc(obj->size * (obj->count + add_count));
    assert(new_addr);

    memcpy(new_addr , obj->addr , obj->size * obj->count);

    if(add_count > 1)
    {
        memset(new_addr + obj->size * obj->count,
        0, obj->size *  add_count);

        memcpy(new_addr + obj->size * (obj->count + add_count - 1),
        val, obj->size);
    }
    else
    {
         memcpy(new_addr + obj->size * obj->count ,
         obj->addr + index * obj->size , obj->size);

         memcpy(new_addr + obj->size * index ,
         val , obj->size);
    }

    
    free(obj->addr);
    obj->addr = new_addr;
    obj->count += add_count;
}
static void array_delete(struct array_obj *obj, uint16_t index)
{
     DEBUG("delete value at index [%d]\n", index);
    if(index > obj->count - 1)
    {
        printf("index [%d] is out of range !\n", index);
        return;
    }

    memcpy(obj->addr + index * obj->size, 
    obj->addr + obj->size * (obj->count - 1),
    obj->size);

    obj->count -= 1;
}

void array_str_init(void)
{
    array.init = array_init;
    array.create = array_create;
    array.destory = array_destory;
    array.insert = array_insert;
    array.delete = array_delete;
}