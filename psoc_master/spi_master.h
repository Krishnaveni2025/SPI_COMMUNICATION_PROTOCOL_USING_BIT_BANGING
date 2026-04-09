#ifndef SPI_MASTER_H
#define SPI_MASTER_H

#include <stdint.h>

#define MOSI 0
#define MISO 1
#define SCK 2
#define NSS 3

#define GPIO_PORT5_PC ((volatile uint32_t *)0x40040508)
#define GPIO_PORT5_DR ((volatile uint32_t *)0x40040500)
#define GPIO_PORT5_PS ((volatile uint32_t *)0x40040504)

void SPI_Master_Init(void);
void SPI_Master_SendCommand(uint8_t cmd);
uint8_t SPI_Master_ReadResponse(void);

#endif
