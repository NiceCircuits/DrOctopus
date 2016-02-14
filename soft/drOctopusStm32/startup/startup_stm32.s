/**
  ******************************************************************************
  * @file      startup_stm32.s
  * @author    Ac6
  * @version   V1.0.0
  * @date      12-June-2014
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m4
  .thumb

.global	g_pfnVectors
.global	Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word	_sidata
/* start address for the .data section. defined in linker script */
.word	_sdata
/* end address for the .data section. defined in linker script */
.word	_edata
/* start address for the .bss section. defined in linker script */
.word	_sbss
/* end address for the .bss section. defined in linker script */
.word	_ebss

.equ  BootRAM,        0xF1E0F85F
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section	.text.Reset_Handler
	.weak	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:

/* Copy the data segment initializers from flash to SRAM */
  movs	r1, #0
  b	LoopCopyDataInit

CopyDataInit:
	ldr	r3, =_sidata
	ldr	r3, [r3, r1]
	str	r3, [r0, r1]
	adds	r1, r1, #4

LoopCopyDataInit:
	ldr	r0, =_sdata
	ldr	r3, =_edata
	adds	r2, r0, r1
	cmp	r2, r3
	bcc	CopyDataInit
	ldr	r2, =_sbss
	b	LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
	movs r3, #0
 	str  r3, [r2]
	adds r2, r2, #4

LoopFillZerobss:
	ldr	r3, = _ebss
	cmp	r2, r3
	bcc	FillZerobss

/* Call the clock system intitialization function.*/
    bl  SystemInit
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
	bl	main

LoopForever:
    b LoopForever

.size	Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
	.size	Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex-M.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
 	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
	.word	_estack
	.word	Reset_Handler
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	SysTick_Handler
	.word	0                                         // 0: Window WatchDog
	.word	0                                         // 1: PVD through EXTI Line detection
	.word	0                                         // 2: Tamper and TimeStamps through the EXTI line
	.word	0                                         // 3: RTC Wakeup through the EXTI line
	.word	0                                         // 4: FLASH
	.word	0                                         // 5: RCC
	.word	0                                         // 6: EXTI Line0
	.word	0                                         // 7: EXTI Line1
	.word	0                                         // 8: EXTI Line2 and Touch Sense controller
	.word	0                                         // 9: EXTI Line3
	.word	0                                         // 10: EXTI Line4
	.word	0                                         // 11: DMA1 Channel 1
	.word	0                                         // 12: DMA1 Channel 2
	.word	0                                         // 13: DMA1 Channel 3
	.word	0                                         // 14: DMA1 Channel 4
	.word	0                                         // 15: DMA1 Channel 5
	.word	0                                         // 16: DMA1 Channel 6
	.word	0                                         // 17: DMA1 Channel 7
	.word	0                                         // 18: ADC1 and ADC2
	.word	0                                         // 19: USB Device High Priority or CAN TX
	.word	0                                         // 20: USB Device Low Priority or CAN RX0
	.word	0                                         // 21: CAN RX1
	.word	0                                         // 22: CAN SCE
	.word	0                                         // 23: External Line[9:5]s
	.word	0                                         // 24: TIM1 Break and TIM15
	.word	TIM1_UP_TIM16_IRQHandler                  // 25: TIM1 Update and TIM16
	.word	0                                         // 26: TIM1 Trigger and Commutation and TIM17
	.word	0                                         // 27: TIM1 Capture Compare
	.word	0                                         // 28: TIM2
	.word	0                                         // 29: TIM3
	.word	0                                         // 30: TIM4
	.word	0                                         // 31: I2C1 Event
	.word	0                                         // 32: I2C1 Error
	.word	0                                         // 33: I2C2 Event
	.word	0                                         // 34: I2C2 Error
	.word	0                                         // 35: SPI1
	.word	0                                         // 36: SPI2
	.word	0                                         // 37: USART1
	.word	0                                         // 38: USART2
	.word	0                                         // 39: USART3
	.word	0                                         // 40: External Line[15:10]s
	.word	0                                         // 41: RTC Alarm (A and B) through EXTI Line
	.word	0                                         // 42: USB Wakeup through EXTI line
	.word	0                                         // 43: TIM8 Break
	.word	0                                         // 44: TIM8 Update
	.word	0                                         // 45: TIM8 Trigger and Commutation
	.word	0                                         // 46: TIM8 Capture Compare
	.word	0                                         // 47: ADC3
	.word	0                                         // 48: FMC
	.word	0                                         // 49: Reserved
	.word	0                                         // 50: Reserved
	.word	0                                         // 51: SPI3
	.word	0                                         // 52: UART4
	.word	0                                         // 53: UART5
	.word	0                                         // 54: TIM6 and DAC1&2 underrun errors
	.word	0                                         // 55: TIM7
	.word	0                                         // 56: DMA2 Channel 1
	.word	0                                         // 57: DMA2 Channel 2
	.word	0                                         // 58: DMA2 Channel 3
	.word	0                                         // 59: DMA2 Channel 4
	.word	0                                         // 60: DMA2 Channel 5
	.word	0                                         // 61: ADC4
	.word	0                                         // 62: Reserved
	.word	0                                         // 63: Reserved
	.word	0                                         // 64: COMP1, COMP2 and COMP3
	.word	0                                         // 65: COMP4, COMP5 and COMP6
	.word	0                                         // 66: COMP7
	.word	0                                         // 67: Reserved
	.word	0                                         // 68: Reserved
	.word	0                                         // 69: Reserved
	.word	0                                         // 70: Reserved
	.word	0                                         // 71: Reserved
	.word	0                                         // 72: I2C3 Event
	.word	0                                         // 73: I2C3 Error
	.word	0                                         // 74: USB High Priority remap
	.word	0                                         // 75: USB Low Priority remap
	.word	0                                         // 76: USB Wakeup remap through EXTI
	.word	0                                         // 77: TIM20 Break
	.word	0                                         // 78: TIM20 Update
	.word	0                                         // 79: TIM20 Trigger and Commutation
	.word	0                                         // 80: TIM20 Capture Compare
	.word	0                                         // 81: FPU

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  	.weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

  	.weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

  	.weak	MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler

  	.weak	BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler

	.weak	UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	SystemInit

/************************ (C) COPYRIGHT Ac6 *****END OF FILE****/
