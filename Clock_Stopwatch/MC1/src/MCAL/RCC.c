#include <MCAL/RCC.h>
/************************************************Defines:*********************************************************************/
#define RCC_BASE 						0x40023800U  

#define RCC_HSIRDY       				0x00000002  	// HSI clock ready flag
#define RCC_HSERDY      	 			0x00020000  	// HSE clock ready flag
#define RCC_PLLRDY	       				0x02000000  	// PLL clock ready flag

#define RCC_HSE_BYPASS_ON				0x00040000		//Bypassed

#define RCC_PLLCFGR_PLLQ_OFFSET       	0x00000018  	// PLLQ[3:0]: Main PLL division factor for USB OTG FS, SDIO, and RNG
#define RCC_PLLCFGR_PLLP_OFFSET       	0x00000010  	// PLLP[1:0]: Main PLL division factor for main system clock
#define RCC_PLLCFGR_PLLN_OFFSET       	0x00000006  	// PLLN[8:0]: Main PLL multiplication factor for VCO
#define RCC_PLLCFGR_PLLM_OFFSET       	0x00000000  	// PLLM[5:0]: Division factor for the main PLL and audio PLL
#define RCC_PLLCFGR_MASK				0x0F037FFF
#define RCC_PPRE2_CLEAR_MASK 			0x0000E000		//APB2 Prescaler Mask 
#define RCC_PPRE1_CLEAR_MASK 			0x00001C00		//APB1 Prescaler Mask 
/************************************************RCC peripheral structure*****************************************************/
typedef struct {
	volatile uint32_t CR;      					/*!< RCC clock control register */
	volatile uint32_t PLLCFGR; 					/*!< RCC PLL configuration register */
	volatile uint32_t CFGR;    					/*!< RCC clock configuration register */
	volatile uint32_t CIR;     					/*!< RCC clock interrupt register */
	volatile uint32_t AHB1RSTR; 				/*!< RCC AHB1 peripheral reset register */
	volatile uint32_t AHB2RSTR; 				/*!< RCC AHB2 peripheral reset register */
	uint32_t RESERVED0[2];        				/*!< Reserved, 0x1C */
	volatile uint32_t APB1RSTR; 				/*!< RCC APB1 peripheral reset register */
	volatile uint32_t APB2RSTR; 				/*!< RCC APB2 peripheral reset register */
	uint32_t RESERVED1[2];     					/*!< Reserved, 0x28-0x2C */
	volatile uint32_t AHB1ENR;  				/*!< RCC AHB1 peripheral clock enable register */
	volatile uint32_t AHB2ENR;  				/*!< RCC AHB2 peripheral clock enable register */
	uint32_t RESERVED2[2];         				/*!< Reserved, 0x3C */
	volatile uint32_t APB1ENR;  				/*!< RCC APB1 peripheral clock enable register */
	volatile uint32_t APB2ENR;  				/*!< RCC APB2 peripheral clock enable register */
	uint32_t RESERVED3[2];      				/*!< Reserved, 0x48-0x4C */
	volatile uint32_t AHB1LPENR; 				/*!< RCC AHB1 peripheral clock enable in low power mode register */
	volatile uint32_t AHB2LPENR; 				/*!< RCC AHB2 peripheral clock enable in low power mode register */
	uint32_t RESERVED4[2];         				/*!< Reserved, 0x5C */
	volatile uint32_t APB1LPENR; 				/*!< RCC APB1 peripheral clock enable in low power mode register */
	volatile uint32_t APB2LPENR; 				/*!< RCC APB2 peripheral clock enable in low power mode register */
	uint32_t RESERVED5[2];      				/*!< Reserved, 0x68-0x6C */
	volatile uint32_t BDCR;     				/*!< RCC Backup domain control register */
	volatile uint32_t CSR;      				/*!< RCC clock control & status register */
	uint32_t RESERVED6[2];      				/*!< Reserved, 0x78-0x7C */
	volatile uint32_t SSCGR;    				/*!< RCC spread spectrum clock generation register */
	volatile uint32_t PLLI2SCFGR; 				/*!< RCC PLLI2S configuration register */
	uint32_t RESERVED7; 						/*!< RCC PLL configuration register */
	volatile uint32_t DCKCFGR;   				/*!< RCC Dedicated Clocks configuration register1 */
} RCC_T;
RCC_T *const RCC = (RCC_T *) RCC_BASE;

