#ifndef __RGB_H__
#define __RGB_H__

#include "../../Mcu/Dio/Dio.h"
#include "../../Mcu/Gpt/Gpt.h"

#define RGB_NONE 	1
#define RGB_RED  	2
#define RGB_GREEN   3
#define RGB_BLUE    4
#define RGB_YELLOW  5
#define RGB_MAGENTA 6
#define RGB_CYAN    7
#define RGB_WHITE   8
#define RGB_RED_BLINK   9
#define RGB_GREEN_BLINK 10
#define RGB_BLUE_BLINK  11

void Rgb_Set(int option);




#endif

