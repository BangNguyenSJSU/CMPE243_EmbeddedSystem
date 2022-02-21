
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "queue_lab.h"

//--------------------------------- Helper fucntion -------------------------

static bool queue__isFULL(queue_s *queue) { return queue->current_capacity == queue->max_capacity ? true : false; }

static bool queue__isEMPTY(queue_s *queue) { return 0 == queue->current_capacity ? true : false; }

// ---------------------------------------------------------------------------

// This should initialize all members of queue_s
void queue__init(queue_s *queue) {

  // If *queue != NULL ??? How to do it ?
  if (queue != NULL) {

    queue->max_capacity = 100;
    queue->current_capacity = 0;
    queue->head_item_index = 0;
    queue->tail_item_index = -1;

    // Init all the array with 0
    uint8_t counter = 0;
    while (100 != counter) {
      queue->queue_memory[counter] = 0;
      counter++;
    }
  }
}

/// @returns false if the queue is full
// always add thing in tail of the queue and update tail
bool queue__push(queue_s *queue, uint8_t push_value) {

  if (!queue__isFULL(queue)) {
    /*
     Note :
      --> First push item tail_item_index = (-1 + 1 ) % 100 = 0

      --> 103 Times, push item tail_item_index = (-1 + 103) % 100 = 2
    */
    // Update a new tail index
    queue->tail_item_index = (queue->tail_item_index + 1) % queue->max_capacity;
    // Update value
    queue->queue_memory[queue->tail_item_index] = push_value;
    // Update size
    queue->current_capacity++;

    return true;
  } else {
    // queue FULL
    return false;
  }
}

/// @returns false if the queue was empty
// always remove thing in head of the queue and update head
bool queue__pop(queue_s *queue, uint8_t *pop_value) {

  if (!queue__isEMPTY(queue)) {
    // Remove the value
    *pop_value = queue->queue_memory[queue->head_item_index];

    // Update new head index
    queue->head_item_index = (queue->head_item_index + 1) % queue->max_capacity;

    // Update size
    queue->current_capacity--;

    return true;
  } else {
    return false;
  }
}

/// @returns number of item inside queue
size_t queue__get_item_count(const queue_s *queue) { return queue->current_capacity; }
