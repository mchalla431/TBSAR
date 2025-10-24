# TBSAR - Embedded Control Unit Project

## Overview

TBSAR is a comprehensive embedded software project for the **NXP LPC11C24** microcontroller, implementing a layered driver architecture for automotive/industrial control applications. The project features a clean separation between low-level hardware drivers and high-level application logic, making it suitable for various embedded control scenarios.

**✅ Hardware Tested & Verified**: RGB LED control confirmed working on LPC11C24 hardware with CP2102 programming interface.

## 🎯 Key Features

- **Target MCU**: NXP LPC11C24 (32KB Flash, 8KB RAM, Cortex-M0) ✅ **Hardware Verified**
- **Layered Architecture**: Clear separation between MCU drivers and ECU applications
- **Comprehensive Drivers**: ADC, UART, GPIO, PWM, SPI, I2C, CAN support
- **Advanced Flash Tools**: Enhanced `flash-all.sh` with auto-detection, monitoring, and error recovery
- **Hardware Abstraction**: Clean APIs for rapid application development
- **Professional Build System**: Verbose output, memory analysis, and comprehensive artifact generation

## 📁 Project Structure

```
TBSAR/
├── App/                    # Application layer
│   └── main.c             # Main application (RGB LED demo)
├── Ecu/                   # ECU (Electronic Control Unit) drivers
│   ├── Buz/               # Buzzer control
│   ├── Dac/               # Digital-to-Analog Converter
│   ├── Eeprom/            # EEPROM management
│   ├── Pc_Com/            # PC Communication (UART + printf)
│   ├── Pwm/               # Pulse Width Modulation
│   ├── Rgb/               # RGB LED control
│   ├── Rotary/            # Rotary encoder
│   ├── Sensors/           # Sensor interfaces
│   └── Ukeys/             # User key inputs
├── Mcu/                   # MCU (Microcontroller Unit) drivers
│   ├── Adc/               # Analog-to-Digital Converter
│   ├── Can/               # CAN bus interface
│   ├── Dio/               # Digital Input/Output
│   ├── Gpt/               # General Purpose Timer
│   ├── I2c/               # I2C communication
│   ├── Spi/               # SPI communication
│   ├── Sys/               # System initialization & clocks
│   └── Uart/              # UART communication
├── Build/                 # Build output directory
├── Makefile              # Comprehensive build system
├── lpc11c24.ld           # Linker script
└── flash-all.sh          # All-in-one flash utility
```

## 🏗️ Architecture

### Two-Layer Design

**MCU Layer (`Mcu/`)**
- Low-level hardware drivers
- Register-level access
- Hardware abstraction APIs
- System initialization and clocking

**ECU Layer (`Ecu/`)**
- High-level application drivers  
- Feature implementations
- Business logic
- User-friendly APIs

### Design Patterns

- **Config Split**: Each module has `*_Config.c/.h` (register macros) and `*.c/.h` (logic)
- **Instance Naming**: Numeric suffixes for multiple instances (e.g., `Gpt1_Match0_Set()`)
- **Consistent APIs**: Module-prefixed function naming (`Module_Action_Object`)

## 🚀 Quick Start

### Prerequisites

- **Toolchain**: ARM GCC (`arm-none-eabi-gcc`)
- **Programmer**: `lpc21isp` utility
- **Hardware**: CP2102 UART-USB bridge for programming

### Building the Project

```bash
# Clean build with verbose output
make clean && make

# Build and flash in one step
./flash-all.sh build
```

### Flashing to Hardware

**Enhanced Flash Script with Auto-Detection & Monitoring**

```bash
# Automatic flash (recommended - no hanging!)
sudo ./flash-all.sh auto

# Check hardware connections & device detection
sudo ./flash-all.sh check

# Flash with built-in terminal monitoring (for UART firmware)
sudo ./flash-all.sh flashterm

# Flash then monitor serial output separately
sudo ./flash-all.sh flashmon

# Manual ISP control
sudo ./flash-all.sh manual

# Alternative baud rates for problematic connections
sudo ./flash-all.sh 57600

# Build, flash, and monitor in one command
sudo ./flash-all.sh build

# Show all enhanced options
./flash-all.sh help
```

