#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "message_processor.h"

/**
 * This processes messages by calling message__read() until:
 *   - There are no messages to process -- which happens when message__read() returns false
 *   - At most 3 messages have been read
 */
bool message_processor(void) {
  bool symbol_found = false;
  message_s message;
  memset(&message, 0, sizeof(message));

  const static size_t max_messages_to_process = 3;
  for (size_t message_count = 0; message_count < max_messages_to_process; message_count++) {
    if (!message__read(&message)) {
      break;
    } else {
      if (message.data[0] == '$') {
        symbol_found = true;
      } else {
        // Symbol not found
      }
    }
  }

  return symbol_found;
}