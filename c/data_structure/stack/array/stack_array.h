#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

#include <stdint.h>
#include <stdbool.h>

struct stack_obj 
{
    uint32_t    size;
    uint32_t    count;
    uint8_t     element_size;
    uint32_t    index;
    uint8_t     *buf;
};

struct stack_array_api
{
    bool (*create_obj)(struct stack_obj *obj);
    bool (*push)(struct stack_obj *obj, uint8_t *buf);
    bool (*pop)(struct stack_obj *obj, uint8_t *buf);
};

extern struct stack_array_api stack_array;
extern void stack_array_str_init(void);
#endif