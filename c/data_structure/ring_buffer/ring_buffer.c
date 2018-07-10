#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "./ring_buffer.h"
#include "../debug.h"

DEBUG_SET_LEVEL(DEBUG_LEVEL_ERR);

struct ring_buffer_func strfunc_rb;

static struct ring_buffer * rb_create(uint32_t size)
{
    struct ring_buffer * rb = (struct ring_buffer *)malloc(sizeof(struct ring_buffer));
    assert(rb != NULL);
    rb->buf = (uint8_t *)malloc(size);
    assert(rb->buf != NULL);
    memset(rb->buf, 0, size);
    rb->size = size;
    rb->empty_size = size;
    rb->write_index = rb->read_index = 0;

    return rb;
}
static bool rb_destory(struct ring_buffer *rb)
{
    bool ret = true;
    if((rb == NULL) || (rb->buf == NULL))
    {
        ERR("rb buffer is NULL!\n");
        ret = false;
        goto quick_out;
    }

    free(rb->buf);
    free(rb);

quick_out:
    return ret;
}
static bool rb_write(struct ring_buffer *rb, uint32_t size, uint8_t *buf)
{
    bool ret = true;
    if((rb == NULL) || (rb->buf == NULL))
    {
        ERR("rb buffer is NULL!\n");
        ret = false;
        goto quick_out;
    }
    uint32_t write_size = size;
    if(rb->empty_size < size)
    {
        write_size = rb->empty_size;
    }
    if(rb->empty_size == 0)
    {
        ERR("ring buffer is full!\n");
        ret = false;
        goto quick_out;
    }
    rb->empty_size -= write_size;

    INFO("request write size = %d, actually write size = %d, so empty size = %d\n",
            size, write_size, rb->empty_size);
    uint32_t first_cp = write_size;
    uint32_t second_cp = 0;
    uint32_t start_index = rb->write_index;
    if(rb->write_index + write_size >= rb->size)
    {
        first_cp = rb->size - rb->write_index;
        second_cp = write_size - first_cp;
        rb->write_index = second_cp;
    }
    else
    {
        rb->write_index += write_size;
    }
    INFO("write start index = %d, first_cp = %d, second_cp = %d, now write_index = %d\n",
            start_index, first_cp, second_cp, rb->write_index);
    memcpy(rb->buf + start_index, buf, first_cp);
    memcpy(rb->buf, buf + first_cp, second_cp);

quick_out:
    return ret;
}
static bool rb_read(struct ring_buffer *rb, uint32_t size, uint8_t *buf)
{
    bool ret = true;
    if((rb == NULL) || (rb->buf == NULL))
    {
        ERR("rb buffer is NULL!\n");
        ret = false;
        goto quick_out;
    }
    uint32_t read_size = size;
    uint32_t full_size = rb->size - rb->empty_size;
    if(full_size < size)
    {
        read_size = full_size;
    }
    if(rb->empty_size == rb->size)
    {
        ERR("ring buffer is empty!\n");
        ret = false;
        goto quick_out;
    }
    rb->empty_size += read_size;

    INFO("request read size = %d, actually read size = %d, so empty size = %d\n",
            size, read_size, rb->empty_size);
    uint32_t first_cp = read_size;
    uint32_t second_cp = 0;
    uint32_t start_index = rb->read_index;

    if(rb->read_index + read_size >= rb->size)
    {
        first_cp = rb->size - rb->read_index;
        second_cp = read_size - first_cp;
        rb->read_index = second_cp;
    }
    else
    {
        rb->read_index += read_size;
    }
    INFO("read start index = %d, first_cp = %d, second_cp = %d, now READ_index = %d\n",
            start_index, first_cp, second_cp, rb->read_index);
    memcpy(buf, rb->buf + start_index, first_cp);
    memcpy(buf + first_cp, rb->buf, second_cp);
quick_out:
    return ret;
}

void rb_strinit(void)
{
    strfunc_rb.create = rb_create;
    strfunc_rb.destory = rb_destory;
    strfunc_rb.write = rb_write;
    strfunc_rb.read = rb_read;
}
