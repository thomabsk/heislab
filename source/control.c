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
    while(1){
        switch(ELEVATOR_STATE)
        {
            case INITIALIZE:
                elevator_calibrate();
                ELEVATOR_STATE = IDLE;
                break;
            case STOP:
                break;
            case IDLE:
                control_poll_buttons();
                if(queue_next_in_queue(elevator_get_current_floor(), current_direction) == -1){

                    break;
                }
                ELEVATOR_STATE = TAKING_ORDER;
                break;
            case TAKING_ORDER:
                if(elevator_change_floor(queue_next_in_queue(elevator_get_current_floor(), current_direction))){
                    printf("%d", queue_next_in_queue(elevator_get_current_floor(), current_direction));
                    printf("\n");
                    break;
                }
                else{
                    ELEVATOR_STATE = IDLE;
                }
                if(!elevator_change_floor(queue_next_in_queue(elevator_get_current_floor(), current_direction))){
                    queue_clear_floor(elevator_get_current_floor());
                    printf("FINISH\n");
                }
                
                break;
    }
    }
}