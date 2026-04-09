/*
 *
 * *****************Bit Banging for SPI Master on CY8CKIT-149 PSOC 4100s Plus Prototyping kit******************************************
 * This code implements a simple SPI master using bit banging on an PSOC 4100s Plus microcontroller.
 * The SPI communication is handled manually by toggling GPIO pins to simulate the SPI protocol.
 * 1. GPIO Configuration: set MOSI, SCKand NSS pins as outputs, and MISO pin as an input.
 *   - SCK (Serial Clock): Configured as an output to send the clock signal to the slave.
 *   - MOSI (Master Out Slave In): Configured as an output to send data to the slave.
 *   - MISO (Master In Slave Out): Configured as an input to receive data from the slave.
 *   - NSS (Slave Select): Configured as an output to select the slave for communication.
 * 2. SPI Communication: The master makes the NSS pin to go low, indicating that the slave is selected.
 *    It then generates the SCK signal and transfers data on the MOSI pin while reading data from the MISO pin.
 *   - On each rising edge of the SCK signal, the master reads a bit from the MOSI pin and shifts it into a buffer.
 *   - After receiving a complete byte, the master can process the data and prepare a response to send back to the slave on the MISO pin.
 * 3. Data Handling: The received data can be processed as needed,
 *    and the slave can send responses back to the master by toggling the MISO pin according to the SPI protocol.
 * 4. Timing Considerations: Since this is a bit-banging implementation, critical for meeting setup/hold times
 */
#include "init_io.h"
#include "spi_master.h"

int main(void)
{
    init_LED_and_Switch();
    SPI_Master_Init();

    while (1)
    {
        if ((*GPIO_PORT3_PS & (1 << SWITCH_PIN)) == PRESSED)
        {
            SPI_Master_SendCommand(0xA1); // tell STM32 to turn LED ON
        }
        else
        {
            SPI_Master_SendCommand(0xA0); // tell STM32 to turn LED OFF
        }

        // Give STM32 a brief moment to process the command and enter SendResponse()
        for (volatile int d = 0; d < 1000; d++)
            ;

        uint8_t response = SPI_Master_ReadResponse();
        if (response == 0xB1)
        {
            *GPIO_PORT2_DR &= ~(1 << LED_PIN); // Turn ON (active LOW)
        }
        else if (response == 0xB0)
        {
            *GPIO_PORT2_DR |= (1 << LED_PIN); // Turn OFF (active LOW)
        }

        for (volatile int d = 0; d < 490000; d++)
            ; // small delay
    }
}
