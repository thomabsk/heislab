#include "timer.h"

static time_t m_timer_start = 0;
static int m_timer_length = 0;


void timer_set(int wait_time)
{
    if(m_timer_start == 0){
        m_timer_length = wait_time;
        time_t current_time = time(NULL);
        m_timer_start = current_time;
    }
}

int timer_get()
{
    time_t current_time = time(NULL);
    return((current_time - m_timer_start) > m_timer_length);
}

void timer_reset()
{
    m_timer_start = 0;
    m_timer_length = 0;
}
