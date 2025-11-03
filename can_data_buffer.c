#include <stdio.h>

typedef struct{
    uint32_t id;
    uint8_t data[8];
    uint8_t length;

}candata;

// voltage is stored in the first two bytes of the data array
uint8_t parse_battery_voltage(candata *data){
    uint16_t voltage = data[0] | (data[1] << 8); // this line is reading the first two bytes of the data array and storing them in the voltage variable
    // pointer style
    /* uint16_t voltage = *((unint16_t *) data); */ 
    // uint16_t * means the data is a pointer to a 16 bit unsigned integer
    // * means dereference the pointer
    // (unint16_t *) means cast the pointer to a 16 bit unsigned integer pointer
    // data is the pointer to the data array
    // data[0] is the first byte of the data array
    // data[1] is the second byte of the data array
    // data[0] | (data[1] << 8) is the voltage
    // data[0] is the first byte of the data array
    // data[1] is the second byte of the data array
    return voltage;
}

//  batter current is stored in the third and fourth bytes of the data array
uint8_t parse_battery_current(uint8_t *data, int16_t current){
    data[2] = current & 0xFF; // meaning current & 0xFF is the current low byte
    data[3] = (current >>8) & 0xFF; // meaning (current >>8) & 0xFF is the current high byte
}


void process_battery_message(void){
    candata battery_msg;
    battery_msg.id = 0x123;
    battery_msg.length = 8;

    battery_msg.data[0] = 0xDC; // 0XDC = 220 low byte in hex
    battery_msg.data[1] = 0x0D; // 0x0DDC = 3556 high byte in hex

    uint16_t voltage = parse_battery_voltage(battery_msg.data);
    printf("Battery voltage: %d\n", voltage);

    uint16_t current = 100;
    parse_battery_current(battery_msg.data, current);
    printf("Battery current: %d\n", current);
}