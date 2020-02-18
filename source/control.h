#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator.h"
#include "queue.h"
#include "utilities.h"

#ifndef CONTROL_H
#define CONTROL_H

extern direction current_direction;


typedef enum{
    STOP,
    INITIALIZE,
    IDLE,
    TAKING_ORDER,
    WAITING
} state;

extern state ELEVATOR_STATE;

void state_machine();
void calculate_next_floor(int *next_floor);
void control_poll_buttons();

#endif