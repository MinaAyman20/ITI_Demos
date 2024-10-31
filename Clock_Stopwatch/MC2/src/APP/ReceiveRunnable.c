/******************************************************************************
 *
 * Project: Digital Clock: 	- Display configurable date and time.
 * 							- Display configurable stopwatch.
 *
 * File Name: ReceiveRunnable.c
 *
 * Description: Runnable concerned with receiving and handling the requests in the project.
 *
 * Authors: Mina Ayman, Shaher Shah.
 *
 * Date: 08-04-2024
 *
 *******************************************************************************/


/************************************************************************************/
/*										Includes									*/
/************************************************************************************/
#include "MCAl/MUSART/MUSART_interface.h"
#include "HAL/HLCD/HLCD_interface.h"



/************************************************************************************/
/*								MACROs definitions									*/
/************************************************************************************/

#define FALSE 						0
#define TRUE 						1


#define UP_START_BUTTON 			0x08
#define DOWN_STOP_BUTTON 			0x09
#define LEFT_RESET_BUTTON 			0x0A
#define RIGHT_BUTTON 				0x0B
#define OK_BUTTON 					0x0C
#define MODE_BUTTON 				0x0D
#define EDIT_BUTTON 				0x0E

#define CORRUPTED_MESSAGE			0xFF

/* These defines are used in edit mode to know which position did the user set the cursor,
 * We are only concerned with the editable positions. */
#define DAY_TENS_POSITION			6
#define DAY_UNITS_POSITION			7
#define MONTHS_TENS_POSITION		9
#define MONTHS_UNITS_POSITION		10
#define YEARS_THOUSANDS_POSITION	12
#define YEARS_HUNDREDS_POSITION		13
#define YEARS_TENS_POSITION			14
#define YEARS_UNITS_POSITION		15

#define HOURS_TENS_POSITION			24
#define HOURS_UNITS_POSITION		25
#define MINUTES_TENS_POSITION		27
#define MINUTES_UNITS_POSITION		28
#define SECONDS_TENS_POSITION		30
#define SECONDS_UNITS_POSITION		31



/************************************************************************************/
/*							User-defined types Declaration							*/
/************************************************************************************/


typedef enum
{
	CLOCK_MODE,
	STOPWATCH_MODE
}MODES;
typedef enum
{ 
	NOT_ACTIVATED,
	ACTIVATED
}EDITMODES;

/**
 *@brief : The Ok button status types
 */
typedef enum
{ 
	NOT_PRESSED,
	FIRST_PRESSED
}OKSTATE;



/************************************************************************************/
/*								Variables's Declaration								*/
/************************************************************************************/


u8 recivedMessage[1] = {0};


extern MODES Mode ;
extern MODES previousMode ;
extern u8 setCursorNeedded ;
extern EDITMODES EditMode ;

/* These variables are related to the edit mode, where they save the current row, current column
 * and current position where the user set the cursor at */
LCD_enuRowNumber_t CurrentRow = LCD_enuFirstRow;
LCD_enuColumnNumber_t CurrentCol = LCD_enuColumn_1;
static u8 CursorPos = 0;

/* Used flags */
u8 receiveFlag = 0 ;
extern u8 clearOnce ;
extern u8 startFlag ;
static u8 resetFlag = FALSE ;
extern u8 stopwatchNotStarted ;
static u8 buttonHandled = TRUE ;
static OKSTATE OKState = NOT_PRESSED;
extern u8 printEntireScreen ;

/* Variables related to the date and time. */
extern u8 hours ;
extern u8 minutes;
extern u8 seconds;
extern u8 day;
extern u8 month;
extern u16 year ;

/* Variable related to the updating of the clock during the displaying */
extern u32 printCounter;
extern u32 S_LCD_Counter;
extern u32 S_printCounter;
extern u8 editModeCounter;

/* Variables related to the date and time. Initially We are setting them as follows */
extern u8  S_hours   ;
extern u8  S_minutes;
extern u8  S_seconds;
extern u16 S_milliseconds;



/************************************************************************************/
/*							Static Functions' Implementation						*/
/************************************************************************************/


/**
 *@brief : Function that decryptes the received encrypted message from the UART.
 *@param : Received message.
 *@return: Data that is extracted from the received encrypted message.
 */
