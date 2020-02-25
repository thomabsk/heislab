/**
 * @file
 * @brief Various usefull utillities for elevator project
 * 
 */

#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @brief Order type used in @c queue_add_floor
 * 
 */
typedef enum {
    ORDER_UP,
    ORDER_INSIDE,
    ORDER_DOWN,
} OrderType;

/**
 * @brief Direction type used in @c queue_next_in_queue 
 * and in @c queue_is_floor_ordered
 * 
 */
typedef enum {
    UP,
    DOWN,
    NONE,
} Direction;

#endif