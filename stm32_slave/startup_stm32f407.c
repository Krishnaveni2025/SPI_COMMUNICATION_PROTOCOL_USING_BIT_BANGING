#include <stdint.h>

extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack; // Top of stack usually defined in linker or below

#define SRAM_START  0x20000000
#define SRAM_SIZE   (128 * 1024)
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

int main(void);

void Reset_Handler(void) {
    // Copy .data section to SRAM
    uint32_t *pSrc = &_sidata;
    uint32_t *pDest = &_sdata;
    while (pDest < &_edata) {
        *pDest++ = *pSrc++;
    }

    // Initialize the .bss section to zero
    pDest = &_sbss;
    while (pDest < &_ebss) {
        *pDest++ = 0;
    }

    // Call main
    main();

    while (1);
}

void Default_Handler(void) {
    while (1);
}

// Vector Table
__attribute__((section(".isr_vector")))
uint32_t vectors[] = {
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)Default_Handler, // NMI
    (uint32_t)Default_Handler, // HardFault
    (uint32_t)Default_Handler, // MemManage
    (uint32_t)Default_Handler, // BusFault
    (uint32_t)Default_Handler, // UsageFault
    0, 0, 0, 0,                // Reserved
    (uint32_t)Default_Handler, // SVCall
    (uint32_t)Default_Handler, // Debug Monitor
    0,                         // Reserved
    (uint32_t)Default_Handler, // PendSV
    (uint32_t)Default_Handler, // SysTick
};
