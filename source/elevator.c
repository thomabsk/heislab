#include "elevator.h"

struct CurrentPosition{
    int current_floor;
    int above;
};

static struct CurrentPosition current_position = {-1, 0};


void elevator_calibrate()
{
    while(current_position.current_floor == -1)
    {
        if(hardware_read_stop_signal()){
            elevator_emergency_stop();
        }
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(hardware_read_floor_sensor(i)){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_floor_indicator_on(i);
                current_position.current_floor = i;
                printf("CALIBRATION COMPLETED\nCURRENT FLOOR: ");
	    	    printf("%d\n", current_position.current_floor);
                return;
            }
        }
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
}

int elevator_get_current_floor()
{
    return current_position.current_floor;
}

int elevator_get_above(){
    return current_position.above;
}
 
int elevator_wait(int wait_time)
{
    hardware_command_door_open(1);
    timer_set(wait_time);
    if(hardware_read_obstruction_signal())
    {
        timer_reset();
        return 0;
    }
    else if(timer_get())
    {
        timer_reset();
        hardware_command_door_open(0);
        return 1;
    } 
    else
    {
        return 0;
    }
}

int elevator_check_emergency_stop()
{
    return hardware_read_stop_signal();
}

void elevator_emergency_stop()
{
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    while(1)
    {
        if(hardware_read_stop_signal())
        {
            hardware_command_stop_light(1);
            if(elevator_currently_at_a_floor())
            {
                hardware_command_door_open(1);
                timer_reset();
                timer_set(3);
            }
        }
        else
        {
            hardware_command_stop_light(0);
            return;
        }
    }
}

int elevator_currently_at_a_floor()
{
    int bool_at_floor = 0;
    for(unsigned int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++)
    {
        if(hardware_read_floor_sensor(i))
        {
            bool_at_floor = 1;
        }
    }
    return bool_at_floor;
}

int elevator_change_floor(int goal_floor)
{
    int bool_between_floors = 1;

    for(unsigned int f = 0; f<HARDWARE_NUMBER_OF_FLOORS; f++) //Updates the current floor, and checks if between two floors.
    {
        if(hardware_read_floor_sensor(f))
        {
            current_position.current_floor = f;
            hardware_command_floor_indicator_on(f);
            bool_between_floors = 0;
        }
    }
   
    if((goal_floor == current_position.current_floor) && (bool_between_floors == 1)){ 
        if(current_position.above){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
        else{
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
    }
    else if(goal_floor == current_position.current_floor)
    {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        return 0;
    }
    else if(goal_floor < current_position.current_floor)
    {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        if(bool_between_floors == 0){
            current_position.above = 0;
        }
        return 1;
    }
    else if(goal_floor > current_position.current_floor)
    {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        if(bool_between_floors == 0){
            current_position.above = 1;
        }
        return 1;
    }
    return 1;
}

