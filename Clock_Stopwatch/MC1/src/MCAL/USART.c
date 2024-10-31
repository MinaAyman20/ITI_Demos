#include "MCAL/USART.h"

#define USART1_BASE_ADDRESS             0x40011000
#define USART2_BASE_ADDRESS             0x40004400
#define USART6_BASE_ADDRESS             0x40011400

#define OVERSAMPLING_BIT				15
#define WORDLENGTH_BIT					12
#define MANTISSA_BIT					4
#define FRACTION_MSK					0x0F
#define PARITY_CONTROL_BIT				10
#define PARITY_SELECTION_BIT			9
#define TX_ENABLE_BIT					3
#define RX_ENABLE_BIT					2
#define USART_ENABLE_BIT				13
#define TRANSMIT_COMPLETE_BIT			6
#define TX_DATA_EMPTY_BIT				7
#define RX_DATA_NOT_EMPTY_BIT			5

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_T;

typedef struct
{
	uint8_t Transmit;
	uint8_t TX_DR_Empty;
	uint8_t RX_DR_Empty;

}Interrupt_State;


static USART_T * const USART_1 = (USART_T*)USART1_BASE_ADDRESS;
static USART_T * const USART_2 = (USART_T*)USART2_BASE_ADDRESS;
static USART_T * const USART_6 = (USART_T*)USART6_BASE_ADDRESS;

static Interrupt_State Loc_Interrupt_Cfg_Arr;

/* Variable to keep track of the usart status throughout the code (TX)*/
static uint8_t USART_prvTXBusyFlag[3];
static uint8_t USART_prvTXBufferIndex[3];
static uint8_t USART_prvTXBufferSize[3];
static CallBack	cbfTX[3];

/* Variable to keep track of the usart status throughout the code (RX)*/
static uint8_t USART_prvRxBusyFlag[3];
static uint8_t USART_prvRxBufferIndex[3];
static uint8_t USART_prvRxBufferSize[3];
static uint8_t * USART_prvRxBufferReceive[3];
static CallBack	cbfRX[3];

static uint8_t * USART1_addBufferValue;
static uint8_t * USART2_addBufferValue;
static uint8_t * USART6_addBufferValue;


