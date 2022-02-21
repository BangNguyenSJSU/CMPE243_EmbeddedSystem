#pragma once

#ifndef QUEUE_LAB_H
#define QUEUE_LAB_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* In this part, the queue memory is statically defined
 * and fixed at compile time for 100 uint8s
 */
;
typedef struct {

  uint8_t queue_memory[100];
  // Keep track size
  uint8_t queue_capacity;
  uint8_t queue_size;

  // Keep track head and tail
  uint8_t head_item_index;
  uint8_t tail_item_index;
} queue_s;

// This should initialize all members of queue_s
void queue__init(queue_s *queue);

/// @returns false if the queue is full
bool queue__push(queue_s *queue, uint8_t push_value);

/// @returns false if the queue was empty
bool queue__pop(queue_s *queue, uint8_t *pop_value);

size_t queue__get_item_count(const queue_s *queue);

#endif