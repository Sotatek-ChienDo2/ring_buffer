#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include<stdio.h>
#include<stdbool.h> // For bool
#include<stddef.h> // For size_t

typedef struct {
    size_t tail_index;
    size_t head_index;
    size_t buffer_size;
    int* buffer;
} ring_buffer_t;

// init
int ringbuffer_init(ring_buffer_t *rb, size_t buffer_size);

// add
int ringbuffer_add(ring_buffer_t *rb, int data);

// remove
int ringbuffer_remove(ring_buffer_t *rb, int* data);

// check empty
bool ringbuffer_is_empty(ring_buffer_t *rb);

// check full
bool ringbuffer_is_full(ring_buffer_t *rb);

// get the number
int ringbuffer_size(ring_buffer_t *rb);

// destroy
void ringbuffer_destroy(ring_buffer_t *rb);

#endif