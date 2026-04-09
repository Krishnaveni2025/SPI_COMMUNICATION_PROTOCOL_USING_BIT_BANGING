#ifndef INIT_IO_
#define INIT_IO_

#include <stdint.h>

#define LED_PIN 0    // LED connected to P1.0
#define SWITCH_PIN 7 // Switch connected to 3.7
#define LOW 0
#define PRESSED LOW
// Register Definitions for Port 3 for Button control
#define GPIO_PORT3_PC ((volatile uint32_t *)0x40040308) // Port 3 configuration register
#define GPIO_PORT3_DR ((volatile uint32_t *)0x40040300) // Port 3 output data register
#define GPIO_PORT3_PS ((volatile uint32_t *)0x40040304) // Port 3 pin status register
// Register Definitions for Port 2 for LED control
#define GPIO_PORT2_PC ((volatile uint32_t *)0x40040208) // Port 2 configuration register
#define GPIO_PORT2_DR ((volatile uint32_t *)0x40040200) // Port 2 output data register

void init_LED_and_Switch(void);
#endif