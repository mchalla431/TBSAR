# ARM GCC Makefile for AI_TBSAR

# Use PowerShell as the shell
SHELL := powershell.exe
.SHELLFLAGS := -Command

# Toolchain
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Project name
TARGET = main

# Source and include discovery
SRC := $(wildcard App/*.c) \
	$(wildcard Ecu/Buz/*.c) \
	$(wildcard Ecu/Dac/*.c) \
	$(wildcard Ecu/Eeprom/*.c) \
	$(wildcard Ecu/Lcd/*.c) \
	$(wildcard Ecu/Pc_Com/*.c) \
	$(wildcard Ecu/Pwm/*.c) \
	$(wildcard Ecu/Rgb/*.c) \
	$(wildcard Ecu/Rotary/*.c) \
	$(wildcard Ecu/Sensors/*.c) \
	$(wildcard Ecu/Ukeys/*.c) \
	$(wildcard Mcu/Adc/*.c) \
	$(wildcard Mcu/Can/*.c) \
	$(wildcard Mcu/Dio/*.c) \
	$(wildcard Mcu/Gpt/*.c) \
	$(wildcard Mcu/I2c/*.c) \
	$(wildcard Mcu/Spi/*.c) \
	$(wildcard Mcu/Sys/*.c) \
	$(wildcard Mcu/Uart/*.c)

INCLUDES := -IApp -IEcu/Buz -IEcu/Dac -IEcu/Eeprom -IEcu/Lcd -IEcu/Pc_Com -IEcu/Pwm -IEcu/Rgb -IEcu/Rotary -IEcu/Sensors -IEcu/Ukeys -IMcu/Adc -IMcu/Can -IMcu/Dio -IMcu/Gpt -IMcu/I2c -IMcu/Spi -IMcu/Sys -IMcu/Uart

# Flags (adjust CPU as needed)
CFLAGS = -mcpu=cortex-m0 -mthumb -Wall -O2 $(INCLUDES)
LDFLAGS = -T linker_script.ld -nostartfiles

# Output
OUT_ELF = $(TARGET).elf
OUT_BIN = $(TARGET).bin
OUT_HEX = $(TARGET).hex

OBJDIR := build
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Build rules
all: $(OUT_ELF) $(OUT_BIN) $(OUT_HEX)

$(OBJDIR)/%.o: %.c
	@if (!(Test-Path -Path $(dir $@))) { New-Item -ItemType Directory -Path $(dir $@) | Out-Null }
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_ELF): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OUT_BIN): $(OUT_ELF)
	$(OBJCOPY) -O binary $< $@

$(OUT_HEX): $(OUT_ELF)
	$(OBJCOPY) -O ihex $< $@

clean:
	Remove-Item -Force -ErrorAction SilentlyContinue $(OUT_ELF),$(OUT_BIN),$(OUT_HEX)
	if (Test-Path $(OBJDIR)) { Remove-Item -Recurse -Force $(OBJDIR) }

.PHONY: all clean