USART_ErrorStatus USART_Init(const USART_Config* ConfigPtr)
{
	USART_ErrorStatus ErrorStatus = USART_enuNOK;
	uint32_t Loc_u32TempValue;
	uint16_t Loc_u16TempMantissa;
	uint16_t Loc_u16TempFraction;

	if(ConfigPtr == NULL)
	{
		 ErrorStatus = USART_enuNullPointer;
	}
	else
	{
		Loc_u32TempValue = ((uint64_t)F_CLK * 1000) / (ConfigPtr->BaudRate * (8 * (2 - ConfigPtr->Oversampling)));
		Loc_u16TempFraction = (Loc_u32TempValue % 1000) * (8 * (2 - ConfigPtr->Oversampling));
		Loc_u16TempFraction = Loc_u16TempFraction / 1000;

		if(Loc_u16TempFraction > 0xF)
		{
			Loc_u16TempMantissa += (Loc_u16TempFraction & 0xF0);
		}
		Loc_u16TempMantissa = Loc_u32TempValue / 1000;

		switch(ConfigPtr->Channel)
		{
			case USART1:
				USART_1->BRR = (Loc_u16TempMantissa << MANTISSA_BIT) | (Loc_u16TempFraction & FRACTION_MSK);
				USART_1->CR1 = 0;
				USART_1->CR1 |= ConfigPtr->Oversampling << OVERSAMPLING_BIT;
				USART_1->CR1 |= ConfigPtr->WordLength << WORDLENGTH_BIT;
				if (ConfigPtr->ParityControl != PARITY_NONE)
				{
					USART_1->CR1 |= 1 << PARITY_CONTROL_BIT;
					USART_1->CR1 |= ConfigPtr->ParityControl << PARITY_SELECTION_BIT;
				}
				USART_1->CR1 |= ConfigPtr->TransEnable << TX_ENABLE_BIT;
				USART_1->CR1 |= ConfigPtr->ReceiveEnable << RX_ENABLE_BIT;

				Loc_Interrupt_Cfg_Arr.Transmit = ConfigPtr->TransComplete_Int << TRANSMIT_COMPLETE_BIT;
				Loc_Interrupt_Cfg_Arr.TX_DR_Empty = ConfigPtr->TransDateRegisterEmpty_Int << TX_DATA_EMPTY_BIT;
				Loc_Interrupt_Cfg_Arr.RX_DR_Empty = ConfigPtr->ReceiveDateRegisterEmpty_Int << RX_DATA_NOT_EMPTY_BIT;

				USART_1->CR1 |= ConfigPtr->USART_Enable << USART_ENABLE_BIT;
				USART_1->SR = 0;
				ErrorStatus = USART_enuOK;
				break;


			case USART2:
				USART_2->BRR = (Loc_u16TempMantissa << MANTISSA_BIT) | (Loc_u16TempFraction & FRACTION_MSK);
				USART_2->CR1 = 0;
				USART_2->CR1 |= ConfigPtr->Oversampling << OVERSAMPLING_BIT;
				USART_2->CR1 |= ConfigPtr->WordLength << WORDLENGTH_BIT;
				if (ConfigPtr->ParityControl != PARITY_NONE)
				{
					USART_2->CR1 |= 1 << PARITY_CONTROL_BIT;
					USART_2->CR1 |= ConfigPtr->ParityControl << PARITY_SELECTION_BIT;
				}
				USART_2->CR1 |= ConfigPtr->TransEnable << TX_ENABLE_BIT;
				USART_2->CR1 |= ConfigPtr->ReceiveEnable << RX_ENABLE_BIT;

				Loc_Interrupt_Cfg_Arr.Transmit = ConfigPtr->TransComplete_Int << TRANSMIT_COMPLETE_BIT;
				Loc_Interrupt_Cfg_Arr.TX_DR_Empty = ConfigPtr->TransDateRegisterEmpty_Int << TX_DATA_EMPTY_BIT;
				Loc_Interrupt_Cfg_Arr.RX_DR_Empty = ConfigPtr->ReceiveDateRegisterEmpty_Int << RX_DATA_NOT_EMPTY_BIT;

				USART_2->CR1 |= ConfigPtr->USART_Enable << USART_ENABLE_BIT;
				USART_2->SR = 0;
				ErrorStatus = USART_enuOK;
				break;


			case USART6:
				USART_6->BRR = (Loc_u16TempMantissa << MANTISSA_BIT) | (Loc_u16TempFraction & FRACTION_MSK);
				USART_6->CR1 = 0;
				USART_6->CR1 |= ConfigPtr->Oversampling << OVERSAMPLING_BIT;
				USART_6->CR1 |= ConfigPtr->WordLength << WORDLENGTH_BIT;
				if (ConfigPtr->ParityControl != PARITY_NONE)
				{
					USART_6->CR1 |= 1 << PARITY_CONTROL_BIT;
					USART_6->CR1 |= ConfigPtr->ParityControl << PARITY_SELECTION_BIT;
				}
				USART_6->CR1 |= ConfigPtr->TransEnable << TX_ENABLE_BIT;
				USART_6->CR1 |= ConfigPtr->ReceiveEnable << RX_ENABLE_BIT;

				Loc_Interrupt_Cfg_Arr.Transmit = ConfigPtr->TransComplete_Int << TRANSMIT_COMPLETE_BIT;
				Loc_Interrupt_Cfg_Arr.TX_DR_Empty = ConfigPtr->TransDateRegisterEmpty_Int << 7;
				Loc_Interrupt_Cfg_Arr.RX_DR_Empty = ConfigPtr->ReceiveDateRegisterEmpty_Int << 5;

				USART_6->CR1 |= ConfigPtr->USART_Enable << USART_ENABLE_BIT;
				USART_6->SR = 0;
				ErrorStatus = USART_enuOK;
				break;
		}
	}
	return ErrorStatus;
}


USART_ErrorStatus USART_SendByteAsynchronous(USART_Channel Channel, uint8_t Copy_Data)
{
	USART_ErrorStatus ErrorStatus = USART_enuNOK;

	if(USART_prvTXBusyFlag[Channel] == 1)
	{
		ErrorStatus = USART_enuBusy;
	}
	else
	{
		switch(Channel)
			{
			case USART1:
				USART_1->DR = Copy_Data;
				USART_prvTXBusyFlag[Channel] = 1;
				USART_prvTXBufferIndex[Channel] = 1;
				USART_prvTXBufferSize[Channel] = 1;
				USART_1->CR1 |= Loc_Interrupt_Cfg_Arr.Transmit;
				ErrorStatus = USART_enuOK;
				break;

			case USART2:
				USART_2->DR = Copy_Data;
				USART_prvTXBusyFlag[Channel] = 1;
				USART_prvTXBufferIndex[Channel] = 1;
				USART_prvTXBufferSize[Channel] = 1;
				USART_2->CR1 |= Loc_Interrupt_Cfg_Arr.Transmit;
				ErrorStatus = USART_enuOK;
				break;

			case USART6:
				USART_6->DR = Copy_Data;
				USART_prvTXBusyFlag[Channel] = 1;
				USART_prvTXBufferIndex[Channel] = 1;
				USART_prvTXBufferSize[Channel] = 1;
				USART_6->CR1 |= Loc_Interrupt_Cfg_Arr.Transmit;
				ErrorStatus = USART_enuOK;
				break;
			}
	}
	return ErrorStatus;
}


