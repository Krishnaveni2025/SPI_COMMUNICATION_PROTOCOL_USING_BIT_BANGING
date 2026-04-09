/*
*
* Bit Banging for SPI Slave on STM32F407
* This code implements a simple SPI slave using bit banging on an STM32F407 microcontroller.
* The SPI communication is handled manually by toggling GPIO pins to simulate the SPI protocol.
*1. GPIO Configuration: set MOSI, SCKand NSS pins as inputs, and MISO pin as an output.
*   - SCK (Serial Clock): Configured as an input to receive the clock signal from the master.
*   - MOSI (Master Out Slave In): Configured as an input to receive data from the master.
*   - MISO (Master In Slave Out): Configured as an output to send data back to the master.
*   - NSS (Slave Select): Configured as an input to detect when the master selects the slave for communication.
2. SPI Communication: The slave waits for the NSS pin to go low, indicating that the master has selected it. It then listens for the SCK signal to synchronize data reception and transmission.
   - On each rising edge of the SCK signal, the slave reads a bit from the MOSI pin and shifts it into a buffer.
   - After receiving a complete byte, the slave can process the data and prepare a response to send back to the master on the MISO pin.
3. Data Handling: The received data can be processed as needed,
and the slave can send responses back to the master by toggling the MISO pin according to the SPI protocol.
4. Timing Considerations: Since this is a bit-banging implementation, critical for meeting setup/hold times
*/

#include "init_io.h"
#include "spi_slave.h"

int main(void)
{
    init_LED_and_Switch();
    SPI_Slave_Init();

    while (1)
    {
        uint8_t cmd = SPI_Slave_ListenCommand();

        if (cmd == 0xA1)
        {
            *GPIOD_ODR |= (1 << LED_PIN); // LED ON
        }
        else if (cmd == 0xA0)
        {
            *GPIOD_ODR &= ~(1 << LED_PIN); // LED OFF
        }

        // Send state of STM32 switch to PSoC
        uint8_t stm32_pressed = (*GPIOA_IDR & (1 << BUTTON_PIN)) != 0;
        uint8_t resp = stm32_pressed ? 0xB1 : 0xB0;
        SPI_Slave_SendResponse(resp);
    }
}
