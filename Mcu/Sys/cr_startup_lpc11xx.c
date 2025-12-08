/**************************************************************************//**
 * @file     startup_ARMCM0.c
 * @brief    CMSIS Core Device Startup File for
 *           ARMCM0 Device
 * @version  V5.3.1
 * @date     09. July 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

#include "lpc11xx.h"


/*----------------------------------------------------------------------------
  Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __copy_table_start__;
extern uint32_t __copy_table_end__;
extern uint32_t __zero_table_start__;
extern uint32_t __zero_table_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );


/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern void _start     (void) __attribute__((noreturn)); /* PreeMain (C library entry point) */
extern int main(void);


/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Default_Handler(void) __attribute__ ((noreturn));
void Reset_Handler  (void) __attribute__ ((noreturn));

void NMI_Handler            (void) __attribute__  ((noreturn));
void HardFault_Handler      (void) __attribute__  ((noreturn));
void SVC_Handler            (void) __attribute__  ((noreturn));
void PendSV_Handler         (void) __attribute__  ((noreturn));
void SysTick_Handler        (void);  /* Allow custom implementation for scheduler */
void WAKEUP1_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP2_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP3_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP4_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP5_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP6_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP7_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP8_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP9_IRQHandler     (void) __attribute__  ((noreturn));
void WAKEUP10_IRQHandler    (void) __attribute__  ((noreturn));
void WAKEUP11_IRQHandler    (void) __attribute__  ((noreturn));
void WAKEUP12_IRQHandler    (void) __attribute__  ((noreturn));
void WAKEUP13_IRQHandler    (void) __attribute__  ((noreturn));
void CAN_IRQHandler    		(void) __attribute__  ((noreturn));
void SSP1_IRQHandler    	(void) __attribute__  ((noreturn));
void I2C_IRQHandler    		(void) __attribute__  ((noreturn));
void TIMER16_0_IRQHandler   (void) __attribute__  ((noreturn));
void TIMER16_1_IRQHandler   (void) __attribute__  ((noreturn));
void TIMER32_0_IRQHandler   (void) __attribute__  ((noreturn));
void TIMER32_1_IRQHandler   (void) __attribute__  ((noreturn));
void SSP0_IRQHandler    	(void) __attribute__  ((noreturn));
void UART_IRQHandler    	(void) __attribute__  ((noreturn));


void Reserved1_IRQHandler   (void) __attribute__   ((noreturn));
void Rserved2_IRQHandler    (void) __attribute__   ((noreturn));
void ADC_IRQHandler    		(void) __attribute__   ((noreturn));
void WDT_IRQHandler    		(void) __attribute__   ((noreturn));
void BOD_IRQHandler    		(void) __attribute__   ((noreturn));
void Reserved3_IRQHandler   (void) __attribute__   ((noreturn));
void PIOINT3_IRQHandler    	(void) __attribute__   ((noreturn));
void PIOINT2_IRQHandler    	(void) __attribute__   ((noreturn));
void PIOINT1_IRQHandler   	(void) __attribute__   ((noreturn));
void PIOINT0_IRQHandler	    (void) __attribute__   ((noreturn));


/*----------------------------------------------------------------------------
  User Initial Stack & Heap
 *----------------------------------------------------------------------------*/
//<h> Stack Configuration
//  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
//</h>
#define  __STACK_SIZE  0x00000200
static uint8_t stack[__STACK_SIZE] __attribute__ ((aligned(8), used, section(".stack")));

//<h> Heap Configuration
//  <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
//</h>
#define  __HEAP_SIZE   0x00000200
#if __HEAP_SIZE > 0
static uint8_t heap[__HEAP_SIZE]   __attribute__ ((aligned(8), used, section(".heap")));
#endif


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak));  /* Implemented in Scheduler.c */


void WAKEUP1_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP2_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP3_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP4_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP5_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP6_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP7_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP8_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP9_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP10_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP11_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP12_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void WAKEUP13_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler"))); 
void CAN_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void SSP1_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_0_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_1_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER32_0_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER32_1_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void SSP0_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));


