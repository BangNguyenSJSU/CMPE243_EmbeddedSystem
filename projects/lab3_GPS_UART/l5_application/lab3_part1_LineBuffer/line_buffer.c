
#include "line_buffer.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// ------------------ Private Section Function ------------------------

static bool line_buffer_isFULL(line_buffer_s *line_buffer) {
  return line_buffer->write_index == line_buffer->max_size ? true : false;
}

static bool line_buffer_isEMPTY(line_buffer_s *line_buffer) { return line_buffer->write_index == 0 ? true : false; }

static bool line_buffer_isCOMPLETE(line_buffer_s *line_buffer) { return line_buffer->new_line_char; }

// --------------------------------------------------------------------

/**
 * Initialize *line_buffer_s with the user provided line_buffer space and size
 * Use should initialize the line_buffer with whatever memory they need
 * @code
 *  char memory[256];
 *  line_buffer_s line_buffer = { };
 *  line_buffer__init(&line_buffer, memory, sizeof(memory));
 * @endcode
 */
bool line_buffer__init(line_buffer_s *line_buffer, char *memory, size_t size) {
  // Checking the NULL pointer
  if (NULL != line_buffer && NULL != memory) {

    line_buffer->max_size = size;
    line_buffer->memory = memory;
    line_buffer->write_index = 0;
    line_buffer->new_line_char = false;
    line_buffer->head_index = 0;
    line_buffer->tail_index = -1;

    return true;
  } else {
    return false;
  }
}

// Adds a byte to the line_buffer, and returns true if the line_buffer had enough space to add the byte
bool line_buffer__add_byte(line_buffer_s *line_buffer, char byte) {

  bool add_status = false;
  if (!line_buffer_isFULL(line_buffer)) {

    // Update Tail index + value
    line_buffer->tail_index = (line_buffer->tail_index + 1) % line_buffer->max_size;
    line_buffer->memory[line_buffer->tail_index] = byte;

    // Identify the index of '\n'
    if (line_buffer->memory[line_buffer->tail_index] == '\n') {
      line_buffer->new_line_char = true;
    }

    line_buffer->write_index++;
    add_status = true;
  } else {
    // full case
    add_status = false;
  }

  return add_status;
}

/**
 * If the line line_buffer has a complete line, it will remove that contents and save it to "char * line"
 * Note that the line_buffer may have multiple lines already in the line_buffer, so it will require multiple
 * calls to this function to empty out those lines
 *
 * The one corner case is that if the line_buffer is FULL, and there is no '\n' character, then you should
 * empty out the line to the user line_buffer even though there is no newline character
 *
 * @param line_max_size This is the max size of 'char * line' memory pointer
 */

bool line_buffer__remove_line(line_buffer_s *line_buffer, char *line, size_t line_max_size) {
  bool remove_status = false;
  if (line_buffer_isCOMPLETE(line_buffer) && (!line_buffer_isEMPTY(line_buffer))) {

    size_t line_counter = 0;

    // head has '\n' byte
    if (line_buffer->memory[line_buffer->head_index] == '\n') {
      // Update new head index
      line_buffer->head_index = (line_buffer->head_index + 1) % line_buffer->max_size;
      line_buffer->write_index--;
      // head has NOT '\n\ byte
    } else {
      for (int i = line_buffer->head_index; line_buffer->memory[i] != '\n'; i++) {
        *(line + line_counter) = line_buffer->memory[i];

        line_counter++;

        // Update new head index
        line_buffer->head_index = (line_buffer->head_index + 1) % line_buffer->max_size;
        line_buffer->write_index--;
      }
      // skip the next '\n'
      line_buffer->head_index = (line_buffer->head_index + 1) % line_buffer->max_size;
      line_buffer->write_index--;
    }

    // Update status
    remove_status = true;
  } else if (!line_buffer_isCOMPLETE(line_buffer) && line_buffer_isFULL(line_buffer)) {

    // Read all except last char
    for (int i = 0; i < line_buffer->max_size - 1; i++) {
      *(line + i) = line_buffer->memory[i];
      // Update new head index
      line_buffer->head_index = (line_buffer->head_index + 1) % line_buffer->max_size;
      line_buffer->write_index--;
    }
    line_buffer->write_index--;

    // Update status
    remove_status = true;
  } else {
    // empty case
    remove_status = false;
  }

  return remove_status;
}
