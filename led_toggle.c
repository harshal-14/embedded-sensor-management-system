// #define PORTB (*(volatile uint8_t *)0x0025) 
// 0x0025 is the address of the PORTB register`
// volatile means the variable can be changed by the hardware
// volatile uint8_t * means the variable is a pointer to a 8 bit unsigned integer
// * means dereference the pointer
// so the whole line means defrencing the pointer to of volatile uint8_t and storing it in the PORTB variable
typedef struct{
    volatile uint8_t PINB;
    volatile uint8_t DDRB;
    volatile uint8_t PORTB;
}gpio_reg_t;

#define GPIO_REG ((gpio_reg_t *)0x0025)

#define LED_PIN 5;

void led_init(void){
    // step1: set led pin as o/p in data direction register
    DDRB | =(1<<LED_PIN); // this line is setting the bit at the position to 1 by ORing with 1

    //step 2: initialize the led pin to OFF state 
    PORTB &= ~(1<<LED_PIN); // this line is clearing the bit at the position to 0 by ANDing with 0
}

// function 2 turn on the led
void led_on(void){
    //set bit 5 of portb to 1
    PORTB |= (1<<LED_PIN);

}

// function 3 turn off the led
void led_off(void){
    //set bit 5 of portb to 0
    PORTB &= ~(1<<LED_PIN);
}

// function 4 toggle the led
void led_toggle(void){
    //toggle bit 5 of portb
    PORTB ^= (1<<LED_PIN);
}

unint8_t led_get_state(void){
    return (PORTB & (1<<LED_PIN)) ? 1:0;
}

