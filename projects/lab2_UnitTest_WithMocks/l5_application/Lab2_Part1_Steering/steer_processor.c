

#include "steer_processor.h"

/*================================== steer_processor ==============================
*@brief:    process steering wheel
*@para:
            uint32_t left_sensor_cm ( input )
            uint32_t right_sensor_cm ( input )
            pin_num
*@return:
            No return

*@Note:
            Assume THRESH HOLD VALUE:  50 cm
            objective is to invoke steering function if sensor value is less that threshhold
            Example: If left sensor is 49 cm, and right is 70 cm --> call steer_right()
====================================================================================*/

void steer_processor(uint32_t left_sensor_cm, uint32_t right_sensor_cm) {

  // one of them less than thresh hold
  if ((50 > left_sensor_cm) || (50 > right_sensor_cm)) {
    // steer_right case:
    if (50 > left_sensor_cm && 50 < right_sensor_cm) {
      steer_right();
    }
    // steer_left case:
    else if (50 > right_sensor_cm && 50 < left_sensor_cm) {
      steer_left();
    }
  }
  // Both of them less than thresh hold
  if ((50 > left_sensor_cm) && (50 > right_sensor_cm)) {

    if (left_sensor_cm < right_sensor_cm) {
      steer_right();
    } else if (right_sensor_cm < left_sensor_cm) {
      steer_left();
    } else if (50 < left_sensor_cm && left_sensor_cm == right_sensor_cm) {
      // Do nothing
    } else if (50 < right_sensor_cm && right_sensor_cm == left_sensor_cm) {
      // Do nothing
    }
  }
  // Both of them greater than thresh hold
  if ((50 < left_sensor_cm) && 50 < (right_sensor_cm)) { // Do Nothing
  }
};
