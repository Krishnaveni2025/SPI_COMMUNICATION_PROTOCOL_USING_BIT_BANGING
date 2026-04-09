#include "spi_slave.h"

void SPI_Slave_SendResponse(uint8_t resp)
{
    // Wait until NSS is HIGH first, to catch the start of a frame and avoid desync
    while ((*GPIOA_IDR & (1 << NSS)) == 0)
        ;

    // Wait until NSS goes low (slave selected)
    while ((*GPIOA_IDR & (1 << NSS)) != 0)
        ;

    // Send 8 bits back to master
    for (int i = 7; i >= 0; i--)
    {
        // Drive MISO according to current bit
        if (resp & (1 << i))
            *GPIOA_ODR |= (1 << MISO);
        else
            *GPIOA_ODR &= ~(1 << MISO);

        // Wait for rising edge of SCK
        while ((*GPIOA_IDR & (1 << SCK)) == 0)
            ;

        // Hold while clock is high
        while ((*GPIOA_IDR & (1 << SCK)) != 0)
            ;
    }

    // Clear MISO after transmission
    *GPIOA_ODR &= ~(1 << MISO);
}

void SPI_Slave_Init(void)
{
    *RCC_AHB1ENR |= (1 << 0); // enable GPIOA

    // MOSI, SCK, NSS inputs; MISO output
    *GPIOA_MODER &= ~((3 << (MOSI * 2)) | (3 << (SCK * 2)) | (3 << (NSS * 2)) | (3 << (MISO * 2)));
    *GPIOA_MODER |= (1 << (MISO * 2));
}

uint8_t SPI_Slave_ListenCommand(void)
{
    uint8_t cmd = 0;

    // Wait until NSS is HIGH first, to catch the start of a frame and avoid desync
    while ((*GPIOA_IDR & (1 << NSS)) == 0)
        ;

    // Wait until NSS goes low (slave selected)
    while ((*GPIOA_IDR & (1 << NSS)) != 0)
        ;

    // Receive 8 bits from master
    for (int i = 7; i >= 0; i--)
    {
        // Wait for rising edge of SCK
        while ((*GPIOA_IDR & (1 << SCK)) == 0)
            ;

        // Sample MOSI while clock is high
        if (*GPIOA_IDR & (1 << MOSI))
            cmd |= (1 << i);

        // Wait for falling edge of SCK
        while ((*GPIOA_IDR & (1 << SCK)) != 0)
            ;
    }

    // Return the received byte
    return cmd;
}
