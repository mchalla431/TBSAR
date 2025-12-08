#ifndef __RGB_H__
#define __RGB_H__

#include "Dio.h"

#define RGB_NONE 	1
#define RGB_RED  	2
#define RGB_GREEN   3
#define RGB_BLUE    4
#define RGB_YELLOW  5
#define RGB_MAGENTA 6
#define RGB_CYAN    7
#define RGB_WHITE   8

void Rgb_Set(int option);
void Rgb_Monitor(int rgb_state);

#endif

