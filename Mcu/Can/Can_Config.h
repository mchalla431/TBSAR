#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include "Can.h"
#include "Syscon.h"

#define CAN_BAUD_100KHZ 1
#define CAN_BAUD_250KHZ 2
#define CAN_BAUD_500KHZ 3
#define CAN_BAUD_1MHZ   4
void Can_Baudrate_Set(int baud);

void Can_Loop_Back_Set(void);

void Can_Config(void);


#endif


