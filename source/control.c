#include "control.h"



static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}


static void control_calculate_next_floor(int *p_next_floor, Direction *p_travel_direction){

    *p_next_floor = queue_next_in_queue(elevator_get_current_floor(), *p_travel_direction, elevator_get_above());
    if(*p_next_floor == -1){
        *p_travel_direction = NONE;
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
    else if((*p_next_floor == elevator_get_current_floor()) && !elevator_currently_at_a_floor()){
        if(elevator_get_above()){
            *p_travel_direction = DOWN;
        }
        else{
            *p_travel_direction = UP;
        }
    }
}

int main()
{
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    printf("=== FUNCTIONING ELEVATOR ===\n");
    printf("Use the elevator as normal\n");
    control_state_machine();
    return 0;
}


void control_state_machine()
{
    State ELEVATOR_STATE = INITIALIZE;
    int next_floor = 0;
    Direction travel_direction = NONE;

    while(1){
        switch(ELEVATOR_STATE)
        {
            case INITIALIZE:
                queue_clear_queue();
                elevator_calibrate();
                ELEVATOR_STATE = IDLE;
                printf("Current state: IDLE\n");
                break;

            case STOP:
                queue_clear_queue();
                elevator_emergency_stop();
                travel_direction = NONE;
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
               
                queue_update();
                control_calculate_next_floor(&next_floor, &travel_direction);
                printf("Current direction: %d\n", travel_direction);
                if(!(next_floor == -1))
                {
                    printf("Current state: TAKING_ORDER\n");
                    ELEVATOR_STATE = TAKING_ORDER;
                    break;
                }
                //queue_clear_floor(elevator_get_current_floor());
                break;

            case TAKING_ORDER:
                if(elevator_check_emergency_stop())
                {
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }

                queue_update();
                control_calculate_next_floor(&next_floor, &travel_direction);
                printf("Current direction: %d\n", travel_direction);
                if(!(elevator_change_floor(next_floor)))
                {
                    printf("Current state: WAITING\n");
                    ELEVATOR_STATE = WAITING;
                    break;
                }
                break;

            case WAITING:
                if(elevator_check_emergency_stop())
                {
                    printf("Current state: STOP\n");
                    ELEVATOR_STATE = STOP;
                    break;
                }

                queue_update();
                queue_clear_floor(elevator_get_current_floor());
                if(elevator_wait(3))
                {
                    printf("Current state: IDLE\n");
                    ELEVATOR_STATE = IDLE;
                    break;
                }
                break;
        }
    }
}