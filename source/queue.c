#include "queue.h"
#include "utilities.h"


int queue_up[NUMBER_OF_FLOORS];
int queue_down[NUMBER_OF_FLOORS];
int queue_inside[NUMBER_OF_FLOORS];



void queue_clear_cueue() {
    
    for(int i = 0; i < NUMBER_OF_FLOORS; i++){
        queue_up[i] = 0;
        queue_down[i] = 0;
        queue_inside[i] = 0;
    }
}

void queue_clear_floor(int floor) {
   
    queue_up[floor - 1] = 0;
    queue_down[floor - 1] = 0;
    queue_inside[floor - 1] = 0;
}


int queue_add_floor(int floor, order_type type) {
    
    switch (type)
    {
        case ORDER_UP:
            queue_up[floor - 1] = 1;
            break;
        
        case ORDER_DOWN:
            queue_down[floor - 1] = 1;
            break;
        
        case ORDER_INSIDE:
            queue_inside[floor - 1] = 1;
            break;
        default:
            return 1;
            break;
    }

    return 0;
}


int queue_next_in_queue(int current_floor, direction direction) {

    if (direction == UP) {
        for(int i = current_floor; i < NUMBER_OF_FLOORS; i++ ) {
            if (queue_up[i] == 1) {
                return i+1;
            }
        }
    }

    if (direction == DOWN) {
         for(int i = current_floor; i <= 0; i-- ) {
            if (queue_down[i] == 1) {
                return i+1;
            }
        }
    }

    return -1;
}


int queue_is_floor_ordered(int floor) {

    if (queue_up[floor -1] || queue_down[floor - 1] || queue_inside[floor - 1]) {
        return 1;
    }

    return 0;
}