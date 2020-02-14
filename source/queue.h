/**
 * @file
 * @brief Library that adds a queue for use with the elevator
 *
 */

/**
 * @brief Clears the whole queue 
*/
void queue_clear_queue();

/**
 * @brief Clears the desired floor of all orders
 * 
 * @param floor The floor you will  
*/
void queue_clear_floor(int floor);

int queue_add_floor(int floor,  order_type type);

int queue_next_in_queue(int current_floor, direction direction);

int queue_is_floor_ordered(int floor);