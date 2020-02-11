#include <stdio.h>
#include "hardware.h"
#include "elevator.h"

int floor = -1;

int calibrate()
{
    while(floor == -1){
        if (hardware_read_floor_sensor(1)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            floor = 1;
            printf("%d", floor);
            break;
        }
        else{
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
    }
}