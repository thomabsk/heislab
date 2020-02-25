#include "queue.h"


static int m_queue_up[NUMBER_OF_FLOORS];
static int m_queue_down[NUMBER_OF_FLOORS];
static int m_queue_inside[NUMBER_OF_FLOORS];


void queue_poll_buttons(){
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

void queue_clear_queue() 
{
    for(int i = 0; i < NUMBER_OF_FLOORS; i++)
    {
        m_queue_up[i] = 0;
        m_queue_down[i] = 0;
        m_queue_inside[i] = 0;

        hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
        hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
        hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
    }
}


void queue_clear_floor(int floor) 
{
    m_queue_up[floor] = 0;
    m_queue_down[floor] = 0;
    m_queue_inside[floor] = 0;

    hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
}


void queue_add_floor(int floor, OrderType order_type) 
{
    switch (order_type)
    {
        case ORDER_UP:
            m_queue_up[floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
            break;
        
        case ORDER_DOWN:
            m_queue_down[floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
            break;
        
        case ORDER_INSIDE:
            m_queue_inside[floor] = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
            break;
    }
}


int queue_next_in_queue(int current_floor, Direction direction) 
{
    if (direction == UP) 
    {
        for(int i = current_floor + 1; i < NUMBER_OF_FLOORS; i++ ) 
        {
            if (m_queue_up[i] == 1 || m_queue_inside[i] == 1) 
            {
                return i;
            }
        }

        if (m_queue_down[NUMBER_OF_FLOORS -1] == 1) 
        {       
            return NUMBER_OF_FLOORS-1;                       //cheking if there are orders downwards in the highest floor.
        }
    }

    else if (direction == DOWN) 
    {
        for(int i = current_floor - 1; i >= 0; i-- ) 
        {
            if (m_queue_down[i] == 1 || m_queue_inside[i] == 1) 
            {
                return i;
            }
        }

        if (m_queue_up[0] == 1) 
        {
            return 0;                                         //cheking if there are orders upwards in the lowest floor.
        }
    }    
    return -1;
}


void queue_print_queue() {
    
    for(int i = 0; i < NUMBER_OF_FLOORS; i++) {
        printf("m_queue_up floor %d = %d\n", i+1, m_queue_up[i]);
    }
    for(int i = 0; i < NUMBER_OF_FLOORS; i++) {
        printf("m_queue_down floor %d = %d\n", i+1, m_queue_down[i]);
    }
    for(int i = 0; i < NUMBER_OF_FLOORS; i++) {
        printf("m_queue_inside floor %d = %d\n", i+1, m_queue_inside[i]);
    }
}