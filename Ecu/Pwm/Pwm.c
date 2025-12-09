#include "Pwm.h"

void Square_Wave_Set(int ton)
{
	//Set the Gpt base mode as Internal timer to make use of internal clock.
	Gpt1_Base_Mode_Set(INTERNAL_TIMER);

	// Set the match0 value (for 5ms Ton , match value = 5ms/1us = 5000)
	Gpt1_Match0_Count_Set(ton);

	// Set the counter initial value to 0
	Gpt1_Count_Set(0);

	// Set the match0 internal option: counter reset
	Gpt1_Match0_iOption_Set(COUNTER_RESET);

	// Set the match0 external option: toggle the pin
	Gpt1_Match0_eOption_Set(MAT_PIN_TOGGLE);
}

void Pwm_Wave_Set(int period, int ton)
{
//	Set the Gpt base mode as Internal timer to make use of internal clock.
	Gpt1_Base_Mode_Set(INTERNAL_TIMER);

//	Set the match1 value (determines Pwm time period)
	Gpt1_Match1_Count_Set(period);

//	Set the match0 value (determines Pwm on-time)
	Gpt1_Match0_Count_Set(ton);

//	Set the counter initial value to 0
	Gpt1_Count_Set(0);

//	Set the match0 internal option: counter continue
	Gpt1_Match0_iOption_Set(COUNTER_CONTINUE);
	
//	Set the match1 internal option: counter reset
	Gpt1_Match1_iOption_Set(COUNTER_RESET);

//	Set the match0 external option: enable Pwm
	Gpt1_Match0_eOption_Set(MAT_PIN_PWM);

}
