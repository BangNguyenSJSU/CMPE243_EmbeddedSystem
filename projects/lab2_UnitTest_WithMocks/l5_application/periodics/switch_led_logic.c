

#include <stdint.h>

#include "board_io.h"
#include "gpio.h"
#include "switch_led_logic.h"

/* ------------- Variable ------------- */
static gpio_s my_led;
static gpio_s my_switch;

/* Initialize function for switch and LED */
void switch_led_logic_initialize() {
  my_led = gpio__construct_as_output(GPIO__PORT_2, 0);
  my_switch = gpio__construct_as_input(GPIO__PORT_2, 1);
}

/*  Switch LED Run Once */
void switch_led_logic_run_once() {
  if (gpio__get(my_switch)) {
    gpio__set(my_led);
  } else {
    gpio__reset(my_led);
  }
}