static u8 Decryption(u8 value) {
	u8 CheckSumBits = value & 0x0F;
	u8 Data = (value >> 4);

	/* Verify Checksum */
	if ((Data ^ CheckSumBits) == 0) {
		return Data; // Return data if checksum matches
	} else {
		return CORRUPTED_MESSAGE; // Return error code for corrupted message
	}
}

/**
 *@brief : Dummy function that passed to any Asynchronus function.
 *@param : void.
 *@return: void.
 */
static void DummyCB(void)
{

}

/**
 *@brief : Callback function which is called whenever the receiving done.
 *@param : void.
 *@return: void.
 */
void receiveCallback (void)
{
	receiveFlag = 1 ;
	buttonHandled = FALSE ;
}

/* The buffer that would be received */
USART_Req_t received_Bytes = {.length = 1, .buffer = recivedMessage, .USART_Peri = USART_Peri_1, .CB = receiveCallback};



/************************************************************************************/
/*								Functions' Implementation							*/
/************************************************************************************/


/**
 *@brief : A runnable that comes every 200 milliseconds to receive user's requests and handle it.
 *@param : void.
 *@return: void.
 */
void receiveRunnable(void)
{
	if(buttonHandled == TRUE)
	{
		USART_RXBufferAsyncZC(received_Bytes);
	}
	else
	{
		/* Do Nothing till the current request is handled */
	}


	/* If a message is received go on handle it */
	if((receiveFlag == TRUE) && (Mode == CLOCK_MODE))
	{
		/* Lower the flag so We could be able to receive the next request once the current one is handled */
		receiveFlag = FALSE;

		u8 receivedButton = 0;
		receivedButton = Decryption(recivedMessage[0]);

		/* Check whether the received data is correct and We can deal with its content
				or it is corrupted so ignore it */
		if(receivedButton != 0xFF)
		{
			/* Check which button the user had pressed to react upon it */
			switch (receivedButton)
			{
			case UP_START_BUTTON:
				/* In case of the user entered the edit mode but still does not pressed the OK
						button, he/she will be only able to navigate through the display */
				if((EditMode == ACTIVATED) && (OKState == NOT_PRESSED))
				{
					/* If the cursor is already in the first row there is no hidden place above that :) */
					if (CurrentRow == LCD_enuFirstRow)
					{
						/* Do Nothing You already on the first row */
					}
					else
					{
						/* If You are on the second row, the cursor should then go up to the first row */
						CurrentRow = LCD_enuFirstRow;
					}
					LCD_enuSetCursorAsync (CurrentRow, CurrentCol, DummyCB);
				}
				/* In case of the user entered the edit mode and pressed the OK button, he/she will
						be able to edit the displayed date and time */
				else if ((EditMode == ACTIVATED) && (OKState == FIRST_PRESSED))
				{
					/* Calculating the position where the user is setting the cursor on to make sure
							that he is editing only the date and time digits*/
					CursorPos = (CurrentCol) + (CurrentRow * 16);

					/* Check on the position of the cursor */
					switch (CursorPos)
					{
					/* The cursor now is at the position of the Days' units */
					case DAY_TENS_POSITION:
						if (month == 2)
						{
							if (day > 18)
							{
								day -= 10;
							}
							else
							{
								day += 10;
							}
						}
						else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
						{
							if (day > 21)
							{
								day -= 20;
							}
							else
							{
								day += 10;
							}
						}
						else
						{
							if (day > 20)
							{
								day -= 20;
							}
							else
							{
								day += 10;
							}
						}
						LCD_enuWriteNumberAsync(day,DummyCB);
						editModeCounter = 0;
						break;
					case DAY_UNITS_POSITION:
						/* The cursor now is at the position of the Days' units */
						if((month == 2) && (day == 28))
						{
							/* Do Nothing as 28 is the last day in February */
						}
						else if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day == 31))
						{
							/* Do Nothing as 31 is the last day in these months */
						}
						else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day == 30))
						{
							/* Do Nothing as 30 is the last day in these months */
						}
						else
						{
							day++;
						}
						LCD_enuWriteNumberAsync(day%10,DummyCB);
						editModeCounter = 0;
						break;
					case MONTHS_TENS_POSITION:
						if ((month == 1) || (month == 2))
						{
							month += 10;
						}
						else if ((month >= 3) && (month<=10))
						{
							month = 1;
						}
						else if ((month == 11) || (month == 12))
						{
							month -= 10;
						}
						LCD_enuWriteNumberAsync(month,DummyCB);
						editModeCounter = 0;
						break ;
					case MONTHS_UNITS_POSITION:
						if(month == 12)
						{
							/* Do Nothing as 12 is the last month in the year */
						}
						else
						{
							month++;
						}
						LCD_enuWriteNumberAsync(month%10,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_THOUSANDS_POSITION:
						year += 1000;
						LCD_enuWriteNumberAsync(year,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_HUNDREDS_POSITION:
						year += 100;
						LCD_enuWriteNumberAsync(year%1000,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_TENS_POSITION:
						year += 10;
						LCD_enuWriteNumberAsync(year%100,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_UNITS_POSITION:
						year += 1;
						LCD_enuWriteNumberAsync(year%10,DummyCB);
						editModeCounter = 0;
						break;
					case HOURS_TENS_POSITION:
						if ((hours >= 0) && (hours <= 13))
						{
							hours += 10;
						}
						else if ((hours >= 14) && (hours <= 23))
						{
							hours -= 10;
						}
						LCD_enuWriteNumberAsync(hours,DummyCB);
						editModeCounter = 0;
						break;
					case HOURS_UNITS_POSITION:
						if((hours >= 0) && (hours <= 22))
						{
							hours++;
						}
						else if (hours == 23)
						{
							/* Do Nothing as 23 is the last hour could be displayed in the hours digits */
						}
						LCD_enuWriteNumberAsync(hours%10,DummyCB);
						editModeCounter = 0;
						break;
					case MINUTES_TENS_POSITION:
						if((minutes >= 0) && (minutes <= 49))
						{
							minutes += 10;
						}
						else if (minutes > 50)
						{
							minutes -= 50;
						}
						LCD_enuWriteNumberAsync(minutes,DummyCB);
						editModeCounter = 0;
						break;
					case MINUTES_UNITS_POSITION:
						if((minutes >= 0) && (minutes <= 58))
						{
							minutes++;
						}
						else if (minutes == 59)
						{
							/* Do Nothing as 59 is the last minutes could be displayed in the minutes digits */
						}
						LCD_enuWriteNumberAsync(minutes%10,DummyCB);
						editModeCounter = 0;
						break;
					case SECONDS_TENS_POSITION:
						if((seconds >= 0) && (seconds <= 49))
						{
							seconds += 10;
						}
						else if (seconds> 50)
						{
							seconds -= 50;
						}
						LCD_enuWriteNumberAsync(seconds,DummyCB);
						editModeCounter = 0;
						break;
					case SECONDS_UNITS_POSITION:
						if((seconds >= 0) && (seconds <= 58))
						{
							seconds++;
						}
						else if (seconds == 59)
						{
							/* Do Nothing as 59 is the last seconds could be displayed in the seconds digits */
						}
						LCD_enuWriteNumberAsync(seconds%10,DummyCB);
						editModeCounter = 0;
						break;
					default:
						/* You are in a position that you can not edit the data in it,
								so your request is ignored*/
						break;
					}
				}
				break;
			case DOWN_STOP_BUTTON:
				/* In case of the user entered the edit mode but still does not pressed the OK
						button, he/she will be only able to navigate through the display */
				if((EditMode == ACTIVATED) && (OKState == NOT_PRESSED))
				{
					/* If the cursor is already in the last row there is no hidden place under that :) */
					if (CurrentRow == LCD_enuSecondRow)
					{
						/* Do Nothing You already on the last row */
					}
					else
					{
						/* If You are on the first row, the cursor should then go down to the second row */
						CurrentRow = LCD_enuSecondRow;
					}
					LCD_enuSetCursorAsync (CurrentRow,CurrentCol,DummyCB);
				}
				else if ((EditMode == ACTIVATED) && (OKState == FIRST_PRESSED))
				{
					/* Calculating the position where the user is setting the cursor on to make sure
							that he is editing only the date and time digits*/
					CursorPos = (CurrentCol) + (CurrentRow * 16);

					/* Check on the position of the cursor */
					switch (CursorPos)
					{

					/* The cursor now is at the position of the Days' units */
					case DAY_TENS_POSITION:
						if ((day >= 1) && (day <= 9))
						{
							/* Do Nothing as 0 is the last value in the tens digit */
						}
						else
						{
							day -= 10;
						}
						LCD_enuWriteNumberAsync(day,DummyCB);
						editModeCounter = 0;
						break;
					case DAY_UNITS_POSITION:
						if( day == 10 ||day == 20 ||day == 30 )
						{
							/* Do Nothing as 0 is the last value in the units digit */
						}
						else
						{
							day--;
						}
						LCD_enuWriteNumberAsync(day%10,DummyCB);
						editModeCounter = 0;
						break;
					case MONTHS_TENS_POSITION:
						if((month >= 1) && (month <= 10))
						{
							/* Do Nothing as 0 is the last value in the tens digit */
						}
						else if (month == 11 || month == 12)
						{
							month -= 10;
						}
						LCD_enuWriteNumberAsync(month,DummyCB);
						editModeCounter = 0;
						break ;
					case MONTHS_UNITS_POSITION:
						if((month == 1) || (month == 10))
						{
							/* Do Nothing as January is the first month and no month is before him
									and as 0 is the last value in the units digit */
						}
						else
						{
							month--;
						}
						LCD_enuWriteNumberAsync(month%10,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_THOUSANDS_POSITION:
						if (year < 1000)
						{

						}
						else
						{
							year -= 1000;
						}LCD_enuWriteNumberAsync(year,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_HUNDREDS_POSITION:
						if (year < 100)
						{

						}
						else
						{
							year -= 100;
						}
						LCD_enuWriteNumberAsync(year%1000,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_TENS_POSITION:
						if (year < 10)
						{

						}
						else
						{
							year -= 10;
						}
						LCD_enuWriteNumberAsync(year%100,DummyCB);
						editModeCounter = 0;
						break;
					case YEARS_UNITS_POSITION:
						if (year < 1)
						{

						}
						else
						{
							year--;
						}
						LCD_enuWriteNumberAsync(year%10,DummyCB);
						editModeCounter = 0;
						break;
					case HOURS_TENS_POSITION:
						if((hours >= 0) && (hours <= 9))
						{

						}
						else if (hours>=10 && hours <=23)
						{
							hours -= 10;
						}
						LCD_enuWriteNumberAsync(hours,DummyCB);
						editModeCounter = 0;
						break;
					case HOURS_UNITS_POSITION:
						if((hours == 0) || (hours == 10) || (hours == 20))
						{

						}
						else
						{
							hours--;
						}
						LCD_enuWriteNumberAsync(hours%10,DummyCB);
						editModeCounter = 0;
						break;
					case MINUTES_TENS_POSITION:
						if((minutes >= 0) && (minutes <= 9))
						{

						}
						else
						{
							minutes -= 10;
						}
						LCD_enuWriteNumberAsync(minutes,DummyCB);
						editModeCounter = 0;
						break;
					case MINUTES_UNITS_POSITION:
						if((minutes % 10) == 0)
						{

						}
						else
						{
							minutes--;
						}
						LCD_enuWriteNumberAsync(minutes%10,DummyCB);
						editModeCounter = 0;
						break;
					case SECONDS_TENS_POSITION:
						if((seconds >= 0) && (seconds <= 9))
						{

						}
						else
						{
							seconds -= 10;
						}
						LCD_enuWriteNumberAsync(seconds,DummyCB);
						editModeCounter = 0;
						break;
					case SECONDS_UNITS_POSITION:
						if((seconds % 10) == 0)
						{

						}
						else
						{
							seconds--;
						}
						LCD_enuWriteNumberAsync(seconds%10,DummyCB);
						editModeCounter = 0;
						break;
					default:
						/* You are in a position that you can not edit the data in it,
								so your request is ignored*/
						break;
					}
				}
				break;
			case RIGHT_BUTTON:
				/* In case of the user entered the edit mode, he/she will be able to navigate through the display */
				if(EditMode == ACTIVATED)
				{
					/* If the cursor is already in the last column, there is no hidden place to the right of that position :) */
					if(CurrentCol == LCD_enuColumn_16 || CurrentCol == LCD_enuColumn_32)
					{
						/* Do Nothing You already on the last column */
					}
					else
					{
						/* If You are on the another column rather the last one, the cursor should
								then go right to the next column in the same row */
						CurrentCol ++ ;
						LCD_enuSetCursorAsync(CurrentRow, CurrentCol, DummyCB);
					}
				}
				break;
			case LEFT_RESET_BUTTON:
				/* In case of the user entered the edit mode, he/she will be able to navigate through the display */
				if(EditMode == ACTIVATED)
				{
					/* If the cursor is already in the first column, there is no hidden place to the left of that position :) */
					if(CurrentCol == LCD_enuColumn_1 || CurrentCol == LCD_enuColumn_17)
					{
						/* Do Nothing You already on the first column */
					}
					else
					{
						/* If You are on the another column rather the first one, the cursor should
								then go left to the next column in the same row */
						CurrentCol -- ;
						LCD_enuSetCursorAsync (CurrentRow, CurrentCol, DummyCB);
					}
				}
				break;
			case OK_BUTTON :
				if(EditMode == ACTIVATED)
				{
					if (OKState == NOT_PRESSED)
					{
						OKState = FIRST_PRESSED;
						LCD_enuSendCommandAsync(LCD_DisplayON_CursorON_BlinkON,DummyCB);
					}
					else if (OKState == FIRST_PRESSED)
					{
						OKState = NOT_PRESSED;
						LCD_enuSendCommandAsync(LCD_DisplayON_CursorON_BlinkOFF,DummyCB);
					}
				}
				break;
			case MODE_BUTTON :
				if(EditMode == NOT_ACTIVATED)
				{
					Mode = STOPWATCH_MODE;
					previousMode = CLOCK_MODE;
					printCounter = 0;
					S_printCounter = 0;
					recivedMessage [0] = 0;
					if(stopwatchNotStarted == FALSE && printEntireScreen == TRUE)
					{
						stopwatchNotStarted = TRUE;
					}
				}
				break;
			case EDIT_BUTTON :
				if(EditMode == NOT_ACTIVATED)
				{
					EditMode = ACTIVATED ;
					setCursorNeedded = TRUE ;
					CurrentCol = LCD_enuColumn_7;
					CurrentRow = LCD_enuFirstRow;
					CursorPos  = 0;
					editModeCounter = 0;
				}
				else if (EditMode == ACTIVATED)
				{
					EditMode = NOT_ACTIVATED ;
					OKState = NOT_PRESSED;
					LCD_enuSendCommandAsync(LCD_DisplayON_CursorOFF_BlinkOFF,DummyCB);
					printCounter = 97 ;
				}
				break;
			}
			/* After handling the latest request, raise this flag to make the driver ready to
			 * receive a new button request */
			buttonHandled = TRUE;
		}
		else
		{
			/* If the data is corrupted raise this flag to make the driver ready to receive
			 * a new button request */
			buttonHandled = TRUE;
		}
	}
	else if ((receiveFlag == TRUE) && (Mode == STOPWATCH_MODE))
	{
		/* Lower the flag so We could be able to receive the next request once the current one is handled */
		receiveFlag = FALSE;

		u8 receivedButton = 0;
		receivedButton = Decryption(recivedMessage[0]);

		/* Check whether the received data is correct and We can deal with its content
				or it is corrupted so ignore it */
		if(receivedButton != CORRUPTED_MESSAGE)
		{
			/* Check which button the user had pressed to react upon it */
			switch (receivedButton)
			{
			case MODE_BUTTON :
				if(EditMode == NOT_ACTIVATED)
				{
					Mode = CLOCK_MODE;
					previousMode = STOPWATCH_MODE;
					clearOnce = FALSE ;

					S_printCounter = 0;
					S_LCD_Counter = 0;
					recivedMessage[0]= 0 ;
				}
				break;
			case UP_START_BUTTON :
				startFlag = TRUE;
				break;
			case DOWN_STOP_BUTTON :
				startFlag = FALSE;
				S_printCounter = 0;
				break;
			case LEFT_RESET_BUTTON :
				LCD_enuClearScreenAsync(DummyCB);
				resetFlag = TRUE ;
				startFlag = FALSE;
				printEntireScreen = TRUE ;
				S_LCD_Counter  = 0;
				S_printCounter = 0;
				S_hours   = 0;
				S_minutes = 0;
				S_seconds = 0;
				S_milliseconds = 0;
				break;

			}
			/* After handling the latest request, raise this flag to make the driver ready to
			 * receive a new button request */
			buttonHandled = TRUE;
		}
		else
		{
			/* If the data is corrupted raise this flag to make the driver ready to receive
			 * a new button request */
			buttonHandled = TRUE;
		}
	}
	else
	{
		/* Do Nothing */
	}
}
