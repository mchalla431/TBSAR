#ifndef __UKEYS_H__
#define __UKEYS_H__

#include "Ukeys.h"
#include "Dio.h"

#define PRESS   1
#define RELEASE 0

/* Global button state variables */
extern uint8_t uk_up_;
extern uint8_t uk_down_;
extern uint8_t uk_left_;
extern uint8_t uk_center_;
extern uint8_t uk_right_;
/* Global button click counters */
extern uint8_t uk_up_clicks;
extern uint8_t uk_down_clicks;
extern uint8_t uk_left_clicks;
extern uint8_t uk_center_clicks;
extern uint8_t uk_right_clicks;

void Ukey_All_Status(void);				// Read all button states and update globals
void Ukey_All_Clicks(void);				// Count button clicks and update global counters

void Ukey_All_Clicks_Reset(void);		// Reset all button click counters
void Ukey_Status_Monitor(void);			// Display all button states
void Ukey_Clicks_Monitor(void);			// Display all button clicks

#endif

