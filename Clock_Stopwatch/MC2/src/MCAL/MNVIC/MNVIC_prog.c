/******************************************************************************
*
* Module: NVIC Driver
*
* File Name: NVIC_prog.c
*
* Description: Driver's APIs' Implementation and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date: 06-03-2024
*
*******************************************************************************/



/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/

#include "MCAL/MNVIC/MNVIC_interface.h"



/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/* Number of bits that is not connected (not implemented) in the Pending register NVIC_IPRx */
#define NVIC_PR_NON_IMP_BITS							(4)

/* The base address of the main NVIC register block */
#define NVIC_BASE_ADDRESS								(0xE000E100UL)
/* The base address of the SCB register block */
#define SCB_BASE_ADDRESS								(0xE000E008UL)

/* Number of bits in a register (register width) */
#define REGISTER_WIDTH									(32)
/* Number of fields included in each one of the IPRx registers */
#define IPR_FIELDS_PER_REGISTER							(4)

/* Mask for the INTID bits in the STIR register in the NVIC */
#define NVIC_STIR_INTID_SET_MASK						(0x000001FFUL)
/* Mask for the IP[N] field in the IPRx register */
#define NVIC_IPRX_IP_N_SET_MASK							(0x000000FFUL)
/* Mask for the PRIGROUP bits in the AIRCR register */
#define SCB_AIRCR_PRIGROUP_BITS_SET_MASK				(0x00000700UL)

/* Number of bits specified for each field in each of the IPRx registers */
#define FIELDS_PER_REGISTER_BITS_NUMBER					(8)

/* Position of the PRIGROUP bits in the AIRCR register */
#define SCB_AIRCR_PRIGROUP_BITS_POSITION				(8)
/* Position of the VECTKEYSTAT/ VECTKEY bits in the AIRCR register */
#define SCB_AIRCR_VECTKEYSTAT_VECTKEY_BITS_POSITION		(16)


/* Priority Group Options */
/* PG stands for Priority Group, GPB stands for Group Priority Bits, and SPB stands for SubPriority Bits */

/* Group priority bits = [7:4], SubPriority bits = None */
#define PG_GPB_7_TO_4_SPB_NONE_VALUE					(0x00000000UL)
/* Group priority bits = [7:5], SubPriority bits = [4] */
#define PG_GPB_7_TO_5_SPB_4_VALUE						(0x00000400UL)
/* Group priority bits = [7:6], SubPriority bits = [5:4] */
#define PG_GPB_7_TO_6_SPB_5_TO_4_VALUE					(0x00000500UL)
/* Group priority bits = [7], SubPriority bits = [6:4] */
#define PG_GPB_7_SPB_6_TO_4_VALUE						(0x00000600UL)
/* Group priority bits = None, SubPriority bits = [7:4] */
#define PG_GPB_NONE_SPB_7_TO_4_VALUE					(0x00000700UL)



/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


typedef struct {
	volatile u32 ISER[8];
	u32 NVIC_Reserved1[24];
	volatile u32 ICER[8];
	u32 NVIC_Reserved2[24];
	volatile u32 ISPR[8];
	u32 NVIC_Reserved3[24];
	volatile u32 ICPR[8];
	u32 NVIC_Reserved4[24];
	volatile u32 IABR[8];
	u32 NVIC_Reserved5[56];
	volatile u8 IPR[240];
	u32 NVIC_Reserved6[644];
	volatile u32 STIR;
}NVIC_strRegsiters_t;


typedef struct {
	volatile u32 ACTLR;
	/* Because the address of the ACTLR register is 0xE000E003, and the base address of the SCB is 0xE000ED00 */
	u32 SCB_Reserved1[829];
	volatile u32 CPUID;
	volatile u32 ICSR;
	volatile u32 VTOR;
	volatile u32 AIRCR;
	volatile u32 SCR;
	volatile u32 CCR;
	volatile u32 SHPR[3];
	volatile u32 SHCSR;
	volatile u32 CFSR;
	volatile u32 HFSR;
	u32 SCB_Reversed2;
	volatile u32 MMFAR;
	volatile u32 BFAR;
	volatile u32 AFSR;

}SCB_strRegsiters_t;



