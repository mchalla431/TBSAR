#include "Sleep.h"
#include "Sleep_Config.h"

void Sleep_Enter(void)
{
    // Enter sleep (Wait For Interrupt)
    __WFI();
}