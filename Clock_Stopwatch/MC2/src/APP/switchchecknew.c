/******************************************************************************
 *
 * Project: Digital Clock: 	- Display configurable date and time.
 * 							- Display configurable stopwatch.
 *
 * File Name: ReceiveRunnable.c
 *
 * Description: Runnable concerned with sending the requests in the project.
 *
 * Authors: Mina Ayman, Shaher Shah.
 *
 * Date: 08-04-2024
 *
 *******************************************************************************/


/************************************************************************************/
/*										Includes									*/
/************************************************************************************/


#include "HAL/HSWITCH/HSWITCH_interface.h"
#include "MCAL/MUSART/MUSART_interface.h"



/************************************************************************************/
/*								MACROs definitions									*/
/************************************************************************************/


#define UP_START_BUTTON 	0x08
#define DOWN_STOP_BUTTON 	0x09
#define LEFT_RESET_BUTTON	0x0A
#define RIGHT_BUTTON    	0x0B
#define OK_BUTTON 			0x0C
#define MODE_BUTTON 		0x0D
#define EDIT_BUTTON 		0x0E



/************************************************************************************/
/*								Variables's Declaration								*/
/************************************************************************************/


u8 message[1] = {0};

/* Used flags */
static u8 readyForNewKey = 1;
static u8 switchState = 0;



/************************************************************************************/
/*							Static Functions' Implementation						*/
/************************************************************************************/


static u8 Encryption(u8 value) {
	u8 CheckSumBits = value & 0x0F; // Only consider lower 4 bits for checksum
	u8 EncryptedMessage = (value << 4) | (CheckSumBits);
	return EncryptedMessage;
}

/**
 *@brief : Callback function which is called whenever the sending done.
 *@param : void.
 *@return: void.
 */
void messageSent (void) 
{
	readyForNewKey = 1;
}

/* The buffer that would be sent */
USART_Req_t USARAT_Bytes = {.length = 1, .buffer = message, .USART_Peri = USART_Peri_1, .CB = messageSent};



/************************************************************************************/
/*								Functions' Implementation							*/
/************************************************************************************/


/**
 *@brief : A runnable that comes every 200 milliseconds to send user's requests.
 *@param : void.
 *@return: void.
 */
void switchesCheckRunnable (void) 
{   
	u8 index = 0  ;

	if (readyForNewKey == 1) 
	{
		for (index=0 ; index < _Switch_Num ; index ++ )
		{
			switchState = HSWITCH_u32GetSwitchState(index);
			if(switchState == SWITCH_STATUS_PRESSED )
			{   
				// Stop responding for a new press till the current message is sent.
				readyForNewKey = 0;

				//Generating the message by adding the checksum to the message.
				message[0]=Encryption(index+8);

				// Send the message.
				USART_TXBufferAsyncZC(USARAT_Bytes);

				break ;
			}
		}
	}
	else
	{
		/* It seems that We are not ready for sending a new key as the current key is being sent */
	}
}
