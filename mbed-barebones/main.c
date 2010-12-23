#include "LPC17xx.h"

void init(void) {
	/* Based on CMSIS SystemInit() for LPC17xx */
	/* Also see chapters 3 and 4 of LPC17xx User Manual, UM10360 */

	/* SCS: OSCRANGE=1 (12MHz on mbed), OSCEN=1 */
	LPC_SC->SCS = 0x20;
	/* Wait for the main oscillator to ready */
	while (!(LPC_SC->SCS & (1<<6)))
		;
	
	/* CLKSRCSEL: CLKSRC=01 for main oscillator as PLL0 source */
	LPC_SC->CLKSRCSEL = 0x01;

	/* CCLKCFG: CCLKSEL = 3, PLL0 is divided by 4 to provide CPU clock */
	LPC_SC->CCLKCFG = 0x03;
	
	/* PCKSEL0 and PCKSEL1 = 00, all peripherals get CCLK/4 */ 
	LPC_SC->PCLKSEL0 = 0x0;
	LPC_SC->PCLKSEL1 = 0x0;

	/* PLL0 Configuration, taken from CMSIS LPC17xx example */
	LPC_SC->PLL0CFG = 0x00050063;
	/* PLL Feed */
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
	/* Enable PLL0 */
	LPC_SC->PLL0CON = 0x01;
	/* PLL Feed */
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
	/* Wait for PLL0 lock */
	while (!(LPC_SC->PLL0STAT & (1<<26)))
		;
	/* Enable and connect PLL0 */
	LPC_SC->PLL0CON = 0x03;
	/* PLL Feed */
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
	/* Wait for PLL1 enable and connect */
	while (!(LPC_SC->PLL0STAT & ((1<<25) | (1<<24))))
		;

	/* PLL1 Configuration, taken from CMSIS LPC17xx example */
	LPC_SC->PLL1CFG = 0x00000023;
	/* PLL Feed */
	LPC_SC->PLL1FEED = 0xAA;
	LPC_SC->PLL1FEED = 0x55;
	/* Enable PLL1 */
	LPC_SC->PLL1CON = 0x01;
	/* PLL Feed */
	LPC_SC->PLL1FEED = 0xAA;
	LPC_SC->PLL1FEED = 0x55;
	/* Wait for PLL1 lock */
	while (!(LPC_SC->PLL1STAT & (1<<10)))
		;
	/* Enable and connect PLL1 */
	LPC_SC->PLL1CON = 0x03;
	/* PLL Feed */
	LPC_SC->PLL1FEED = 0xAA;
	LPC_SC->PLL1FEED = 0x55;
	/* Wait for PLL1 enable and connect */
	while (!(LPC_SC->PLL1STAT & ((1<<9) | (1<<8))))
		;

	/* Additional settings */
	//LPC_SC->USBCLKCFG = ...;
	//LPC_SC->PCONP = ...;
	//LPC_SC->CLKOUTCFG = ...;
	//LPC_SC->FLASHCFG = ...;
}

int main(void) {
	/* Your code goes here */

	/* Turn on all of port 1 (this includes the 4 mbed LEDs) */
	LPC_GPIO1->FIODIR = 0xFFFFFFFF;
	LPC_GPIO1->FIOPIN = 0xFFFFFFFF;
	while (1)
		;
}
