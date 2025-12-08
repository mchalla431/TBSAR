#include "Dio.h"
#include "lpc11xx.h"


// Port Pin Write Macroes
#define GPIO0_Pin_Set_High(pin)			GPIO0_DATA |= (1<<pin)
#define GPIO1_Pin_Set_High(pin)			GPIO1_DATA |= (1<<pin)
#define GPIO2_Pin_Set_High(pin)			GPIO2_DATA |= (1<<pin)
#define GPIO3_Pin_Set_High(pin)			GPIO3_DATA |= (1<<pin)

#define GPIO0_Pin_Set_Low(pin)			GPIO0_DATA &= ~(1<<pin)
#define GPIO1_Pin_Set_Low(pin)			GPIO1_DATA &= ~(1<<pin)
#define GPIO2_Pin_Set_Low(pin)			GPIO2_DATA &= ~(1<<pin)
#define GPIO3_Pin_Set_Low(pin)			GPIO3_DATA &= ~(1<<pin)

#define GPIO0_Pin_Toggle(pin)			GPIO0_DATA ^= (1<<pin)
#define GPIO1_Pin_Toggle(pin)			GPIO1_DATA ^= (1<<pin)
#define GPIO2_Pin_Toggle(pin)			GPIO2_DATA ^= (1<<pin)
#define GPIO3_Pin_Toggle(pin)			GPIO3_DATA ^= (1<<pin)

// Port Pin Read Drivers
#define GPIO0_Pin_Get_State(pin)		(GPIO0_DATA & (1<<pin))?1:0
#define GPIO1_Pin_Get_State(pin)		(GPIO1_DATA & (1<<pin))?1:0
#define GPIO2_Pin_Get_State(pin)		(GPIO2_DATA & (1<<pin))?1:0
#define GPIO3_Pin_Get_State(pin)		(GPIO3_DATA & (1<<pin))?1:0

/* EINT Macores */
#define EINT_Enable(port, pin)			GPIO##port##_IE |=  (1<<pin)
#define EINT_Disable(port, pin)			GPIO##port##_IE &=  ~(1<<pin)
#define EINT_Reset(port, pin)			GPIO##port##_IC  =  (1<<pin) 



void Gpio0_Pin_Set(int pin, int option)
{
	switch(option)
	{
		case LOW:		GPIO0_Pin_Set_Low(pin);  break;
		case HIGH:		GPIO0_Pin_Set_High(pin); break;
		case TOGGLE:	GPIO0_Pin_Toggle(pin); 	 break;
	}
}

void Gpio1_Pin_Set(int pin, int option)
{
	switch(option)
	{
		case LOW:		GPIO1_Pin_Set_Low(pin);  break;
		case HIGH:		GPIO1_Pin_Set_High(pin); break;
		case TOGGLE:	GPIO1_Pin_Toggle(pin); 	 break;
	}
}

void Gpio2_Pin_Set(int pin, int option)
{
	switch(option)
	{
		case LOW:		GPIO2_Pin_Set_Low(pin);  break;
		case HIGH:		GPIO2_Pin_Set_High(pin); break;
		case TOGGLE:	GPIO2_Pin_Toggle(pin); 	 break;
	}
}

void Gpio3_Pin_Set(int pin, int option)
{
	switch(option)
	{
		case LOW:		GPIO3_Pin_Set_Low(pin);  break;
		case HIGH:		GPIO3_Pin_Set_High(pin); break;
		case TOGGLE:	GPIO3_Pin_Toggle(pin); 	 break;
	}
}

int Gpio0_Pin_Get(int pin)
{
	int state;
	
	state = GPIO0_Pin_Get_State(pin);
	
	return state;
}

int Gpio1_Pin_Get(int pin)
{
	int state;
	
	state = GPIO1_Pin_Get_State(pin);
	
	return state;
}

int Gpio2_Pin_Get(int pin)
{
	int state;
	
	state = GPIO2_Pin_Get_State(pin);
	
	return state;
}

int Gpio3_Pin_Get(int pin)
{
	int state;
	
	state = GPIO3_Pin_Get_State(pin);
	
	return state;
}

// Additional functions
#define NIBBLE_MASK	0xf
void Gpio0_Nibble_Set(int nbn, int nbd)
{
	GPIO0_DATA =  (GPIO0_DATA & ~(NIBBLE_MASK<<(4*nbn))) | (nbd<<(4*nbn)); 
}

void Gpio1_Nibble_Set(int nbn, int nbd)
{
	GPIO1_DATA =  (GPIO1_DATA & ~(NIBBLE_MASK<<(4*nbn))) | (nbd<<(4*nbn)); 
}

void Gpio2_Nibble_Set(int nbn, int nbd)
{
	GPIO2_DATA =  (GPIO2_DATA & ~(NIBBLE_MASK<<(4*nbn))) | (nbd<<(4*nbn)); 
}

void Gpio3_Nibble_Set(int nbn, int nbd)
{
	GPIO3_DATA =  (GPIO3_DATA & ~(NIBBLE_MASK<<(4*nbn))) | (nbd<<(4*nbn)); 
}


void Eint0_Disable(int pin)
{
	EINT_Disable(0,pin);
}

void Eint1_Disable(int pin)
{
	EINT_Disable(1,pin);
}

void Eint2_Disable(int pin)
{
	EINT_Disable(2,pin);
}

void Eint3_Disable(int pin)
{
	EINT_Disable(3,pin);
}

void Eint0_Enable(int pin)
{
	EINT_Enable(0,pin);
}

void Eint1_Enable(int pin)
{
	EINT_Enable(1,pin);
}

void Eint2_Enable(int pin)
{
	EINT_Enable(2,pin);
}

void Eint3_Enable(int pin)
{
	EINT_Enable(3,pin);
}

void Eint0_Reset(int pin)
{
	EINT_Reset(0,pin);
	__NOP();	
	__NOP();	
}

void Eint1_Reset(int pin)
{
	EINT_Reset(1,pin);
	__NOP();	
	__NOP();	
}

void Eint2_Reset(int pin)
{
	EINT_Reset(2,pin);
	__NOP();	
	__NOP();	
}

void Eint3_Reset(int pin)
{
	EINT_Reset(3,pin);
	__NOP();	
	__NOP();	
}
