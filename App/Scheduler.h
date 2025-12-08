/**
 * @file Scheduler.h
 * @brief Task Scheduler API - Simplified interface
 * @author GitHub Copilot
 * @date 2025-11-16
 * 
 * Simple cooperative task scheduler with 1ms base tick.
 * Tasks execute automatically in SysTick interrupt context.
 * 
 * @section Usage
 * 1. Implement Scheduler_Task1ms(), Scheduler_Task5ms(), etc. in main.c
 * 2. Call Scheduler_Init() to initialize and start
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "lpc11xx.h"

/* =============================================================================
 * Configuration Constants
 * ===========================================================================*/

/**
 * @brief Base time tick in milliseconds
 */
#define SCHEDULER_BASE_TICK_MS          (10U)

/**
 * @brief Calculate SysTick reload value for 1ms tick
 * @note SystemCoreClock is defined in system_LPC11xx.c (typically 48MHz)
 */
#define SCHEDULER_SYSTICK_RELOAD_VALUE  ((SystemCoreClock / 1000U) * SCHEDULER_BASE_TICK_MS)

/* =============================================================================
 * Public API Functions
 * ===========================================================================*/

/**
 * @brief Initialize the scheduler
 * @details Initializes SysTick timer for 1ms base tick and starts execution
 * @note SysTick is enabled and started automatically by this function
 * @return void
 */
void Scheduler_Init(void);

/* =============================================================================
 * Application Task Functions (to be implemented in main.c)
 * ===========================================================================*/

/**
 * @brief 10ms periodic task - implement in main.c
 * @note Called every 10ms from SysTick interrupt
 */
void Scheduler_10ms(void);

/**
 * @brief 20ms periodic task - implement in main.c
 * @note Called every 20ms from SysTick interrupt
 */
void Scheduler_20ms(void);

/**
 * @brief 50ms periodic task - implement in main.c
 * @note Called every 50ms from SysTick interrupt
 */
void Scheduler_50ms(void);

/**
 * @brief 100ms periodic task - implement in main.c
 * @note Called every 100ms from SysTick interrupt
 */
void Scheduler_100ms(void);

#endif /* SCHEDULER_H */
