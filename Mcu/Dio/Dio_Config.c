#include "Dio_Config.h"


/* GPIO Macroes */
#define GPIO_Pin_Config_Input(port,pin)		GPIO##port##_DIR &= ~(1<<pin)
#define GPIO_Pin_Config_Output(port,pin)	GPIO##port##_DIR |=  (1<<pin)

/* EINT Macroes */
#define EINT_Trigger_Edge(port,pin)			GPIO##port##_IS  &= ~(1<<pin)
#define EINT_Trigger_Both_Edge(port,pin)	GPIO##port##_IBE |= (1<<pin)
#define EINT_Trigger_Single_Edge(port,pin)	GPIO##port##_IBE &= ~(1<<pin)
#define EINT_Trigger_Fall_Edge(port,pin)	GPIO##port##_IEV |=  (1<<pin)
#define EINT_Trigger_Rise_Edge(port,pin)	GPIO##port##_IEV &= ~(1<<pin)

#define EINT_Trigger_Level(port,pin)		GPIO##port##_IS  |=  (1<<pin)
#define EINT_Trigger_High_Level(port,pin)	GPIO##port##_IEV |=  (1<<pin)
#define EINT_Trigger_Low_Level(port,pin)	GPIO##port##_IEV &= ~(1<<pin)

void Gpio0_Direction_Set(int pin, int dir)
{
	switch(dir)
	{
		case INPUT:		GPIO_Pin_Config_Input(0,pin);  break;
		case OUTPUT:	GPIO_Pin_Config_Output(0,pin); break;
	}
}

void Gpio1_Direction_Set(int pin, int dir)
{
	switch(dir)
	{
		case INPUT:		GPIO_Pin_Config_Input(1,pin);  break;
		case OUTPUT:	GPIO_Pin_Config_Output(1,pin); break;
	}
}

void Gpio2_Direction_Set(int pin, int dir)
{
	switch(dir)
	{
		case INPUT:		GPIO_Pin_Config_Input(2,pin);  break;
		case OUTPUT:	GPIO_Pin_Config_Output(2,pin); break;
	}
}

void Gpio3_Direction_Set(int pin, int dir)
{
	switch(dir)
	{
		case INPUT:		GPIO_Pin_Config_Input(3,pin);  break;
		case OUTPUT:	GPIO_Pin_Config_Output(3,pin); break;
	}
}

void Eint0_Level_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Level(0,pin);

	switch(option)
	{
		case LOW_LEVEL_TRIGGER:
		{
			EINT_Trigger_Low_Level(0,pin);
			break;
		}		

		case HIGH_LEVEL_TRIGGER:
		{
			EINT_Trigger_High_Level(0,pin);
			break;
		}		
	}	
}

void Eint0_Edge_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Edge(0,pin);
	
	switch(option)
	{
		case FALLING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(0,pin);
			EINT_Trigger_Fall_Edge(0,pin);	
			break;
		}	
				
		case RISING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(0,pin);
			EINT_Trigger_Rise_Edge(0,pin);	
			break;
		}	

		case BOTH_EDGE_TRIGGER:
		{
			EINT_Trigger_Both_Edge(0,pin);	
			break;
		}	
	}
}

void Eint1_Level_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Level(1,pin);

	switch(option)
	{
		case LOW_LEVEL_TRIGGER:
		{
			EINT_Trigger_Low_Level(1,pin);
			break;
		}		

		case HIGH_LEVEL_TRIGGER:
		{
			EINT_Trigger_High_Level(1,pin);
			break;
		}		
	}	
}

void Eint1_Edge_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Edge(1,pin);
	
	switch(option)
	{
		case FALLING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(1,pin);
			EINT_Trigger_Fall_Edge(1,pin);	
			break;
		}	
				
		case RISING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(1,pin);
			EINT_Trigger_Rise_Edge(1,pin);	
			break;
		}	

		case BOTH_EDGE_TRIGGER:
		{
			EINT_Trigger_Both_Edge(1,pin);	
			break;
		}	
	}
}

void Eint2_Level_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Level(2,pin);

	switch(option)
	{
		case LOW_LEVEL_TRIGGER:
		{
			EINT_Trigger_Low_Level(2,pin);
			break;
		}		

		case HIGH_LEVEL_TRIGGER:
		{
			EINT_Trigger_High_Level(2,pin);
			break;
		}		
	}	
}

void Eint2_Edge_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Edge(2,pin);
	
	switch(option)
	{
		case FALLING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(2,pin);
			EINT_Trigger_Fall_Edge(2,pin);	
			break;
		}	
				
		case RISING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(2,pin);
			EINT_Trigger_Rise_Edge(2,pin);	
			break;
		}	

		case BOTH_EDGE_TRIGGER:
		{
			EINT_Trigger_Both_Edge(2,pin);	
			break;
		}	
	}
}

void Eint3_Level_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Level(3,pin);

	switch(option)
	{
		case LOW_LEVEL_TRIGGER:
		{
			EINT_Trigger_Low_Level(3,pin);
			break;
		}		

		case HIGH_LEVEL_TRIGGER:
		{
			EINT_Trigger_High_Level(3,pin);
			break;
		}		
	}	
}

void Eint3_Edge_Trigger_Set(int pin, int option)
{
	EINT_Trigger_Edge(3,pin);
	
	switch(option)
	{
		case FALLING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(3,pin);
			EINT_Trigger_Fall_Edge(3,pin);	
			break;
		}	
				
		case RISING_EDGE_TRIGGER:
		{
			EINT_Trigger_Single_Edge(3,pin);
			EINT_Trigger_Rise_Edge(3,pin);	
			break;
		}	

		case BOTH_EDGE_TRIGGER:
		{
			EINT_Trigger_Both_Edge(3,pin);	
			break;
		}	
	}
}


