/******************************************************************************
 *
 * Project: Digital Clock: 	- Display configurable date and time.
 * 							- Display configurable stopwatch.
 *
 * File Name: StopwatchRunnable.c
 *
 * Description: Runnable concerned with Stopwatch mode in the project.
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


/* Variables related to the date and time. Initially We are setting them as follows */
u8  S_hours   = 0;
u8  S_minutes = 0;
u8  S_seconds = 0;
u16 S_milliseconds = 0;

/* Variable related to the updating of the clock during the displaying */
u32  S_LCD_Counter          = 0;
u32  S_printCounter         = 0;

/* Used flags */
u8 printEntireScreen = TRUE;
u8 startFlag = FALSE ;
u8 stopFlag = FALSE ;
u8 clearOnce = FALSE ;
u8  stopwatchNotStarted = FALSE ;


extern MODES Mode ;
extern MODES previousMode ;

/* Counter that is responsible of updating the stopwatch variables in the background */
static u32  entryCounter    = 0;



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
 *@brief : A runnable that comes every 20 milliseconds to update the stopwatch.
 *@param : void.
 *@return: void.
 */
void StopwatchRunnable(void)
{  

	/************************************************************************************/
	/* 			The following part updates the stopwatch every 100 milliseconds 			*/
	/************************************************************************************/
	if(startFlag == TRUE && entryCounter %5 == 0 && entryCounter !=0)
	{ 
		S_milliseconds +=100;

		if(S_milliseconds == 1000)
		{
			S_milliseconds =0;
			/* Every 1 second update the seconds variable */
			S_seconds++;
			if(S_seconds == 60)
			{
				/* If 60 seconds passed reset the seconds digits and increment the minutes digits by one */
				S_seconds = 0;
				S_minutes++;
				if(S_minutes == 60)
				{
					/* If 60 minutes passed reset the minutes digits and increment the hours digits by one */
					S_minutes = 0;
					S_hours++;
					if (S_hours == 100)
					{
						S_hours=0;
					}
				}

			}
		}

	}

	/* Only update the stopwatch when the start button is pressed */
	if(startFlag == TRUE)
	{
		entryCounter ++ ;
	}

	/************************************************************************************/
	/* 	The following part checks on the selected mode, if it is the STOPWATCH_MODE, it Will
		display the updated values of the stopwatch. */
	/************************************************************************************/
	if((Mode == STOPWATCH_MODE) && ((printEntireScreen == FALSE) && (startFlag == TRUE) || (stopwatchNotStarted == FALSE)))
	{
		switch(S_printCounter)
		{
		/* The empty cases are because the LCD driver is not buffering the coming requests,
		* so We need to hold on the required time for each request from the LCD */
		case 0:
			if(clearOnce == FALSE)
			{
				LCD_enuClearScreenAsync(DummyCB);
				clearOnce = TRUE ;
			}
			S_printCounter ++ ;
			break ;
		case 1 :
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuSetCursorAsync  (LCD_enuFirstRow,LCD_enuColumn_4 ,DummyCB);
			}
			else
			{
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_3,DummyCB);
			}
			S_printCounter ++;
			break;
		case 2 :
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuWriteStringAsync("STOPWATCH",DummyCB);
			}
			else
			{
				if (S_hours < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_hours,DummyCB);
				}
			}
			S_printCounter ++;
			break;
		case 3:
		case 4:
		case 5:
		case 6:
			S_printCounter ++;
			break;
		case 7:
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_3,DummyCB);
			}
			else
			{
				if(S_hours < 10)
				{
					LCD_enuWriteNumberAsync(S_hours,DummyCB);
				}
				else
				{

				}
			}
			S_printCounter ++;
			break;
		case 8:
			S_printCounter ++;
			break;
		case 9:
			if (previousMode == CLOCK_MODE)
			{
				if (S_hours < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_hours,DummyCB);
				}
			}
			else
			{
				LCD_enuWriteStringAsync(":",DummyCB);
			}
			S_printCounter ++;
			break;
		case 10:
			S_printCounter ++;
			break;
		case 11:
			if (previousMode == CLOCK_MODE)
			{
				if(S_hours < 10)
				{
					LCD_enuWriteNumberAsync(S_hours,DummyCB);
				}
				else
				{

				}
			}
			else
			{
				if (S_minutes < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_minutes,DummyCB);
				}
			}
			S_printCounter ++;
			break;
		case 12:
			S_printCounter ++;
			break;
		case 13:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 14:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 15:
			S_printCounter ++;
			break;
		case 16:
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_5,DummyCB);
			}
			else
			{
				if (S_minutes < 10)
				{
					LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_7,DummyCB);
				}
				else
				{
					LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_8,DummyCB);
				}
			}
			S_printCounter ++;
			break;
		case 17:
			S_printCounter ++;
			break;
		case 18:
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuWriteStringAsync(":",DummyCB);
			}
			else
			{
				if(S_minutes < 10)
				{
					LCD_enuWriteNumberAsync(S_minutes,DummyCB);
				}
				else
				{

				}
			}
			S_printCounter ++;
			break;
		case 19:
			S_printCounter ++;
			break;
		case 20:
			if (previousMode == CLOCK_MODE)
			{
				if (S_minutes < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_minutes,DummyCB);
				}
			}
			else
			{
				LCD_enuWriteStringAsync(":",DummyCB);
			}
			S_printCounter ++;
			break;
		case 21:
			S_printCounter ++;
			break;
		case 22:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 23:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 24:
			S_printCounter ++;
			break;
		case 25 :
			if (previousMode == CLOCK_MODE)
			{
				if (S_minutes < 10)
				{
					LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_7,DummyCB);
				}
				else
				{
					LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_8,DummyCB);
				}
			}
			else
			{
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_9,DummyCB);
			}
			S_printCounter ++;
			break;
		case 26:
			if (previousMode == CLOCK_MODE)
			{
				if(S_minutes < 10)
				{
					LCD_enuWriteNumberAsync(S_minutes,DummyCB);
				}
				else
				{

				}
			}
			else
			{
				if (S_seconds < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_seconds,DummyCB);
				}
			}
			S_printCounter ++;
			break;
		case 27:
			S_printCounter ++;
			break;
		case 28:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 29:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 30:
			S_printCounter ++;
			break;
		case 31:
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_8,DummyCB);
			}
			else
			{
				if (S_seconds < 10)
				{
					LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_9,DummyCB);
				}
				else
				{
					LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_11,DummyCB);
				}
			}
			S_printCounter ++;
			break;
		case 32:
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuWriteStringAsync(":",DummyCB);
			}
			else
			{
				if(S_seconds < 10)
				{
					LCD_enuWriteNumberAsync(S_seconds,DummyCB);
				}
				else
				{

				}
			}
			S_printCounter ++;
			break;
		case 33:
			S_printCounter ++;
			break;
		case 34:
			if (previousMode == CLOCK_MODE)
			{
				if (S_seconds < 10)
				{
					LCD_enuWriteStringAsync("0",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_seconds,DummyCB);
				}
			}
			else
			{
				LCD_enuWriteStringAsync(":",DummyCB);
			}
			S_printCounter ++;
			break;
		case 35:
			S_printCounter ++;
			break;
		case 36:
			if (previousMode == CLOCK_MODE)
			{
				if(S_seconds < 10)
				{
					LCD_enuWriteNumberAsync(S_seconds,DummyCB);
				}
				else
				{

				}
			}
			else
			{
				if(S_milliseconds == 0)
				{
					LCD_enuWriteStringAsync("000",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
				}
			}
			S_printCounter ++;
			break;
		case 37:
			S_printCounter++;
			break;
		case 38:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 39:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 40:
			S_printCounter ++;
			break;
		case 41:
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_11,DummyCB);
			}
			else
			{

			}
			S_printCounter ++;

			break;
		case 42 :
			if (previousMode == CLOCK_MODE)
			{
				LCD_enuWriteStringAsync(":",DummyCB);
			}
			else
			{

			}
			S_printCounter ++;
			break;
		case 43:
			if (previousMode == CLOCK_MODE)
			{
				if(S_milliseconds == 0)
				{
					LCD_enuWriteStringAsync("000",DummyCB);
				}
				else
				{
					LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
				}
				//previousMode = STOPWATCH_MODE;
			}
			else
			{

			}
			S_printCounter ++;
			break;
		case 44 :
			S_printCounter ++;
			break;
		case 45:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 46:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 47:
		case 48:
			S_printCounter ++;
			break;
		case 49:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 50:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 51:
		case 52:
			S_printCounter ++;
			break;
		case 53:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 54:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 55:
			S_printCounter ++;
			break;
		case 56:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 57:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 58:
			S_printCounter ++;
			break;
		case 59:
			LCD_enuSetCursorAsync(LCD_enuSecondRow, LCD_enuColumn_9, DummyCB);
			S_printCounter ++;
			break;
		case 60:
			if (S_seconds < 10)
			{
				LCD_enuWriteStringAsync("0", DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_seconds, DummyCB);
			}
			S_printCounter ++;
			break;
		case 61:
			S_printCounter ++;
			break;
		case 62:
			if (S_seconds < 10)
			{
				LCD_enuWriteNumberAsync(S_seconds, DummyCB);
			}
			else
			{

			}
			S_printCounter ++;
			break;
		case 63:
			S_printCounter ++;
			break;
		case 64:
			LCD_enuSetCursorAsync(LCD_enuSecondRow,LCD_enuColumn_12,DummyCB);
			S_printCounter ++;
			break;
		case 65:
			if(S_milliseconds == 0)
			{
				LCD_enuWriteStringAsync("000",DummyCB);
			}
			else
			{
				LCD_enuWriteNumberAsync(S_milliseconds,DummyCB);
			}
			S_printCounter ++;
			break;
		case 66:
		case 67:
			S_printCounter ++;
			break;
		case 68:
			S_printCounter =0;
			break;
		}
	}
	/************************************************************************************/
	/* 	The following part checks on the selected mode, if it is the STOPWATCH_MODE, it Will
		display the initial state of the stopwatch */
	/************************************************************************************/
	if(Mode == STOPWATCH_MODE)
	{  
		if(printEntireScreen == TRUE || ((startFlag == FALSE) && (stopwatchNotStarted == TRUE)))
		{
			switch(S_LCD_Counter)
			{
			case 0:
			case 1:
			case 2:
				S_LCD_Counter++;
				break;
			case 3:
				LCD_enuClearScreenAsync(DummyCB);
				S_LCD_Counter++;
				break;
			case 4:
				LCD_enuSetCursorAsync  (LCD_enuFirstRow,LCD_enuColumn_4 ,DummyCB);
				S_LCD_Counter ++ ;
				break;
			case 5:
				LCD_enuWriteStringAsync("STOPWATCH",DummyCB);
				S_LCD_Counter ++ ;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
				S_LCD_Counter ++ ;
				break;
			case 15 :
				LCD_enuSetCursorAsync  (LCD_enuSecondRow,LCD_enuColumn_3 ,DummyCB);
				S_LCD_Counter ++ ;
				break;
			case 16:
				LCD_enuWriteStringAsync("00:",DummyCB);
				S_LCD_Counter ++ ;
				break;
			case 17:
			case 18:
				S_LCD_Counter ++ ;
				break;
			case 19:
				LCD_enuWriteStringAsync("00:",DummyCB);
				S_LCD_Counter ++ ;
				break;
			case 20:
			case 21:
				S_LCD_Counter ++ ;
				break;
			case 22:
				LCD_enuWriteStringAsync("00:",DummyCB);
				S_LCD_Counter ++ ;
				break;
			case 23:
			case 24:
				S_LCD_Counter ++ ;
				break;
			case 25:
				LCD_enuWriteStringAsync("000",DummyCB);
				S_LCD_Counter ++ ;
				break;
			case 26:
			case 27:
				S_LCD_Counter ++ ;
				break;
			case 28:
				S_LCD_Counter = 0 ;
				printEntireScreen = FALSE ;
				stopwatchNotStarted = FALSE;
				break;
			}
		}
		else
		{
			/* Do Nothing because the current mode is not stopwatch mode. */
		}
	}
}
