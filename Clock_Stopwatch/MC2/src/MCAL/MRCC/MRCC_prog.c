/******************************************************************************
*
* Module: RCC Driver
*
* File Name: RCC_prog.c
*
* Description: Driver's APIs' Implementation and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date: 07-02-2024
*
*******************************************************************************/



/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/

#include "MCAL/MRCC/MRCC_interface.h"



/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/*=========================================================*/
/*=========================================================*/
/* The base address in which the registers of RCC are allocated in the memory */
#define RCC_BASE_ADDRESS				(0x40023800UL)
/*=========================================================*/
/*=========================================================*/

/* The value of the external HSI clock */
#define HSI_VALUE						(16000000UL)

/* The limits of the VCO input frequency (PLL input frequency / PLLM) */
#define VCO_IN_FREQ_LWR_LMT				(1000000UL)
#define VCO_IN_FREQ_UPR_LMT				(2000000UL)

/* The limits of the VCO output frequency
 * for PLL: = (VCO input frequency * PLLN)
 * for PLLI2S: = (VCO input frequency * PLLI2SN) */
#define VCO_OUT_FREQ_LWR_LMT			(192000000UL)
#define VCO_OUT_FREQ_UPR_LMT			(432000000UL)

/* PLL and PLLI2S upper Limits */
#define PLL_FREQ_UPR_LMT				(84000000UL)
#define PLLI2S_FREQ_UPR_LMT				(192000000UL)

/* USB OTG FS clock frequency value */
#define USBOTGFS_FREQ_UPR_LMT			(48000000UL)

/* APB1 domain maximum frequency limit */
#define APB1_FREQ_UPR_LMT				(42000000UL)
/* APB2 domain maximum frequency limit */
#define APB2_FREQ_UPR_LMT				(84000000UL)
/**************************************************************************************/



/* RCC_PLLCFGR's Bits offset */

/* Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks */
#define RCC_PLLCFGR_PLLQ				24
/* Main PLL(PLL) and audio PLL (PLLI2S) entry clock source */
#define RCC_PLLCFGR_PLLSRC				22
/* Main PLL (PLL) division factor for main system clock */
#define RCC_PLLCFGR_PLLP				16
/* Main PLL (PLL) multiplication factor for VCO */
#define RCC_PLLCFGR_PLLN				6
/* Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock */
#define RCC_PLLCFGR_PLLM				0
/*************************************************************************************/


/* RCC_PLLI2SCFGR's Bits offset */

/* PLLI2S division factor */
#define RCC_PLLI2SCFGR_PLLI2SR			28
/* PLLI2S multiplication */
#define RCC_PLLI2SCFGR_PLLI2SN			6
/*************************************************************************************/


/* System Clock Source status options */
#define SYSCLKSTATUS_HSI				(0x00000000UL)	/* 	Mask for SWS bit			*/
#define SYSCLKSTATUS_HSE				(0x00000004UL)	/* 	Mask for SWS bit			*/
#define SYSCLKSTATUS_PLL				(0x00000008UL)	/* 	Mask for SWS bit 			*/
/**************************************************************************************/


/* RCC_CR register's bits' Masks */
#define HSION							(0x00000001UL)	/* 	Mask for HSION bit			*/
#define HSIRDY							(0x00000002UL)	/* 	Mask for HSIRDY bit			*/
#define HSEON							(0x00010000UL)	/* 	Mask for HSEON bit			*/
#define HSERDY							(0x00020000UL)	/* 	Mask for HSERDY bit			*/
#define HSEBYP							(0x00040000UL)	/* 	Mask for HSEBYP bit			*/
#define CSSON							(0x00080000UL)	/* 	Mask for CSSON bit			*/
#define PLLON							(0x01000000UL)	/* 	Mask for PLLON bit			*/
#define PLLRDY							(0x02000000UL)	/* 	Mask for PLLRDY bit			*/
#define PLLI2SON						(0x04000000UL)	/* 	Mask for PLLI2SON bit		*/
#define PLLI2SRDY						(0x08000000UL)	/* 	Mask for PLLI2SRDY bit		*/
/**************************************************************************************/

/* Set Masks */

#define HSITRIM_SETMASK					(0x000000F8UL)	/*	Mask for HSITRIM bits		*/

#define PLLSRC_SETMASK					(0x00400000UL)	/*	Mask for PLLSRC bit			*/

#define PLLM_SETMASK					(0x0000003FUL)	/*	Mask for PLLM bits			*/

#define PLLN_SETMASK					(0x00007FC0UL)	/*	Mask for PLLN bits			*/

#define PLLP_SETMASK					(0x00030000UL)	/*	Mask for PLLP bits			*/

#define PLLQ_SETMASK					(0x0F000000UL)	/*	Mask for PLLQ bits			*/

#define PLLI2SN_SETMASK					(0x00007FC0UL)	/*	Mask for PLLI2SN bits		*/

#define PLLI2SR_SETMASK					(0x70000000UL)	/*	Mask for PLLI2SR bits		*/

#define SW_SETMASK						(0x00000003UL)	/*	Mask for SW bits			*/

#define	AHBPRES_SETMASK					(0x000000F0UL)	/*	Mask for HPRE bits			*/

