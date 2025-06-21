#include "../Mcu/Sys/Syscon.h"
#include "../Mcu/Sys/Iocon.h"
#include "../../Ecu/Rgb/Rgb.h"
#include <stdint.h>

// Use enum for task indices for readability
typedef enum
{
    TASK_10MS = 0,
    TASK_20MS,
    TASK_50MS,
    TASK_100MS,
    NUM_TASKS
} TaskIndex;

// Function pointer type for tasks
typedef void (*TaskFunc)(void);

// Task function declarations
void Task_10ms(void);
void Task_20ms(void);
void Task_50ms(void);
void Task_100ms(void);

/**
 * @brief Task executed every 10ms.
 *
 * This function is called every 10ms by the scheduler. It maintains an internal counter
 * to track elapsed time. Every 100 calls (i.e., every 1 second), it toggles the RGB Red LED
 * using Rgb_Set(RGB_RED_BLINK). The counter is then reset. This provides a periodic 1-second
 * blink on the Red LED for system heartbeat or status indication.
 */
void Task_10ms(void)
{
    static uint16_t counter = 0;
    counter++;
    if (counter >= 100) // 10ms * 100 = 1 second
    {
        Rgb_Set(RGB_RED_BLINK); // Toggle Red LED
        counter = 0;
    }
}

/**
 * @brief Task executed every 20ms.
 *
 * This function is called every 20ms by the scheduler. It is currently a placeholder for user code.
 * Add any periodic operations that need to run every 20ms here.
 */
void Task_20ms(void)
{

}

/**
 * @brief Task executed every 50ms.
 *
 * This function is called every 50ms by the scheduler. It is currently a placeholder for user code.
 * Add any periodic operations that need to run every 50ms here.
 */
void Task_50ms(void)
{

}

/**
 * @brief Task executed every 100ms.
 *
 * This function is called every 100ms by the scheduler. It is currently a placeholder for user code.
 * Add any periodic operations that need to run every 100ms here.
 */
void Task_100ms(void)
{

}

// Volatile flags for task scheduling
volatile uint8_t task_flags[NUM_TASKS] = {0};

// Array of task function pointers
TaskFunc tasks[NUM_TASKS] =
{
    Task_10ms,
    Task_20ms,
    Task_50ms,
    Task_100ms
};

/**
 * @brief Main entry point. Initializes SysTick and runs the task scheduler loop.
 *
 * This function configures the SysTick timer to generate an interrupt every 10ms, which is used
 * to schedule periodic tasks. The main loop checks the task flags set by the SysTick_Handler and
 * calls the corresponding task functions. Overrun detection is included to handle missed tasks.
 * Optionally, power-saving modes can be implemented when no tasks are pending.
 */
int main(void)
{
    SysTick_Config(480000); // 480000/48MHZ = 10ms
    // SysTick interrupts the processor every 10ms
    while(1)
    {
        for (int i = 0; i < NUM_TASKS; i++)
        {
            // Optional: Check for missed tasks (overrun detection)
            if (task_flags[i])
            {
                if (task_flags[i] > 1)
                {
                    // Overrun detected: handle as needed (e.g., log, set error flag, etc.)
                    // For now, just clear the flag
                }
                task_flags[i] = 0;
                tasks[i]();
            }
        }
        // Optional: Power-saving mode could be entered here if supported
    }
}

/**
 * @brief SysTick interrupt handler. Sets task flags according to their intervals.
 *
 * This interrupt handler is called every 10ms by the SysTick timer. It maintains counters for each
 * periodic task and sets the corresponding task flag when the interval is reached (10ms, 20ms, 50ms, 100ms).
 * The main loop checks these flags to execute the tasks. Overflow protection is included for the flags.
 */
void SysTick_Handler(void)
{
    static volatile uint8_t ctr[NUM_TASKS] = {0};
    static const uint8_t intervals[NUM_TASKS] = {1, 2, 5, 10};
    for (int i = 0; i < NUM_TASKS; i++)
    {
        ctr[i]++;
        if (ctr[i] >= intervals[i])
        {
            if (task_flags[i] < 255) task_flags[i]++; // Prevent overflow
            ctr[i] = 0;
        }
    }
}

// Comments have been added for clarity and maintainability.
// The code now uses enums for task indices, overrun detection, and is ready for further expansion.




