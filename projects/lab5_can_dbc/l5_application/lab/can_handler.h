#pragma once

void can_handler__init(void);
void can_handler__send_sensor_update(void);
void can_handler__read_sensor_update(void);
void can_handler__manage_mia_10hz(void);