/************************************************Static Functions**************************************************************/
static uint32_t RCC_CheckReadyFlag(uint32_t sysclk)
{
	uint32_t value;
	if((sysclk == RCC_SYSCLK_HSE))
	{
		value = RCC->CR & RCC_HSERDY;
	}
	else if((sysclk == RCC_SYSCLK_HSI) || (sysclk == RCC_ClkHSION))
	{
		value = RCC->CR & RCC_HSIRDY;
	}
	else if((sysclk == RCC_SYSCLK_PLL) || (sysclk == RCC_ClkPLLON))
	{
		value = RCC->CR & RCC_PLLRDY;
	}
	return value;
}
/************************************************GLOBAL FUNCTIONS**************************************************************/
/**
*@brief  : function to control any clock. Before calling this Function, You MUST be sure the selected clock is not the system clock.
*@param  : Type(Name)of clock, status of clock
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_ControlClock (uint32_t clock, RCC_enumStatus_t Status)
{
	ErrorStatus_t Loc_return = Ok;
	if((Status != Status_Disable)&&(Status != Status_Enable))
	{
		Loc_return = ArgumentError;
	}

	else if ((clock != RCC_ClkHSEON)&&(clock != RCC_ClkHSEON)&&(clock != RCC_ClkHSION)&&(clock != RCC_ClkPLLON))
	{
		Loc_return = ArgumentError;
	}
	
	else
	{
		Loc_return = Ok;
		switch (Status)
		{
			case Status_Disable:
				RCC->CR &= ~clock;
			break;
			
			case Status_Enable:
				RCC->CR |= clock;
			break;

			default:
					/*do nothing*/
			break;
		}
	}

	return Loc_return;
}

/**
*@brief  : function to configure the PLL Clock. Before calling this Function, You MUST be sure PLL is not the system clock 
			and the pll source selected is on and ready. 
*@param  : source of PLL, M[2:63] , N[192:432], p[2:15], q[2,4,6,8].
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_ConfigurePLL (uint32_t RCC_PLLSRC, uint32_t Copy_M, uint32_t Copy_N, uint32_t copy_p, uint32_t copy_q)
{
	ErrorStatus_t Loc_Return = Ok;
	if((RCC_PLLSRC != RCC_PLLSRC_HSE)&&(RCC_PLLSRC != RCC_PLLSRC_HSI))
	{
		Loc_Return = ArgumentError;
	}
	else if ((Copy_M <= 2)||(Copy_M >= 63))
	{
		Loc_Return = ArgumentError;
	}
	else if ((Copy_N <= 192)||(Copy_N >= 432))
	{
		Loc_Return = ArgumentError;
	}
	else if ((copy_q <= 2)||(copy_q >= 15))
	{
		Loc_Return = ArgumentError;
	}
	else if ((copy_p != 2)&&(copy_p != 4)&&(copy_p != 6)&&(copy_p != 8))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		Loc_Return = Ok;
		/*selected clock to PLL*/
		RCC->PLLCFGR |= RCC_PLLSRC;
		/*convert p to binary value*/
		copy_p = (copy_p / 2) - 1;
		/*set M, N, P and Q values*/
		uint32_t LOC_PLLCFGRvalue = RCC->PLLCFGR;
		LOC_PLLCFGRvalue &= ~RCC_PLLCFGR_MASK;
		LOC_PLLCFGRvalue |= Copy_M << RCC_PLLCFGR_PLLM_OFFSET;
		LOC_PLLCFGRvalue |= Copy_N << RCC_PLLCFGR_PLLN_OFFSET;
		LOC_PLLCFGRvalue |= copy_p << RCC_PLLCFGR_PLLP_OFFSET;
		LOC_PLLCFGRvalue |= copy_q << RCC_PLLCFGR_PLLQ_OFFSET;
		RCC->PLLCFGR = LOC_PLLCFGRvalue;
	}

	return Loc_Return;	
}

