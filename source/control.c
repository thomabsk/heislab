#include "control.h"


static void control_calculate_next_floor(int *p_next_floor, Direction *p_travel_direction){

    *p_next_floor = queue_next_in_queue(elevator_get_current_floor(), *p_travel_direction);
    if(*p_next_floor == -1){
        *p_travel_direction = STILL;
        return;
    }
    else if(*p_next_floor < elevator_get_current_floor())
    {
        *p_travel_direction = DOWN;
    }
    else if(*p_next_floor > elevator_get_current_floor())
    {
        *p_travel_direction = UP;
    }
}

void control_state_machine()
{
    state ELEVATOR_STATE = INITIALIZE;
    int next_floor = 0;
    Direction travel_direction = UP;

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
                if(elevator_currently_at_a_floor())
                {
                    printf("Current state: WAITING\n");
                    ELEVATOR_STATE = WAITING;
                    break;
                }
                printf("Current state: IDLE\n");
                ELEVATOR_STATE = IDLE;
                break;
                
            case IDLE:
                
                if(elevator_check_emergency_stop())
                {
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }
                queue_poll_buttons();
                control_calculate_next_floor(&next_floor, &travel_direction);
                if(!(next_floor == -1))
                {
                    printf("Current state: TAKING_ORDER\n");
                    ELEVATOR_STATE = TAKING_ORDER;
                }
                break;

            case TAKING_ORDER:
                
                if(elevator_check_emergency_stop())
                {
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }

                queue_poll_buttons();
                control_calculate_next_floor(&next_floor, &travel_direction);
                if(!(elevator_change_floor(next_floor)))
                {
                    printf("Current state: WAITING\n");
                    ELEVATOR_STATE = WAITING;
                }
                //control_calculate_next_floor(&next_floor, &travel_direction); // Calculate again if between two floors, and stopping.
                break;

            case WAITING:
                
                if(elevator_check_emergency_stop())
                {
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }
                queue_poll_buttons();
                
                queue_clear_floor(elevator_get_current_floor());
                if(elevator_wait(3))
                {
                    printf("Current state: IDLE\n");
                    ELEVATOR_STATE = IDLE;
                }
                break;
        }
    }
}