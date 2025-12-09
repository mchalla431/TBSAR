#include "Pwm.h"

uint32_t pwm_freq =0; // in Hz
uint32_t pwm_duty =0; // in %
uint32_t pwm_volt =0; // in mV


void Pwm_Set(void)
{
    // Use global variables pwm_freq (Hz) and pwm_duty (%)
    // Calculate period and on-time
    uint32_t period = 0;
    uint32_t ton = 0;
    if (pwm_freq > 0) {
	 period = 1000000 / pwm_freq; // period in microseconds
	 ton = (period * pwm_duty) / 100; // on-time in microseconds
    }

    // Calculate effective voltage (0 to 3300 mV)
    pwm_volt = (3300 * pwm_duty) / 100;

    // Set the Gpt base mode as Internal timer to make use of internal clock.
    Gpt1_Base_Mode_Set(INTERNAL_TIMER);

    // Set the match1 value (determines Pwm time period)
    Gpt1_Match1_Count_Set(period);

    // Set the match0 value (determines Pwm on-time)
    Gpt1_Match0_Count_Set(ton);

    // Set the counter initial value to 0
    Gpt1_Count_Set(0);

    // Set the match0 internal option: counter continue
    Gpt1_Match0_iOption_Set(COUNTER_CONTINUE);

    // Set the match1 internal option: counter reset
    Gpt1_Match1_iOption_Set(COUNTER_RESET);

    // Set the match0 external option: enable Pwm
    Gpt1_Match0_eOption_Set(MAT_PIN_PWM);
}
