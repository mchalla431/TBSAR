#ifndef __DIO_H__
#define __DIO_H__

#include "lpc11xx.h"

/* GPIO Driver Function Prototype Declarations */
#define LOW    0
#define HIGH   1
#define TOGGLE 2
void Gpio0_Pin_Set(int pin, int option); // pin: 0 to 11, option: LOW/ HIGH/ TOGGLE
void Gpio1_Pin_Set(int pin, int option);
void Gpio2_Pin_Set(int pin, int option);
void Gpio3_Pin_Set(int pin, int option);

int Gpio0_Pin_Get(int pin); // return value: LOW/HIGH
int Gpio1_Pin_Get(int pin);
int Gpio2_Pin_Get(int pin);                                     
int Gpio3_Pin_Get(int pin);

// GPIO nibble functions
void Gpio0_Nibble_Set(int nbn, int nbd);
void Gpio1_Nibble_Set(int nbn, int nbd);
void Gpio2_Nibble_Set(int nbn, int nbd);
void Gpio3_Nibble_Set(int nbn, int nbd);

// Eint functions 
void Eint0_Disable(int pin);
void Eint1_Disable(int pin);
void Eint2_Disable(int pin);
void Eint3_Disable(int pin);

void Eint0_Enable(int pin);
void Eint1_Enable(int pin);
void Eint2_Enable(int pin);
void Eint3_Enable(int pin);

void Eint0_Reset(int pin);
void Eint1_Reset(int pin);
void Eint2_Reset(int pin);
void Eint3_Reset(int pin);

#endif
