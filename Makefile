# Simple Makefile for LPC11C24
TARGET = tbsar
BUILD_DIR = build
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

MCU = cortex-m0
CFLAGS = -mcpu=$(MCU) -mthumb -mfloat-abi=soft -O2 -g3 -Wall -std=c99
LDFLAGS = -mcpu=$(MCU) -mthumb -mfloat-abi=soft -Wl,--gc-sections -specs=nano.specs -Tlpc11c24.ld

INC_DIRS = -I./App \
		   -I./Mcu/Sys -I./Mcu/Adc -I./Mcu/Can -I./Mcu/Dio -I./Mcu/Gpt -I./Mcu/I2c -I./Mcu/Sleep -I./Mcu/Spi -I./Mcu/Uart -I./Mcu/Wakeup \
		   -I./Ecu/Buz -I./Ecu/Dac -I./Ecu/Eeprom -I./Ecu/Monitor -I./Ecu/Rgb -I./Ecu/Rotary -I./Ecu/Sensors -I./Ecu/Ukeys -I./Ecu/Lcd

SOURCES = App/main.c App/Scheduler.c \
		  Ecu/Buz/Buz.c Ecu/Buz/Buz_Config.c \
		  Ecu/Rgb/Rgb.c Ecu/Rgb/Rgb_Config.c \
		  Mcu/Adc/Adc.c Mcu/Adc/Adc_Config.c \
		  Mcu/Can/Can.c Mcu/Can/Can_Config.c \
		  Mcu/I2c/I2c.c Mcu/I2c/I2c_Config.c \
		  Mcu/Spi/Spi.c Mcu/Spi/Spi_Config.c \
		  Mcu/Dio/Dio.c Mcu/Dio/Dio_Config.c \
		  Mcu/Gpt/Gpt.c Mcu/Gpt/Gpt_Config.c \
		  Mcu/Sleep/Sleep.c Mcu/Sleep/Sleep_Config.c \
		  Mcu/Wakeup/Wakeup.c Mcu/Wakeup/Wakeup_Config.c \
		  Mcu/Uart/Uart.c Mcu/Uart/Uart_Config.c \
		  Mcu/Sys/cr_startup_lpc11xx.c Mcu/Sys/system_LPC11xx.c Mcu/Sys/Syscon.c Mcu/Sys/Iocon.c Mcu/Sys/syscalls.c \
		  Ecu/Monitor/Monitor.c Ecu/Monitor/Monitor_Config.c \
		  Ecu/Dac/Dac.c Ecu/Dac/Dac_Config.c \
		  Ecu/Eeprom/Eeprom.c Ecu/Eeprom/Eeprom_Config.c \
		  Ecu/Rotary/Rotary.c Ecu/Rotary/Rotary_Config.c \
		  Ecu/Sensors/Sensors.c Ecu/Sensors/Sensors_Config.c \
		  Ecu/Ukeys/Ukeys.c Ecu/Ukeys/Ukeys_Config.c \
		  Ecu/Lcd/Lcd.c Ecu/Lcd/Lcd_Config.c
OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin size

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	@echo "🔗 Linking..."
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@echo "📦 Creating FlashMagic-compatible HEX file..."
	$(OBJCOPY) -O ihex --set-start 0x00000000 $< $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@echo "📦 Creating binary file..."
	$(OBJCOPY) -O binary $< $@

size: $(BUILD_DIR)/$(TARGET).elf
	@echo "📊 Memory usage:"
	$(SIZE) $<

$(BUILD_DIR)/%.o: %.c
	@echo "🔨 Compiling $<..."
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

flash: $(BUILD_DIR)/$(TARGET).hex
	@echo "🚀 Flashing via ISP..."
	@sudo lpc21isp -control -hex $(BUILD_DIR)/$(TARGET).hex /dev/ttyUSB1 115200 12000
	@echo "🚪 Releasing control lines and exiting ISP..."
	@sleep 1
	@python3 isp.py || true
	@echo "✅ Flash complete - device should be running"

output:
	@echo "📡 Starting UART Monitor..."
	@echo ""
	@python3 monitor.py

run: flash
	@echo "🔄 Flash complete, starting monitor in 2 seconds..."
	@sleep 2
	@$(MAKE) --no-print-directory output

clean:
	@echo "🧹 Cleaning build directory..."
	rm -rf $(BUILD_DIR)

help:
	@echo "📋 Available targets:"
	@echo "  all     - Build project (creates .hex and .bin files)"
	@echo "  flash   - Flash via ISP (Linux lpc21isp)"
	@echo "  output  - Monitor UART output (printf debugging)"
	@echo "  clean   - Clean build directory"
	@echo "  size    - Show memory usage"
	@echo "  help    - Show this help"
	@echo ""
	@echo "� Quick workflow:"
	@echo "  make flash   # Program the MCU"
	@echo "  make output  # Monitor printf output"
	@echo ""
	@echo "�📁 Build structure:"
	@echo "  $(BUILD_DIR)/           - All build artifacts"
	@echo "  $(BUILD_DIR)/$(TARGET).hex - Intel HEX format (FlashMagic compatible)"
	@echo "  $(BUILD_DIR)/$(TARGET).bin - Raw binary format"
	@echo "  $(BUILD_DIR)/$(TARGET).elf - ELF debug format"
	@echo "  $(BUILD_DIR)/**/*.o     - Object files organized by source structure"

.PHONY: all clean flash output run size help
