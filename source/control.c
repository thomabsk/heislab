#include "control.h"

state ELEVATOR_STATE = INITIALIZE;

void control_poll_buttons(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f,HARDWARE_ORDER_INSIDE,1);
         }
        if(hardware_read_order(f, HARDWARE_ORDER_UP)){
             hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            }
        if(hardware_read_order(f,HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
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
                elevator_change_floor(2);
                break;
            case TAKING_ORDER:
                break;
    }
    }
}