USART_ErrorStatus USART_ReceiveBuffer(USART_RXBuffer * ReceiveBuffer)
{
	USART_ErrorStatus ErrorStatus = USART_enuNOK;
	if(USART_prvRxBusyFlag[ReceiveBuffer->Channel] == 0)
	{
		USART_prvRxBufferReceive[ReceiveBuffer->Channel] = (uint8_t *)&ReceiveBuffer->Data;
		USART_prvRxBufferIndex[ReceiveBuffer->Channel] = ReceiveBuffer->Index; 
		USART_prvRxBufferSize[ReceiveBuffer->Channel] = ReceiveBuffer->Size;
		USART_prvRxBusyFlag[ReceiveBuffer->Channel] = 1;

		switch(ReceiveBuffer->Channel)
		{
			case USART1:
				USART_1->CR1 |= Loc_Interrupt_Cfg_Arr.RX_DR_Empty;
				ErrorStatus = USART_enuOK;
				break;

			case USART2:
				USART_2->CR1 |= Loc_Interrupt_Cfg_Arr.RX_DR_Empty;
				ErrorStatus = USART_enuOK;
				break;

			case USART6:
				USART_6->CR1 |= Loc_Interrupt_Cfg_Arr.RX_DR_Empty;
				ErrorStatus = USART_enuOK;
				break;
		}
	}
	else
	{
		ErrorStatus = USART_enuBusy;
	}
	return ErrorStatus;
}


USART_ErrorStatus USART_SendBufferZeroCopy(USART_TXBuffer* Copy_ConfigBuffer)
{
	USART_ErrorStatus ErrorStatus = USART_enuNOK;

	if(Copy_ConfigBuffer == NULL)
	{
		ErrorStatus = USART_enuNullPointer;

	}

	else if(USART_prvTXBusyFlag[Copy_ConfigBuffer->Channel] == 1)
	{
		ErrorStatus = USART_enuBusy;

	}

	else
	{
		switch(Copy_ConfigBuffer->Channel)
		{
		case USART1:

			USART1_addBufferValue = Copy_ConfigBuffer->Data;
			USART_1->DR  = Copy_ConfigBuffer->Data[USART_prvTXBufferIndex[USART1]];
			ErrorStatus = USART_enuOK;
			break;

		case USART2:

			USART2_addBufferValue = Copy_ConfigBuffer->Data;
			USART_2->DR  = Copy_ConfigBuffer->Data[USART_prvTXBufferIndex[USART2]];
			ErrorStatus = USART_enuOK;
			break;

		case USART6:

			USART6_addBufferValue = Copy_ConfigBuffer->Data;
			USART_6->DR  = Copy_ConfigBuffer->Data[USART_prvTXBufferIndex[USART6]];
			ErrorStatus = USART_enuOK;
			break;

		}

		USART_prvTXBusyFlag[Copy_ConfigBuffer->Channel] = 1;
		USART_prvTXBufferIndex[Copy_ConfigBuffer->Channel] = 1;
		USART_prvTXBufferSize[Copy_ConfigBuffer->Channel] = Copy_ConfigBuffer->Size;
		USART_1->CR1 |= Loc_Interrupt_Cfg_Arr.Transmit;


	}
	return ErrorStatus;

}


USART_ErrorStatus USART_RegisterCallBackFunction(USART_Channel Channel, USART_Mode Mode, CallBack CallBackFunction)
{
	USART_ErrorStatus ErrorStatus = USART_enuNOK;
	if(CallBackFunction)
	{
		if (Mode == SEND)
		{
			cbfTX[Channel] = CallBackFunction;
			ErrorStatus = USART_enuOK;
		}
		else if (Mode == RECEIVE)
		{
			cbfRX[Channel] = CallBackFunction;
			ErrorStatus = USART_enuOK;
		}
	}
	else
	{
		ErrorStatus = USART_enuNullPointer;
	}
	return ErrorStatus;
}


