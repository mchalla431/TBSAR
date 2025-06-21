# AI_TBSAR ARM GCC Project

This project is organized for the ARM GCC (arm-none-eabi-gcc) toolchain.

## Folder Structure
- `App/` — Main application code
- `Ecu/` — ECU modules (Buz, Dac, Eeprom, Lcd, Pc_Com, Pwm, Rgb, Rotary, Sensors, Ukeys)
- `Mcu/` — MCU drivers (Adc, Can, Dio, Gpt, I2c, Spi, Sys, Uart)

## Build Instructions

1. Install the ARM GCC toolchain (e.g., `arm-none-eabi-gcc`).
2. Open a terminal in the project root.
3. Run:

   ```powershell
   make
   ```

   This will produce `main.elf` and `main.bin`.

4. To clean build artifacts, run:

   ```powershell
   make clean
   ```

## Notes
- You may need to provide a suitable `linker_script.ld` for your target MCU.
- Adjust the CPU and FPU flags in the Makefile as needed for your hardware.
