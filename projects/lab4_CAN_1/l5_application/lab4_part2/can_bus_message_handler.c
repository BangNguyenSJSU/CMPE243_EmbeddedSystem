#include "can_bus_message_handler.h"

#include "board_io.h"
#include "can_bus.h"
#include "gpio.h"
#include <stddef.h>
#include <stdint.h>

static can__msg_t can_message1 = {0};

static can__msg_t can_message2 = {0};

static gpio_s sw;
static void switch_init(void) { sw = board_io__get_sw0(); }

void can_bus_handle(void) {

  switch_init();

  can_message1.msg_id = 15;
  can_message1.frame_fields.data_len = 8;
  can_message2.msg_id = 11;
  can_message2.frame_fields.data_len = 8;
  can_message1.data = (can__data_t){5};
  can_message2.data = (can__data_t){0xaabbccddeeffaabb};

  if (!gpio__get(sw)) {
    can__tx(can1, &can_message1, 100);
  } else {
    can__tx(can1, &can_message2, 100);
  }

  //   while (can__rx(can1, &can_message2, 100)) {
  //     printf("Message ID: %d", can_message2.msg_id);
  //   }
}