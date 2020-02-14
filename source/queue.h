void queue_clear_queue();

void queue_clear_floor(int floor);

int queue_add_floor(int floor,  order_type type);

int queue_next_in_queue(int current_floor, direction direction);

int queue_is_floor_ordered(int floor);