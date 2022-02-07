#pragma once

#include "board_io.h"
#include "gpio.h"
#include <stdint.h>

/* Initialize function for switch and LED */
void switch_led_logic__initialize();

/*  Switch LED Run Once */
void switch_led_logic__run_once();