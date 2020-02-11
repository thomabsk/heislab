#include <stdio.h>
#include <time.h>
#include "timer.h"


int getTime(){
    time_t currentTime;
    currentTime = time(NULL);
    return currentTime;
}