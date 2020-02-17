#include "queue.h"


int QUEUE_UP[NUMBER_OF_FLOORS];
int QUEUE_DOWN[NUMBER_OF_FLOORS];
int QUEUE_INSIDE[NUMBER_OF_FLOORS];


void queue_clear_queue() {
    
    for(int i = 0; i < NUMBER_OF_FLOORS; i++){
        QUEUE_UP[i] = 0;
        QUEUE_DOWN[i] = 0;
        QUEUE_INSIDE[i] = 0;

        hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
        hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
        hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
    }
}


void queue_clear_floor(int floor) {
   
    QUEUE_UP[floor] = 0;
    QUEUE_DOWN[floor] = 0;
    QUEUE_INSIDE[floor] = 0;

    hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
}


int queue_add_floor(int floor, order_type type) {
    
    switch (type)
    {
        case ORDER_UP:
            QUEUE_UP[floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
            break;
        
        case ORDER_DOWN:
            QUEUE_DOWN[floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
            break;
        
        case ORDER_INSIDE:
            QUEUE_INSIDE[floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
            break;

        default:
            return 1;
            break;
    }

    return 0;
}


int queue_next_in_queue(int current_floor, direction direction) {

    if (direction == UP) {
        for(int i = current_floor + 1; i < NUMBER_OF_FLOORS; i++ ) {
            if (QUEUE_UP[i] == 1 || QUEUE_INSIDE[i] == 1) {
                return i;
            }
        }
        if (QUEUE_DOWN[NUMBER_OF_FLOORS -1] == 1) {       
            return 3;                       //cheking if there are orders downwards in the highest floor.
        }
    }

    if (direction == DOWN) {
         for(int i = current_floor - 1; i >= 0; i-- ) {
            if (QUEUE_DOWN[i] == 1 || QUEUE_INSIDE[i] == 1) {
                return i;
            }
        }
        if (QUEUE_UP[0] == 1) {
            return 0;                       //cheking if there are orders upwards in the lowest floor.
        }
    }

    return -1;
}


int queue_is_floor_ordered(int floor, direction direction) {

   if (direction == UP) {
       return (QUEUE_UP[floor] || QUEUE_INSIDE[floor]);
   }

   if (direction == DOWN) {
       return (QUEUE_DOWN[floor] || QUEUE_INSIDE[floor]);
   }
   return 0;
}


void queue_print_queue() {
    for(int i = 0; i < NUMBER_OF_FLOORS; i++) {
        printf("queue_up floor %d = %d\n", i+1, QUEUE_UP[i]);
    }
    for(int i = 0; i < NUMBER_OF_FLOORS; i++) {
        printf("queue_down floor %d = %d\n", i+1, QUEUE_DOWN[i]);
    }
    for(int i = 0; i < NUMBER_OF_FLOORS; i++) {
        printf("queue_inside floor %d = %d\n", i+1, QUEUE_INSIDE[i]);
    }
}