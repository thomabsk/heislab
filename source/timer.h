/**
 * @file
 * @brief Timer library.
 *
 */
#include <time.h>

static int timer_length;
static time_t timer_start;


/**
 * @brief Starts the timer
 * 
 * @param wait_time The amount to count down
*/
void timer_set(int wait_time);

/**
 * @brief Polls the timer to see if it is finished
 * 
 * @return return 1 when timer is finished, 0 when still counting.
*/
int timer_get();


/**
 * @brief Resets the timer
*/
void timer_reset();