#include "unity.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "queue_lab2.h"

#define NUMBER_OF_BYTE 100
static uint8_t queue_array[NUMBER_OF_BYTE];

queue_s2 test_obj_queue;

void setUp(void) { static_memory_queue__init(&test_obj_queue, queue_array, sizeof(queue_array)); }

void tearDown(void) {}

void test_queue__init(void) {

  // Testing the parameter passed into queue__init ??SS

  /* ---------------- Need to ask professor about this --------
    int max_size = 100;
    uint8_t queue_array[max_size];
  */

  // Test current index
  TEST_ASSERT_EQUAL_UINT8(100, test_obj_queue.max_capacity);
  TEST_ASSERT_EQUAL_UINT8(0, test_obj_queue.current_capacity);

  // Test Init head and tail
  TEST_ASSERT_EQUAL_INT(0, test_obj_queue.head_item_index);
  TEST_ASSERT_EQUAL_INT(-1, test_obj_queue.tail_item_index);

  // Test all the array init with 0 or NOT
  for (int byte_index = 0; byte_index < 100; byte_index++) {
    TEST_ASSERT_EQUAL_UINT8(0, *(test_obj_queue.static_memory_for_queue + byte_index));
  }
}

// void test_queue__push_boundary(void) {

//   int dummy_value = 99;
//   int queue_test_size = 102;
//   int queue_max_size = 100;

//   queue__init(&test_obj_queue);

//   // Test
//   for (int i = 0; i < 102; i++) {
//     if (i < queue_max_size) {
//       TEST_ASSERT_TRUE(queue__push(&test_obj_queue, dummy_value));
//     } else {
//       TEST_ASSERT_FALSE(queue__push(&test_obj_queue, dummy_value));
//     }
//   }
// }

// void test_queue__push_first(void) {
//   int test_value = 1;
//   queue__init(&test_obj_queue);

//   // Test queue function
//   TEST_ASSERT_TRUE(queue__push(&test_obj_queue, test_value));
//   TEST_ASSERT_EQUAL_UINT(1, queue__get_item_count(&test_obj_queue));

//   // Test struct element
//   TEST_ASSERT_EQUAL_UINT(1, test_obj_queue.queue_size);
//   TEST_ASSERT_EQUAL_UINT(test_value, test_obj_queue.queue_memory[test_obj_queue.queue_size - 1]);
//   TEST_ASSERT_EQUAL_UINT(0, test_obj_queue.tail_item_index);
//   TEST_ASSERT_EQUAL_UINT(0, test_obj_queue.head_item_index);
// }

// void test_queue__push_2nd_till_end(void) {
//   queue__init(&test_obj_queue);

//   // only have 99 space left
//   for (int item = 0; item < test_obj_queue.queue_capacity; item++) {
//     int test_value = item;

//     // test push
//     TEST_ASSERT_TRUE(queue__push(&test_obj_queue, test_value));
//     // test size
//     TEST_ASSERT_EQUAL_UINT(item + 1, queue__get_item_count(&test_obj_queue));
//     // test tail
//     TEST_ASSERT_EQUAL_UINT(item, test_obj_queue.tail_item_index);
//     // // test head
//     TEST_ASSERT_EQUAL_UINT(0, test_obj_queue.head_item_index);
//   }
// }

// void test_queue__push_FULL_queue(void) {
//   int test_value = 10;
//   TEST_ASSERT_FALSE(queue__push(&test_obj_queue, test_value));
// }

// void test_queue__pop(void) {
//   uint8_t pop_value = -1;
//   TEST_ASSERT_TRUE(queue__pop(&test_obj_queue, &pop_value));
//   TEST_ASSERT_EQUAL_UINT(99, queue__get_item_count(&test_obj_queue));
// }

void test_comprehensive(void) {

  const size_t max_queue_size = 100; // Change if needed
  for (size_t item = 0; item < max_queue_size; item++) {
    const uint8_t item_pushed = (uint8_t)item;
    TEST_ASSERT_TRUE(static_memory_queue__push(&test_obj_queue, item_pushed));
    TEST_ASSERT_EQUAL((item + 1), static_memory_queue__get_item_count(&test_obj_queue));
  }

  // Should not be able to push anymore
  TEST_ASSERT_FALSE(static_memory_queue__push(&test_obj_queue, 123));
  TEST_ASSERT_EQUAL(max_queue_size, static_memory_queue__get_item_count(&test_obj_queue));

  // //== == == == == == == == == == == DONE == == == == == == == == == == == =

  // Pull and verify the FIFO order
  for (size_t item = 0; item < 100; item++) {
    uint8_t popped_value = 0;
    TEST_ASSERT_TRUE(static_memory_queue__pop(&test_obj_queue, &popped_value));
    TEST_ASSERT_EQUAL(100 - (item + 1), static_memory_queue__get_item_count(&test_obj_queue));
    TEST_ASSERT_EQUAL((uint8_t)item, popped_value);
  }

  // Test wrap-around case
  const uint8_t pushed_value = 123;
  TEST_ASSERT_TRUE(static_memory_queue__push(&test_obj_queue, pushed_value));
  uint8_t popped_value = 0;
  TEST_ASSERT_TRUE(static_memory_queue__pop(&test_obj_queue, &popped_value));
  TEST_ASSERT_EQUAL(pushed_value, popped_value);

  TEST_ASSERT_EQUAL(0, static_memory_queue__get_item_count(&test_obj_queue));
  TEST_ASSERT_FALSE(static_memory_queue__pop(&test_obj_queue, &popped_value));
}