/**
 * @file Scheduler.c
 * @brief Task Scheduler implementation - Simplified version
 * @author GitHub Copilot
 * @date 2025-11-16
 * 
 * Implements a simple task scheduler with 4 fixed-period tasks:
 * 10ms, 20ms, 50ms, and 100ms using SysTick interrupt.
 * Uses CMSIS SysTick_Config() for hardware initialization.
 */

#include "Scheduler.h"

/* =============================================================================
 * Private Variables
 * ===========================================================================*/

/**
 * @brief Task period counters
 * @note Decremented in SysTick interrupt, reset when reaching zero
 */
static volatile uint16_t task_counter_10ms = 1U;
static volatile uint16_t task_counter_20ms = 2U;
static volatile uint16_t task_counter_50ms = 5U;
static volatile uint16_t task_counter_100ms = 10U;

/* =============================================================================
 * Public Functions
 * ===========================================================================*/

/**
 * @brief Initialize the scheduler
 * @details Initializes task counters and configures SysTick for 10ms interrupts
 */
void Scheduler_Init(void)
{
    /* Initialize task counters to their periods (in 10ms ticks) */
    task_counter_10ms = 1U;    /* 10ms / 10ms = 1 tick */
    task_counter_20ms = 2U;    /* 20ms / 10ms = 2 ticks */
    task_counter_50ms = 5U;    /* 50ms / 10ms = 5 ticks */
    task_counter_100ms = 10U;  /* 100ms / 10ms = 10 ticks */
    
    /* Configure and start SysTick timer using CMSIS function
     * This automatically enables the timer and interrupt */
    SysTick_Config(SCHEDULER_SYSTICK_RELOAD_VALUE);
}

/* =============================================================================
 * SysTick Interrupt Handler
 * ===========================================================================*/

/**
 * @brief SysTick interrupt handler - executes every 10ms
 * @note Overrides weak alias in cr_startup_lpc11xx.c
 * @note Keep total execution time of all tasks under 10ms to avoid overrun
 */
void SysTick_Handler(void)
{
    /* 10ms task - executes every tick (10ms) */
    if (--task_counter_10ms == 0U) {
        task_counter_10ms = 1U;
        Scheduler_10ms();
    }
    
    /* 20ms task - executes every 2 ticks (20ms) */
    if (--task_counter_20ms == 0U) {
        task_counter_20ms = 2U;
        Scheduler_20ms();
    }
    
    /* 50ms task - executes every 5 ticks (50ms) */
    if (--task_counter_50ms == 0U) {
        task_counter_50ms = 5U;
        Scheduler_50ms();
    }
    
    /* 100ms task - executes every 10 ticks (100ms) */
    if (--task_counter_100ms == 0U) {
        task_counter_100ms = 10U;
        Scheduler_100ms();
    }
}
