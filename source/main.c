#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "control.h"
#include "timer.h"
#include "elevator.h"
#include "queue.h"
#include "utilities.h"





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

    printf("=== FUNCTIONING ELEVATOR ===\n");
    printf("Use the elevator as normal\n");
    control_state_machine();
    return 0;
}
