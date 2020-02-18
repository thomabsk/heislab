/**
 * @file
 * @brief Library for commanding the elevator
 *
 */

#include <stdio.h>
#include "hardware.h"
#include "timer.h"
#include "utilities.h"

#ifndef ELEVATOR_H
#define ELEVATOR_H

extern int current_floor;
extern int between_floors;

/**
 * @brief Calibrates the hardware, by making it go to the first floor
*/
void elevator_calibrate();

/**
 * @brief Returns the current floor
 * 
 * @return Current floor
*/
int elevator_get_current_floor();

/**
 * @brief Makes the elevator move towards a desired floor.
 * 
 * @param goal_floor The floor the elevator moves towards.
 * 
 * @return Returns 1 if the elevator is still moving, 0 if stopped at desired floor.
*/
int elevator_change_floor(int goal_floor, direction dir);

/**
 * @brief Stops the elevator 
*/
void elevator_emergency_stop();

/**
 * @brief Makes the elevator stop to pick up passengers 
*/
int elevator_wait(int wait_time);

int elevator_currently_at_a_floor();

#endif