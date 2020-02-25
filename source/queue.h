/**
 * @file
 * @brief Library for handling elevator queue
 *
 */
#ifndef QUEUE_H
#define QUEUE_H
#include "utilities.h"
#include "hardware.h"
#include <stdio.h>


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
 * @brief Add order to queue corresponding to @p floor in queue correspinging to ordertype @p type.
 * 
 * @param floor The floor the order corresponds to.
 * @param type Type of order.
 * 
 */
void queue_add_floor(int floor,  OrderType order_type);

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

void queue_poll_buttons();


void queue_print_queue();

#endif