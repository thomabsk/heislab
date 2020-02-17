#include "control.h"

state ELEVATOR_STATE = INITIALIZE;
direction current_direction = UP;

void control_poll_buttons(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
            queue_add_floor(f,ORDER_INSIDE);
         }
        if(hardware_read_order(f, HARDWARE_ORDER_UP)){
            queue_add_floor(f, ORDER_UP);
            }
        if(hardware_read_order(f,HARDWARE_ORDER_DOWN)){
            queue_add_floor(f, ORDER_DOWN);
        }
    }
}


void state_machine(){
    int next_floor = 0;
    while(1){
        switch(ELEVATOR_STATE)
        {
            case INITIALIZE:
                elevator_calibrate();
                queue_clear_queue();
                ELEVATOR_STATE = IDLE;
                break;
            case STOP:
                elevator_emergency_stop();
                queue_clear_queue();
                if(hardware_read_stop_signal()){
                    hardware_command_stop_light(1);
                    if(elevator_currently_at_a_floor()){
                        hardware_command_door_open(1);
                        timer_reset();
                        timer_set(3);
                    }
                    break;
                }
                else if(!elevator_currently_at_a_floor()){
                    hardware_command_stop_light(0);
                    queue_clear_queue();
                    timer_reset();
                    ELEVATOR_STATE = IDLE;
                }
                if(!hardware_read_stop_signal()){
                    hardware_command_stop_light(0);
                }
                if(hardware_read_obstruction_signal()){
                    timer_reset();
                    timer_set(3);
                }
                if(elevator_currently_at_a_floor() && timer_get()){
                    hardware_command_stop_light(0);
                    hardware_command_door_open(0);
                    queue_clear_queue();
                    timer_reset();
                    ELEVATOR_STATE = IDLE;
                }
                break;
            case IDLE:
                if(hardware_read_stop_signal()){
                    ELEVATOR_STATE = STOP;
                    break;
                }
                control_poll_buttons();
                
                //if((elevator_get_current_floor() == 0) && (current_direction == DOWN)) current_direction = UP;
                //if((elevator_get_current_floor() == HARDWARE_NUMBER_OF_FLOORS -1 ) && (current_direction == UP)) current_direction = DOWN;
                next_floor = queue_next_in_queue(elevator_get_current_floor(), current_direction);
                printf("%d\n", next_floor);
                if(next_floor == -1)
                {
                    if(current_direction == UP){
                        current_direction = DOWN;
                        next_floor = queue_next_in_queue(HARDWARE_NUMBER_OF_FLOORS-1, current_direction);
                    } 
                    else if(current_direction == DOWN){
                        current_direction = UP;
                        next_floor = queue_next_in_queue(0, current_direction);
                    }
                }
                if(!(next_floor == -1)){
                    ELEVATOR_STATE = TAKING_ORDER;
                }
                break;
            case TAKING_ORDER:
                if(hardware_read_stop_signal()){
                    ELEVATOR_STATE = STOP;
                    break;
                }
                control_poll_buttons();
                

                if(elevator_change_floor(next_floor)){
                    ELEVATOR_STATE = IDLE;
                }
                else{
                    ELEVATOR_STATE = WAITING;
                }

                break;
            case WAITING:
                control_poll_buttons();
                if(hardware_read_stop_signal()){
                    ELEVATOR_STATE = STOP;
                    break;
                }
                queue_clear_floor(elevator_get_current_floor());
                if(elevator_wait(3)){
                    ELEVATOR_STATE = IDLE;
                }
                break;

    }
    }
}