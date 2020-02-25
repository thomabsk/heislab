/**
 * @file
 * @brief Library for commanding the elevator
 *
 */

#include <stdio.h>
#include "hardware.h"
#include "timer.h"

#ifndef ELEVATOR_H
#define ELEVATOR_H



/**
 * @brief Calibrates the hardware, by making it go to the first floor.
*/
void elevator_calibrate();

/**
 * @brief Returns the current floor.
 * 
 * @return Returns the current floor.
*/
int elevator_get_current_floor();

/**
 * @brief Makes the elevator move towards a desired floor.
 * 
 * @param goal_floor The floor the elevator moves towards.
 * 
 * @return Returns 1 if the elevator is still moving, 0 if stopped at desired floor.
 * 
 * @warning @p goal_floor has to be a valid floor.
*/
int elevator_change_floor(int goal_floor);

/**
 * @brief Stops the elevator in emergency mode.
 * 
 * @warning Does not return before stop button is released.
*/
void elevator_emergency_stop();

/**
 * @brief Makes the elevator stop to pick up passengers at a floor.
 * 
 * @return Returns 1 if the elevator is finished waiting, 0 otherwise.
*/
int elevator_wait(int wait_time);

/**
 * @brief Returns whether or not the elevator is at a floor or between floors.
 * 
 * @return Returns 1 if at a floor, 0 otherwise.
 */
int elevator_currently_at_a_floor();

int elevator_check_emergency_stop();

#endif