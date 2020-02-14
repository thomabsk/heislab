#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator.h"

#ifndef CONTROL_H
#define CONTROL_H




typedef enum{
    STOP,
    INITIALIZE,
    IDLE,
    TAKING_ORDER,
} state;

extern state ELEVATOR_STATE;

void state_machine();
int calculate_next_floor();
void control_poll_buttons();

#endif