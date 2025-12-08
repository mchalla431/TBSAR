#ifndef _CAN_H_
#define _CAN_H_

#include <stdint.h>
#include "lpc11xx.h"


#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

typedef struct  
{
  uint32_t  id;                       /* 29 bit identifier                    */
  uint8_t   data[8];                  /* Data field                           */
  uint8_t   len;                      /* Length of data field in bytes        */
  uint8_t   format;                   /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
  uint8_t   type;                     /* 0 - DATA FRAME, 1 - REMOTE FRAME     */
} CAN_msg;


/* Functions Prototypes */
void Can_Init(void);
void Can_Message_Send(uint32_t id, uint8_t *dbuf, uint8_t len,  uint8_t format);
void Can_Message_Receive(CAN_msg *msg);
void Can_Accept_Filter_Set(uint32_t id, uint8_t format);  
void Can_Test_Mode(void); 
int Can_Transmit_Status_Get(void);
int Can_Receive_Status_Get(void);


#endif // _CAN_H_


