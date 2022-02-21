#include "Mocksteering.h"
#include "steer_processor.h"
#include "unity.h"

void test_steer_processor__move_left(void) {
  steer_left_Expect();
  steer_processor(51, 49);
}

void test_steer_processor__move_right(void) {
  steer_right_Expect();
  steer_processor(49, 51);
}

void test_steer_processor__both_sensors_less_than_threshold_left_less_right(void) {
  steer_left_Ignore();
  steer_right_Expect();
  steer_processor(40, 45);
}

void test_steer_processor__both_sensors_less_than_threshold_right_less_left(void) {
  steer_right_Ignore();
  steer_left_Expect();
  steer_processor(45, 40);
}

void test_steer_processor__both_sensors_less_than_threshold_butEqual(void) {
  steer_right_Ignore();
  steer_left_Ignore();
  steer_processor(67, 75);
}

void test_steer_processor__both_sensors_more_than_threshold(void) {
  steer_left_Ignore();
  steer_right_Ignore();
  steer_processor(65, 75);
}

void test_steer_processor(void) {
  steer_right_Expect();
  steer_processor(10, 20);

  steer_left_Expect();
  steer_processor(20, 10);
}