/**
 * @file
 * @brief Timer library.
 *
 */
#include <time.h>
#include <stdio.h>

/**
 * @brief Starts the timer if it is not active.
 * 
 * @param wait_time The amount to count down.
 * 
 * @warning Always reset the timer before setting it!
*/
void timer_set(int wait_time);

/**
 * @brief Polls the timer to see if it is finished
 * 
 * @return Return 1 when timer is finished, 0 when still counting.
*/
int timer_get();


/**
 * @brief Resets the timer
*/
void timer_reset();
