/******************************************************************************
 *
 * Project: Digital Clock: 	- Display configurable date and time.
 * 							- Display configurable stopwatch.
 *
 * File Name: ClockRunnable.c
 *
 * Description: Runnable concerned with Clock mode in the project.
 *
 * Authors: Mina Ayman, Shaher Shah.
 *
 * Date: 08-04-2024
 *
 *******************************************************************************/


/************************************************************************************/
/*										Includes									*/
/************************************************************************************/

#include "MCAL/MUSART/MUSART_interface.h"
#include "HAL/HLCD/HLCD_interface.h"



/************************************************************************************/
/*							User-defined types Declaration							*/
/************************************************************************************/


/**
 *@brief : Boolean Values
 */
enum
{
	FALSE = 0,
	TRUE
};

/**
 *@brief : The Modes types
 */
typedef enum
{
	CLOCK_MODE,
	STOPWATCH_MODE
}MODES;

/**
 *@brief : The edit button status types
 */
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

/* We initially statring our system with Date and Time displayed */
MODES Mode = CLOCK_MODE;
MODES previousMode = STOPWATCH_MODE ;

EDITMODES EditMode = NOT_ACTIVATED;

u8 setCursorNeedded = FALSE ;

/* Counter that is responsible of updating the clock variables in the background */
u32  entryCounter  = 0;

/* Variable related to the updating of the clock during the displaying */
u32  printCounter  = 0;

u8 editModeCounter= 0 ;

/* Variables related to the date and time. Initially We are setting them as follows */
u8 hours   = 6;
u8 minutes = 0;
u8 seconds = 0;
u8 day = 17;
u8 month = 4;
u16 year = 2024;

/* These variables are related to the edit mode, where they save the current row and column
 * where the user set the cursor at */
extern LCD_enuRowNumber_t CurrentRow ;
extern LCD_enuColumnNumber_t CurrentCol;



/************************************************************************************/
/*							Static Functions' Implementation						*/
/************************************************************************************/


/**
 *@brief : Dummy function that passed to any Asynchronus function.
 *@param : void.
 *@return: void.
 */
static void DummyCB(void)
{

}



/************************************************************************************/
/*								Functions' Implementation							*/
/************************************************************************************/


/**
 *@brief : A runnable that comes every 10 milliseconds to update the date and time.
 *@param : void.
 *@return: void.
 */
