/**
 * @file main.c
 * @brief TBSAR Main Application
 * @author Murali Challa
 * @date 2025-12-07
 */

#include <stdint.h>
#include "Scheduler.h"
#include "App.h"


/* =============================================================================
 * Scheduler Task: Every 10ms
 * ===========================================================================*/

void Scheduler_10ms(void)
{
     
     Ukey_All_Status();			
    Ukey_All_Clicks();	



}

/* =============================================================================
 * Scheduler Task: Every 20ms
 * ===========================================================================*/
void Scheduler_20ms(void)
{

}

/* =============================================================================
 * Scheduler Task: Every 50ms
 * ===========================================================================*/
void Scheduler_50ms(void)
{

}

/* =============================================================================
 * Scheduler Task: Every 100ms
 * ===========================================================================*/


void Scheduler_100ms(void)
{
        
    if (buz_timer > 0) {
        buz_timer--;
        if (buz_timer == 0) {
            Buz_Off();
        }
    }

    
    
    static uint8_t center_count = 0;
    static uint8_t center_long_handled = 0;

    if (uk_center_ == PRESS) {
        center_processing = 1;
        center_count++;

       
        if (center_count > 30 && center_long_handled == 0)
        {            
            if (SystemState == 1) 
            {
                System_off();
            }
            center_long_handled = 1;
        }
    }
    else { 
        if (center_processing) {
           
            if (center_long_handled == 0) {
                if (center_count > 0 && center_count < 30) {
                    
                    if (SystemState == 0) {
                        System_on();
                    }
                }
            }
            
            center_count = 0;
            center_long_handled = 0;
            center_processing = 0;
        }
    }
                static uint8_t up_press_count = 0;
                static uint8_t up_long_handled = 0;

                if (SystemState == 1 && center_processing == 0)
                {
                    if (uk_up_ == PRESS)
                    {
                        if (up_long_handled == 0)
                        {
                            up_press_count++;

                            if (up_press_count >= 20 && menu_state == MENU_NONE)
                            {
                                menu_state = MENU_SET_SOURCE;
                                up_long_handled = 1;

                                Lcd_Clear();
                                Lcd_Backlight_On();
                                RGB_Update();

                                Ukey_All_Clicks_Reset();   // OK here
                            }
                        }
                    }
                    else
                    {
                        up_press_count = 0;
                        up_long_handled = 0;
                    }
                }



       

                    if (menu_state == MENU_SET_SOURCE)
                {
                    Lcd_Set_Cursor(1,1);
                    lcd_printf("Set Source");



                    Lcd_Set_Cursor(2,1);
                    lcd_printf("%s   ", Audio_Source[AudioSource]);

                    Lcd_Set_Cursor(2,13);
                    lcd_printf("V:%d", Load_Config_Version());

                    if (uk_right_clicks > 0)
                    {
                        AudioSource = (AudioSource + 1) % SRC_MAX;
                        uk_up_clicks = 0;
                    }

                    if (uk_left_clicks > 0)
                    {
                        AudioSource = (AudioSource == 0) ? (SRC_MAX - 1) : (AudioSource - 1);
                        uk_down_clicks = 0;
                    }

                    if (uk_center_clicks > 0)
                    {
                        uk_center_clicks = 0;

                        Save_AudioSource_To_Eeprom(AudioSource);

                        menu_state = MENU_SET_VOLUME;   // 👉 GO TO VOLUME
                        Lcd_Clear();
                    }
                    
                    
                    RGB_Update();
                    Ukey_All_Clicks_Reset();
                    return;
                }

                if (menu_state == MENU_SET_VOLUME)
                {
                    Lcd_Set_Cursor(1,1);
                    lcd_printf("Set Volume");

                    Lcd_Set_Cursor(2,1);
                    lcd_printf("%d%%   ", Volume);

                    Lcd_Set_Cursor(2,13);
                    lcd_printf("V:%d", Load_Config_Version());

                    if (uk_right_clicks > 0)
                    {
                        if (Volume <= 90) Volume += 10;
                        else Volume = 100;

                        uk_right_clicks = 0;
                    }

                    if (uk_left_clicks > 0)
                    {
                        if (Volume >= 10) Volume -= 10;
                        else Volume = 0;

                        uk_left_clicks = 0;
                    }

                    if (uk_center_clicks > 0)
                    {
                        uk_center_clicks = 0;

                        Save_Volume_To_Eeprom(Volume);

                        menu_state = MENU_NONE;   // 👉 EXIT MENU
                        RGB_Update();
                        Update_Display();
                    }

                    Ukey_All_Clicks_Reset();
                    return;
                }



                    if (uk_up_clicks > 0) 
                    {
                        AudioSource = (AudioSource + 1) % SRC_MAX;
                        uk_up_clicks = 0;
                        RGB_Update();
                    }
                    if (uk_down_clicks > 0) 
                    {
                        AudioSource = (AudioSource == 0) ? (SRC_MAX - 1) : (AudioSource - 1);
                        uk_down_clicks = 0;
                        RGB_Update();
                    }

                
                    if (uk_right_clicks > 0)
                    {
                        if (Volume <= 90)
                        {
                             Volume += 10;
                          
                        }
                        else if(Volume == 100)
                        { 
                            Buz_ShortBeep();
                            Lcd_Set_Cursor(2,10);
                            lcd_printf("MAX");
                        }

                        uk_right_clicks = 0;
                    }

                    if (uk_left_clicks > 0) 
                    {
                        if (Volume >= 10)
                        { 
                            Volume -= 10;
                        }
                        else  if(Volume == 0)                       
                        { 
                            Buz_ShortBeep();
                            Lcd_Set_Cursor(2,10);
                            lcd_printf("MAX");
                        }

                        uk_left_clicks = 0;
                    }


                
                Update_Display();
            

    
}


 
/* =============================================================================
 * Main Function
 * ===========================================================================*/
int main(void) 
{
     
    /* Initialize hardware */
    Scheduler_Init();
    Buz_Config();      /* on-board buzzer calm at startup */
    Monitor_Config(); /* UART monitor initialization */
    Lcd_Config();     /* LCD hardware initialization */ 
    Rgb_Config();
    Eeprom_Config();
   
 

     
    AudioSource = Load_AudioSource_From_Eeprom();
    Volume =Load_Volume_From_Eeprom(); 
    SystemState = 0;

    RGB_Update();
    Update_Display();

   
    while(1) 
    {
        __asm volatile("wfi");  
    }   

    return 0;
}

