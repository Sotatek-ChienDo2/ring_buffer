#include<stdio.h>
#include"inc/ring_buffer.h"

int main()
{
    ring_buffer_t rb;
    ringbuffer_init(&rb, 5);

    ringbuffer_add(&rb, 10);
    ringbuffer_add(&rb, 20);
    
    int value = 10;
    ringbuffer_remove(&rb, &value);

    ringbuffer_destroy(&rb);
    
    return 0;
}