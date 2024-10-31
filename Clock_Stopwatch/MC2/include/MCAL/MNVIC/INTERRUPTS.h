/******************************************************************************
 *
 * Module: NVIC Driver.
 *
 * File Name: INTERRUPTS.h
 *
 * Description: Interrupts included in the Vector Table.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date:	06-03-2024
 *
 *******************************************************************************/

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


/**
 *@brief : Positions of IRQ in the Vector table for STM32F401xB/CSTM32F401xD/E.
 */
typedef enum
{
	IRQ_WWDG					= 0,	/* Window WatchDog Interrupt								*/
	IRQ_EXTI16					= 1,	/* EXTI Line 16 interrupt 									*/
	IRQ_PVD						= 1,	/* PVD through EXTI Line detection Interrupt				*/
	IRQ_EXTI21					= 2,	/* EXTI Line 21 interrupt 									*/
	IRQ_TAMP_STAMP				= 2,	/* Tamper and TimeStamp interrupts through the EXTI line	*/
	IRQ_EXTI22					= 3,	/* EXTI Line 22 interrupt 									*/
	IRQ_RTC_WKUP				= 3,	/* RTC Wakeup interrupt through the EXTI line				*/
	IRQ_FLASH					= 4,	/* FLASH global Interrupt									*/
	IRQ_RCC						= 5,	/* RCC global Interrupt										*/
	IRQ_EXTI0					= 6,	/* EXTI Line0 Interrupt										*/
	IRQ_EXTI1					= 7,	/* EXTI Line1 Interrupt										*/
	IRQ_EXTI2					= 8,	/* EXTI Line2 Interrupt										*/
	IRQ_EXTI3					= 9,	/* EXTI Line3 Interrupt										*/
	IRQ_EXTI4					= 10,	/* EXTI Line4 Interrupt										*/
	IRQ_DMA1_Stream0			= 11,	/* DMA1 Stream 0 global Interrupt							*/
	IRQ_DMA1_Stream1			= 12,	/* DMA1 Stream 1 global Interrupt							*/
	IRQ_DMA1_Stream2			= 13,	/* DMA1 Stream 2 global Interrupt							*/
	IRQ_DMA1_Stream3			= 14,	/* DMA1 Stream 3 global Interrupt							*/
	IRQ_DMA1_Stream4			= 15,	/* DMA1 Stream 4 global Interrupt							*/
	IRQ_DMA1_Stream5			= 16,	/* DMA1 Stream 5 global Interrupt							*/
	IRQ_DMA1_Stream6			= 17,	/* DMA1 Stream 6 global Interrupt							*/
	IRQ_ADC						= 18,	/* ADC1, ADC2 and ADC3 global Interrupts					*/
	IRQ_EXTI5					= 23,	/* EXTI Line5 Interrupt										*/
	IRQ_EXTI6					= 23,	/* EXTI Line6 Interrupt										*/
	IRQ_EXTI7					= 23,	/* EXTI Line7 Interrupt										*/
	IRQ_EXTI8					= 23,	/* EXTI Line8 Interrupt										*/
	IRQ_EXTI9					= 23,	/* EXTI Line9 Interrupt										*/
	IRQ_TIM1_BRK				= 24,	/* TIM1 Break interrupt										*/
	IRQ_TIM9					= 24,	/* TIM9 global interrupt									*/
	IRQ_TIM1_UP					= 25,	/* TIM1 Update Interrupt									*/
	IRQ_TIM10					= 25,	/* TIM10 global interrupt									*/
	IRQ_TIM1_TRG_COM			= 26,	/* TIM1 Trigger and Commutation Interrupt					*/
	IRQ_TIM11					= 26,	/* TIM11 global interrupt									*/
	IRQ_TIM1_CC					= 27,	/* TIM1 Capture Compare Interrupt							*/
	IRQ_TIM2					= 28,	/* TIM2 global Interrupt									*/
	IRQ_TIM3					= 29,	/* TIM3 global Interrupt									*/
	IRQ_TIM4					= 30,	/* TIM4 global Interrupt									*/
	IRQ_I2C1_EV					= 31,	/* I2C1 Event Interrupt 									*/

	IRQ_I2C1_ER					= 32,	/* I2C1 Error Interrupt 									*/
	IRQ_I2C2_EV					= 33,	/* I2C2 Event Interrupt 									*/
	IRQ_I2C2_ER					= 34,	/* I2C2 Error Interrupt 									*/
	IRQ_SPI1					= 35,	/* SPI1 global Interrupt									*/
	IRQ_SPI2					= 36,	/* SPI2 global Interrupt									*/
	IRQ_USART1					= 37,	/* USART1 global Interrupt									*/
	IRQ_USART2					= 38,	/* USART2 global Interrupt									*/
	IRQ_EXTI10					= 40,	/* EXTI Line10 Interrupt									*/
	IRQ_EXTI11					= 40,	/* EXTI Line11 Interrupt									*/
	IRQ_EXTI12					= 40,	/* EXTI Line12 Interrupt									*/
	IRQ_EXTI13					= 40,	/* EXTI Line13 Interrupt									*/
	IRQ_EXTI14					= 40,	/* EXTI Line14 Interrupt									*/
	IRQ_EXTI15					= 40,	/* EXTI Line15 Interrupt									*/
	IRQ_EXTI17					= 41,	/* EXTI Line 17 interrupt									*/
	IRQ_RTC_Alarm				= 41,	/* RTC Alarm (A and B) through EXTI Line Interrupt			*/
	IRQ_EXTI18					= 42,	/* EXTI Line 18 interrupt									*/
	IRQ_OTG_FS_WKUP				= 42,	/* USB OTG FS Wakeup through EXTI line interrupt			*/
	IRQ_DMA1_Stream7			= 47,	/* DMA1 Stream7 Interrupt									*/
	IRQ_SDIO					= 49,	/* SDIO global Interrupt									*/
	IRQ_TIM5					= 50,	/* TIM5 global Interrupt									*/
	IRQ_SPI3					= 51,	/* SPI3 global Interrupt									*/
	IRQ_DMA2_Stream0			= 56,	/* DMA2 Stream 0 global Interrupt							*/
	IRQ_DMA2_Stream1			= 57,	/* DMA2 Stream 1 global Interrupt							*/
	IRQ_DMA2_Stream2			= 58,	/* DMA2 Stream 2 global Interrupt							*/
	IRQ_DMA2_Stream3			= 59,	/* DMA2 Stream 3 global Interrupt							*/
	IRQ_DMA2_Stream4			= 60,	/* DMA2 Stream 4 global Interrupt							*/

	IRQ_OTG_FS					= 67,	/* USB OTG FS global Interrupt								*/
	IRQ_DMA2_Stream5			= 68,	/* DMA2 Stream 5 global interrupt							*/
	IRQ_DMA2_Stream6			= 69,	/* DMA2 Stream 6 global interrupt							*/
	IRQ_DMA2_Stream7			= 70,	/* DMA2 Stream 7 global interrupt							*/
	IRQ_USART6					= 71,	/* USART6 global interrupt									*/
	IRQ_I2C3_EV					= 72,	/* I2C3 event interrupt										*/
	IRQ_I2C3_ER					= 73,	/* I2C3 error interrupt										*/
	IRQ_FPU						= 81,	/* FPU global interrupt										*/
	IRQ_SPI4					= 84,	/* SPI4 global Interrupt									*/
	_IRQ_MAX
}IRQs_t;


#endif /* INTERRUPTS_H_ */
