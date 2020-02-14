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

int elevator_get_current_floor(){
    return current_floor;
}
 
void elevator_wait(int wait_time){
    hardware_command_door_open(1);
    timer_set(wait_time);
    while(1){
        if(hardware_read_obstruction_signal()){
            timer_reset();
            timer_set(3);
        }
        else{
            if(timer_get()){
                break;
            }
        }
    }
    hardware_command_door_open(0);
}

void elevator_emergency_stop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

int elevator_change_floor(int goal_floor){
    for(unsigned int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            current_floor = i;
        }
    }
    if(goal_floor == current_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        hardware_command_floor_indicator_on(current_floor);
        return 0;
    }
    else if(goal_floor < current_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        return 1;
    }
    else if(goal_floor > current_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        return 1;
    }
}