/**
 * @file
 * @brief The control unit containing the finite state machine for the elevator
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "elevator.h"
#include "queue.h"

#ifndef CONTROL_H
#define CONTROL_H



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
} State;

/**
 * @brief The state machine used in controlling the elevator
 * 
 * @warning Never returns, is supposed to keep running until terminated
 */
void control_state_machine();

#endif