 




#ifndef APP_H
#define APP_H

#include <stdint.h>

#include "Buz_Config.h"
#include "Buz.h"

#include "Monitor_Config.h"

#include "Lcd_Config.h"
#include "Lcd.h"

#include "Rgb.h"
#include "Rgb_Config.h"

#include "Ukeys.h"
#include "Ukeys_Config.h"

#include "Eeprom.h"
#include "Eeprom_Config.h"



 #define EEPROM_AUDIO_SRC_ADDR   0x22
 #define EEPROM_VOLUME_ADDR      0x21
 #define EEPROM_VERSION_ADDR     0x20 
/* ================= TYPES ================= */

typedef enum {
    SRC_BT = 0,
    SRC_OPT,
    SRC_USB,
    SRC_AUX,
    SRC_MAX
} AudioSource_t;

typedef enum {
    MENU_NONE = 0,
    MENU_SET_SOURCE,
    MENU_SET_VOLUME
} MenuState_t;

/* ================= GLOBAL STATE (extern only) ================= */

extern uint8_t SystemState;
extern uint8_t center_processing;

extern AudioSource_t AudioSource;
extern uint8_t Volume;
extern MenuState_t menu_state;
extern uint8_t  buz_timer;

extern const char *Audio_Source[SRC_MAX];


/* ================= EEPROM APIs ================= */

AudioSource_t Load_AudioSource_From_Eeprom(void);
void Save_AudioSource_To_Eeprom(AudioSource_t src);

uint8_t Load_Volume_From_Eeprom(void);
void Save_Volume_To_Eeprom(uint8_t vol);

uint8_t Load_Config_Version(void);
void Increment_Config_Version(void);

void System_on(void);
void System_off(void);
void RGB_Update(void);
void Update_Display(void);
void Buz_ShortBeep(void);


#endif /* APP_H */
