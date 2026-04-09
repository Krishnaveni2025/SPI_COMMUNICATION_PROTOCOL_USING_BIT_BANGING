#include "spi_master.h"

void SPI_Master_Init(void)
{
    *GPIO_PORT5_PC &= ~((0x07 << (MOSI * 3)) | (0x07 << (SCK * 3)) | (0x07 << (NSS * 3)) | (0x07 << (MISO * 3)));
    *GPIO_PORT5_PC |= ((0x06 << (MOSI * 3)) | (0x06 << (SCK * 3)) | (0x06 << (NSS * 3))); // outputs
    *GPIO_PORT5_PC |= (0x02 << (MISO * 3));                                               // input pull-up

    *GPIO_PORT5_DR |= (1 << NSS); // NSS high
    *GPIO_PORT5_DR &= ~((1 << SCK) | (1 << MOSI));
}

void SPI_Master_SendCommand(uint8_t cmd)
{
    *GPIO_PORT5_DR &= ~(1 << NSS);
    for (int i = 7; i >= 0; i--)
    {
        if (cmd & (1 << i))
            *GPIO_PORT5_DR |= (1 << MOSI);
        else
            *GPIO_PORT5_DR &= ~(1 << MOSI);

        for (volatile int d = 0; d < 100; d++)
            ;
        *GPIO_PORT5_DR |= (1 << SCK);
        for (volatile int d = 0; d < 100; d++)
            ;
        *GPIO_PORT5_DR &= ~(1 << SCK);
    }
    *GPIO_PORT5_DR |= (1 << NSS);
}

uint8_t SPI_Master_ReadResponse(void)
{
    uint8_t rx = 0;
    *GPIO_PORT5_DR &= ~(1 << NSS);
    
    // Give slave time to enter loop and output first bit
    for (volatile int d = 0; d < 100; d++)
        ;

    for (int i = 7; i >= 0; i--)
    {
        *GPIO_PORT5_DR |= (1 << SCK);
        for (volatile int d = 0; d < 200; d++)
            ;
        if (*GPIO_PORT5_PS & (1 << MISO))
            rx |= (1 << i);
        *GPIO_PORT5_DR &= ~(1 << SCK);
        
        // Add delay while SCK is low so slave can detect falling edge and prepare next bit
        for (volatile int d = 0; d < 200; d++)
            ;
    }
    *GPIO_PORT5_DR |= (1 << NSS);
    return rx;
}
