#include <stdio.h>
#include <time.h>
#include "timer.h"


int timer_get_time(){
    time_t currentTime;
    currentTime = time(NULL);
    return currentTime;
}

int timer_set_timer(long int wait_time){
    time_t start_time = timer_get_time();
    while((timer_get_time()-start_time) < wait_time){
        continue;
    }
    return 0;
}