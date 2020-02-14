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
 * @brief Clears all orders in the queue
 * Must be called once to initialize the queue
 */
void queue_clear_queue();

/**
 * @brief Clears all orders corresponding to the given @p floor
 * 
 * @param floor Floor to clear from queue
 */
void queue_clear_floor(int floor);

/**
 * @brief Add order to queue corresponding to @p floor in queue correspinging to ordertype @p type
 * 
 * @param floor The floor the order corresponds to
 * @param type Type of order.
 * 
 * @return Returns 0 if floor is sucsesfully added, 1 if it 
 */
int queue_add_floor(int floor,  order_type type);


int queue_next_in_queue(int current_floor, direction direction);

int queue_is_floor_ordered(int floor);

void queue_print_queue();

#endif