TARGET = spi_slave

# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Flags
CFLAGS = -mcpu=cortex-m4 -mthumb -g -Wall -O0
LDFLAGS = -mcpu=cortex-m4 -mthumb -T stm32f407.ld -Wl,-Map=$(TARGET).map -nostartfiles

# Files
SRCS = main.c startup_stm32f407.c init_io.c spi_slave.c
OBJS = $(SRCS:.c=.o)
HEX = $(TARGET).hex

# Rules
all: $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex $(TARGET).map

# OPEN OCD
# Convert backslashes to forward slashes to prevent shell escaping issues
OPENOCD_DIR := $(subst \,/,$(IFX_BARE_METAL_COURSE))/openocd
OCD = $(OPENOCD_DIR)

# OpenOCD command to program STM32F407
program: $(HEX)
	"$(OCD)/bin/openocd.exe" -f board/stm32f4discovery.cfg -c "program $(HEX) verify reset exit"
