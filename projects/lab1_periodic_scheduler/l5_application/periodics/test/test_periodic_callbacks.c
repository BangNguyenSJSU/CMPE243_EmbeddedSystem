#include <stdio.h>
#include <string.h>

#include "unity.h"

// Include the Mocks
// - This will not pull the REAL source code of these modules (such as board_io.c)
// - This will auto-generate "Mock" versions based on the header file
#include "Mockboard_io.h"
#include "Mockgpio.h"
#include "Mockswitch_led_logic.h"
#include "Mocktask.h"

// Include the source we wish to test
#include "periodic_callbacks.h"
//#include "switch_led_logic.h"

void setUp(void) {}

void tearDown(void) {}

void test__periodic_callbacks__initialize(void) {

  switch_led_logic_initialize_Expect();
  periodic_callbacks__initialize();

  /* it has the error if i call thes two function with this order  */

  // periodic_callbacks__initialize();
  //  switch_led_logic_initialize_Expect();
}

void test__periodic_callbacks__1Hz(void) {
  gpio_s gpio = {};
  board_io__get_led0_ExpectAndReturn(gpio);
  gpio__toggle_Expect(gpio);

  switch_led_logic_run_once_Expect();
  periodic_callbacks__1Hz(0);
}