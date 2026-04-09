#include "init_io.h"
void init_LED_and_Switch(void)
{
    // PC: Set P2.0 to Strong Drive mode (6)
    *GPIO_PORT2_PC &= ~(0x07 << (LED_PIN * 3));
    *GPIO_PORT2_PC |= (0x06 << (LED_PIN * 3));
    *GPIO_PORT2_DR |= (1 << LED_PIN); // Turn off LED initially
    // PC: Set P3.7 to resistive pull up mode (2)
    *GPIO_PORT3_PC &= ~(0x07 << (SWITCH_PIN * 3));
    *GPIO_PORT3_PC |= (0x02 << (SWITCH_PIN * 3));
    *GPIO_PORT3_DR |= (1 << SWITCH_PIN); // Set P3.7 high
}
