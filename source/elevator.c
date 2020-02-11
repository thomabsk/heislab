#include <stdio.h>
#include "hardware.h"
#include "elevator.h"

int currentFloor = -1;

void calibrate()
{
    while(currentFloor == -1){
        if (hardware_read_floor_sensor(1)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            currentFloor = 1;
            printf("%d", currentFloor);
            break;
        }
        else{
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
    }
}