/**
*@brief  : function to Select System Clock. Before calling this Function, You MUST be sure the selected clock is enabled and have their time to be ready
*@param  : System Clock
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_SelectSystemClock(uint32_t SysClk)
{
	ErrorStatus_t Loc_Return = Ok;
	if( (SysClk != RCC_SYSCLK_HSE) && (SysClk != RCC_SYSCLK_HSI) && (SysClk != RCC_SYSCLK_PLL) )
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		Loc_Return = Ok;
		if (RCC_CheckReadyFlag(SysClk))
		{
			RCC->CFGR |= SysClk;
		}
		else
		{
			Loc_Return = NotOk;
		}
	}
	return Loc_Return;
}

/**
*@brief  : function to configure the HSE bypass state, Before calling this function please insure that HSE is not the current system clock.
*@param  : BypassState
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_Control_HSEBypass(uint32_t status)
{
	ErrorStatus_t Loc_Return = Ok;
	if((status != Status_Disable) || (status != Status_Enable))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		switch (status)
		{
		case Status_Disable:
			RCC->CR &= ~(RCC_HSE_BYPASS_ON);	
		break;
		
		case Status_Enable:
			RCC->CR |= RCC_HSE_BYPASS_ON;
		break;

		default:
			/*do nothing*/
		break;
		}
		Loc_Return = Ok;
	}
	return Loc_Return;
}

/**
*@brief  : function to control on any clock. Before calling this Function, You MUST be sure the selected preipheral connected to AHB1.
*@param  : ClockName, status
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_Control_AHB1Peripherals(uint32_t RCC_PERI_AHB1, RCC_enumStatus_t Status)
{
	ErrorStatus_t Loc_Return = Ok;
	if((Status != Status_Enable) && (Status != Status_Disable))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		Loc_Return = Ok;
		switch (Status)
		{
			case Status_Enable:
				RCC->AHB1ENR |= RCC_PERI_AHB1;
			break;
			
			case Status_Disable:
				RCC->AHB1ENR &= ~RCC_PERI_AHB1;
			break;

			default:
				/*do nothing*/
			break;
		}
	}
	return Loc_Return;
}

/**
*@brief  : function to control on any clock. Before calling this Function, You MUST be sure the selected preipheral connected to AHB2.
*@param  : ClockName, status
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_Control_AHB2Peripherals(uint32_t RCC_PERI_AHB2, RCC_enumStatus_t Status)
{
		ErrorStatus_t Loc_Return = Ok;
	if((Status != Status_Enable) && (Status != Status_Disable))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		Loc_Return = Ok;
		switch (Status)
		{
			case Status_Enable:
				RCC->AHB2ENR |= RCC_PERI_AHB2;
			break;
			
			case Status_Disable:
				RCC->AHB2ENR &= ~RCC_PERI_AHB2;
			break;

			default:
				/*do nothing*/
			break;
		}
	}
	return Loc_Return;
}

/**
*@brief  : function to control on any clock. Before calling this Function, You MUST be sure the selected preipheral connected to APB1.
*@param  : ClockName, status
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_Control_APB1Peripherals(uint32_t RCC_PERI_APB1, RCC_enumStatus_t Status)
{
	ErrorStatus_t Loc_Return = Ok;
	if((Status != Status_Enable) && (Status != Status_Disable))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		Loc_Return = Ok;
		switch (Status)
		{
			case Status_Enable:
				RCC->APB1ENR |= RCC_PERI_APB1;
			break;
			
			case Status_Disable:
				RCC->APB1ENR &= ~RCC_PERI_APB1;
			break;

			default:
				/*do nothing*/
			break;
		}
	}
	return Loc_Return;
}

