# 🚀 TBSAR Release Files

This directory contains ready-to-flash firmware files for the **NXP LPC11C24** microcontroller.

## 📁 **Flash Files**

### 🎯 **For Flash Magic (Windows)**
- **`tbsar_flashmagic.hex`** - **RECOMMENDED** - Flash Magic compatible version
- **`tbsar.hex`** - Standard Flash Magic compatible version

**Flash Magic Settings:**
- Device: `LPC11C24/301`
- Crystal: `12.000 MHz`
- Interface: `None (ISP)`
- Load file: `tbsar_flashmagic.hex`

### 🐧 **For lpc21isp (Linux)**
- **`tbsar.bin`** - Raw binary format (fastest programming)
- **`tbsar.hex`** - Intel HEX format

**lpc21isp Command:**
```bash
sudo lpc21isp -bin tbsar.bin /dev/ttyUSB0 9600 12000
```

## 🔧 **Hardware Setup**
- **MCU:** NXP LPC11C24 (32KB Flash, 8KB RAM)
- **Interface:** CP2102 UART-to-USB bridge
- **Baud Rate:** 9600 (for programming)
- **Crystal:** 12 MHz external crystal

## ✨ **Application Features**
- RGB LED control and patterns
- Automatic application start after programming
- No power cycle required after flashing
- Hardware tested and verified

## 🏗️ **Build Information**
- **Compiler:** ARM GCC (arm-none-eabi-gcc)
- **Target:** Cortex-M0 optimized
- **Flash Usage:** 1,500 bytes (4.6% of 32KB)
- **RAM Usage:** 544 bytes (6.6% of 8KB)
- **Build Date:** October 18, 2025

---
*These files are automatically generated from the latest source code. For building from source, see the main README.md.*