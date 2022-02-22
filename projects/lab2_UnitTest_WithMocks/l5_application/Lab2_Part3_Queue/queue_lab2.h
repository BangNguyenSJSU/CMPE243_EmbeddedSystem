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

  uint8_t *static_memory_for_queue;

  // Keep track size
  size_t max_capacity;
  size_t current_capacity;

  // Keep track head and tail
  int head_item_index;
  int tail_item_index;
} queue_s2;

// This should initialize all members of queue_s2
void static_memory_queue__init(queue_s2 *queue, void *static_memory_for_queue, size_t number_of_byte);

/// @returns false if the queue is full
bool static_memory_queue__push(queue_s2 *queue, uint8_t push_value);

/// @returns false if the queue was empty
bool static_memory_queue__pop(queue_s2 *queue, uint8_t *pop_value_ptr);

size_t static_memory_queue__get_item_count(const queue_s2 *queue);

#endif