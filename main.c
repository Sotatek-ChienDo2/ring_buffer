// #include<stdio.h>
#include"inc/ring_buffer.h"
#include<gtest/gtest.h>

TEST(RingBufferTest, InitZeroSize)
{
    ring_buffer_t rb;

    ASSERT_EQ(ringbuffer_init(&rb, 0), -1);

    int result = ringbuffer_init(&rb, SIZE_MAX);
    ASSERT_EQ(result, -1);

}

TEST(RingBufferTest, InitAndBasicOperations)
{
    ring_buffer_t rb;

    // Test init
    ASSERT_EQ(ringbuffer_init(&rb, 5), 0);
    ASSERT_EQ(ringbuffer_size(&rb), 0);
    ASSERT_FALSE(ringbuffer_is_full(&rb));
    ASSERT_TRUE(ringbuffer_is_empty(&rb));

    // Test add
    ASSERT_EQ(ringbuffer_add(&rb, 10), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 20), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 30), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 40), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 50), 0);
    ASSERT_EQ(ringbuffer_size(&rb), 5);
    ASSERT_TRUE(ringbuffer_is_full(&rb));

    // Test remove
    int data;
    ASSERT_EQ(ringbuffer_remove(&rb, &data), 0);
    ASSERT_EQ(data, 10);
    ASSERT_EQ(ringbuffer_size(&rb), 4);

    ringbuffer_destroy(&rb);
}

TEST(RingBufferTest, AddToFullBuffer)
{
    ring_buffer_t rb;

    // Test init
    ASSERT_EQ(ringbuffer_init(&rb, 3), 0);
    ASSERT_FALSE(ringbuffer_is_full(&rb));
    ASSERT_TRUE(ringbuffer_is_empty(&rb));

    // Test add
    ASSERT_EQ(ringbuffer_add(&rb, 10), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 20), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 30), 0);
    ASSERT_TRUE(ringbuffer_is_full(&rb));
    ASSERT_EQ(ringbuffer_add(&rb, 40), -1);

    ringbuffer_destroy(&rb);
}

TEST(RingBufferTest, RemoveFromEmptyBuffer)
{
    ring_buffer_t rb;

    // Test init
    ASSERT_EQ(ringbuffer_init(&rb, 3), 0);
    ASSERT_FALSE(ringbuffer_is_full(&rb));
    ASSERT_TRUE(ringbuffer_is_empty(&rb));

    // Test remove
    int data;
    ASSERT_EQ(ringbuffer_remove(&rb, &data), -1);

    ringbuffer_destroy(&rb);
}

TEST(RingBufferTest, AddAndRemove)
{
    ring_buffer_t rb;

    // Test init
    ASSERT_EQ(ringbuffer_init(&rb, 3), 0);
    ASSERT_FALSE(ringbuffer_is_full(&rb));
    ASSERT_TRUE(ringbuffer_is_empty(&rb));

    // Test add and remove
    ASSERT_EQ(ringbuffer_add(&rb, 10), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 20), 0);
    ASSERT_EQ(ringbuffer_size(&rb), 2);

    int data;
    ASSERT_EQ(ringbuffer_remove(&rb, &data), 0);
    ASSERT_EQ(data, 10);
    ASSERT_EQ(ringbuffer_add(&rb, 30), 0);
    ASSERT_EQ(ringbuffer_add(&rb, 40), 0);
    ASSERT_TRUE(ringbuffer_is_full(&rb));
    ASSERT_EQ(ringbuffer_remove(&rb, &data), 0);
    ASSERT_EQ(data, 20);
    ASSERT_EQ(ringbuffer_remove(&rb, &data), 0);
    ASSERT_EQ(data, 30);
    ASSERT_EQ(ringbuffer_remove(&rb, &data), 0);
    ASSERT_EQ(data, 40);
    ASSERT_TRUE(ringbuffer_is_empty(&rb));

    ringbuffer_destroy(&rb);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}