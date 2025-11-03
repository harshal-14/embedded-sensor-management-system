void set_bit(unint8_t *byte, unint8_t bit_position){
    *byte |= (1 << bit_position); // set the bit at the position to 1 by ORing with 1
}

void clear_bit(unint8_t *byte, unint8_t bit_position){
    *byte & = ~(1 << bit_position); // clear the bit at the position to 0 by ANDing with 0
}

void toggle_bit(unint8_t *byte, unint8_t bit_position){
    *byte ^= (1 << bit_position); // toggle the bit at the position by XORing with 1
}

void get_bit(unint8_t *byte, unint8_t bit_position){
    return (*byte & (1 << bit_position)) ? 1 : 0; // get the bit at the position
}
