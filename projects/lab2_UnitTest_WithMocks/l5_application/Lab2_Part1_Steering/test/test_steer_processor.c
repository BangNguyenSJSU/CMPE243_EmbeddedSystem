#include "Mocksteering.h"
#include "steer_processor.h"
#include "unity.h"

void test_steer_processor__move_left(void) {
  steer_left_Expect();
  steer_processor(10, 20);
}

void test_steer_processor__move_right(void) {
  //   steer_right_Expect();
  //   steer_processor(20, 10);
}

void test_steer_processor__both_sensors_less_than_threshold(void) {}

// Hint: If you do not setup an Expect()
// then this test will only pass none of the steer functions is called
void test_steer_processor__both_sensors_more_than_threshold(void) {}

// Do not modify this test case
// Modify your implementation of steer_processor() to make it pass
// This tests corner case of both sensors below the threshold
void test_steer_processor(void) {
  // steer_right_Expect();
  // steer_processor(10, 20);

  // steer_left_Expect();
  // steer_processor(20, 10);
}