/**
*@brief  : function to control on any clock. Before calling this Function, You MUST be sure the selected preipheral connected to APB2.
*@param  : ClockName, status
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_Control_APB2Peripherals(uint32_t RCC_PERI_APB2, RCC_enumStatus_t Status)
{
	ErrorStatus_t Loc_Return = Ok;
	if((Status != Status_Enable) && (Status != Status_Disable))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		Loc_Return = Ok;
		switch (Status)
		{
			case Status_Enable:
				RCC->APB2ENR |= RCC_PERI_APB2;
			break;
			
			case Status_Disable:
				RCC->APB2ENR &= ~RCC_PERI_APB2;
			break;

			default:
				/*do nothing*/
			break;
		}
	}
	return Loc_Return;	
}

/**
*@brief  : function to configure the value of APB2 pre_scaler.
*@param  : PreScaler
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_ConfigureAPB2_PreScaler(uint32_t RCC_APB2_PRESCALER)
{
	ErrorStatus_t Loc_Return = Ok;
	if((RCC_APB2_PRESCALER !=RCC_APB2_PRESCALER_DIV1) && (RCC_APB2_PRESCALER !=RCC_APB2_PRESCALER_DIV2) && (RCC_APB2_PRESCALER !=RCC_APB2_PRESCALER_DIV4) && (RCC_APB2_PRESCALER !=RCC_APB2_PRESCALER_DIV8) && (RCC_APB2_PRESCALER !=RCC_APB2_PRESCALER_DIV16))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		uint32_t TempReg = RCC->CFGR;
		TempReg &= ~RCC_PPRE2_CLEAR_MASK;
		TempReg |= RCC_APB2_PRESCALER;
		RCC->CFGR = TempReg;
		Loc_Return = Ok; 
	}
	return Loc_Return;
}

/**
*@brief  : function to configure the value of APB1 pre_scaler.
*@param  : PreScaler
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_ConfigureAPB1_PreScaler(uint32_t RCC_APB1_PRESCALER)
{
	ErrorStatus_t Loc_Return = Ok;
	if((RCC_APB1_PRESCALER !=RCC_APB1_PRESCALER_DIV1) && (RCC_APB1_PRESCALER !=RCC_APB1_PRESCALER_DIV2) && (RCC_APB1_PRESCALER !=RCC_APB1_PRESCALER_DIV4) && (RCC_APB1_PRESCALER !=RCC_APB1_PRESCALER_DIV8) && (RCC_APB1_PRESCALER !=RCC_APB1_PRESCALER_DIV16))
	{
		Loc_Return = ArgumentError;
	}
	else
	{
		uint32_t TempReg = RCC->CFGR;
		TempReg &= ~RCC_PPRE1_CLEAR_MASK;
		TempReg |= RCC_APB1_PRESCALER;
		RCC->CFGR = TempReg;
		Loc_Return = Ok; 
	}
	return Loc_Return;
}

/**
*@brief  : function to configure the value of AHB pre_scaler.
*@param  : PreScaler
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t RCC_ConfigureAHB_PreScaler(uint32_t RCC_AHB_PRESCALER)
{
	ErrorStatus_t Loc_return = Ok;
	if(( RCC_AHB_PRESCALER < RCC_AHB_PRESCALER_DIV1) && (RCC_AHB_PRESCALER > RCC_AHB_PRESCALER_DIV512))
	{
		Loc_return = ArgumentError;
	}
	else
	{
		uint32_t TempReg = RCC->CFGR;
		TempReg &= ~RCC_AHB_PRESCALER_DIV512;
		TempReg |= RCC_AHB_PRESCALER;
		RCC->CFGR = TempReg;
		Loc_return = Ok; 
	}
	return Loc_return;
}