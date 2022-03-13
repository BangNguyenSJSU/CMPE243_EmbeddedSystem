#include <stdint.h>

#include "acceleration.h"
#include "board_io.h"
#include "can_bus.h"
#include "gpio.h"

#include "canlab.h"

static dbc_SENSOR_ACCEL_s dbc_sensor_accel = {0};

static gpio_s mia_led;

static can__num_e can_option = can1;
static uint32_t timeout_ms = 10;
static uint32_t can_baudrate_kbps = 100;
static uint32_t can_rxq_size = 50;
static uint32_t can_txq_size = 10;

static bool accel_sensor_ready = false;

static void callback_BusOFF(uint32_t parameter1) {
  // simply reset bus for now
  // can__reset_bus(can_1);
}
static void callback_OverRun(uint32_t parameter1) {
  // simply reset bus for now
  can__reset_bus(can_option);
}

bool dbc_send_can_message(void *argument_from_dbc_encode_and_send, uint32_t message_id, const uint8_t bytes[8],
                          uint8_t dlc) {
  can__msg_t tx_msg = {0};
  tx_msg.msg_id = message_id;
  tx_msg.frame_fields.data_len = dlc;
  for (int i = 0; i < 8; i++) {
    tx_msg.data.bytes[i] = bytes[i];
  }

  return can__tx(can_option, &tx_msg, 0);
}

static dbc_SENSOR_ACCEL_s get_sensor_data() {
  dbc_SENSOR_ACCEL_s dbc_sensor_data = {0};
  acceleration__axis_data_s sensor_data = {0};
  sensor_data = acceleration__get_data();

  dbc_sensor_data.SENSOR_ACCEL_x = sensor_data.x;
  dbc_sensor_data.SENSOR_ACCEL_y = sensor_data.y;
  dbc_sensor_data.SENSOR_ACCEL_z = sensor_data.z;
  return dbc_sensor_data;
}

void can_handler__init(void) {
  can__init(can_option, can_baudrate_kbps, can_rxq_size, can_txq_size, callback_BusOFF, callback_OverRun);
  can__bypass_filter_accept_all_msgs();
  can__reset_bus(can_option);

  // initialize ACCEL SENSOR
  accel_sensor_ready = acceleration__init();
  // initialize MIA LED indicator
  mia_led = board_io__get_led3();
  gpio__set(board_io__get_led0());
  gpio__set(board_io__get_led1());
  gpio__set(board_io__get_led2());
  gpio__set(board_io__get_led3());
}

void can_handler__read_sensor_update() {
  can__msg_t rx_msg = {0};
  while (can__rx(can_option, &rx_msg, 0)) {
    const dbc_message_header_t header = {
        .message_id = rx_msg.msg_id,
        .message_dlc = rx_msg.frame_fields.data_len,
    };
    dbc_decode_SENSOR_ACCEL(&dbc_sensor_accel, header, rx_msg.data.bytes);
    printf("dbc_SENSOR_ACCEL | x:%d, y:%d, z:%d\n", dbc_sensor_accel.SENSOR_ACCEL_x, dbc_sensor_accel.SENSOR_ACCEL_y,
           dbc_sensor_accel.SENSOR_ACCEL_z);
  }
}

void can_handler__send_sensor_update() {
  if (accel_sensor_ready) {
    dbc_SENSOR_ACCEL_s dbc_sensor_data = get_sensor_data();
    printf("sensor data: %d, %d, %d\n", dbc_sensor_data.SENSOR_ACCEL_x, dbc_sensor_data.SENSOR_ACCEL_y,
           dbc_sensor_data.SENSOR_ACCEL_z);
    if (dbc_encode_and_send_SENSOR_ACCEL(NULL, &dbc_sensor_data)) {
      printf("message sent to CAN bus\n");
    }
  } else {
    printf("sensor not ready!\n");
  }
}

void can_handler__manage_mia_10hz(void) {
  // We are in 10hz slot, so increment MIA counter by 100ms
  const uint32_t mia_increment_value = 100;

  if (dbc_service_mia_SENSOR_ACCEL(&dbc_sensor_accel, mia_increment_value)) {
    // Take action when a message has gone MIA?
    // Maybe light up an LED?
    gpio__reset(mia_led);
    printf("mia detected!\n");
  } else {
    gpio__set(mia_led);
  }
}
