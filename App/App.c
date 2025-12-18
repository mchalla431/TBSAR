#include "App.h"

/* Global variable definitions (declared as extern in App.h) */
uint8_t center_processing = 0;
uint8_t SystemState = 0;
uint8_t buz_timer = 0;

const char *Audio_Source[SRC_MAX] = {"BT", "OPT", "USB", "AUX"};
AudioSource_t AudioSource = SRC_BT;
uint8_t Volume = 40;
MenuState_t menu_state = MENU_NONE;



void Buz_ShortBeep(void)
{
    Buz_On();
    buz_timer = 4;   
}


void RGB_Update(void)
{
    if (SystemState == 0)
    {
        Rgb_Set(RGB_RED);
        return;
    }
    if (menu_state != MENU_NONE)
    {
        Rgb_Set(RGB_NONE);
        return;
    }

    switch (AudioSource)
    {
        case SRC_BT:  Rgb_Set(RGB_BLUE);    break;
        case SRC_OPT: Rgb_Set(RGB_GREEN);   break;
        case SRC_USB: Rgb_Set(RGB_WHITE);   break;
        case SRC_AUX: Rgb_Set(RGB_MAGENTA); break;
        default:      Rgb_Set(RGB_RED);     break;
    }
}

void System_on(void)
{
    Buz_ShortBeep();
    AudioSource = Load_AudioSource_From_Eeprom();   
    Volume = Load_Volume_From_Eeprom();   
    SystemState = 1;
    Lcd_Backlight_On();
    RGB_Update();
    
}
 

void System_off(void)
{
    SystemState = 0;
    menu_state = MENU_NONE;
    Lcd_Clear();
    Lcd_Backlight_Off();
    RGB_Update();
    Buz_ShortBeep();
}

void Update_Display(void)
{
     static AudioSource_t last_src = SRC_MAX;
    static uint8_t last_vol = 255;

    if (SystemState == 0)
        return;

    if (last_src != AudioSource || last_vol != Volume)
    {
        Lcd_Clear();

        Lcd_Set_Cursor(1,1);
        lcd_printf("Audio:%-4s", Audio_Source[AudioSource]);

        Lcd_Set_Cursor(2,1);
        lcd_printf("Vol:%3d%%", Volume);

        last_src = AudioSource;
        last_vol = Volume;
    }

    
}

void Save_AudioSource_To_Eeprom(AudioSource_t src)
{
    uint8_t old;

    Eeprom_Bytes_Read(EEPROM_AUDIO_SRC_ADDR, &old, 1);

    if (old != src)   // ✅ write only if changed
    {
        uint8_t data = (uint8_t)src;
        Eeprom_Bytes_Write(EEPROM_AUDIO_SRC_ADDR, &data, 1);

          Increment_Config_Version(); 
    }
}


AudioSource_t Load_AudioSource_From_Eeprom(void)
{
    uint8_t data = 0xFF;

    Eeprom_Bytes_Read(EEPROM_AUDIO_SRC_ADDR, &data, 1);
    Eeprom_Monitor_Read(&data, 1);   

    if (data < SRC_MAX)
    {
        return (AudioSource_t)data;
    }
    else
    {
        return SRC_BT;   // safe default
    }
}

void Save_Volume_To_Eeprom(uint8_t vol)
{
    uint8_t old;

    if (vol > 100)
        vol = 100;

    Eeprom_Bytes_Read(EEPROM_VOLUME_ADDR, &old, 1);

    if (old != vol)
    {
        Eeprom_Bytes_Write(EEPROM_VOLUME_ADDR, &vol, 1);
        
          Increment_Config_Version(); 
    }
}

uint8_t Load_Volume_From_Eeprom(void)
{
    uint8_t vol = 0xFF;

    Eeprom_Bytes_Read(EEPROM_VOLUME_ADDR, &vol, 1);

    if (vol <= 100)
        return vol;
    else
        return 40;   // default volume
}

uint8_t Load_Config_Version(void)
{
    uint8_t ver = 0xFF;

    Eeprom_Bytes_Read(EEPROM_VERSION_ADDR, &ver, 1);

    if (ver == 0xFF)   // uninitialized EEPROM
        return 0;

    return ver;
}

void Increment_Config_Version(void)
{
    uint8_t ver = Load_Config_Version();

    if (ver < 255)     // avoid overflow
        ver++;
    else
        ver = 0;       // or keep max, your choice

    Eeprom_Bytes_Write(EEPROM_VERSION_ADDR, &ver, 1);
}