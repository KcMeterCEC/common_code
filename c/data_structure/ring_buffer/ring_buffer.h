#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__
#include <stdint.h>
#include <stdbool.h>

struct ring_buffer
{
    uint32_t    size;
    uint32_t    empty_size;
    uint32_t    write_index;
    uint32_t    read_index;
    uint8_t     *buf;
};
struct ring_buffer_func
{
    struct ring_buffer * (*create)(uint32_t size);
    bool (*destory)(struct ring_buffer *rb);
    bool (*write)(struct ring_buffer *rb, uint32_t size, uint8_t *buf);
    bool (*read)(struct ring_buffer *rb, uint32_t size, uint8_t *buf);
};

extern struct ring_buffer_func strfunc_rb;
extern void rb_strinit(void);
#endif