void clockRunnable(void)
{  

	/************************************************************************************/
	/* 			The following part updates the date and time every 1 seconds 			*/
	/************************************************************************************/
	if(entryCounter % 100 == 0)
	{    
		/* Every 1 second update the seconds variable */
		seconds++;
		if(seconds == 60)
		{
			/* If 60 seconds passed reset the seconds digits and increment the minutes digits by one */
			seconds = 0;
			minutes++;
			if(minutes == 60)
			{
				/* If 60 minutes passed reset the minutes digits and increment the hours digits by one */
				minutes = 0;
				hours++;
			}
			if(hours == 24)
			{
				/* If 24 hours passed reset the hours digits and increment the Day digits by one */
				hours = 0;
				day++;
			}

			/* If a total month passed increment the month digits and reset the days digits to one */
			if((month == 1 ||month == 3 ||month == 5 ||month == 7 ||month == 8 ||month == 10 || month == 12) \
					&& (day == 32))
			{
				day = 1;
				month++;
			}
			else if ((month == 4 ||month == 6 ||month == 9 ||month == 11) && (day == 31))
			{
				day = 1;
				month++;
			}
			else if ((month == 2) && (day == 29))
			{
				day = 1;
				month++;
			}
			else
			{
				/* Do Nothing */
			}

			if(month == 13)
			{
				/* If 12 months passed, reset the months digits to 1 and increment the years digits by one */
				month = 1;
				year++;
			}
		}
	}

	/* Increment the counter which is responsible of updating the date and time variables. */
	entryCounter ++ ;

	/************************************************************************************/
	/* 	The following part checks on the selected mode, if it is the CLOCK_MODE, it Will
		display Date and Time after each update.
		We are updating the whole screen once each one second, and the part of the hours, minutes,
		seconds are being updated twice during the one second. */
	/************************************************************************************/
	if(Mode == CLOCK_MODE )
	{   
		if(EditMode == NOT_ACTIVATED)
		{
			switch(printCounter)
			{
			/* The empty cases are because the LCD driver is not buffering the coming requests,
			 * so We need to hold on the required time for each request from the LCD */
			case 0:
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_1,DummyCB);
				printCounter ++;
				break;
			case 1:
				printCounter ++;
				break;
			case 2:
				LCD_enuWriteStringAsync("Time:   ",DummyCB);
				printCounter ++;
				break;
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
				printCounter ++;
				break;
			case 15:
				if (hours < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(hours,DummyCB);
				}
				printCounter ++;
				break;
			case 16:
				printCounter ++;
				break;
			case 17:
				if(hours < 10)
				{
					LCD_enuWriteNumberAsync(hours,DummyCB);
				}
				else
				{

				}
				printCounter ++ ;
				break;
			case 18:
				printCounter ++;
				break;
			case 19:
				LCD_enuWriteStringAsync(":",DummyCB);
				printCounter ++;
				break;
			case 20:
				printCounter ++;
				break;
			case 21:
				if (minutes < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(minutes,DummyCB);
				}
				printCounter ++;
				break;
			case 22:
				printCounter ++;
				break;
			case 23:
				if(minutes < 10)
				{
					LCD_enuWriteNumberAsync(minutes,DummyCB);
				}
				else
				{

				}
				printCounter ++ ;
				break;
			case 24:
				printCounter ++;
				break;
			case 25:
				LCD_enuWriteStringAsync(":",DummyCB);
				printCounter ++;
				break;
			case 26:
				printCounter ++;
				break;
			case 27:
				if (seconds < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(seconds,DummyCB);
				}
				printCounter ++;
				break;
			case 28:
				printCounter ++;
				break;
			case 29:
				if(seconds < 10)
				{
					LCD_enuWriteNumberAsync(seconds,DummyCB);
				}
				else
				{

				}
				printCounter ++ ;
				break;
			case 30:
				printCounter ++;
				break;
			case 31:
				LCD_enuSetCursorAsync(LCD_enuFirstRow,LCD_enuColumn_1,DummyCB);
				printCounter ++;
				break;
			case 32:
				printCounter ++;
				break;
			case 33:
				LCD_enuWriteStringAsync("Date: ",DummyCB);
				printCounter ++;
				break;
			case 34:
			case 35:
			case 36:
			case 37:
			case 38:
			case 39:
			case 40:
			case 41:
			case 42:
				printCounter ++;
				break;
			case 43:
				if (day < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(day,DummyCB);
				}
				printCounter++;
				break;
			case 44:
				printCounter++;
				break;
			case 45:
				if (day < 10)
				{
					LCD_enuWriteNumberAsync(day,DummyCB);
				}
				else
				{

				}
				printCounter++;
				break;
			case 46:
				printCounter++;
				break;
			case 47:
				LCD_enuWriteStringAsync("/",DummyCB);
				printCounter++;
				break;
			case 48:
				printCounter++;
				break;
			case 49:
				if (month < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(month,DummyCB);
				}
				printCounter++;
				break;
			case 50:
				printCounter++;
				break;
			case 51:
				if (month < 10)
				{
					LCD_enuWriteNumberAsync(month,DummyCB);
				}
				else
				{

				}
				printCounter++;
				break;
			case 52:
				printCounter++;
				break;
			case 53:
				LCD_enuWriteStringAsync("/",DummyCB);
				printCounter++;
				break;
			case 54:
				printCounter++;
				break;
			case 55:
				if (year < 1000)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else if (year < 100)
				{
					LCD_enuWriteStringAsync("00",DummyCB);
				}
				else if (year < 10)
				{
					LCD_enuWriteStringAsync("000",DummyCB);
				}
				else if (year < 1)
				{
					LCD_enuWriteStringAsync("0000",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(year,DummyCB);
				}
				printCounter++;
				break;
			case 56:
			case 57:
			case 58:
			case 59:
			case 60:
			case 61:
				printCounter++;
				break;
			case 62:
				if (year < 1000)
				{
					LCD_enuWriteNumberAsync(year,DummyCB);
				}
				else if (year < 100)
				{
					LCD_enuWriteNumberAsync(year,DummyCB);
				}
				else if (year < 10)
				{
					LCD_enuWriteNumberAsync(year,DummyCB);
				}
				else if (year < 1)
				{
					LCD_enuWriteNumberAsync(year,DummyCB);
				}
				else
				{

				}
				printCounter++;
				break;
			case 63:
			case 64:
			case 65:
			case 66:
				printCounter++;
				break;
			case 67:
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_9,DummyCB);
				printCounter++;
				break;
			case 68:
				printCounter++;
				break;
			case 69:
				if (hours < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(hours,DummyCB);
				}
				printCounter ++;
				break;
			case 70:
				printCounter ++;
				break;
			case 71:
				if(hours < 10)
				{
					LCD_enuWriteNumberAsync(hours,DummyCB);
				}
				else
				{

				}
				printCounter ++ ;
				break;
			case 72:
				printCounter ++;
				break;
			case 73:
				LCD_enuWriteStringAsync(":",DummyCB);
				printCounter ++;
				break;
			case 74:
				printCounter ++;
				break;
			case 75:
				if (minutes < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(minutes,DummyCB);
				}
				printCounter ++;
				break;
			case 76:
				printCounter ++;
				break;
			case 77:
				if(minutes < 10)
				{
					LCD_enuWriteNumberAsync(minutes,DummyCB);
				}
				else
				{

				}
				printCounter ++ ;
				break;
			case 78:
				printCounter ++;
				break;
			case 79:
				LCD_enuWriteStringAsync(":",DummyCB);
				printCounter ++;
				break;
			case 80:
				printCounter ++;
				break;
			case 81:
				if (seconds < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(seconds,DummyCB);
				}
				printCounter ++;
				break;
			case 82:
				printCounter ++;
				break;
			case 83:
				if(seconds < 10)
				{
					LCD_enuWriteNumberAsync(seconds,DummyCB);
				}
				else
				{

				}
				printCounter ++ ;
				break;
			case 84:
				printCounter ++;
				break;
			case 85:
			case 86:
			case 87:
			case 88:
			case 89:
			case 90:
			case 91:
			case 92:
			case 93:
			case 94:
			case 95:
			case 96:
			case 97:
			case 98:
				printCounter ++;
				break;
			case 99:
				printCounter = 0;
				break;
			}
		}
		else
		{
			/* When the edit mode is activated We need to set the cursor to the tens digit of the
			 * days, and turning the cursor on without blinking and always make sure that the cursor
			 * is at the place the user stopped at */
			switch (editModeCounter)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
				editModeCounter ++ ;
				break;
			case 12:
				if(setCursorNeedded == TRUE)
				{
					LCD_enuSetCursorAsync (LCD_enuFirstRow,LCD_enuColumn_7,DummyCB);
				}
				editModeCounter ++;
				break;
			case 13:
			case 14:
				editModeCounter ++ ;
				break;
			case 15:
				if(setCursorNeedded == TRUE)
				{
					LCD_enuSendCommandAsync(LCD_DisplayON_CursorON_BlinkOFF,DummyCB);
					setCursorNeedded = FALSE ;
				}
				editModeCounter ++;
				break;
			case 16:
			case 17:
				editModeCounter ++ ;
				break;
			case 18:
				LCD_enuSetCursorAsync(CurrentRow,CurrentCol,DummyCB);
				editModeCounter ++ ;
				break;
			case 19:
			case 20:
				editModeCounter ++ ;
				break;
			case 21:
				editModeCounter = 0 ;
				break;
			}
		}

	}
	else
	{
		/* Do Nothing as the current mode is not the Clock mode */
	}
}
