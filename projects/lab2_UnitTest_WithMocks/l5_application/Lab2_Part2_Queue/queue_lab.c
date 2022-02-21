
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "queue_lab.h"

// This should initialize all members of queue_s
void queue__init(queue_s *queue) {

  // If *queue != NULL ??? How to do it ?
  if (queue != NULL) {

    queue->queue_capacity = 100;
    queue->queue_size = 0;
    queue->head_item_index = 0;
    queue->tail_item_index = 0;

    // Init all the array with 0
    uint8_t counter = 0;
    while (100 != counter) {
      queue->queue_memory[counter] = 0;
      counter++;
    }
  }
}

/// @returns false if the queue is full
bool queue__push(queue_s *queue, uint8_t push_value) {

  // first time
  if (0 == queue->queue_size) {
    queue->queue_memory[queue->queue_size] = push_value;
    queue->queue_size++;
    return true;
  }
  // queue still have space
  if (0 != queue->queue_size && (queue->queue_size < queue->queue_capacity)) {

    queue->tail_item_index = queue->queue_size;
    queue->queue_memory[queue->tail_item_index] = push_value;
    queue->queue_size++;
    return true;
  }

  // queue FULL
  return false;
}

/// @returns false if the queue was empty
bool queue__pop(queue_s *queue, uint8_t *pop_value) {

  if (0 != queue->queue_size) {

    *pop_value = queue->queue_memory[queue->head_item_index];
    queue->queue_size--;

    for (int i = 0; i < queue->queue_size; i++) {
      queue->queue_memory[i] = queue->queue_memory[i + 1];
    }

    return true;
  } else {
    return false;
  }
}

/// @returns number of item inside queue
size_t queue__get_item_count(const queue_s *queue) { return queue->queue_size; }
