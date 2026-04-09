#ifndef INIT_IO_H
#define INIT_IO_H

#include <stdint.h>

#define LED_PIN 12
#define BUTTON_PIN 0

// LED (Port D)
#define RCC_AHB1ENR ((volatile uint32_t *)0x40023830)
#define GPIOD_MODER ((volatile uint32_t *)0x40020C00)
#define GPIOD_ODR ((volatile uint32_t *)0x40020C14)

// Button (Port A)
#define GPIOA_MODER ((volatile uint32_t *)0x40020000)
#define GPIOA_IDR ((volatile uint32_t *)0x40020010)
#define GPIOA_PUPDR ((volatile uint32_t *)0x4002000C)

void init_LED_and_Switch(void);

#endif
