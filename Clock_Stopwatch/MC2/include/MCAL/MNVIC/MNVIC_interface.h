/******************************************************************************
*
* Module: NVIC Driver.
*
* File Name: NVIC_interface.h
*
* Description: Driver's APIs' prototypes and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date:	06-03-2024
*
*******************************************************************************/

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_



/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/

#include <LIB/std_types.h>

#include "MCAL/MNVIC/INTERRUPTS.h"



/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/* Pending Status */
#define NOT_PENDING_STATE					(0)
#define PENDING_STATE						(1)


/* Active Status */
#define NOT_ACTIVE_STATE					(0)
#define ACTIVE_STATE						(1)


/* Preemption Levels */
#define PREEMPTION_LEVEL_0					(0)
#define PREEMPTION_LEVEL_1					(1)
#define PREEMPTION_LEVEL_2					(2)
#define PREEMPTION_LEVEL_3					(3)
#define PREEMPTION_LEVEL_4					(4)
#define PREEMPTION_LEVEL_5					(5)
#define PREEMPTION_LEVEL_6					(6)
#define PREEMPTION_LEVEL_7					(7)
#define PREEMPTION_LEVEL_8					(8)
#define PREEMPTION_LEVEL_9					(9)
#define PREEMPTION_LEVEL_10					(10)
#define PREEMPTION_LEVEL_11					(11)
#define PREEMPTION_LEVEL_12					(12)
#define PREEMPTION_LEVEL_13					(13)
#define PREEMPTION_LEVEL_14					(14)
#define PREEMPTION_LEVEL_15					(15)


/* SubPriority Levels */
#define SUBPRIORITY_LEVEL_0					(0)
#define SUBPRIORITY_LEVEL_1					(1)
#define SUBPRIORITY_LEVEL_2					(2)
#define SUBPRIORITY_LEVEL_3					(3)
#define SUBPRIORITY_LEVEL_4					(4)
#define SUBPRIORITY_LEVEL_5					(5)
#define SUBPRIORITY_LEVEL_6					(6)
#define SUBPRIORITY_LEVEL_7					(7)
#define SUBPRIORITY_LEVEL_8					(8)
#define SUBPRIORITY_LEVEL_9					(9)
#define SUBPRIORITY_LEVEL_10				(10)
#define SUBPRIORITY_LEVEL_11				(11)
#define SUBPRIORITY_LEVEL_12				(12)
#define SUBPRIORITY_LEVEL_13				(13)
#define SUBPRIORITY_LEVEL_14				(14)
#define SUBPRIORITY_LEVEL_15				(15)


/* Priority Group Options */
/* PG stands for Priority Group, GPB stands for Group Priority Bits, and SPB stands for SubPriority Bits */

/* Group priority bits = [7:4], SubPriority bits = None */
#define PG_GPB_7_TO_4_SPB_NONE_MASK			(0x00000000UL)
/* Group priority bits = [7:5], SubPriority bits = [4] */
#define PG_GPB_7_TO_5_SPB_4_MASK			(0x00000400UL)
/* Group priority bits = [7:6], SubPriority bits = [5:4] */
#define PG_GPB_7_TO_6_SPB_5_TO_4_MASK		(0x00000500UL)
/* Group priority bits = [7], SubPriority bits = [6:4] */
#define PG_GPB_7_SPB_6_TO_4_MASK			(0x00000600UL)
/* Group priority bits = None, SubPriority bits = [7:4] */
#define PG_GPB_NONE_SPB_7_TO_4_MASK			(0x00000700UL)



/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


/**
 *@brief : The Error List Type
 */
typedef enum
{
	/**
	 *@brief : Everything OK, function had Performed Correctly.
	 */
	NVIC_enuOk = 0,
	/**
	 *@brief : Something went wrong in the function.
	 */
	NVIC_enuNotOk,
	/**
	 *@brief : Null pointer is passed to a function as an argument.
	 */
	NVIC_enuNullPointer,
	/**
	 *@brief : Wrong preemption level is passed to a function as an argument.
	 */
	NVIC_enuWrongPreemptionLevel,
	/**
	*@brief : Wrong SubPriority level is passed to a function as an argument.
	 */
	NVIC_enuWrongSubPriorityLevel,
	/**
	 *@brief : Wrong priority grouping is passed to a function as an argument.
	 */
	NVIC_enuWrongPriorityGrouping

}NVIC_enuErrorStatus_t;



/****************************************************************************************/
/*									Functions' Declaration								*/
/****************************************************************************************/


/**
 *@brief : Function to enable an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_EnableIRQ(IRQs_t IRQ_);


/**
 *@brief : Function to disable an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_DisableIRQ(IRQs_t IRQ_);


/**
 *@brief : Function to set the pending bit for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_SetPendingIRQ(IRQs_t IRQ_);


/**
 *@brief : Function to clear the pending bit for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_ClearPendingIRQ(IRQs_t IRQ_);


/**
 *@brief : Function to Get the pending bit status for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Pointer in which the value of the pending bit will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetPendingIRQ(IRQs_t IRQ_, u32* pendingStatus);


/**
 *@brief : Function to Get the pending bit status for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Pointer in which the value of the Active flag bit will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetActiveStatusIRQ(IRQs_t IRQ_, u32* activeStatus);


/**
 *@brief : Function to set the priority for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Preemption level.
 *@param : SubPriority level.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_SetPriorityIRQ(IRQs_t IRQ_, u8 PREEMPTION_LEVEL_, u8 SUBPRIORITY_LEVEL_);

/**
 *@brief : Function to get the priority for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Pointer in which the Priority level will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetPriorityIRQ(IRQs_t IRQ_, u8* priorityLevel);


/**
 *@brief : Function to generate a software interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GenerateSoftwareIRQ(IRQs_t IRQ_);


/**
 *@brief : Function to set the priority group for all the IRQs.
 *@param : Priority group option from the options specified in the data sheet.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_SetPriorityGrouping(u32 priorityGroup);


/**
 *@brief : Function to get the priority group for all the IRQs.
 *@param : Pointer inside which the value of the priority group will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetPriorityGrouping(u32* priorityGroup);


#endif /* NVIC_INTERFACE_H_ */
