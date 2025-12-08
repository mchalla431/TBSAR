/**
 * @file Rotary.c
 * @brief Rotary encoder driver with interrupt-driven quadrature decoding
 * 
 * Features:
 * - Phase A/B quadrature decoding via GPIO Port 1 interrupt (rising edge)
 * - Switch click detection via polling in 10ms scheduler
 * - Hardware debouncing: hysteresis enabled on all pins
 * - Software debouncing: pin state confirmation in ISR (10 iterations)
 */

#include "Rotary.h"
#include "Monitor.h"

/* Rotary encoder hardware pins */
#define ROTARY_PHASE_A_PIN      5   /* PIO1_5 - interrupt (rising edge) */
#define ROTARY_PHASE_B_PIN      8   /* PIO1_8 - polled in ISR */
#define ROTARY_SWITCH_PIN       7   /* PIO0_7 - polled in scheduler */

/* Global rotary encoder variables */
int32_t rcount = 0;       /* Rotary encoder count (increments/decrements) */
uint8_t rclicks = 0;      /* Switch click counter */
static int8_t rdir = 0;    /* Rotation direction: 1=CW, -1=CCW, 0=no motion */


void Rotary_Clicks(void)
{
	static uint8_t switch_state_prev = 1;  /* Previous switch state (1=released, 0=pressed) */
	uint8_t switch_state_curr;
	
	/* Read current switch state (active low: 0=pressed, 1=released) */
	switch_state_curr = Gpio0_Pin_Get(ROTARY_SWITCH_PIN);
	
	/* Detect falling edge (press): transition from 1 to 0 */
	if ((switch_state_prev == 1) && (switch_state_curr == 0))
	{
		rclicks++;
	}
	
	/* Save current state for next call */
	switch_state_prev = switch_state_curr;
}

void PIOINT1_IRQHandler(void)
{
	uint8_t phase_a, phase_b;
	uint8_t phase_a_conf, phase_b_conf;
	int ctr;
	
	/* Read pin states */
	phase_a = Gpio1_Pin_Get(ROTARY_PHASE_A_PIN);
	phase_b = Gpio1_Pin_Get(ROTARY_PHASE_B_PIN);
	
	/* Stabilization loop (multiple reads to let pins settle) */
	for (ctr = 0; ctr < 10; ctr++)
	{
		phase_a_conf = Gpio1_Pin_Get(ROTARY_PHASE_A_PIN);
		phase_b_conf = Gpio1_Pin_Get(ROTARY_PHASE_B_PIN);
	}
	
	/* Only process if pins are stable (confirm read matches initial read) */
	if (phase_a != phase_a_conf || phase_b != phase_b_conf)
	{
		/* Pins still bouncing - clear flag and return */
		Eint1_Reset(ROTARY_PHASE_A_PIN);
		return;
	}
	
	/* Pins are stable - determine direction and update count */
	if (phase_a == phase_b)
	{
		/* Phases match: Clockwise rotation */
		rcount++;
		rdir = 1;
	}
	else
	{
		/* Phases don't match: Counter-clockwise rotation */
		rcount--;
		rdir = -1;
	}
	
	/* Clear interrupt flag for Port 1, Pin 5 */
	Eint1_Reset(ROTARY_PHASE_A_PIN);
}

void Rotary_Monitor(void)
{
	uart_printf("\rRotary:Cnt=");
	uart_printf("%d", rcount);
	uart_printf(" | Clicks=");
	uart_printf("%d", rclicks);
	uart_printf("   ");
}
