#include "elevator.h"


int current_floor = -1;


void elevator_calibrate()
{
    while(current_floor == -1){
        if (hardware_read_floor_sensor(0)){
        	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        	current_floor = 0;
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
 
int elevator_wait(int wait_time){
    hardware_command_door_open(1);
    if(timer_start == 0) timer_set(wait_time);
    if(hardware_read_obstruction_signal()){
        timer_reset();
        return 0;
    }
    if(timer_get()){
        timer_reset();
        hardware_command_door_open(0);
        return 1;
    } 
    else{
        return 0;
    }
}

void elevator_emergency_stop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    int tilstand = 1;
    while(tilstand){
        if(hardware_read_stop_signal()){
            hardware_command_stop_light(1);
            if(elevator_currently_at_a_floor()){
                hardware_command_door_open(1);
                timer_reset();
                timer_set(3);
            }
        }
        else{
            hardware_command_stop_light(0);
            return;
        }




        /*
        if(hardware_read_stop_signal()){
            hardware_command_stop_light(1);
            if(elevator_currently_at_a_floor()){
                hardware_command_door_open(1);
                timer_reset();
                timer_set(3);
            }
        }
        
        else{
            hardware_command_stop_light(0);
            if(hardware_read_obstruction_signal()){
                timer_reset();
                timer_set(3);
            }
            if(timer_get() && elevator_currently_at_a_floor()){
                tilstand = 0;
                timer_reset();
                hardware_command_door_open(0);
            }
            else if(!elevator_currently_at_a_floor()){
                timer_reset();
                tilstand = 0;
            }
        }
        */
    }
}

int elevator_currently_at_a_floor(){
    int at_floor = 0;
    for(unsigned int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++)
    {
        if(hardware_read_floor_sensor(i)){
            at_floor = 1;
        }
    }
    return at_floor;
}

int elevator_change_floor(int goal_floor, direction dir){
    int between_floors_inside = 1;
    for(unsigned int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            current_floor = i;
            hardware_command_floor_indicator_on(i);
            between_floors_inside = 0;
        }
    }
    
    if((goal_floor == current_floor) && (between_floors_inside == 1)){
        if(dir == UP){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            return 1;
        }
        else if(dir == DOWN){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            return 1;
        }
    }
    else if(goal_floor == current_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
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
    return 0;
}