void Reserved1_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void Rserved2_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler"))); 
void ADC_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void WDT_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void BOD_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void Reserved3_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler"))); 
void PIOINT3_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void PIOINT2_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void PIOINT1_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void PIOINT0_IRQHandler	    (void) __attribute__ ((weak, alias("Default_Handler")));


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const pFunc __Vectors[ 48];
       const pFunc __Vectors[ 48] __attribute__((used, section(".vectors"))) = {
  (pFunc)(&__StackTop),                     /*     Initial Stack Pointer */
  Reset_Handler,                            /*     Reset Handler */
  NMI_Handler,                              /* -14 NMI Handler */
  HardFault_Handler,                        /* -13 Hard Fault Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  SVC_Handler,                              /*  -5 SVCall Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  PendSV_Handler,                           /*  -2 PendSV Handler */
  SysTick_Handler,                          /*  -1 SysTick Handler */

  /* Interrupts */
                                            /* Interrupts 10 .. 31 are left out */
	WAKEUP1_IRQHandler,
 	WAKEUP2_IRQHandler,
 	WAKEUP3_IRQHandler,
 	WAKEUP4_IRQHandler,
 	WAKEUP5_IRQHandler,
 	WAKEUP6_IRQHandler,
 	WAKEUP7_IRQHandler,
 	WAKEUP8_IRQHandler,
 	WAKEUP9_IRQHandler,
 	WAKEUP10_IRQHandler,
 	WAKEUP11_IRQHandler,
 	WAKEUP12_IRQHandler,
 	WAKEUP13_IRQHandler,
 	CAN_IRQHandler,
	SSP1_IRQHandler,
	I2C_IRQHandler,
	TIMER16_0_IRQHandler, 
	TIMER16_1_IRQHandler, 
	TIMER32_0_IRQHandler, 
	TIMER32_1_IRQHandler, 
	SSP0_IRQHandler, 
	UART_IRQHandler, 
	Reserved1_IRQHandler,
	Rserved2_IRQHandler,
	ADC_IRQHandler, 
	WDT_IRQHandler, 
	BOD_IRQHandler, 
	Reserved3_IRQHandler,
	PIOINT3_IRQHandler, 
	PIOINT2_IRQHandler, 
	PIOINT1_IRQHandler, 
	PIOINT0_IRQHandler 
};


/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void) {
  uint32_t *pSrc, *pDest;
  uint32_t *pTable __attribute__((unused));

/* Firstly it copies data from read only memory to RAM.
 * There are two schemes to copy. One can copy more than one sections.
 * Another can copy only one section. The former scheme needs more
 * instructions and read-only data to implement than the latter.
 * Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.
 */

#ifdef __STARTUP_COPY_MULTIPLE
/* Multiple sections scheme.
 *
 * Between symbol address __copy_table_start__ and __copy_table_end__,
 * there are array of triplets, each of which specify:
 *   offset 0: LMA of start of a section to copy from
 *   offset 4: VMA of start of a section to copy to
 *   offset 8: size of the section to copy. Must be multiply of 4
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
  pTable = &__copy_table_start__;

  for (; pTable < &__copy_table_end__; pTable = pTable + 3) {
    pSrc  = (uint32_t*)*(pTable + 0);
    pDest = (uint32_t*)*(pTable + 1);
    for (; pDest < (uint32_t*)(*(pTable + 1) + *(pTable + 2)) ; ) {
      *pDest++ = *pSrc++;
    }
  }
#else
/* Single section scheme.
 *
 * The ranges of copy from/to are specified by following symbols
 *   __etext: LMA of start of the section to copy from. Usually end of text
 *   __data_start__: VMA of start of the section to copy to
 *   __data_end__: VMA of end of the section to copy to
 *
 * All addresses must be aligned to 4 bytes boundary.
 */
  pSrc  = &__etext;
  pDest = &__data_start__;

  for ( ; pDest < &__data_end__ ; ) {
    *pDest++ = *pSrc++;
  }
#endif /*__STARTUP_COPY_MULTIPLE */

/* This part of work usually is done in C library startup code.
 * Otherwise, define this macro to enable it in this startup.
 *
 * There are two schemes too.
 * One can clear multiple BSS sections. Another can only clear one section.
 * The former is more size expensive than the latter.
 *
 * Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 * Otherwise define macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/* Multiple sections scheme.
 *
 * Between symbol address __copy_table_start__ and __copy_table_end__,
 * there are array of tuples specifying:
 *   offset 0: Start of a BSS section
 *   offset 4: Size of this BSS section. Must be multiply of 4
 */
  pTable = &__zero_table_start__;

  for (; pTable < &__zero_table_end__; pTable = pTable + 2) {
    pDest = (uint32_t*)*(pTable + 0);
    for (; pDest < (uint32_t*)(*(pTable + 0) + *(pTable + 1)) ; ) {
      *pDest++ = 0;
    }
  }
#elif defined (__STARTUP_CLEAR_BSS)
/* Single BSS section scheme.
 *
 * The BSS section is specified by following symbols
 *   __bss_start__: start of the BSS section.
 *   __bss_end__: end of the BSS section.
 *
 * Both addresses must be aligned to 4 bytes boundary.
 */
  pDest = &__bss_start__;

  for ( ; pDest < &__bss_end__ ; ) {
    *pDest++ = 0UL;
  }
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

  SystemInit();                             /* CMSIS System Initialization */
  main();                                  /* Call main application entry point */
  while(1);                                /* Infinite loop if main returns */
}


/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void) 
{

  while(1);
}