**✅ Fixed Issues**: Flash script no longer hangs in terminal mode. Clean exit after programming.

### Enhanced Development Workflow ✨ **Streamlined Process**

1. **Write Code**: Modify `App/main.c` or add ECU drivers
2. **Build & Flash**: `sudo ./flash-all.sh build` (one-command build and program)
3. **Monitor**: `sudo ./flash-all.sh monitor` (for UART-enabled firmware)
4. **Test**: Application starts automatically - LED should flash immediately!
5. **Debug**: Use verbose build output, memory analysis, and serial monitoring

**Quick RGB LED Testing Cycle**:
```bash
# Edit App/main.c to change RGB_RED to RGB_GREEN or RGB_BLUE
sudo ./flash-all.sh auto     # Flash in seconds, no hanging
# LED starts flashing immediately - no power cycle needed!
```

**✅ Verified Development Chain**: Build → Flash → Test cycle confirmed working on hardware

**🚀 Instant Application Launch**: Firmware starts automatically after programming - no power cycling required!

## 🪟 Windows Flash Magic Support

For users who prefer the **Flash Magic** GUI tool on Windows, we provide a compatible hex file format:

### Building Flash Magic Compatible HEX
```bash
# Build special hex file for Flash Magic
make flashmagic
```

This creates `Build/tbsar_flashmagic.hex` optimized for Flash Magic compatibility.

