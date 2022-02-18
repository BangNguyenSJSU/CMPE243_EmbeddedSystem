

#include "steer_processor.h"

void steer_processor(uint32_t left_sensor_cm, uint32_t right_sensor_cm) {

  if (10 == left_sensor_cm) {
    steer_left();
  } else if (10 == right_sensor_cm) {
    steer_right();
  }
}
