#include "can_bus_initializer.h"
#include "can_bus.h"
#include <stdio.h>

static void callback_BusOFF(uint32_t parameter1) {
  // do nothing
}
static void callback_OverRun(uint32_t parameter1) {
  // do nothing
}

void can_initial(void) {

  printf("Can ininit\n");

  static can__num_e can_1 = can1;
  static uint32_t can_baudrate = 100;
  static uint32_t can_rxq1 = 10;
  static uint32_t can_txq1 = 10;
  can__init(can_1, can_baudrate, can_rxq1, can_txq1, callback_BusOFF, callback_OverRun);
  can__bypass_filter_accept_all_msgs();
  can__reset_bus(can_1);
}