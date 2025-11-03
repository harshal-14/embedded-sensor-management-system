// CAN transceiver control

// Hardware registers for CAN controller
#define CAN_CTRL_REG    (*(volatile uint8_t *)0x4000)
#define CAN_STATUS_REG  (*(volatile uint8_t *)0x4001)

// Control register bits (from CAN transceiver datasheet)
#define CAN_ENABLE_BIT      0
#define CAN_LOOPBACK_BIT    1
#define CAN_SILENT_BIT      2
#define CAN_EXTENDED_ID_BIT 3  // You implemented this at GM!

// Initialize CAN transceiver
void can_init(void) {
    // Start with all bits cleared
    CAN_CTRL_REG = 0x00;
    
    // Enable CAN controller
    CAN_CTRL_REG |= (1 << CAN_ENABLE_BIT);
    
    // Enable extended CAN IDs (your GM work!)
    CAN_CTRL_REG |= (1 << CAN_EXTENDED_ID_BIT);
    
    // Leave loopback and silent mode disabled
    // (bits already 0 from initialization)
}

// Enter silent mode for bus monitoring
void can_enter_silent_mode(void) {
    CAN_CTRL_REG |= (1 << CAN_SILENT_BIT);
}

// Exit silent mode
void can_exit_silent_mode(void) {
    CAN_CTRL_REG &= ~(1 << CAN_SILENT_BIT);
}

// Check if CAN is ready
uint8_t is_can_ready(void) {
    // Read status register and check ready bit (assume bit 0)
    return (CAN_STATUS_REG & 0x01) ? 1 : 0;
}

// Power driver control (like oil pump drivers you worked on)
#define PWR_DRIVER_REG  (*(volatile uint8_t *)0x5000)

#define PUMP_ENABLE_BIT   0
#define PUMP_FAULT_BIT    7  // Read-only status bit

void oil_pump_enable(void) {
    PWR_DRIVER_REG |= (1 << PUMP_ENABLE_BIT);
}

void oil_pump_disable(void) {
    PWR_DRIVER_REG &= ~(1 << PUMP_ENABLE_BIT);
}

uint8_t is_pump_fault_detected(void) {
    // Check fault bit in status register
    return (PWR_DRIVER_REG & (1 << PUMP_FAULT_BIT)) ? 1 : 0;
}