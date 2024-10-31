#pragma once

#include <stdio.h>

#define F_CLK	    				16000000
#define ENABLE 						1
#define DISABLE						0
#define OVERSAMPLING_8				1
#define OVERSAMPLING_16				0
#define WORDLENGTH_8				0
#define WORDLENGTH_9				1
#define PARITY_ODD					1
#define PARITY_EVEN					0
#define PARITY_NONE					3

typedef enum
{
	USART1,
	USART2,
	USART6
}USART_Channel;



/*
 * Possible values for USART_Config struct:
 *   - Channel:              					USART1, USART2, USART6.
 *   - Oversampling:         					OVERSAMPLING_8, OVERSAMPLING_16
 *   - USART_Enable:         					ENABLE, DISABLE
 *   - WordLength:           					WORDLENGTH_8, WORDLENGTH_9
 *   - ParityControl:        					PARITY_NONE, PARITY_EVEN, PARITY_ODD
 *   - TransDateRegisterEmpty_Int:   			ENABLE, DISABLE
 *   - TransComplete_Int:    					ENABLE, DISABLE
 *   - ReceiveDateRegisterEmpty_Int: 			ENABLE, DISABLE
 *   - TransEnable:          					ENABLE, DISABLE
 *   - ReceiveEnable:        					ENABLE, DISABLE
 *   - BaudRate:             					9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600
 */
typedef struct
{
	USART_Channel Channel;
	uint8_t Oversampling;
	uint8_t USART_Enable;
	uint8_t WordLength;
	uint8_t ParityControl;
	uint8_t TransDateRegisterEmpty_Int;
	uint8_t TransComplete_Int;
	uint8_t ReceiveDateRegisterEmpty_Int;
	uint8_t TransEnable;
	uint8_t ReceiveEnable;
	uint32_t BaudRate;
}USART_Config;


typedef enum
{
	USART_enuOK,
	USART_enuNOK,
	USART_enuNullPointer,
	USART_enuValueExceed,
	USART_enuBusy
}USART_ErrorStatus;


typedef struct
{
	uint8_t * Data;
	uint32_t Size;
	USART_Channel Channel;
}USART_TXBuffer;

typedef struct
{
	USART_Channel Channel;
	uint8_t * Data;
	uint32_t Size;
	uint32_t Index;
}USART_RXBuffer;


typedef enum
{
	SEND,
	RECEIVE
}USART_Mode;


typedef void(*CallBack)(void);


USART_ErrorStatus USART_Init(const USART_Config* ConfigPtr);
USART_ErrorStatus USART_SendByteAsynchronous(USART_Channel Channel, uint8_t Copy_Data);
USART_ErrorStatus USART_ReceiveBuffer(USART_RXBuffer * ReceiveBuffer);
USART_ErrorStatus USART_SendBufferZeroCopy(USART_TXBuffer* Copy_ConfigBuffer);
USART_ErrorStatus USART_RegisterCallBackFunction(USART_Channel Channel, USART_Mode Mode, CallBack CallBackFunction);