void USART1_IRQHandler(void)
{
	if((USART_1->SR >> 6) & 0x01)
	{
		if(USART_prvTXBufferIndex[USART1] == USART_prvTXBufferSize[USART1])
		{
			USART_prvTXBusyFlag[USART1] = 0;
			USART_prvTXBufferSize[USART1] = 0;
			if(cbfTX[USART1])
			{			
				cbfTX[USART1]();
			}
			USART_1->SR &= ~(1 << 6);
		}
		else
		{
			USART_1->SR &= ~(1 << 6);
			USART_1->DR = USART1_addBufferValue[USART_prvTXBufferIndex[USART1]];
			USART_prvTXBufferIndex[USART1]++;
		}
	}

	if(USART_prvRxBusyFlag[USART1] == 1 && ((USART_1->SR >> 5) & 0x01))
	{
		USART_prvRxBufferReceive[USART1][USART_prvRxBufferIndex[USART1]] = USART_1->DR;
		USART_prvRxBufferIndex[USART1]++;
		if(USART_prvRxBufferSize[USART1] == USART_prvRxBufferIndex[USART1])
		{
			USART_1->CR1 &= ~(1 << 5);
			USART_prvRxBusyFlag[USART1] = 0;
			USART_prvRxBufferSize[USART1] = 0;
			if(cbfRX[USART1])
			{
				cbfRX[USART1]();
			}
		}
	}
	else
	{
	}
}

void USART2_IRQHandler(void)
{
	if((USART_2->SR >> 6) & 0x01)
	{
		if(USART_prvTXBufferIndex[USART2] == USART_prvTXBufferSize[USART2])
		{
			USART_prvTXBusyFlag[USART2] = 0;
			USART_prvTXBufferSize[USART2] = 0;
			if(cbfTX[USART2])
			{			
				cbfTX[USART2]();
			}
			USART_2->SR &= ~(1 << 6);
		}
		else
		{
			USART_2->SR &= ~(1 << 6);
			USART_2->DR = USART2_addBufferValue[USART_prvTXBufferIndex[USART2]];
			USART_prvTXBufferIndex[USART2]++;
		}
	}

	if(USART_prvRxBusyFlag[USART2] == 1 && ((USART_2->SR >> 5) & 0x01))
	{
		USART_prvRxBufferReceive[USART2][USART_prvRxBufferIndex[USART2]] = USART_2->DR;
		USART_prvRxBufferIndex[USART2]++;
		if(USART_prvRxBufferSize[USART2] == USART_prvRxBufferIndex[USART2])
		{
			USART_2->CR1 &= ~(1 << 5);
			USART_prvRxBusyFlag[USART2] = 0;
			USART_prvRxBufferSize[USART2] = 0;
			if(cbfRX[USART2])
			{
				cbfRX[USART2]();
			}
		}
	}
	else
	{
	}
}

void USART6_IRQHandler(void)
{
	if((USART_6->SR >> 6) & 0x01)
	{
		if(USART_prvTXBufferIndex[USART6] == USART_prvTXBufferSize[USART6])
		{
			USART_prvTXBusyFlag[USART6] = 0;
			USART_prvTXBufferSize[USART6] = 0;
			if(cbfTX[USART6])
			{			
				cbfTX[USART6]();
			}
			USART_6->SR &= ~(1 << 6);
		}
		else
		{
			USART_6->SR &= ~(1 << 6);
			USART_6->DR = USART6_addBufferValue[USART_prvTXBufferIndex[USART6]];
			USART_prvTXBufferIndex[USART6]++;
		}
	}

	if(USART_prvRxBusyFlag[USART6] == 1 && ((USART_6->SR >> 5) & 0x01))
	{
		USART_prvRxBufferReceive[USART6][USART_prvRxBufferIndex[USART6]] = USART_6->DR;
		USART_prvRxBufferIndex[USART6]++;
		if(USART_prvRxBufferSize[USART6] == USART_prvRxBufferIndex[USART6])
		{
			USART_6->CR1 &= ~(1 << 5);
			USART_prvRxBusyFlag[USART6] = 0;
			USART_prvRxBufferSize[USART6] = 0;
			if(cbfRX[USART6])
			{
				cbfRX[USART6]();
			}
		}
	}
	else
	{
	}
}