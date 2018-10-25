#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <stdint.h>
#include <stdbool.h>

struct array_obj
{
    uint8_t size;
    uint32_t count;
    void *addr;
};

struct array_api
{
    bool (*init)(void);
    void * (*create)(struct array_obj * obj);
    void  (*destory)(struct array_obj * obj);
    void (*insert)(struct array_obj *obj, uint16_t index, uint8_t *val);
    void (*delete)(struct array_obj *obj, uint16_t index);
};

extern struct array_api array;
extern void array_str_init(void);
#endif