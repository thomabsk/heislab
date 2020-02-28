/**
 * @file
 * @brief Library for handling elevator queue
 *
 */
#ifndef QUEUE_H
#define QUEUE_H
#include "hardware.h"
#include <stdio.h>



/**
 * @brief Direction type used in @c queue_next_in_queue , @c control_state_machine and @c control_calculate_next_floor
 * 
 */
typedef enum {
    UP,
    DOWN,
    NONE,
} Direction;

/**
 * @brief Clears all orders in the queue.
 * Must be called once to initialize the queue.
 */
void queue_clear_queue();

/**
 * @brief Clears all orders corresponding to the given @p floor.
 * 
 * @param floor Floor to clear from queue.
 */
void queue_clear_floor(int floor);



/**
 * @brief Finds and return next floor based on @p current_floor and @p direction of the elevator.
 * 
 * @param current_floor The current floor of the elevator.
 * @param direction The direction of the elevator.
 * 
 * @return Returns an int corresponding to next floor in queue. 
 * Return -1 if there are no more orders in the given @p direction.
 */
int queue_next_in_queue(int current_floor, Direction direction);

/**
 * @brief Polls all the buttons, adds to queue, and turns the right lights on.
 * 
 */
void queue_update();

#endif