#include "init_io.h"

void init_LED_and_Switch(void)
{
    *RCC_AHB1ENR |= (1 << 0) | (1 << 3); // enable GPIOA + GPIOD

    // LED PD12 output
    *GPIOD_MODER &= ~(3 << (LED_PIN * 2));
    *GPIOD_MODER |= (1 << (LED_PIN * 2));
    *GPIOD_ODR &= ~(1 << LED_PIN);

    // Button PA0 input
    *GPIOA_MODER &= ~(3 << (BUTTON_PIN * 2));
}
