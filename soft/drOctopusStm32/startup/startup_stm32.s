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
	.word	WWDG_IRQHandler                   // 0: Window WatchDog
	.word	PVD_IRQHandler                    // 1: PVD through EXTI Line detection
	.word	TAMP_STAMP_IRQHandler             // 2: Tamper and TimeStamps through the EXTI line
	.word	RTC_WKUP_IRQHandler               // 3: RTC Wakeup through the EXTI line
	.word	FLASH_IRQHandler                  // 4: FLASH
	.word	RCC_IRQHandler                    // 5: RCC
	.word	EXTI0_IRQHandler                  // 6: EXTI Line0
	.word	EXTI1_IRQHandler                  // 7: EXTI Line1
	.word	EXTI2_TSC_IRQHandler              // 8: EXTI Line2 and Touch Sense controller
	.word	EXTI3_IRQHandler                  // 9: EXTI Line3
	.word	EXTI4_IRQHandler                  // 10: EXTI Line4
	.word	DMA1_Channel1_IRQHandler          // 11: DMA1 Channel 1
	.word	DMA1_Channel2_IRQHandler          // 12: DMA1 Channel 2
	.word	DMA1_Channel3_IRQHandler          // 13: DMA1 Channel 3
	.word	DMA1_Channel4_IRQHandler          // 14: DMA1 Channel 4
	.word	DMA1_Channel5_IRQHandler          // 15: DMA1 Channel 5
	.word	DMA1_Channel6_IRQHandler          // 16: DMA1 Channel 6
	.word	DMA1_Channel7_IRQHandler          // 17: DMA1 Channel 7
	.word	ADC1_2_IRQHandler                 // 18: ADC1 and ADC2
	.word	USB_HP_CAN_TX_IRQHandler          // 19: USB Device High Priority or CAN TX
	.word	USB_LP_CAN_RX0_IRQHandler         // 20: USB Device Low Priority or CAN RX0
	.word	CAN_RX1_IRQHandler                // 21: CAN RX1
	.word	CAN_SCE_IRQHandler                // 22: CAN SCE
	.word	EXTI9_5_IRQHandler                // 23: External Line[9:5]s
	.word	TIM1_BRK_TIM15_IRQHandler         // 24: TIM1 Break and TIM15
	.word	TIM1_UP_TIM16_IRQHandler          // 25: TIM1 Update and TIM16
	.word	TIM1_TRG_COM_TIM17_IRQHandler     // 26: TIM1 Trigger and Commutation and TIM17
	.word	TIM1_CC_IRQHandler                // 27: TIM1 Capture Compare
	.word	TIM2_IRQHandler                   // 28: TIM2
	.word	TIM3_IRQHandler                   // 29: TIM3
	.word	TIM4_IRQHandler                   // 30: TIM4
	.word	I2C1_EV_IRQHandler                // 31: I2C1 Event
	.word	I2C1_ER_IRQHandler                // 32: I2C1 Error
	.word	I2C2_EV_IRQHandler                // 33: I2C2 Event
	.word	I2C2_ER_IRQHandler                // 34: I2C2 Error
	.word	SPI1_IRQHandler                   // 35: SPI1
	.word	SPI2_IRQHandler                   // 36: SPI2
	.word	USART1_IRQHandler                 // 37: USART1
	.word	USART2_IRQHandler                 // 38: USART2
	.word	USART3_IRQHandler                 // 39: USART3
	.word	EXTI15_10_IRQHandler              // 40: External Line[15:10]s
	.word	RTC_Alarm_IRQHandler              // 41: RTC Alarm (A and B) through EXTI Line
	.word	USBWakeUp_IRQHandler              // 42: USB Wakeup through EXTI line
	.word	TIM8_BRK_IRQHandler               // 43: TIM8 Break
	.word	TIM8_UP_IRQHandler                // 44: TIM8 Update
	.word	TIM8_TRG_COM_IRQHandler           // 45: TIM8 Trigger and Commutation
	.word	TIM8_CC_IRQHandler                // 46: TIM8 Capture Compare
	.word	ADC3_IRQHandler                   // 47: ADC3
	.word	FMC_IRQHandler                    // 48: FMC
	.word	0                                 // 49: Reserved
	.word	0                                 // 50: Reserved
	.word	SPI3_IRQHandler                   // 51: SPI3
	.word	UART4_IRQHandler                  // 52: UART4
	.word	UART5_IRQHandler                  // 53: UART5
	.word	TIM6_DAC_IRQHandler               // 54: TIM6 and DAC1&2 underrun errors
	.word	TIM7_IRQHandler                   // 55: TIM7
	.word	DMA2_Channel1_IRQHandler          // 56: DMA2 Channel 1
	.word	DMA2_Channel2_IRQHandler          // 57: DMA2 Channel 2
	.word	DMA2_Channel3_IRQHandler          // 58: DMA2 Channel 3
	.word	DMA2_Channel4_IRQHandler          // 59: DMA2 Channel 4
	.word	DMA2_Channel5_IRQHandler          // 60: DMA2 Channel 5
	.word	ADC4_IRQHandler                   // 61: ADC4
	.word	0                                 // 62: Reserved
	.word	0                                 // 63: Reserved
	.word	COMP1_2_3_IRQHandler              // 64: COMP1, COMP2 and COMP3
	.word	COMP4_5_6_IRQHandler              // 65: COMP4, COMP5 and COMP6
	.word	COMP7_IRQHandler                  // 66: COMP7
	.word	0                                 // 67: Reserved
	.word	0                                 // 68: Reserved
	.word	0                                 // 69: Reserved
	.word	0                                 // 70: Reserved
	.word	0                                 // 71: Reserved
	.word	I2C3_EV_IRQHandler                // 72: I2C3 Event
	.word	I2C3_ER_IRQHandler                // 73: I2C3 Error
	.word	USB_HP_IRQHandler                 // 74: USB High Priority remap
	.word	USB_LP_IRQHandler                 // 75: USB Low Priority remap
	.word	USBWakeUp_RMP_IRQHandler          // 76: USB Wakeup remap through EXTI
	.word	TIM20_BRK_IRQHandler              // 77: TIM20 Break
	.word	TIM20_UP_IRQHandler               // 78: TIM20 Update
	.word	TIM20_TRG_COM_IRQHandler          // 79: TIM20 Trigger and Commutation
	.word	TIM20_CC_IRQHandler               // 80: TIM20 Capture Compare
	.word	FPU_IRQHandler                    // 81: FPU

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