#define	APB1PRES_SETMASK				(0x00001C00UL)	/*	Mask for PPRE1 bits			*/

#define	APB2PRES_SETMASK				(0x0000E000UL)	/*	Mask for PPRE2 bits			*/



/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


typedef struct{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 RCC_Reserved1;
	u32 RCC_Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 RCC_Reserved3;
	u32 RCC_Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 RCC_Reserved5;
	u32 RCC_Reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 RCC_Reserved7;
	u32 RCC_Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 RCC_Reserved9;
	u32 RCC_Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 RCC_Reserved11;
	u32 RCC_Reserved12;
	u32 BDCR;
	u32 CSR;
	u32 RCC_Reserved13;
	u32 RCC_Reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 RCC_Reserved15;
	u32 DCKCFGR;
}RCC_strRegsiters_t;



/********************************************************************************************/
/*									Variables's Declaration									*/
/********************************************************************************************/

static volatile RCC_strRegsiters_t* const RCC = ((RCC_strRegsiters_t*)(RCC_BASE_ADDRESS));



/********************************************************************************************/
/*								Static Functions' Declaration								*/
/********************************************************************************************/



/********************************************************************************************/
/*									Functions' Implementation								*/
/********************************************************************************************/

/**
 *@brief : Function to Set the HSI clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableHSI(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set HSI ON */
	RCC->CR |= HSION;
	/* loop till the ready flag is set or when reach a timeout */
	while ((!(RCC->CR & HSIRDY)) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is set or not */
	if(RCC->CR & HSIRDY)
	{
		/* If the flag is set, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not set, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the HSI clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableHSI(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set HSI OFF */
	RCC->CR &= ~(HSION);
	/* loop till the ready flag is cleared or when reach a timeout */
	while ((RCC->CR & HSIRDY) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is cleared or not */
	if(!(RCC->CR & HSIRDY))
	{
		/* If the flag is cleared, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not cleared, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the HSE crystal clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableHSECrystal(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set HSE ON */
	RCC->CR |= HSEON;
	/* loop till the ready flag is set or when reach a timeout */
	while ((!(RCC->CR & HSERDY)) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is set or not */
	if(RCC->CR & HSERDY)
	{
		/* If the flag is set, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not set, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the HSE crystal clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableHSECrystal(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set HSE OFF */
	RCC->CR &= ~(HSEON);
	/* loop till the ready flag is cleared or when reach a timeout */
	while ((RCC->CR & HSERDY) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is cleared or not */
	if(!(RCC->CR & HSERDY))
	{
		/* If the flag is cleared, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not cleared, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the HSE Bypass clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableHSEBYP(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* First check if the HSE is ON, if so We cannot enable bypass mode */
	if (RCC->CR & HSEON)
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}
	else
	{
		/* Now We can enable bypass mode as the HSE is not ON (not enabled) */

		/* Used for timeout mechanism */
		u32 LOC_u32Counter = 1000;

		/* Set HSEBYP ON */
		RCC->CR |= HSEBYP;

		/* Set HSE ON */
		RCC->CR |= HSEON;

		/* loop till the ready flag is set or when reach a timeout */
		while ((!(RCC->CR & HSERDY)) && (LOC_u32Counter > 0))
		{
			LOC_u32Counter--;
		}

		/* Check if the code got out from the loop because the flag is set or not */
		if(RCC->CR & HSERDY)
		{
			/* If the flag is set, then Mission is DONE */
		}
		else
		{
			/* If a timeout is reached and the flag is not set, return NOT OK status */
			LOC_enuErrorStatus = RCC_enuNotOk;
		}
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the HSE Bypass clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableHSEBYP(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set HSE OFF */
	RCC->CR &= ~(HSEON);
	/* loop till the ready flag is cleared or when reach a timeout */
	while ((RCC->CR & HSERDY) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is cleared or not */
	if(!(RCC->CR & HSERDY))
	{
		/* If the flag is cleared, then Mission is DONE */

		/* Not bypass the HSE oscillator */
		RCC->CR &= ~(HSEBYP);
	}
	else
	{
		/* If a timeout is reached and the flag is not cleared, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the Main PLL clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableMainPLL(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set PLL ON */
	RCC->CR |= PLLON;
	/* loop till the ready flag is set or when reach a timeout */
	while ((!(RCC->CR & PLLRDY)) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is set or not */
	if(RCC->CR & PLLRDY)
	{
		/* If the flag is set, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not set, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the Main PLL clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableMainPLL(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set PLL OFF */
	RCC->CR &= ~(PLLON);
	/* loop till the ready flag is cleared or when reach a timeout */
	while ((RCC->CR & PLLRDY) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is cleared or not */
	if(!(RCC->CR & PLLRDY))
	{
		/* If the flag is cleared, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not cleared, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Set the PLLI2S clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnablePLLI2S(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set PLLI2S ON */
	RCC->CR |= PLLI2SON;
	/* loop till the ready flag is set or when reach a timeout */
	while ((!(RCC->CR & PLLI2SRDY)) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is set or not */
	if(RCC->CR & PLLI2SRDY)
	{
		/* If the flag is set, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not set, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}



/**
 *@brief : Function to Set the PLLI2S clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisablePLLI2S(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Used for timeout mechanism */
	u32 LOC_u32Counter = 1000;

	/* Set PLLI2S OFF */
	RCC->CR &= ~(PLLI2SON);
	/* loop till the ready flag is cleared or when reach a timeout */
	while ((RCC->CR & PLLI2SRDY) && (LOC_u32Counter > 0))
	{
		LOC_u32Counter--;
	}

	/* Check if the code got out from the loop because the flag is cleared or not */
	if(!(RCC->CR & PLLI2SRDY))
	{
		/* If the flag is cleared, then Mission is DONE */
	}
	else
	{
		/* If a timeout is reached and the flag is not cleared, return NOT OK status */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}



/**
 *@brief : Function to Set the Clock security system ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableCSS(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Set CSS ON */
	RCC->CR |= CSSON;

	return LOC_enuErrorStatus;
}



/**
 *@brief : Function to Set the Clock security system OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableCSS(void)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Set CSS ON */
	RCC->CR &= ~(CSSON);

	return LOC_enuErrorStatus;
}
/**************************************************************************************/


/**
 *@brief : Function to Set the PLLs clock source.
 *@param : PLLSRC_HSI	or	PLLSRC_HSE.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuSelectPLLsSrc(u32 Copy_u32PLLSrc)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	if ((Copy_u32PLLSrc == PLLSRC_HSI) || (Copy_u32PLLSrc == PLLSRC_HSE))
	{
		/* The user entered a valid choice */
		/* Check first if PLL or PLLI2S are enabled as We won't be able to set the PLLSRC bits */
		if ((RCC->CR & PLLON) || (RCC->CR & PLLI2SON))
		{
			/* If one of them is set (ON) (Enabled) then return NOT OK */
			LOC_enuErrorStatus = RCC_enuNotOk;
		}
		else
		{
			/* As Neither PLL nor PLLI2S is enabled, We can select their source now */

			/* Create a local variable as an image of the real register */
			u32 LOC_u32LocalReg = RCC->PLLCFGR;
			/* Clean the bits before assigning in it */
			LOC_u32LocalReg &= ~(PLLSRC_SETMASK);
			/* Assign the passed values in the local variable */
			LOC_u32LocalReg |= (Copy_u32PLLSrc);
			/* As We finish the configurations, We can assign directly in the
			 * real register */
			RCC->PLLCFGR = LOC_u32LocalReg;
		}
	}
	else
	{
		/* The user entered a NON-VALID choice, return NOT OK */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}



/**
 *@brief : Function to Get the PLLs clock source, will be used in calculations.
 *@param : Address of a variable in which the current PLLs clock source will be returned.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuGetPLLsSrc(u32* Add_u32PLLSrc)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check if the passed pointer if it is a NULL pointer or not */
	if (Add_u32PLLSrc == NULL_PTR)
	{
		/* If a NULL pointer, return error */
		LOC_enuErrorStatus = RCC_enuNullPointer;
	}
	else
	{
		/* Seems like We can start our job */

		/* We will return the value of PLLSRC bit in the passed pointer */
		if ((RCC->PLLCFGR & PLLSRC_HSI) == PLLSRC_HSI)
		{
			*Add_u32PLLSrc = PLLSRC_HSI;
		}
		else if (((RCC->PLLCFGR & PLLSRC_HSE) == PLLSRC_HSE))
		{
			*Add_u32PLLSrc = PLLSRC_HSE;
		}
		else
		{
			/* Do Nothing */
		}
	}

	return LOC_enuErrorStatus;
}



/**
 *@brief : Function to Configure The Main PLL.
 *@param : Values of PLLM, PLLN, PLLP, PLLQ respectively.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigMainPLL(u32 Copy_u32PLLM, u32 Copy_u32PLLN, u32 Copy_u32PLLP, u32 Copy_u32PLLQ)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Before an thing we will check that neither PLL nor PLLI2S is enabled */

	if((RCC->CR & PLLON) || (RCC->CR & PLLI2SON))
	{
		/* Return NOT OK, We can not configure M,N,P,Q unless PLL and PLLI2S are disabled */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}
	else
	{
		/* As neither PLL nor PLLI2S is enabled, We can configure them */


		/* Check on all the passed factors that they are in the range specified in the reference manual */
		if (((Copy_u32PLLM >= PLLM_2) && (Copy_u32PLLM <= PLLM_63)) \
				&& ((Copy_u32PLLN >= PLLN_192) && (Copy_u32PLLN <= PLLN_432)) \
				/* The compiler will generate the following warning:
				 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
				 * ignore it */
				&& ((Copy_u32PLLP >= PLLP_2) && (Copy_u32PLLP <= PLLP_8)) \
				&& ((Copy_u32PLLQ >= PLLQ_2) && (Copy_u32PLLQ <= PLLQ_15)))
		{
			/* Since the factors are in the specified range We will assign the values in the bits
			 * making sure that the output frequency from each stage is in the specified range too */

			/* First get the PLL source to know the input clock frequency value that will used in
			 * the calculations and operations */
			u32 LOC_PLLSrc, LOC_VCOINValue, LOC_VCOOUTValue, LOC_PLLFreqValue, LOC_OTGFreqValue;
			if ((RCC_enuGetPLLsSrc(&LOC_PLLSrc) == RCC_enuOk))
			{
				switch (LOC_PLLSrc)
				{
				/* In case PLLSRC is HSI, then the input clock frequency is 16 MHz */
				case PLLSRC_HSI:

					/* First We will divide the input clock frequency by PLLM, checking that the output
					 * is in the specified range (from 1 MHz to 2 MHz) */
					LOC_VCOINValue = HSI_VALUE / Copy_u32PLLM;
					if((LOC_VCOINValue >= VCO_IN_FREQ_LWR_LMT) && (LOC_VCOINValue <= VCO_IN_FREQ_UPR_LMT))
					{
						/* VCO input value is in the range, continue the calculations */
						LOC_VCOOUTValue = LOC_VCOINValue * Copy_u32PLLN;

						/* Check whether VCO output value is in the limits or not */
						if ((LOC_VCOOUTValue >= VCO_OUT_FREQ_LWR_LMT) && (LOC_VCOOUTValue <= VCO_OUT_FREQ_UPR_LMT))
						{
							/* VCO output value is in the range, continue the calculations */
							LOC_PLLFreqValue = LOC_VCOOUTValue / Copy_u32PLLP;
							LOC_OTGFreqValue = LOC_VCOOUTValue / Copy_u32PLLQ;

							/* Check that LOC_PLLFreqValue and LOC_OTGFreqValue are in the range */
							if((LOC_PLLFreqValue <= PLL_FREQ_UPR_LMT) && (LOC_OTGFreqValue <= USBOTGFS_FREQ_UPR_LMT))
							{
								/* Seems like all the passed parameters are in the specified ranges,
								 * so We will assign the passed values in the specified register */

								/* Create a local variable as an image of the real register */
								u32 LOC_u32LocalReg = RCC->PLLCFGR;
								/* Clean the bits before assigning in it */
								LOC_u32LocalReg &= ~(PLLM_SETMASK) & ~(PLLN_SETMASK) & ~(PLLP_SETMASK) \
													& ~(PLLQ_SETMASK);
								/* Assign the passed values in the local variable */
								LOC_u32LocalReg |= (Copy_u32PLLM << RCC_PLLCFGR_PLLM)\
													| (Copy_u32PLLN << RCC_PLLCFGR_PLLN)\
													| (Copy_u32PLLP << RCC_PLLCFGR_PLLP)\
													| (Copy_u32PLLQ << RCC_PLLCFGR_PLLQ);
								/* As We finish the configurations, We can assign directly in the
								 * real register */
								RCC->PLLCFGR = LOC_u32LocalReg;
							}
							else
							{
								/* PLL frequency or USBOTGFS frequency exceeds the limits, return NOT OK */
								LOC_enuErrorStatus = RCC_enuNotOk;
							}
						}
						else
						{
							/* VCO output exceeds the limits, return NOT OK */
							LOC_enuErrorStatus = RCC_enuNotOk;
						}
					}
					else
					{
						/* VCO input exceeds the limits, return NOT OK */
						LOC_enuErrorStatus = RCC_enuNotOk;
					}
					break;
					/* In case PLLSRC is HSE, then the input clock frequency is HSE_CRYSTAL_VALUE MHz */
				case PLLSRC_HSE:

					/* First We will divide the input clock frequency by PLLM, checking that the output
					 * is in the specified range (from 1 MHz to 2 MHz) */
					LOC_VCOINValue = HSE_CRYSTAL_VALUE / Copy_u32PLLM;
					if((LOC_VCOINValue >= VCO_IN_FREQ_LWR_LMT) && (LOC_VCOINValue <= VCO_IN_FREQ_UPR_LMT))
					{
						/* VCO input value is in the range, continue the calculations */
						LOC_VCOOUTValue = LOC_VCOINValue * Copy_u32PLLN;

						/* Check whether VCO output value is in the limits or not */
						if ((LOC_VCOOUTValue >= VCO_OUT_FREQ_LWR_LMT) && (LOC_VCOOUTValue <= VCO_OUT_FREQ_UPR_LMT))
						{
							/* VCO output value is in the range, continue the calculations */
							LOC_PLLFreqValue = LOC_VCOOUTValue / Copy_u32PLLP;
							LOC_OTGFreqValue = LOC_VCOOUTValue / Copy_u32PLLQ;

							/* Check that LOC_PLLFreqValue and LOC_OTGFreqValue are in the range */
							if((LOC_PLLFreqValue <= PLL_FREQ_UPR_LMT) && (LOC_OTGFreqValue <= USBOTGFS_FREQ_UPR_LMT))
							{
								/* Seems like all the passed parameters are in the specified ranges,
								 * so We will assign the passed values in the specified register */

								/* Create a local variable as an image of the real register */
								u32 LOC_u32LocalReg = RCC->PLLCFGR;
								/* Clean the bits before assigning in it */
								LOC_u32LocalReg &= ~(PLLM_SETMASK) & ~(PLLN_SETMASK) & ~(PLLP_SETMASK) \
													& ~(PLLQ_SETMASK);
								/* Assign the passed values in the local variable */
								LOC_u32LocalReg |= (Copy_u32PLLM << RCC_PLLCFGR_PLLM)\
													| (Copy_u32PLLN << RCC_PLLCFGR_PLLN)\
													| (Copy_u32PLLP << RCC_PLLCFGR_PLLP)\
													| (Copy_u32PLLQ << RCC_PLLCFGR_PLLQ);
								/* As We finish the configurations, We can assign directly in the
								 * real register */
								RCC->PLLCFGR = LOC_u32LocalReg;
							}
							else
							{
								/* PLL frequency or USBOTGFS frequency exceeds the limits, return NOT OK */
								LOC_enuErrorStatus = RCC_enuNotOk;
							}
						}
						else
						{
							/* VCO output exceeds the limits, return NOT OK */
							LOC_enuErrorStatus = RCC_enuNotOk;
						}
					}
					else
					{
						/* VCO input exceeds the limits, return NOT OK */
						LOC_enuErrorStatus = RCC_enuNotOk;
					}
					break;
				default:
					/* DO Nothing */
					break;
				}
			}
			else
			{
				/* Seems like there is a problem when getting the info of the PLLSRC */
				LOC_enuErrorStatus = RCC_enuNotOk;
			}
		}
		else
		{
			/* Seems that one of the factors is out of the range */
			LOC_enuErrorStatus = RCC_enuNotOk;
		}
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Configure The PLLI2S clock.
 *@param : Values of PLLM, PLLI2SN, PLLI2SR respectively.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigPLLI2SN(u32 Copy_u32PLLM, u32 Copy_u32PLLI2SN, u32 Copy_u32PLLI2SR)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Before an thing we will check that neither PLL nor PLLI2S is enabled */

	if((RCC->CR & PLLON) || (RCC->CR & PLLI2SON))
	{
		/* Return NOT OK, We can not configure M,N,P,Q unless PLL and PLLI2S are disabled */
		LOC_enuErrorStatus = RCC_enuNotOk;
	}
	else
	{
		/* As neither PLL nor PLLI2S is enabled, We can configure them */


		/* Check on all the passed factors that they are in the range specified in the reference manual */
		if (((Copy_u32PLLM >= PLLM_2) && (Copy_u32PLLM <= PLLM_63)) \
				&& ((Copy_u32PLLI2SN >= PLLI2SN_192) && (Copy_u32PLLI2SN <= PLLI2SN_432)) \
				&& ((Copy_u32PLLI2SR >= PLLI2SR_2) && (Copy_u32PLLI2SR <= PLLI2SR_7)))
		{
			/* Since the factors are in the specified range We will assign the values in the bits
			 * making sure that the output frequency from each stage is in the specified range too */

			/* First get the PLL source to know the input clock frequency value that will used in
			 * the calculations and operations */
			u32 LOC_PLLSrc, LOC_VCOINValue, LOC_VCOOUTValue, LOC_I2SFreqValue;
			if ((RCC_enuGetPLLsSrc(&LOC_PLLSrc) == RCC_enuOk))
			{
				switch (LOC_PLLSrc)
				{
				/* In case PLLSRC is HSI, then the input clock frequency is 16 MHz */
				case PLLSRC_HSI:

					/* First We will divide the input clock frequency by PLLM, checking that the output
					 * is in the specified range (from 1 MHz to 2 MHz) */
					LOC_VCOINValue = HSI_VALUE / Copy_u32PLLM;
					if((LOC_VCOINValue >= VCO_IN_FREQ_LWR_LMT) && (LOC_VCOINValue <= VCO_IN_FREQ_UPR_LMT))
					{
						/* VCO input value is in the range, continue the calculations */
						LOC_VCOOUTValue = LOC_VCOINValue * Copy_u32PLLI2SN;

						/* Check whether VCO output value is in the limits or not */
						if ((LOC_VCOOUTValue >= VCO_OUT_FREQ_LWR_LMT) && (LOC_VCOOUTValue <= VCO_OUT_FREQ_UPR_LMT))
						{
							/* VCO output value is in the range, continue the calculations */
							LOC_I2SFreqValue = LOC_VCOOUTValue / Copy_u32PLLI2SR;

							/* Check that LOC_PLLFreqValue and LOC_OTGFreqValue are in the range */
							if(LOC_I2SFreqValue <= PLLI2S_FREQ_UPR_LMT)
							{
								/* Seems like all the passed parameters are in the specified ranges,
								 * so We will assign the passed values in the specified register */

								/* Create a local variable as an image of the real register */
								u32 LOC_u32LocalPLLReg = RCC->PLLCFGR;
								u32 LOC_u32LocalPLLI2SReg = RCC->PLLI2SCFGR;
								/* Clean the bits before assigning in it */
								LOC_u32LocalPLLReg &= ~(PLLM_SETMASK);
								LOC_u32LocalPLLI2SReg &= ~(PLLI2SN_SETMASK) & ~(PLLI2SR_SETMASK);
								/* Assign the passed values in the local variable */
								LOC_u32LocalPLLReg |= (Copy_u32PLLM << RCC_PLLCFGR_PLLM);
								LOC_u32LocalPLLI2SReg |= (Copy_u32PLLI2SN << RCC_PLLI2SCFGR_PLLI2SN)\
														| (Copy_u32PLLI2SR << RCC_PLLI2SCFGR_PLLI2SR);
								/* As We finish the configurations, We can assign directly in the
								 * real register */
								RCC->PLLCFGR = LOC_u32LocalPLLReg;
								RCC->PLLI2SCFGR = LOC_u32LocalPLLI2SReg;
							}
							else
							{
								/* I2S frequency exceeds the limits, return NOT OK */
								LOC_enuErrorStatus = RCC_enuNotOk;
							}
						}
						else
						{
							/* VCO output exceeds the limits, return NOT OK */
							LOC_enuErrorStatus = RCC_enuNotOk;
						}
					}
					else
					{
						/* VCO input exceeds the limits, return NOT OK */
						LOC_enuErrorStatus = RCC_enuNotOk;
					}
					break;
					/* In case PLLSRC is HSE, then the input clock frequency is HSE_CRYSTAL_VALUE MHz */
				case PLLSRC_HSE:

					/* First We will divide the input clock frequency by PLLM, checking that the output
					 * is in the specified range (from 1 MHz to 2 MHz) */
					LOC_VCOINValue = HSE_CRYSTAL_VALUE / Copy_u32PLLM;
					if((LOC_VCOINValue >= VCO_IN_FREQ_LWR_LMT) && (LOC_VCOINValue <= VCO_IN_FREQ_UPR_LMT))
					{
						/* VCO input value is in the range, continue the calculations */
						LOC_VCOOUTValue = LOC_VCOINValue * Copy_u32PLLI2SN;

						/* Check whether VCO output value is in the limits or not */
						if ((LOC_VCOOUTValue >= VCO_OUT_FREQ_LWR_LMT) && (LOC_VCOOUTValue <= VCO_OUT_FREQ_UPR_LMT))
						{
							/* VCO output value is in the range, continue the calculations */
							LOC_I2SFreqValue = LOC_VCOOUTValue / Copy_u32PLLI2SR;

							/* Check that LOC_PLLFreqValue and LOC_OTGFreqValue are in the range */
							if(LOC_I2SFreqValue <= PLLI2S_FREQ_UPR_LMT)
							{
								/* Seems like all the passed parameters are in the specified ranges,
								 * so We will assign the passed values in the specified register */

								/* Create a local variable as an image of the real register */
								u32 LOC_u32LocalPLLReg = RCC->PLLCFGR;
								u32 LOC_u32LocalPLLI2SReg = RCC->PLLI2SCFGR;
								/* Clean the bits before assigning in it */
								LOC_u32LocalPLLReg &= ~(PLLM_SETMASK);
								LOC_u32LocalPLLI2SReg &= ~(PLLI2SN_SETMASK) & ~(PLLI2SR_SETMASK);
								/* Assign the passed values in the local variable */
								LOC_u32LocalPLLReg |= (Copy_u32PLLM << RCC_PLLCFGR_PLLM);
								LOC_u32LocalPLLI2SReg |= (Copy_u32PLLI2SN << RCC_PLLI2SCFGR_PLLI2SN)\
														| (Copy_u32PLLI2SR << RCC_PLLI2SCFGR_PLLI2SR);
								/* As We finish the configurations, We can assign directly in the
								 * real register */
								RCC->PLLCFGR = LOC_u32LocalPLLReg;
								RCC->PLLI2SCFGR = LOC_u32LocalPLLI2SReg;
							}
							else
							{
								/* I2S frequency exceeds the limits, return NOT OK */
								LOC_enuErrorStatus = RCC_enuNotOk;
							}
						}
						else
						{
							/* VCO output exceeds the limits, return NOT OK */
							LOC_enuErrorStatus = RCC_enuNotOk;
						}
					}
					else
					{
						/* VCO input exceeds the limits, return NOT OK */
						LOC_enuErrorStatus = RCC_enuNotOk;
					}
					break;
				default:
					/* DO Nothing */
					break;
				}
			}
			else
			{
				/* Seems like there is a problem when getting the info of the PLLSRC */
				LOC_enuErrorStatus = RCC_enuNotOk;
			}
		}
		else
		{
			/* Seems that one of the factors is out of the range */
			LOC_enuErrorStatus = RCC_enuNotOk;
		}
	}

	return LOC_enuErrorStatus;
}
/**************************************************************************************/



/**
 *@brief : Function to Select the System clock source.
 *@param : Copy_u32SysClk. Options: HSI or HSE or PLL.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuSelectSysClk(u32 Copy_u32SysClk)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the passed value is one of the specified inputs to the user */
	/* The compiler will generate the following warning:
	 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
	 * ignore it */
	if ((Copy_u32SysClk >= SYSCLK_HSI) && (Copy_u32SysClk <= SYSCLK_PLL))
	{
		/* Create a local variable as an image of the real register */
		u32 LOC_u32LocalReg = RCC->CFGR;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(SW_SETMASK);
		/* Assign the passed values in the local variable */
		LOC_u32LocalReg |= Copy_u32SysClk;
		/* As We finish the configurations, We can assign directly in the
		 * real register */
		RCC->CFGR = LOC_u32LocalReg;
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Know the System clock source, will be used inside other functions.
 *@param : Add_u32SysClk, Address of a variable in which the current System clock source will be returned.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuGetSysClk(u32* Add_u32SysClk)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check first that the passed pointer is not a NULL pointer */
	if (Add_u32SysClk == NULL_PTR)
	{
		LOC_enuErrorStatus = RCC_enuNullPointer;
	}
	else
	{
		/* Seems like the user is OK and didn't pass a NULL pointer, let's go */
		switch(RCC->CFGR & SW_SETMASK)
		{
		case SYSCLKSTATUS_HSI:
			*Add_u32SysClk = SYSCLK_HSI;
			break;
		case SYSCLKSTATUS_HSE:
			*Add_u32SysClk = SYSCLK_HSE;
			break;
		case SYSCLKSTATUS_PLL:
			*Add_u32SysClk = SYSCLK_PLL;
			break;
		default:
			/* DO NOTHING */
			break;
		}
	}

	return LOC_enuErrorStatus;
}
/**************************************************************************************/



/**
 *@brief : Function to Enable one of the peripherals connected to AHB1 bus.
 *@param : Copy_u32AHB1Peripheral. Options: AHB1_GPIOA ~ AHB1_GPIOH, AHB1_CRC, AHB1_DMA1 and AHB1_DMA2.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAHB1Peripheral(u32 Copy_u32AHB1Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if ((Copy_u32AHB1Peripheral >= AHB1_GPIOA) && (Copy_u32AHB1Peripheral <= AHB1_DMA2))
	{
		/* Set the responsible bit to enable the peripheral */
		RCC->AHB1ENR |= Copy_u32AHB1Peripheral;
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Disable one of the peripherals connected to AHB1 bus.
 *@param : Copy_u32AHB1Peripheral. Options: AHB1_GPIOA ~ AHB1_GPIOH, AHB1_CRC, AHB1_DMA1 and AHB1_DMA2.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAHB1Peripheral(u32 Copy_u32AHB1Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if ((Copy_u32AHB1Peripheral >= AHB1_GPIOA) && (Copy_u32AHB1Peripheral <= AHB1_DMA2))
	{
		/* Clear the responsible bit to disable the peripheral */
		RCC->AHB1ENR &= ~(Copy_u32AHB1Peripheral);
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Enable one of the peripherals connected to AHB2 bus.
 *@param : Copy_u32AHB2Peripheral. Options: AHB2_USBOTGFS.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAHB2Peripheral(u32 Copy_u32AHB2Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if (Copy_u32AHB2Peripheral == AHB2_USBOTGFS)
	{
		/* Set the responsible bit to enable the peripheral */
		RCC->AHB2ENR |= (Copy_u32AHB2Peripheral);
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Disable one of the peripherals connected to AHB2 bus.
 *@param : Copy_u32AHB2Peripheral. Options: AHB2_USBOTGFS.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAHB2Peripheral(u32 Copy_u32AHB2Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if (Copy_u32AHB2Peripheral == AHB2_USBOTGFS)
	{
		/* Clear the responsible bit to disable the peripheral */
		RCC->AHB2ENR &= ~(Copy_u32AHB2Peripheral);
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Enable one of the peripherals connected to APB1 bus.
 *@param : Copy_u32APB1Peripheral. Options: 	APB1_TIM2 ~ APB1_TIM5, APB1_WWDG, APB1_SPI2, APB1_SPI3,
 *											APB1_USART2, APB1_I2C1 ~ APB1_I2C3 and APB1_PWR.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAPB1Peripheral(u32 Copy_u32APB1Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if ((Copy_u32APB1Peripheral >= APB1_TIM2) && (Copy_u32APB1Peripheral <= APB1_PWR))
	{
		/* Set the responsible bit to enable the peripheral */
		RCC->APB1ENR |= (Copy_u32APB1Peripheral);
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Disable one of the peripherals connected to APB1 bus.
 *@param : Copy_u32APB1Peripheral. Options: 	APB1_TIM2 ~ APB1_TIM5, APB1_WWDG, APB1_SPI2, APB1_SPI3,
 *											APB1_USART2, APB1_I2C1 ~ APB1_I2C3 and APB1_PWR.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAPB1Peripheral(u32 Copy_u32APB1Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if ((Copy_u32APB1Peripheral >= APB1_TIM2) && (Copy_u32APB1Peripheral <= APB1_PWR))
	{
		/* Clear the responsible bit to disable the peripheral */
		RCC->APB1ENR &= ~(Copy_u32APB1Peripheral);
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Enable one of the peripherals connected to APB2 bus.
 *@param : Copy_u32APB2Peripheral. Options: TIM1, USART1, USART6, ADC1, SDIO, SPI1, SPI4, SYSCFG, TIM9 ~ TIM11.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAPB2Peripheral(u32 Copy_u32APB2Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if ((Copy_u32APB2Peripheral >= APB2_TIM1) && (Copy_u32APB2Peripheral <= APB2_TIM11))
	{
		/* Set the responsible bit to enable the peripheral */
		RCC->APB2ENR |= (Copy_u32APB2Peripheral);
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}




/**
 *@brief : Function to Disable one of the peripherals connected to APB2 bus.
 *@param : Copy_u32APB2Peripheral. Options: TIM1, USART1, USART6, ADC1, SDIO, SPI1, SPI4, SYSCFG, TIM9 ~ TIM11.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAPB2Peripheral(u32 Copy_u32APB2Peripheral)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input argument is in the range */
	if ((Copy_u32APB2Peripheral >= APB2_TIM1) && (Copy_u32APB2Peripheral <= APB2_TIM11))
	{
		/* Clear the responsible bit to disable the peripheral */
		RCC->APB2ENR &= ~(Copy_u32APB2Peripheral);
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}
/**************************************************************************************/



/**
 *@brief : Function to Configure the pre-scaler of the AHB clock source.
 *@param : Copy_u32AHBPRES. Options: 	AHBPRES_1, AHBPRES_2, AHBPRES_4,
 *										AHBPRES_8, AHBPRES_16, AHBPRES_64,
 *										AHBPRES_128, AHBPRES_256, AHBPRES_512.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigAHBPRES(u32 Copy_u32AHBPRES)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input parameters are in the range */
	/* The compiler will generate the following warning:
	 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
	 * ignore it */
	if ((Copy_u32AHBPRES >= AHBPRES_1) && (Copy_u32AHBPRES <= AHBPRES_512))
	{
		/* Create a local variable as an image of the real register */
		u32 LOC_u32LocalReg = RCC->CFGR;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(AHBPRES_SETMASK);
		/* Assign the passed values in the local variable */
		LOC_u32LocalReg |= (Copy_u32AHBPRES);
		/* As We finish the configurations, We can assign directly in the
		 * real register */
		RCC->CFGR = LOC_u32LocalReg;
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}



/**
 *@brief : Function to Configure the pre-scaler of the APB1 clock source.
 *@param : Copy_u32APB1PRES. Options: 	APB1PRES_1, APB1PRES_2, APB1PRES_4,
 *										APB1PRES_8, APB1PRES_16.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigAPB1PRES(u32 Copy_u32APB1PRES)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input parameters are in the range */
	/* The compiler will generate the following warning:
	 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
	 * ignore it */
	if ((Copy_u32APB1PRES >= APB1PRES_1) && (Copy_u32APB1PRES <= APB1PRES_16))
	{
		/* Create a local variable as an image of the real register */
		u32 LOC_u32LocalReg = RCC->CFGR;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(APB1PRES_SETMASK);
		/* Assign the passed values in the local variable */
		LOC_u32LocalReg |= (Copy_u32APB1PRES);
		/* As We finish the configurations, We can assign directly in the
		 * real register */
		RCC->CFGR = LOC_u32LocalReg;
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Configure the pre-scaler of the APB2 clock source.
 *@param : Copy_u32APB2PRES. Options: 	APB2PRES_1, APB2PRES_2, APB2PRES_4,
 *										APB2PRES_8, APB2PRES_16.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigAPB2PRES(u32 Copy_u32APB2PRES)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input parameters are in the range */
	/* The compiler will generate the following warning:
	 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
	 * ignore it */
	if ((Copy_u32APB2PRES >= APB2PRES_1) && (Copy_u32APB2PRES <= APB2PRES_16))
	{
		/* Create a local variable as an image of the real register */
		u32 LOC_u32LocalReg = RCC->CFGR;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(APB2PRES_SETMASK);
		/* Assign the passed values in the local variable */
		LOC_u32LocalReg |= (Copy_u32APB2PRES);
		/* As We finish the configurations, We can assign directly in the
		 * real register */
		RCC->CFGR = LOC_u32LocalReg;
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


/**
 *@brief : Function to Control the clock frequency of all the timers connected to APB1 and APB2 domain..
 *@param : Copy_u32TIMsPRES. Options: 	TIMPRE_0, TIMPRE_1.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigTimersPRES(u32 Copy_u32TIMsPRES)
{
	RCC_enuErrorStatus_t LOC_enuErrorStatus = RCC_enuOk;

	/* Check that the input parameters are in the range */
	/* The compiler will generate the following warning:
	 * "comparison of unsigned expression >= 0 is always true [-Wtype-limits]"
	 * ignore it */
	if ((Copy_u32TIMsPRES >= TIMPRE_0) && (Copy_u32TIMsPRES <= TIMPRE_1))
	{
		/* Create a local variable as an image of the real register */
		u32 LOC_u32LocalReg = RCC->DCKCFGR;
		/* Clean the bits before assigning in it */
		LOC_u32LocalReg &= ~(TIMPRE_1);
		/* Assign the passed values in the local variable */
		LOC_u32LocalReg |= (Copy_u32TIMsPRES);
		/* As We finish the configurations, We can assign directly in the
		 * real register */
		RCC->DCKCFGR = LOC_u32LocalReg;
	}
	else
	{
		LOC_enuErrorStatus = RCC_enuNotOk;
	}

	return LOC_enuErrorStatus;
}


