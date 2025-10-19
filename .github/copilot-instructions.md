## Purpose

This file gives concise, actionable guidance for AI coding agents working on the TBSAR embedded codebase (NXP LPC11xx drivers and higher-level ECU logic). Focus on discoverable, reproducible patterns so you can make safe changes quickly.

## Big picture

- Two-layer structure: `Mcu/` contains hardware drivers (ADC, UART, GPIO, GPT, SPI, I2C, Sys startup). `Ecu/` contains higher-level features that call Mcu drivers (e.g. `Ecu/Pwm/` uses `Mcu/Gpt/`).
- System initialization and clock config live in `Mcu/Sys/` (see `system_LPC11xx.c`, `cr_startup_lpc11xx.c`, and `lpc11xx.h`).

## Key patterns & conventions

- Config split: Many modules have a pair of files `Xxx_Config.c/.h` and `Xxx.c/.h`. The `_Config` file contains register macros and low-level wrappers; the main file implements logic that calls those wrappers. Example: `Mcu/Uart/Uart_Config.c` provides `UART_Update_DLL(...)` macros and `Uart_Baudrate_Set()`; `Ecu/Pc_Com/Pc_Com.c` calls `Uart_` helpers to send bytes.
- Relative includes are used (e.g. `#include "../../Mcu/Gpt/Gpt_Config.h"`). Keep include paths consistent with this layout.
- Hardware access: registers and IRQ numbers are defined in `Mcu/Sys/lpc11xx.h`. Prefer adding abstraction wrappers in `*_Config.c` rather than changing `lpc11xx.h`.
- Instance naming: driver instances use numeric suffixes (e.g. `Gpt1_Match0_Count_Set(...)`) — follow existing instance-style names when adding new channel-level APIs.
- Function naming is descriptive and module-prefixed: `Module_Action_Object` (e.g. `Pc_Com_String_Send`, `Gpio0_Pin_Set`, `Adc_Input_Select`). Use the same style.

## Integration points / examples

- Sending serial data: `Ecu/Pc_Com/Pc_Com.c` -> uses `Uart_Transmit_Buffer_Check()` and `Uart_Transmit_Buffer_Write()` (see `Mcu/Uart/Uart.c` and `Mcu/Uart/Uart_Config.c`).
- PWM control: `Ecu/Pwm/Pwm.c` calls `Gpt1_*` APIs (see `Mcu/Gpt/` files) and sets match options like `MAT_PIN_PWM`.
- Sensors: `Ecu/Sensors/Sensors.c` uses `Adc_*` APIs and converts counts to engineering units (mV, Celsius). Prefer adding conversions here rather than in low-level ADC driver.

## Safe edit guidance

- For register-level changes, update or add macros/wrappers in the module's `*_Config.c/.h` (e.g. `Mcu/Uart/Uart_Config.c`) so higher-level callers remain unchanged.
- When exposing new functionality, add prototypes in the module header and follow existing naming and instance suffix conventions.
- Avoid changing `Mcu/Sys/lpc11xx.h` unless adding missing definitions; it's the MCU vendor header.

## Build / test / debug notes (discoverable)

- No Makefile, CI config, or README describing the toolchain was found in the repository. Common toolchains for this layout are Keil uVision or an arm-none-eabi GCC Makefile. Ask a human for the canonical build system before adding project-wide changes.
- System startup is handled by `Mcu/Sys/cr_startup_lpc11xx.c` and `system_LPC11xx.c` — useful breakpoints for bring-up and clock issues.

## Where to look first (quick checklist)

1. `Mcu/Sys/` — system init, clocks, vendor headers (`lpc11xx.h`).
2. `Mcu/*/` — driver implementations and `*_Config` register wrappers.
3. `Ecu/*/` — feature-level code that composes drivers (good examples of usage patterns).

## If you need more info

- If a build or test workflow is required, ask the repository owner to supply the project/IDE files or preferred toolchain and flash/debug instructions. I can then update this file with concrete build commands.

---
Please review and tell me which areas you'd like expanded (build/tooling, coding conventions, or example PRs to follow) and I'll iterate.
