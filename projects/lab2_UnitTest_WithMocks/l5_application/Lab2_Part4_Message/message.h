#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdbool.h>

typedef struct {
  char data[8];

} message_s;

bool message__read(message_s *message_to_read);

#endif