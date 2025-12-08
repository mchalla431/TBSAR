#include "Ukeys.h"
#include "Monitor.h"

/* Global button state variables */
uint8_t uk_up_ = RELEASE;
uint8_t uk_down_ = RELEASE;
uint8_t uk_left_ = RELEASE;
uint8_t uk_center_ = RELEASE;
uint8_t uk_right_ = RELEASE;

/* Global button click counters */
uint8_t uk_up_clicks = 0;
uint8_t uk_down_clicks = 0;
uint8_t uk_left_clicks = 0;
uint8_t uk_center_clicks = 0;
uint8_t uk_right_clicks = 0;


static void Ukey_Up_Status(void)
{
	uint8_t pn;
	pn = Gpio0_Pin_Get(3);
	
	if(pn == 0)
		uk_up_ = PRESS;
	else
		uk_up_ = RELEASE;
}

static void Ukey_Down_Status(void)
{
	uint8_t pn;
	pn = Gpio2_Pin_Get(6);
	
	if(pn == 0)
		uk_down_ = PRESS;
	else
		uk_down_ = RELEASE;
}

static void Ukey_Center_Status(void)
{
	uint8_t pn;
	pn = Gpio2_Pin_Get(8);
	
	if(pn == 0)
		uk_center_ = PRESS;
	else
		uk_center_ = RELEASE;
}

static void Ukey_Left_Status(void)
{
	uint8_t pn;
	pn = Gpio2_Pin_Get(7);
	
	if(pn == 0)
		uk_left_ = PRESS;
	else
		uk_left_ = RELEASE;
}

static void Ukey_Right_Status(void)
{
	uint8_t pn;
	pn = Gpio1_Pin_Get(4);
	
	if(pn == 0)
		uk_right_ = PRESS;
	else
		uk_right_ = RELEASE;
}


static void Ukey_Up_Clicks(void)
{
	uint8_t state_current;
	static uint8_t state_previous = RELEASE;
	
	Ukey_Up_Status();
	state_current = uk_up_;
	
	if(state_current == PRESS && state_previous == RELEASE)
	{
		uk_up_clicks++;
	}	
	state_previous = state_current;
}  

static void Ukey_Down_Clicks(void)
{
	uint8_t state_current;
	static uint8_t state_previous = RELEASE;
	
	Ukey_Down_Status();
	state_current = uk_down_;
	
	if(state_current == PRESS && state_previous == RELEASE)
	{
		uk_down_clicks++;
	}	
	state_previous = state_current;
}  

static void Ukey_Center_Clicks(void)
{
	uint8_t state_current;
	static uint8_t state_previous = RELEASE;
	
	Ukey_Center_Status();
	state_current = uk_center_;
	
	if(state_current == PRESS && state_previous == RELEASE)
	{
		uk_center_clicks++;
	}	
	state_previous = state_current;
}

static void Ukey_Left_Clicks(void)
{
	uint8_t state_current;
	static uint8_t state_previous = RELEASE;
	
	Ukey_Left_Status();
	state_current = uk_left_;
	
	if(state_current == PRESS && state_previous == RELEASE)
	{
		uk_left_clicks++;
	}	
	state_previous = state_current;
}

static void Ukey_Right_Clicks(void)
{
	uint8_t state_current;
	static uint8_t state_previous = RELEASE;
	
	Ukey_Right_Status();
	state_current = uk_right_;
	
	if(state_current == PRESS && state_previous == RELEASE)
	{
		uk_right_clicks++;
	}	
	state_previous = state_current;
}

/* Task function to read all button states */
void Ukey_All_Status(void)
{
	Ukey_Up_Status();
	Ukey_Down_Status();
	Ukey_Left_Status();
	Ukey_Center_Status();
	Ukey_Right_Status();
}

/* Task function to count all button clicks */
void Ukey_All_Clicks(void)
{
	Ukey_Up_Clicks();
	Ukey_Down_Clicks();
	Ukey_Left_Clicks();
	Ukey_Center_Clicks();
	Ukey_Right_Clicks();
}

void Ukey_All_Clicks_Reset(void)
{
	uk_up_clicks = 0;
	uk_down_clicks = 0;
	uk_left_clicks = 0;
	uk_center_clicks = 0;
	uk_right_clicks = 0;
}

void Ukey_Status_Monitor(void)
{
	uart_printf("\rUKEYS: U:%s D:%s L:%s C:%s R:%s   ",
		(uk_up_ == PRESS) ? "PRESS" : "RELEASE",
		(uk_down_ == PRESS) ? "PRESS" : "RELEASE",
		(uk_left_ == PRESS) ? "PRESS" : "RELEASE",
		(uk_center_ == PRESS) ? "PRESS" : "RELEASE",
		(uk_right_ == PRESS) ? "PRESS" : "RELEASE");
}

void Ukey_Clicks_Monitor(void)
{
	// Display click counts using globals
	uart_printf("\rCLICKS: U:%u D:%u L:%u C:%u R:%u   ",
		uk_up_clicks, uk_down_clicks, uk_left_clicks, uk_center_clicks, uk_right_clicks);
}