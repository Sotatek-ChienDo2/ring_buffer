#include "ring_buffer.h"
#include <stdlib.h>
// #include <string.h>

// init
int ringbuffer_init(ring_buffer_t *rb, size_t buffer_size)
{
    if(buffer_size == 0)
    {
        return -1;
    }

    rb->buffer = (int*)malloc(buffer_size * sizeof(int));
    if (rb->buffer == NULL) {
        return -1; 
    }

    rb->buffer_size = buffer_size;
    rb->head_index = 0;
    rb->tail_index = 0;
    rb->full_size = 0;
    return 0;
}

// add
int ringbuffer_add(ring_buffer_t *rb, int data)
{
    if(ringbuffer_is_full(rb))
    {
        return -1;
    }

    rb->buffer[rb->tail_index] = data;
    rb->tail_index = (rb->tail_index + 1) % rb->buffer_size;
    rb->full_size++;
    return 0;
}

// remove
int ringbuffer_remove(ring_buffer_t *rb, int* data)
{
    if(ringbuffer_is_empty(rb))
    {
        return -1;
    }

    *data = rb->buffer[rb->head_index];
    rb->head_index = (rb->head_index + 1) % rb->buffer_size;
    rb->full_size--;
    return 0; 
}

// check empty
bool ringbuffer_is_empty(ring_buffer_t *rb)
{
    return rb->full_size == 0;
}

// check full
bool ringbuffer_is_full(ring_buffer_t *rb)
{
    return rb->full_size == rb->buffer_size;
}

// get the size
int ringbuffer_size(ring_buffer_t *rb)
{
    if (rb->tail_index > rb->head_index) 
    {
        return rb->tail_index - rb->head_index;
    } else if(rb->tail_index == rb->head_index)
    {
        if(ringbuffer_is_full(rb))
        {
            return rb->buffer_size;
        } else
        {
            return 0;
        }
    } else
    {
        return rb->buffer_size - (rb->head_index - rb->tail_index);
    }
}

// destroy
void ringbuffer_destroy(ring_buffer_t *rb)
{
    free(rb->buffer);
    rb->buffer = NULL;
    rb->buffer_size = 0;
    rb->head_index = 0;
    rb->tail_index = 0;
    rb->full_size = 0;
}