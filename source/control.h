#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator.h"
#include "queue.h"
#include "utilities.h"

#ifndef CONTROL_H
#define CONTROL_H

//extern direction current_direction;

/**
 * @brief State used in @c state_machine
 * 
 */
typedef enum{
    STOP,
    INITIALIZE,
    IDLE,
    TAKING_ORDER,
    WAITING
} state;

extern state ELEVATOR_STATE;


/**
 * @brief The state machine used in controlling the elevator
 * 
 * @warning Never returns, is supposed to keep running until terminated
 */
void state_machine();

/**
 * @brief Calculates which floor the elevator should go to
 * 
 * @param next_floor Pointer to the variable which saves the next floor
 * 
 * @param curren_direction Pointer to the current direction the elevator is looking in
 * 
 */
void calculate_next_floor(int *next_floor, direction *current_direction);

/**
 * 
 * @brief Polls the buttons for input, adds to queue.
 * 
 */
void control_poll_buttons();

#endif