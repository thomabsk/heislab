#include "queue.h"


static int m_queue_up[HARDWARE_NUMBER_OF_FLOORS];
static int m_queue_down[HARDWARE_NUMBER_OF_FLOORS];
static int m_queue_inside[HARDWARE_NUMBER_OF_FLOORS];


void queue_update(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
            m_queue_inside[f] = 1;
            hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
         }
        if(hardware_read_order(f, HARDWARE_ORDER_UP)){
            m_queue_up[f] = 1;
            hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            }
        if(hardware_read_order(f,HARDWARE_ORDER_DOWN)){
            m_queue_down[f] = 1;
            hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
        }
    }
}

void queue_clear_queue() 
{
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
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

int queue_next_in_queue(int current_floor, Direction direction) 
{
    if (direction == UP) 
    {
        for(int i = current_floor + 1; i < HARDWARE_NUMBER_OF_FLOORS; i++ ) 
        {
            if (m_queue_up[i] == 1 || m_queue_inside[i] == 1) 
            {
                return i;
            }
        }

        for(int i = HARDWARE_NUMBER_OF_FLOORS-1; i >= current_floor; i-- ) 
        {
            if (m_queue_down[i] == 1) 
            {
                return i;
            }
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

        for(int i = 0; i < current_floor; i++ ) 
        {
            if (m_queue_up[i] == 1) 
            {
                return i;
            }
        }

    }   
    else if (direction == NONE){
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if (m_queue_down[i] == 1 || m_queue_inside[i] == 1 || m_queue_up[i] == 1){
                return i;
            }
        }
    }
    return -1;
}