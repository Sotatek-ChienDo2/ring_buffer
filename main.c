#include<stdio.h>
#include"inc/ring_buffer.h"

int main()
{
    ring_buffer_t rb;
    ringbuffer_init(&rb, 5);
    
    if(ringbuffer_is_empty(&rb))
    {
        printf("Buffer is empty\n");
    }

    ringbuffer_add(&rb, 10);
    ringbuffer_add(&rb, 20);
    ringbuffer_add(&rb, 30);
    ringbuffer_add(&rb, 40);
    ringbuffer_add(&rb, 50);
    
    if(ringbuffer_is_full(&rb))
    {
        printf("Buffer is full\n");
    }

    int value;
    ringbuffer_remove(&rb, &value);
    printf("Value: %d\n", value);

    printf("Value: %d\n", ringbuffer_size(&rb));
    ringbuffer_destroy(&rb);
    
    return 0;
}