/****************************************************************************************/
/*									Variables's Declaration								*/
/****************************************************************************************/


static NVIC_strRegsiters_t* const NVIC = (NVIC_strRegsiters_t*)NVIC_BASE_ADDRESS;

static SCB_strRegsiters_t* const SCB = (SCB_strRegsiters_t*)SCB_BASE_ADDRESS;



/****************************************************************************************/
/*								Static Functions' Declaration							*/
/****************************************************************************************/







/****************************************************************************************/
/*								Functions' Implementation								*/
/****************************************************************************************/


/**
 *@brief : Function to enable an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_EnableIRQ(IRQs_t IRQ_)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request */

		/* Set the bit corresponding to the passed IRQ in the right ISER register */
		NVIC->ISER[IRQ_ / REGISTER_WIDTH] |= (1 << (IRQ_ % REGISTER_WIDTH));
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to disable an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_DisableIRQ(IRQs_t IRQ_)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request */

		/* set the bit corresponding to the passed IRQ in the right ICER register to disable the IRQ */
		NVIC->ICER[IRQ_ / REGISTER_WIDTH] |= (1 << (IRQ_ % REGISTER_WIDTH));
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to set the pending bit for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_SetPendingIRQ(IRQs_t IRQ_)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request */

		/* set the bit corresponding to the passed IRQ in the right ISPR register */
		NVIC->ISPR[IRQ_ / REGISTER_WIDTH] |= (1 << (IRQ_ % REGISTER_WIDTH));
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to clear the pending bit for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_ClearPendingIRQ(IRQs_t IRQ_)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request */

		/* set the bit corresponding to the passed IRQ in the right ICPR register to clear the pending of the IRQ */
		NVIC->ICPR[IRQ_ / REGISTER_WIDTH] |= (1 << (IRQ_ % REGISTER_WIDTH));
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Get the pending bit status for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Pointer in which the value of the pending bit will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetPendingIRQ(IRQs_t IRQ_, u32* pendingStatus)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else if (pendingStatus == NULL_PTR)
	{
		/* If the user is passing a NULL pointer, return an error in the error status */
		LOC_enuErrorStatus = NVIC_enuNullPointer;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request, and didn't enter a NULL pointer, so we can deal with it */

		/* Get the pending bit state which is corresponding to the passed IRQ */
		*pendingStatus = ((NVIC->ISPR[IRQ_ / REGISTER_WIDTH] & (1 << (IRQ_ % REGISTER_WIDTH))) >> (IRQ_ % REGISTER_WIDTH));
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Get the pending bit status for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Pointer in which the value of the Active flag bit will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetActiveStatusIRQ(IRQs_t IRQ_, u32* activeStatus)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else if (activeStatus == NULL_PTR)
	{
		/* If the user is passing a NULL pointer, return an error in the error status */
		LOC_enuErrorStatus = NVIC_enuNullPointer;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request, and didn't enter a NULL pointer, so we can deal with it */

		/* Get the active bit state which is corresponding to the passed IRQ */
		*activeStatus = ((NVIC->IABR[IRQ_ / REGISTER_WIDTH] & (1 << (IRQ_ % REGISTER_WIDTH))) >> (IRQ_ % REGISTER_WIDTH));
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to set the priority for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Preemption level.
 *@param : SubPriority level.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_SetPriorityIRQ(IRQs_t IRQ_, u8 PREEMPTION_LEVEL_, u8 SUBPRIORITY_LEVEL_)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	/* Check on the inputed preemption level if it in the specified range or not */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	else if ((PREEMPTION_LEVEL_ < PREEMPTION_LEVEL_0) || (PREEMPTION_LEVEL_ > PREEMPTION_LEVEL_15))
	{
		/* if not return an error */
		LOC_enuErrorStatus = NVIC_enuWrongPreemptionLevel;
	}
	/* Check on the inputed subPriority level if it in the specified range or not */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	else if ((SUBPRIORITY_LEVEL_ < SUBPRIORITY_LEVEL_0) || (SUBPRIORITY_LEVEL_ > SUBPRIORITY_LEVEL_15))
	{
		/* if not return an error */
		LOC_enuErrorStatus = NVIC_enuWrongSubPriorityLevel;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request and for a priority level */

		/* Create a local variable to assign in it the value of the PRIGROUP bits */
		u32 LOC_priorityGroup;
		if (NVIC_GetPriorityGrouping(&LOC_priorityGroup) == NVIC_enuOk)
		{

			/* Create a local variable as an image of the real register */
			u32 LOC_u32LocalReg = NVIC->IPR[IRQ_ / IPR_FIELDS_PER_REGISTER];
			/* Clean the bits before assigning in it */
			LOC_u32LocalReg &= ~(NVIC_IPRX_IP_N_SET_MASK << ((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER));

			/* if the function works properly and it returns with error status equals OK, We can no continue */
			switch (LOC_priorityGroup)
			{
			case PG_GPB_7_TO_4_SPB_NONE_VALUE:
				/* Assign the passed values in the local variable */
				LOC_u32LocalReg |= PREEMPTION_LEVEL_ << (((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER) + NVIC_PR_NON_IMP_BITS);
				break;
			case PG_GPB_7_TO_5_SPB_4_VALUE:
				/* Check that the user entered values that can be assigned in the PRIGROUP bits */
				if ((PREEMPTION_LEVEL_ <= PREEMPTION_LEVEL_7) && (SUBPRIORITY_LEVEL_ <= SUBPRIORITY_LEVEL_1))
				{
					/* Assign the passed values in the local variable */
					LOC_u32LocalReg |= ((PREEMPTION_LEVEL_ << 1) | SUBPRIORITY_LEVEL_) << (((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER) + NVIC_PR_NON_IMP_BITS);
				}
				else
				{
					LOC_enuErrorStatus = NVIC_enuNotOk;
				}
				break;
			case PG_GPB_7_TO_6_SPB_5_TO_4_VALUE:
				/* Check that the user entered values that can be assigned in the PRIGROUP bits */
				if ((PREEMPTION_LEVEL_ <= PREEMPTION_LEVEL_3) && (SUBPRIORITY_LEVEL_ <= SUBPRIORITY_LEVEL_3))
				{
					/* Assign the passed values in the local variable */
					LOC_u32LocalReg |= ((PREEMPTION_LEVEL_ << 2) | SUBPRIORITY_LEVEL_) << (((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER) + NVIC_PR_NON_IMP_BITS);
				}
				else
				{
					LOC_enuErrorStatus = NVIC_enuNotOk;
				}
				break;
			case PG_GPB_7_SPB_6_TO_4_VALUE:
				/* Check that the user entered values that can be assigned in the PRIGROUP bits */
				if ((PREEMPTION_LEVEL_ <= PREEMPTION_LEVEL_1) && (SUBPRIORITY_LEVEL_ <= SUBPRIORITY_LEVEL_7))
				{
					/* Assign the passed values in the local variable */
					LOC_u32LocalReg |= ((PREEMPTION_LEVEL_ << 3) | SUBPRIORITY_LEVEL_) << (((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER) + NVIC_PR_NON_IMP_BITS);
				}
				else
				{
					LOC_enuErrorStatus = NVIC_enuNotOk;
				}
				break;
			case PG_GPB_NONE_SPB_7_TO_4_VALUE:
				/* Assign the passed values in the local variable */
				LOC_u32LocalReg |= SUBPRIORITY_LEVEL_ << (((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER) + NVIC_PR_NON_IMP_BITS);
				break;
			default:
				/* The code shouldn't reach here */
				break;
			}
			if (LOC_enuErrorStatus == NVIC_enuOk)
			{
				/* As We finish the configurations, We can assign directly in the
				 * real register */
				NVIC->IPR[IRQ_ / IPR_FIELDS_PER_REGISTER] = LOC_u32LocalReg;
			}
			else
			{
				/* Do nothing */
			}
		}
		else
		{
			LOC_enuErrorStatus = NVIC_enuNotOk;
		}
	}

	return LOC_enuErrorStatus;
}

/**
 *@brief : Function to get the priority for an interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@param : Pointer in which the Priority level will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetPriorityIRQ(IRQs_t IRQ_, u8* priorityLevel)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else if (priorityLevel == NULL_PTR)
	{
		/* If the user is passing a NULL pointer, return an error in the error status */
		LOC_enuErrorStatus = NVIC_enuNullPointer;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request, and didn't enter a NULL pointer, so we can deal with it */

		/* Get the active bit state which is corresponding to the passed IRQ */
		*priorityLevel = ((NVIC->IPR[IRQ_ / IPR_FIELDS_PER_REGISTER] & (NVIC_IPRX_IP_N_SET_MASK << ((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER))) >> ((IRQ_ % IPR_FIELDS_PER_REGISTER) * FIELDS_PER_REGISTER_BITS_NUMBER));
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to generate a software interrupt.
 *@param : Interrupt Acronym, form the Vector Table in the reference manual, corresponding to the interrupt request you want.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GenerateSoftwareIRQ(IRQs_t IRQ_)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison is always false due to limited range of data type [-Wtype-limits]"
	 * ignore it */
	if ((IRQ_ < 0) || (IRQ_ >= _IRQ_MAX))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuNotOk;
	}
	else
	{
		/* Seems like the user entered a valid value for an interrupt request */

		/* Create a local variable as an image of the real register */
		u32 LOC_u32LocalReg = NVIC->STIR;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(NVIC_STIR_INTID_SET_MASK);
		/* Assign the passed values in the local variable */
		LOC_u32LocalReg |= (IRQ_);
		/* As We finish the configurations, We can assign directly in the
		 * real register */
		NVIC->STIR = LOC_u32LocalReg;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to set the priority group for all the IRQs.
 *@param : Priority group option from the options specified in the data sheet.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_SetPriorityGrouping(u32 priorityGroup)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check that the entered IRQ is in the specified range */
	/* The compiler will generate the following warning:
	 * "comparison of unsigned expression < 0 is always false [-Wtype-limits]"
	 * ignore it */
	if ((priorityGroup < PG_GPB_7_TO_4_SPB_NONE_MASK) || (priorityGroup > PG_GPB_NONE_SPB_7_TO_4_MASK))
	{
		/* If the user entered an invalid value for the interrupt request, return NOT OK in the error status */
		LOC_enuErrorStatus = NVIC_enuWrongPriorityGrouping;
	}
	else
	{
		/* Seems like the user entered a valid value for an priority group */

		/* Create a local variable as an image of the real register */
		u32 LOC_u32LocalReg = SCB->AIRCR;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(SCB_AIRCR_PRIGROUP_BITS_SET_MASK);
		/* Assign the passed values in the local variable */
		LOC_u32LocalReg |= (priorityGroup);
		/* As We finish the configurations, We can assign directly in the
		 * real register */

		/* But it is mentioned in the data sheet that we must write 0x5FA in the VECTKEYSTAT/ VECTKEY bits in AIRCR
		 * so that what We write after could be listened */
		SCB->AIRCR = (0x5FA << SCB_AIRCR_VECTKEYSTAT_VECTKEY_BITS_POSITION) | (LOC_u32LocalReg);
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to get the priority group for all the IRQs.
 *@param : Pointer inside which the value of the priority group will be assigned.
 *@return: Error status.
 */
NVIC_enuErrorStatus_t NVIC_GetPriorityGrouping(u32* priorityGroup)
{
	NVIC_enuErrorStatus_t LOC_enuErrorStatus = NVIC_enuOk;

	/* Check if the passed pointer is a NULL pointer or not */
	if (priorityGroup == NULL_PTR)
	{
		/* If the user is passing a NULL pointer, return an error in the error status */
		LOC_enuErrorStatus = NVIC_enuNullPointer;
	}
	else
	{
		/* Seems like the user didn't enter a NULL pointer, so we can deal with it */

		/* Get the active bit state which is corresponding to the passed IRQ */
		*priorityGroup = ((SCB->AIRCR & (SCB_AIRCR_PRIGROUP_BITS_SET_MASK)) >> (SCB_AIRCR_PRIGROUP_BITS_POSITION));
	}

	return LOC_enuErrorStatus;
}

