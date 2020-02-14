#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "control.h"
#include "timer.h"
#include "elevator.h"
#include "queue.h"
#include "utilities.h"



static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    clear_all_order_lights();
    state_machine();

    /*
    clear_all_order_lights();
    elevator_calibrate();
    while(1){
        if(hardware_read_stop_signal()){
            elevator_emergency_stop();
        }
        else if(!elevator_change_floor(2)){
            break;
        }
    }
    elevator_wait(5);
    while(1){
        control_poll_buttons();
    }
    */
    return 0;
}
