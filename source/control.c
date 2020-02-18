#include "control.h"

state ELEVATOR_STATE = INITIALIZE;
//direction current_direction = UP;

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

void calculate_next_floor(int *next_floor, direction *current_direction){
    *next_floor = queue_next_in_queue(elevator_get_current_floor(), *current_direction);
    
    if(*next_floor == -1)
    {
        if(*current_direction == UP){
            *current_direction = DOWN;
            *next_floor = queue_next_in_queue(HARDWARE_NUMBER_OF_FLOORS-1, *current_direction);
            
        } 
        else if(*current_direction == DOWN){
            *current_direction = UP;
            *next_floor = queue_next_in_queue(0, *current_direction);
        }
    }
}

void state_machine(){
    int next_floor = 0;
    direction current_direction = UP;
    while(1){
        switch(ELEVATOR_STATE)
        {
            case INITIALIZE:
                
                elevator_calibrate();
                queue_clear_queue();
                ELEVATOR_STATE = IDLE;
                printf("Current state: IDLE\n");
                break;
            case STOP:
                queue_clear_queue();
                elevator_emergency_stop();
                if(elevator_currently_at_a_floor()){
                    printf("Current state: WAITING\n");
                    ELEVATOR_STATE = WAITING;
                    break;
                }
                printf("Current state: IDLE\n");
                ELEVATOR_STATE = IDLE;
                break;
                
            case IDLE:
                
                if(hardware_read_stop_signal()){
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }
                control_poll_buttons();
                calculate_next_floor(&next_floor, &current_direction);
                if(!(next_floor == -1)){
                    printf("Current state: TAKING_ORDER\n");
                    ELEVATOR_STATE = TAKING_ORDER;
                }
                break;
            case TAKING_ORDER:
                
                if(hardware_read_stop_signal()){
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }
                control_poll_buttons();
                if(!(next_floor == -1)){
                    if(elevator_change_floor(next_floor, current_direction)){
                        calculate_next_floor(&next_floor, &current_direction);
                    }
                    else{
                       printf("Current state: WAITING\n");
                       ELEVATOR_STATE = WAITING;
                    }
                }
                calculate_next_floor(&next_floor, &current_direction);
                break;
            case WAITING:
                
                control_poll_buttons();
                if(hardware_read_stop_signal()){
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }
                queue_clear_floor(elevator_get_current_floor());
                if(elevator_wait(3)){
                    printf("Current state: IDLE\n");
                    ELEVATOR_STATE = IDLE;
                }
                break;

    }
    }
}