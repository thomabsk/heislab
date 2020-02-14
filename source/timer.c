#include <stdio.h>
#include "timer.h"

time_t timer_start = 0;
int timer_length = 0;


void timer_set(int wait_time){
    timer_length = wait_time;
    time_t current_time = time(NULL);
    timer_start = current_time;
}

int timer_get(){
    time_t current_time = time(NULL);
    return((current_time - timer_start) > timer_length);
}

void timer_reset(){
    timer_start = 0;
    timer_length = 0;
}
