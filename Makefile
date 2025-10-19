# Makefile for TBSAR project - NXP LPC11C24 with ARM GCC

# Project name
PROJECT = tbsar

# Target MCU
MCU = cortex-m0

# Toolchain
TOOLCHAIN = arm-none-eabi-
CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump
SIZE = $(TOOLCHAIN)size
GDB = $(TOOLCHAIN)gdb

# Directories
BUILD_DIR = Build
APP_DIR = App
MCU_DIR = Mcu
ECU_DIR = Ecu

# Source files
# App sources
APP_SRCS = $(wildcard $(APP_DIR)/*.c)

# MCU sources
MCU_SRCS = $(wildcard $(MCU_DIR)/*/*.c)

# ECU sources  
ECU_SRCS = $(wildcard $(ECU_DIR)/*/*.c)

# All C sources
SRCS = $(APP_SRCS) $(MCU_SRCS) $(ECU_SRCS)

# Startup source (separate from regular sources)
STARTUP_SRC = $(MCU_DIR)/Sys/cr_startup_lpc11xx.c

# Filter out startup from regular sources
SRCS_FILTERED = $(filter-out $(STARTUP_SRC), $(SRCS))

# Object files
OBJS = $(SRCS_FILTERED:%.c=$(BUILD_DIR)/%.o)
STARTUP_OBJ = $(STARTUP_SRC:%.c=$(BUILD_DIR)/%.o)

# Include directories
INCLUDES = -I$(MCU_DIR)/Sys \
           -I$(MCU_DIR)/Adc \
           -I$(MCU_DIR)/Can \
           -I$(MCU_DIR)/Dio \
           -I$(MCU_DIR)/Gpt \
           -I$(MCU_DIR)/I2c \
           -I$(MCU_DIR)/Spi \
           -I$(MCU_DIR)/Uart \
           -I$(ECU_DIR)/Buz \
           -I$(ECU_DIR)/Dac \
           -I$(ECU_DIR)/Eeprom \
           -I$(ECU_DIR)/Pc_Com \
           -I$(ECU_DIR)/Pwm \
           -I$(ECU_DIR)/Rgb \
           -I$(ECU_DIR)/Rotary \
           -I$(ECU_DIR)/Sensors \
           -I$(ECU_DIR)/Ukeys

# Defines
DEFINES = -DLPC11C24 \
          -DARM_MATH_CM0 \
          -D__CORTEX_M0

# Compiler flags
CFLAGS = -mcpu=$(MCU) \
         -mthumb \
         -mfloat-abi=soft \
         -Wall \
         -Wextra \
         -Wno-unused-parameter \
         -Wno-unused-function \
         -std=c99 \
         -ffunction-sections \
         -fdata-sections \
         -fno-common \
         -fmessage-length=0 \
         $(INCLUDES) \
         $(DEFINES)

# Debug/Release flags
ifdef DEBUG
    CFLAGS += -g3 -O0 -DDEBUG
    BUILD_TYPE = debug
else
    CFLAGS += -Os -DNDEBUG
    BUILD_TYPE = release
endif

# Linker flags
LDFLAGS = -mcpu=$(MCU) \
          -mthumb \
          -mfloat-abi=soft \
          -specs=nano.specs \
          -specs=nosys.specs \
          -T lpc11c24.ld \
          -Wl,--gc-sections \
          -Wl,--print-memory-usage \
          -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map

# Output files
ELF = $(BUILD_DIR)/$(PROJECT).elf
HEX = $(BUILD_DIR)/$(PROJECT).hex
BIN = $(BUILD_DIR)/$(PROJECT).bin
LST = $(BUILD_DIR)/$(PROJECT).lst

# Default target
all: build-start $(BUILD_DIR) $(HEX) $(BIN) size copy-to-release build-complete

# Flash Magic compatible build with ultra-compatible HEX
flashmagic: build-start $(BUILD_DIR) $(BUILD_DIR)/$(PROJECT)_flashmagic.hex size copy-flashmagic-to-release
	@echo "🎯 Flash Magic HEX file ready for Windows!"
	@echo "📁 File: $(BUILD_DIR)/$(PROJECT)_flashmagic.hex"
	@echo "💡 This version has maximum Flash Magic compatibility"

# Copy flashmagic artifact to Release
copy-flashmagic-to-release: $(BUILD_DIR)/$(PROJECT)_flashmagic.hex
	@mkdir -p Release
	@cp $(BUILD_DIR)/$(PROJECT)_flashmagic.hex Release/
	@echo "✅ Flash Magic HEX copied to Release directory"

# Create Flash Magic Compatible HEX (for Flash Magic tool)
$(BUILD_DIR)/$(PROJECT)_flashmagic.hex: $(ELF)
	@echo "===================================================================================="
	@echo "📄 CREATING FLASH MAGIC HEX: Maximum compatibility"
	@echo "📁 Input: $<"
	@echo "📁 Output: $@"
	@echo "🎯 Format: Flash Magic compatible Intel HEX"
	@echo "===================================================================================="
	$(OBJCOPY) -O ihex --only-section=.text --set-start=0x00000000 --change-addresses=0x00000000 $< $@
	@echo "✅ Flash Magic HEX created: $(notdir $@)"
	@ls -lh $@ | awk '{print "📏 Size: " $$5}'
	@echo "💡 Settings for Flash Magic:"
	@echo "   - Device: LPC11C24/301"
	@echo "   - Crystal: 12.000 MHz"  
	@echo "   - Interface: None (ISP)"
	@echo "   - Oscillator: 12000 kHz"
	@echo ""

# Build start banner
build-start:
	@echo ""
	@echo "🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯"
	@echo "🚀 TBSAR BUILD SYSTEM - NXP LPC11C24 Cross-Compilation"
	@echo "🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯"
	@echo "🏗️  Project: $(PROJECT)"
	@echo "🎯 Target: $(MCU) (NXP LPC11C24)"
	@echo "🔧 Toolchain: $(CC)"
	@echo "⚙️  Build Type: $(if $(DEBUG),Debug ($(CFLAGS)),Release ($(CFLAGS)))"
	@echo "📂 Source Files: $(words $(SRCS)) files"
	@echo "📁 Build Dir: $(BUILD_DIR)"
	@date +"🕐 Build Time: %Y-%m-%d %H:%M:%S"
	@echo ""

# Copy artifacts to Release directory
copy-to-release: $(HEX) $(BIN)
	@echo "===================================================================================="
	@echo "📦 COPYING ARTIFACTS TO RELEASE"
	@echo "===================================================================================="
	@mkdir -p Release
	@echo "📁 Copying build artifacts to Release directory:"
	@cp $(HEX) Release/ && echo "   ✅ $(notdir $(HEX)) copied"
	@cp $(BIN) Release/ && echo "   ✅ $(notdir $(BIN)) copied"
	@if [ -f "$(BUILD_DIR)/$(PROJECT)_flashmagic.hex" ]; then \
		cp $(BUILD_DIR)/$(PROJECT)_flashmagic.hex Release/ && echo "   ✅ $(PROJECT)_flashmagic.hex copied"; \
	fi
	@echo "📁 Release directory updated with latest artifacts"
	@echo ""

# Build completion banner  
build-complete:
	@echo "🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯"
	@echo "✅ BUILD SUCCESSFUL! Ready for flashing."
	@echo "🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯🎯"
	@echo "📦 Generated Files:"
	@echo "   📄 $(HEX) - Ready for flashing"
	@echo "   📄 $(BIN) - Raw binary" 
	@echo "   📄 $(ELF) - Debug executable"
	@echo ""
	@echo "🚀 Next Steps:"
	@echo "   sudo make flash  - Program to LPC11C24"
	@echo "   make clean       - Clean build files"  
	@echo "   make debug       - Build with debug info"
	@echo ""

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(APP_DIR)
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/Adc
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/Can
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/Dio
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/Gpt
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/I2c
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/Spi
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/Sys
	@mkdir -p $(BUILD_DIR)/$(MCU_DIR)/Uart
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Buz
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Dac
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Eeprom
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Pc_Com
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Pwm
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Rgb
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Rotary
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Sensors
	@mkdir -p $(BUILD_DIR)/$(ECU_DIR)/Ukeys

# Compile C files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "===================================================================================="
	@echo "🔨 COMPILING: $<"
	@echo "📁 Output: $@"
	@echo "🎯 Flags: $(CFLAGS)"
	@echo "===================================================================================="
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "✅ Compilation successful: $(notdir $@)"
	@echo ""

# Link
$(ELF): $(OBJS) $(STARTUP_OBJ)
	@echo "===================================================================================="
	@echo "🔗 LINKING: Creating ELF executable"
	@echo "📁 Output: $@"
	@echo "📦 Objects: $(words $(OBJS) $(STARTUP_OBJ)) files"
	@echo "🎯 Linker Script: lpc11c24.ld"
	@echo "🎯 Flags: $(LDFLAGS)"
	@echo "===================================================================================="
	$(CC) $(OBJS) $(STARTUP_OBJ) $(LDFLAGS) -o $@
	@echo "✅ Linking successful: $(notdir $@)"
	@echo ""

# Create HEX file (Flash Magic Compatible Intel HEX)
$(HEX): $(ELF)
	@echo "===================================================================================="
	@echo "📄 CREATING HEX: Flash Magic compatible Intel HEX format"
	@echo "📁 Input: $<"
	@echo "📁 Output: $@"
	@echo "🎯 Format: Intel HEX optimized for Flash Magic compatibility"
	@echo "===================================================================================="
	$(OBJCOPY) -O ihex --only-section=.text --only-section=.init --only-section=.fini --only-section=.data $< $@
	@echo "✅ HEX file created: $(notdir $@) - Flash Magic Compatible"
	@ls -lh $@ | awk '{print "📏 Size: " $$5}'
	@echo "💡 Compatible with Flash Magic, lpc21isp, and other ISP tools"
	@echo "💡 Only includes essential sections: .text, .init, .fini, .data"
	@echo ""

# Create BIN file  
$(BIN): $(ELF)
	@echo "===================================================================================="
	@echo "📄 CREATING BIN: Raw binary format"
	@echo "📁 Input: $<"
	@echo "📁 Output: $@"
	@echo "🎯 Format: Raw Binary (-O binary)"
	@echo "===================================================================================="
	$(OBJCOPY) -O binary $< $@
	@echo "✅ Binary file created: $(notdir $@)"
	@ls -lh $@ | awk '{print "📏 Size: " $$5}'
	@echo ""

# Create listing file
$(LST): $(ELF)
	@echo "OBJDUMP $@"
	@$(OBJDUMP) -h -S $< > $@

# Show size
size: $(ELF)
	@echo "===================================================================================="
	@echo "📊 MEMORY ANALYSIS: LPC11C24 Memory Usage"
	@echo "===================================================================================="
	@$(SIZE) $<
	@echo ""
	@echo "📋 Memory Breakdown:"
	@$(SIZE) $< | tail -1 | awk '{printf "   📦 Flash (text): %d bytes (%.1f%% of 32KB)\n", $$1, $$1/32768*100}'
	@$(SIZE) $< | tail -1 | awk '{printf "   💾 RAM (data+bss): %d bytes (%.1f%% of 8KB)\n", $$2+$$3, ($$2+$$3)/8192*100}'
	@$(SIZE) $< | tail -1 | awk '{printf "   🎯 Total Image: %d bytes\n", $$4}'
	@echo ""

# Clean build files
clean:
	@echo "===================================================================================="
	@echo "🧹 CLEANING BUILD FILES"
	@echo "===================================================================================="
	@if [ -d "$(BUILD_DIR)" ]; then \
		echo "📁 Removing build directory: $(BUILD_DIR)"; \
		echo "   🗑️  Deleting object files (*.o)"; \
		echo "   🗑️  Deleting dependency files (*.d)"; \
		echo "   🗑️  Deleting ELF files (*.elf)"; \
		echo "   🗑️  Deleting HEX files (*.hex)"; \
		echo "   🗑️  Deleting BIN files (*.bin)"; \
		echo "   🗑️  Deleting MAP files (*.map)"; \
		rm -rf $(BUILD_DIR); \
		echo "✅ Build directory cleaned successfully!"; \
	else \
		echo "ℹ️  Build directory already clean ($(BUILD_DIR) not found)"; \
	fi
	@if [ -d "Release" ]; then \
		echo "📁 Cleaning Release directory artifacts"; \
		echo "   🗑️  Deleting release HEX files (*.hex)"; \
		echo "   🗑️  Deleting release BIN files (*.bin)"; \
		find Release -name "*.hex" -delete 2>/dev/null || true; \
		find Release -name "*.bin" -delete 2>/dev/null || true; \
		echo "✅ Release artifacts cleaned (README.md preserved)"; \
	else \
		echo "ℹ️  Release directory not found"; \
	fi
	@echo "✅ Clean completed successfully!"
	@echo "===================================================================================="

# Debug build
debug:
	@$(MAKE) all DEBUG=1

# Program using UART ISP (CP2102) with automatic DTR/RTS control
flash: $(HEX)
	@echo "===================================================================================="
	@echo "🚀 FLASHING: Programming LPC11C24 Microcontroller"
	@echo "===================================================================================="
	@echo "📁 HEX File: $(HEX)"
	@ls -lh $(HEX) | awk '{print "📏 File Size: " $$5}'
	@echo "📡 Port: /dev/ttyUSB0"
	@echo "⚡ Baud Rate: 115200"
	@echo "🎯 Target: LPC11C24 (32KB Flash / 8KB RAM)"
	@echo "🔧 Tool: lpc21isp"
	@echo ""
	@echo "🔄 Starting ISP programming..."
	@echo "===================================================================================="
	lpc21isp -control Build/tbsar.hex /dev/ttyUSB0 115200 12000
	@echo "===================================================================================="
	@echo "✅ FLASH PROGRAMMING COMPLETE!"
	@echo "===================================================================================="
	@echo ""
	@echo "⚠️  POWER CYCLE REQUIRED FOR APPLICATION START:"
	@echo "   1️⃣  Unplug the USB cable from board"
	@echo "   2️⃣  Wait 2-3 seconds"  
	@echo "   3️⃣  Plug the USB cable back in"
	@echo "   4️⃣  ✅ Application should start running immediately!"
	@echo ""
	@echo "🎉 Development cycle complete!"
	@echo "===================================================================================="

# Manual flash (user controls ISP mode)
flash-manual: $(HEX)
	@echo "Flashing $(HEX) to LPC11C24 via UART..."
	@echo "Make sure to put the board in ISP mode (hold ISP button while reset)"
	@echo "Press Enter when ready, or Ctrl+C to cancel..."
	@read dummy
	lpc21isp -control -term $(HEX) /dev/ttyUSB0 115200 12000

# Alternative flash target with different baud rates and auto ISP
flash-57600: $(HEX)
	@echo "Flashing at 57600 baud with auto ISP..."
	lpc21isp -control $(HEX) /dev/ttyUSB0 57600 12000

flash-38400: $(HEX)
	@echo "Flashing at 38400 baud with auto ISP..."
	lpc21isp -control $(HEX) /dev/ttyUSB0 38400 12000

# Start GDB session
gdb: $(ELF)
	$(GDB) $(ELF)

# Print variables (for debugging Makefile)
print-%:
	@echo $* = $($*)

# Help
help:
	@echo "Available targets:"
	@echo "  all          - Build project (default)"
	@echo "  flashmagic   - Alias for 'all' (HEX file is Flash Magic compatible)"
	@echo "  debug        - Build with debug symbols"
	@echo "  clean        - Remove build files"
	@echo "  flash        - Program MCU using UART ISP (auto DTR/RTS)"
	@echo "  flash-manual - Program MCU using UART ISP (manual mode)"
	@echo "  flash-57600  - Program MCU at 57600 baud (auto DTR/RTS)"
	@echo "  flash-38400  - Program MCU at 38400 baud (auto DTR/RTS)"
	@echo "  size         - Show memory usage"
	@echo "  gdb          - Start GDB session"
	@echo "  help         - Show this help"
	@echo ""
	@echo "Helper scripts:"
	@echo "  ./flash.sh        - Interactive flash tool (tries auto then manual)"
	@echo "  ./check-dtr-rts.sh - Show DTR/RTS hardware connection guide"

.PHONY: all clean debug flash gdb size help print-%