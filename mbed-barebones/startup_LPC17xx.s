/* LPC1768 Startup Script */

.syntax unified
.thumb

.section ".interrupt_vector_table"
.global __interrupt_vector_table
/* This interrupt vector table gets pulled in by the linker script
 * into flash right before the startup code */
__interrupt_vector_table:
.long _end_stack
.long Reset_Handler
.long NMI_Handler
.long HardFault_Handler
.long MemManage_Handler
.long BusFault_Handler
.long UsageFault_Handler
.long 0
.long 0
.long 0
.long 0
.long SVC_Handler
.long DebugMon_Handler
.long 0
.long PendSV_Handler
.long SysTick_Handler
/* External interrupts */
.long WDT_IRQHandler
.long TIMER0_IRQHandler
.long TIMER1_IRQHandler
.long TIMER2_IRQHandler
.long TIMER3_IRQHandler
.long UART0_IRQHandler
.long UART1_IRQHandler
.long UART2_IRQHandler
.long UART3_IRQHandler
.long PWM1_IRQHandler
.long I2C0_IRQHandler
.long I2C1_IRQHandler
.long I2C2_IRQHandler
.long SPI_IRQHandler
.long SSP0_IRQHandler
.long SSP1_IRQHandler
.long PLL0_IRQHandler
.long RTC_IRQHandler
.long EINT0_IRQHandler
.long EINT1_IRQHandler
.long EINT2_IRQHandler
.long EINT3_IRQHandler
.long ADC_IRQHandler
.long BOD_IRQHandler
.long USB_IRQHandler
.long CAN_IRQHandler
.long DMA_IRQHandler
.long I2S_IRQHandler
.long ENET_IRQHandler
.long RIT_IRQHandler
.long MCPWM_IRQHandler
.long QEI_IRQHandler
.long PLL1_IRQHandler

/* Addresses for all of the interrupts handlers above, can be pointed to a
 * real IRQ handler instead of falling through to the startup code. */
NMI_Handler:
HardFault_Handler: 
MemManage_Handler: 
BusFault_Handler: 
UsageFault_Handler:
SVC_Handler:
DebugMon_Handler:
PendSV_Handler:
SysTick_Handler:
WDT_IRQHandler:
TIMER0_IRQHandler:
TIMER1_IRQHandler:
TIMER2_IRQHandler:
TIMER3_IRQHandler:
UART0_IRQHandler:
UART1_IRQHandler:
UART2_IRQHandler:
UART3_IRQHandler:
PWM1_IRQHandler:
I2C0_IRQHandler:
I2C1_IRQHandler:
I2C2_IRQHandler:
SPI_IRQHandler:
SSP0_IRQHandler:
SSP1_IRQHandler:
PLL0_IRQHandler:
RTC_IRQHandler:
EINT0_IRQHandler:
EINT1_IRQHandler:
EINT2_IRQHandler:
EINT3_IRQHandler:
ADC_IRQHandler:
BOD_IRQHandler:
USB_IRQHandler:
CAN_IRQHandler:
DMA_IRQHandler:	 
I2S_IRQHandler:
ENET_IRQHandler:
RIT_IRQHandler:
MCPWM_IRQHandler:
QEI_IRQHandler:
PLL1_IRQHandler:

.section ".startup","x",%progbits
.thumb_func
.global _startup
.global Reset_Handler

Reset_Handler:
_startup:
	/* Clear the BSS section */ 
/*	mov r0, #0
	ldr r1, = _start_bss
	ldr r2, = _end_bss
	sub r2, #1
_loop:	cmp r1, r2
	str r0, [r1, #0]
	add r1, #4
	blo _loop */

	/* Jump to init() */
	ldr r0, =init
	blx r0

	/* Jump to main() */
	ldr r0, =main
	bx r0
	
.end
