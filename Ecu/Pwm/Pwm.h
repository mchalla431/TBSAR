#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>
#include "Gpt.h"

extern uint32_t pwm_freq; // in Hz
extern uint32_t pwm_duty; // in %
extern uint32_t pwm_volts // in mv



void Pwm_Set(void);


#endif

