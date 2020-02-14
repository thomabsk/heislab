#include "control.h"

void poll_buttons(){
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