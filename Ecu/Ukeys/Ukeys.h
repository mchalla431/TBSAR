#ifndef __UKEYS_H__
#define __UKEYS_H__

#include "../../Mcu/Dio/Dio.h"
#include "../../Mcu/Gpt/Gpt.h"

#define TOUCH 	1
#define UNTOUCH 2

uint8_t Ukey_Up_State_Get(void); 			// returns TOUCH/ UNTOUCH
uint8_t Ukey_Down_State_Get(void); 			// returns TOUCH/ UNTOUCH
uint8_t Ukey_Center_State_Get(void); 		// returns TOUCH/ UNTOUCH
uint8_t Ukey_Left_State_Get(void); 			// returns TOUCH/ UNTOUCH
uint8_t Ukey_Right_State_Get(void); 		// returns TOUCH/ UNTOUCH

void Ukey_Up_Clicks_Get(uint8_t *clicks);    // Get the clicks by reference variable
void Ukey_Down_Clicks_Get(uint8_t *clicks);  // Get the clicks by reference variable
void Ukey_Center_Clicks_Get(uint8_t *clicks);// Get the clicks by reference variable
void Ukey_Left_Clicks_Get(uint8_t *clicks);  // Get the clicks by reference variable
void Ukey_Right_Clicks_Get(uint8_t *clicks); // Get the clicks by reference variable

void Ukeys_Status_Monitor(uint8_t up, uint8_t down, uint8_t left, uint8_t center, uint8_t right); // Monitor button states
void Ukeys_Clicks_Monitor(uint8_t up_clicks, uint8_t down_clicks, uint8_t left_clicks, uint8_t center_clicks, uint8_t right_clicks); // Monitor click counts

#endif

