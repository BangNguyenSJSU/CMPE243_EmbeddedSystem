#include "unity.h"

// Include the Mocks
// - This will not pull the REAL source code of these modules (such as board_io.c)
// - This will auto-generate "Mock" versions based on the header file
#include "Mockboard_io.h"
#include "Mockcan_handler.h"
#include "Mockgpio.h"
// Include the source we wish to test
#include "periodic_callbacks.h"

void setUp(void) {}
void tearDown(void) {}

void test__periodic_callbacks__initialize(void) {
  can_handler__init_Expect();

  periodic_callbacks__initialize();
}

void test__periodic_callbacks__1Hz(void) { periodic_callbacks__1Hz(0); }

void test__periodic_callbacks__10Hz(void) {

  can_handler__send_sensor_update_Expect();
  // can_handler__manage_mia_10hz_Expect();
  periodic_callbacks__10Hz(0);
}

void test__periodic_callbacks__100Hz(void) {

  // can_handler__read_sensor_update_Expect();

  periodic_callbacks__100Hz(0);
}