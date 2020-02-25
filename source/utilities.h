/**
 * @file
 * @brief Various usefull utillities for elevator project
 * 
 */

#ifndef UTILITIES_H
#define UTILITIES_H
#define NUMBER_OF_FLOORS HARDWARE_NUMBER_OF_FLOORS

/**
 * @brief Order type used in @c queue_add_floor
 * 
 */
typedef enum {
    ORDER_UP,
    ORDER_INSIDE,
    ORDER_DOWN,
} OrderType; //Bytte rekkefølge og legge til Utilities foran

/**
 * @brief Direction type used in @c queue_next_in_queue 
 * and in @c queue_is_floor_ordered
 * 
 */
typedef enum {
    UP,
    DOWN,
    STILL
} Direction;

#endif