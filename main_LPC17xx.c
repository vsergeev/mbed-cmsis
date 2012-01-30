/**************************************************************************//**
 * @file     main.c
 * @brief    CMSIS Cortex-M3 Blinky example
 *           Blink a LED using CM3 SysTick
 * @version  V1.03
 * @date     24. September 2009
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include "LPC17xx.h"

/*
 * To see how the LEDs are connected, refer to:
 * http://mbed.org/projects/libraries/svn/mbed/trunk/PinNames.h
 */
#define LED1 	(1<<18)		/* LED1 = P1_18 */
#define LED2 	(1<<20)		/* LED2 = P1_20 */
#define LED3 	(1<<21)		/* LED3 = P1_21 */
#define LED4 	(1<<23)		/* LED4 = P1_23 */

volatile uint32_t msTicks;		/* counts 1ms timeTicks */

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
	msTicks++;			/* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delay (uint32_t dlyTicks) {
	uint32_t curTicks;

	curTicks = msTicks;
	while ((msTicks - curTicks) < dlyTicks);
}

/*------------------------------------------------------------------------------
  configer LED pins
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Config(void) {
	LPC_GPIO1->FIODIR = 0xFFFFFFFF;		/* LEDs PORT1 are Output */
}

/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_On (uint32_t led) {
	LPC_GPIO1->FIOPIN |=  (led);		/* Turn On LED */
}


/*------------------------------------------------------------------------------
  Switch off LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Off (uint32_t led) {
	LPC_GPIO1->FIOPIN &= ~(led);		/* Turn Off LED */
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	/* Adjust SystemCoreClock global according to clock registers */
	SystemCoreClockUpdate();

	if (SysTick_Config(SystemCoreClock / 1000)) {	/* Setup SysTick Timer for 1 msec interrupts  */
		while (1);				/* Capture error */
	}

	LED_Config();

	while(1) {
		LED_On(LED1);			/* Turn on the LED */
		Delay(100);			/* Delay 100 Msec */
		LED_Off(LED1);			/* Turn off the LED */
		Delay(100);			/* Delay 100 Msec */
	}
}

