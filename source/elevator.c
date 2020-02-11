#include <stdio.h>
#include "hardware.h"
#include "elevator.h"

int current_floor = -1;

void elevator_calibrate()
{
    while(current_floor == -1){
        if (hardware_read_floor_sensor(0)){
        	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        	current_floor = 1;
        	printf("CALIBRATION COMPLETED\nCURRENT FLOOR: ");
		printf("%d", current_floor);
		printf("\n");
	
            break;
        }
        else{
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
    }
}
