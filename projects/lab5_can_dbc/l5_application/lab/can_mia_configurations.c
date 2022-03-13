#include <stdbool.h>
#include <stdint.h>

#include "canlab.h"

const uint32_t dbc_mia_threshold_DRIVER_HEARTBEAT = 3000;
const uint32_t dbc_mia_threshold_SENSOR_ACCEL = 150;

// Leave uninitialized if we wish to accept zero values as sane MIA replacement
const dbc_DRIVER_HEARTBEAT_s dbc_mia_replacement_DRIVER_HEARTBEAT;
const dbc_SENSOR_ACCEL_s dbc_mia_replacement_SENSOR_ACCEL;