### Flash Magic Configuration
1. **Download**: [Flash Magic](https://www.flashmagictool.com/) (free tool)
2. **Device Settings**:
   - **Device**: `LPC11C24/301` 
   - **Crystal Frequency**: `12.000 MHz`
   - **Interface**: `None (ISP)`
   - **COM Port**: Select your CP2102 USB-UART port
   - **Baud Rate**: `115200` (or try `57600` if issues)

### Flash Magic Procedure
1. **Load HEX**: Browse to `Build/tbsar_flashmagic.hex`
2. **ISP Mode**: Hold ISP button on board, press Reset, release ISP
3. **Program**: Click "Start" to program the device
4. **Reset**: Press Reset button to run firmware

### Flash Magic vs Linux ISP
| Feature | Flash Magic (Windows) | Linux lpc21isp |
|---------|----------------------|----------------|
| **Interface** | ✅ GUI-based | ⚡ Command-line |
| **Auto-Detection** | ❌ Manual setup | ✅ Auto device detection |
| **Speed** | 🐌 Slower | ⚡ Faster programming |
| **ISP Control** | 🔧 Manual button | ✅ Auto DTR/RTS control |
| **Monitoring** | ❌ No terminal | ✅ Built-in serial monitor |

**💡 Recommendation**: Use Linux tools for development, Flash Magic for occasional Windows programming.

## 💡 Example Applications

### Current Demo: RGB LED Control ✅ **Hardware Tested**
```c
#include "../Ecu/Rgb/Rgb.h"
#include "../Ecu/Rgb/Rgb_Config.h"

int main(void) {
    // Initialize RGB LED configuration
    Rgb_Config();
    
    // Simple LED test - currently configured for GREEN
    while (1) {
        // Turn GREEN LED ON
        Rgb_Set(RGB_GREEN);
        Software_Delay(500000);  // 500ms ON
        
        // Turn GREEN LED OFF
        Rgb_Set(RGB_NONE);
        Software_Delay(500000);  // 500ms OFF
    }
}
```

**✅ Verified Hardware Pin Mapping**:
- **Red LED**: Port2.10 (GPIO2) ✅ Tested
- **Green LED**: Port1.2 (GPIO1) ✅ Tested  
- **Blue LED**: Port1.10 (GPIO1) - Ready for testing
```

### Printf Support ✨ **NEW Feature**
TBSAR now includes full printf support automatically redirected to UART output:

```c
#include "../Ecu/Pc_Com/Pc_Com.h"

int main(void) {
    // Initialize system
    Syscon_Init();
    Uart_Init();
    
    // Use printf directly - output goes to UART/serial terminal
    printf("TBSAR System Starting...\n");
    printf("Sensor Reading: %d\n", sensor_value);
    printf("Voltage: %.2f V\n", voltage);
    printf("Status: %s\n", "READY");
    
    while(1) {
        printf("Loop count: %d\n", counter++);
        // ... your application code
    }
}
```

**Features**:
- **Full Format Support**: All standard printf formats (%d, %f, %s, %x, %c, etc.)
- **UART Redirection**: Automatic output to serial terminal via CP2102
- **Memory Efficient**: Uses nano specs library - no Flash/RAM overhead
- **Seamless Integration**: Just include `Pc_Com.h` and use printf normally

**Serial Output**: Connect to `/dev/ttyUSB0` at 9600 baud to see printf output!

### Potential Applications
- **Industrial Control**: Sensor monitoring, actuator control
- **Automotive ECUs**: Dashboard displays, motor control
- **IoT Devices**: Data acquisition, communication gateways  
- **Test Equipment**: Signal generation, measurement systems
- **Debug & Logging**: Real-time system monitoring with printf

## 🔧 Build System Features

### Comprehensive Makefile
- **Verbose Output**: Detailed compilation and linking information
- **Memory Analysis**: Flash and RAM usage reporting (currently 4.6% Flash, 6.6% RAM)
- **Multiple Formats**: Generates ELF, HEX, and BIN files
- **Dependency Tracking**: Automatic header dependency management
- **Clean Builds**: Detailed cleanup with file type reporting

### Enhanced Flash Utility (`flash-all.sh`) ✨ **Major Upgrade**
- **Auto-Device Detection**: Finds CP2102 via `/dev/serial/by-id/` for stable connections
- **Multiple Modes**: Auto, manual, different baud rates, with/without terminal monitoring
- **Permission Management**: Automatic detection and clear solutions for device access issues
- **Process Conflict Detection**: Uses `lsof`/`fuser` to identify competing processes
- **Intelligent Error Analysis**: Parses `lpc21isp` output for targeted troubleshooting
- **No More Hanging**: Removed `-term` flag for clean exit after programming
- **Serial Monitoring**: Built-in UART monitoring with configurable baud rates
- **One-Command Workflow**: Build and flash in single operation with comprehensive feedback

## 🔌 Hardware Requirements

### Minimum Setup
- **MCU Board**: NXP LPC11C24 development board
- **Programming**: CP2102 USB-UART bridge
- **Power**: USB or external 3.3V supply

### Supported Peripherals
- **LEDs**: RGB LED control (GPIO-based)
- **Communication**: UART, SPI, I2C interfaces
- **Analog**: ADC inputs, DAC output
- **Timing**: PWM generation, precise delays
- **Storage**: EEPROM interface
- **User Interface**: Rotary encoder, buttons

## 📊 Memory Optimization ✅ **Real Hardware Results**

The build system provides detailed memory analysis with **verified hardware results**:
- **Flash Usage**: Highly optimized at **4.6%** (1,500 bytes of 32KB)
- **RAM Usage**: Efficient at **6.6%** (544 bytes of 8KB) 
- **Binary Size**: Only **1.5KB** for full RGB LED demo
- **Build Artifacts**: ELF (2,044 bytes), HEX (4.2KB), BIN (1.5KB)

**Memory Breakdown (from actual build)**:
```
Memory region         Used Size  Region Size  %age Used
           FLASH:        1500 B        32 KB      4.58%
             RAM:         544 B         8 KB      6.64%
          CANRAM:           0 B         2 KB      0.00%
```

**Excellent Efficiency**: Leaves **95.4% Flash** and **93.4% RAM** free for application expansion!

## 🛠️ Development Tools

### Build Targets
```bash
make            # Standard build with verbose output
make clean      # Clean with detailed file removal
make flash      # Build and program via Makefile  
make debug      # Debug build with additional symbols
```

### Enhanced Flash Options ✨ **All New Features**
```bash
sudo ./flash-all.sh auto           # Automatic DTR/RTS ISP (clean exit, no hanging)
sudo ./flash-all.sh check          # Hardware detection & connection verification  
sudo ./flash-all.sh manual         # Manual ISP button control
sudo ./flash-all.sh 57600          # Slower baud rate for problematic connections
sudo ./flash-all.sh build          # Clean, build, and flash in one command
sudo ./flash-all.sh monitor [baud] # Monitor serial output (default: 57600)
sudo ./flash-all.sh flashmon       # Flash then monitor serial output
sudo ./flash-all.sh flashterm      # Flash with built-in terminal (for UART firmware)
```

**✅ Key Improvements**: Auto-device detection, permission checking, no terminal hanging, serial monitoring

## 📈 Scalability

### Adding New Features
1. **MCU Drivers**: Add low-level hardware support in `Mcu/`
2. **ECU Applications**: Implement features using MCU drivers in `Ecu/`
3. **Applications**: Compose ECU drivers in `App/main.c`

### Integration Points
- **Serial Communication**: `Pc_Com` module for UART-based protocols **+ printf support**
- **Debug & Logging**: Use `printf()` for real-time system monitoring
- **Sensor Integration**: `Sensors` module with ADC conversion
- **Motor Control**: `Pwm` module using `Gpt` timers
- **User Interface**: `Ukeys` and `Rotary` for input handling

## 🔍 Debugging & Troubleshooting

### Common Issues & Solutions ✅ **Enhanced Troubleshooting**

**✅ Fixed: Terminal Hanging**
- **Issue**: Flash script used to hang after programming
- **Solution**: Removed `-term` flag from `lpc21isp` calls for clean exit

**Hardware Issues**
- **LED Not Blinking**: Application should start automatically; try manual power cycle if needed
- **Device Not Found**: Run `sudo ./flash-all.sh check` for auto-detection
- **Permission Denied**: Script provides specific solutions (add user to dialout group or use sudo)
- **Process Conflicts**: Automatic detection of processes using UART port

**Flash Failures**  
- **Connection Issues**: Enhanced hardware checking with detailed diagnostics
- **ISP Mode Problems**: Try `sudo ./flash-all.sh manual` with clear instructions
- **Baud Rate Issues**: Use `sudo ./flash-all.sh 57600` for problematic connections

**Build Errors**
- **Missing Toolchain**: Verify ARM GCC toolchain installation
- **Path Issues**: Build system provides detailed compilation output for debugging

### Debug Features
- **Verbose Build**: Shows compilation of all 37+ source files
- **Memory Maps**: Detailed section analysis and usage
- **Hardware Verification**: Connection testing and signal validation

## 📚 Documentation

- **Code Comments**: Comprehensive function and module documentation
- **Naming Conventions**: Clear, descriptive function and variable names
- **Architecture Guide**: See `.github/copilot-instructions.md` for detailed patterns

## 🎓 Learning Path

1. **Start**: Understand the RGB LED demo in `App/main.c`
2. **Explore**: Review ECU drivers like `Rgb`, `Pwm`, `Sensors`
3. **Deep Dive**: Examine MCU drivers for hardware understanding
4. **Extend**: Add new functionality using existing patterns
5. **Optimize**: Use build system memory analysis for efficiency

## 📄 License

This project is part of the TBSAR embedded systems development framework. Please refer to your organization's licensing terms for usage guidelines.

## 🤝 Contributing

When contributing:
1. Follow existing naming conventions (`Module_Action_Object`)
2. Maintain the MCU/ECU layer separation
3. Add comprehensive comments and documentation
4. Test with the provided build and flash tools
5. Verify memory usage remains within acceptable limits

---

**Ready to start embedded development with TBSAR!** 🚀

The project provides a solid foundation for embedded control applications with professional build tools, comprehensive driver support, and scalable architecture patterns.