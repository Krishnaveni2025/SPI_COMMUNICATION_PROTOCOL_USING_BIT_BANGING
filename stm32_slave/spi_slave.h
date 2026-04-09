#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include <stdint.h>

#define MOSI 7
#define MISO 6
#define SCK 5
#define NSS 4

#define GPIOA_MODER ((volatile uint32_t *)0x40020000)
#define GPIOA_IDR ((volatile uint32_t *)0x40020010)
#define GPIOA_ODR ((volatile uint32_t *)0x40020014)

#define RCC_AHB1ENR ((volatile uint32_t *)0x40023830)

void SPI_Slave_Init(void);
uint8_t SPI_Slave_ListenCommand(void);
void SPI_Slave_SendResponse(uint8_t resp);

#endif
