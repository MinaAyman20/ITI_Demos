#pragma once
#include <stdint.h>
#include <stdio.h>
#include "HAL/LCD.h"
#include "HAL/Switch.h"
#include "MCAL/USART.h"

/*******************************************************************************************************************/
/*                                                 Defines:                                                        */
/*******************************************************************************************************************/

/*Define constants for different modes*/ 
#define CLOCK_MODE 0
#define STOPWATCH_MODE 1
#define EDIT_MODE_ON 1
#define EDIT_MODE_OFF 0
#define COMMAND_DONE 1
#define COMMAND_IN_PROGRESS 0
#define STOPWATCH_RUNNING 1
#define STOPWATCH_STOPPED 0
#define STOPWATCH_RESET 2
#define OK_MODE_ON 1
#define OK_MODE_OFF 0

/*Define button codes*/
#define UP_START_BUTTON 0B1000
#define DOWN_STOP_BUTTON 0B1001
#define LEFT_RESET_BUTTON 0B1010
#define RIGHT_BUTTON 0B1011
#define OK_BUTTON 0B1100
#define MODE_BUTTON 0B1101
#define EDIT_BUTTON 0B1110

/*Define button state indices*/
#define UP_START_BUTTON_STATE 0
#define DOWN_STOP_BUTTON_STATE 1
#define LEFT_RESET_BUTTON_STATE 2
#define RIGHT_BUTTON_STATE 3
#define OK_BUTTON_STATE 4
#define MODE_BUTTON_STATE 5
#define EDIT_BUTTON_STATE 6
#define NO_BUTTON_PRESSED 0

/*Define cursor positions for clock and date*/
#define CLOCK_CURSOR_START_X 0
#define CLOCK_CURSOR_END_X 7
#define DATE_CURSOR_START_X 0
#define DATE_CURSOR_END_X 9
#define CURSOR_AT_CLOCK_Y 0
#define CURSOR_AT_DATE_Y 1
#define HOUR_EDIT_POSITION 1
#define MINUTE_EDIT_POSITION 4
#define SECOND_EDIT_POSITION 7
#define DAY_EDIT_POSITION 1
#define MONTH_EDIT_POSITION 4
#define YEAR_EDIT_POSITION 9
#define DECADE_EDIT_POSITION 8
#define CENTURY_EDIT_POSITION 7
#define MILLENIUM_EDIT_POSITION 6


/*******************************************************************************************************************/
/*                                                 Structures                                                      */
/*******************************************************************************************************************/
// Structure for date and time
typedef struct
{
    uint16_t milliseconds;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} DateTime;

// Structure for cursor position
typedef struct
{
    int8_t X;
    uint8_t Y;
} Cursor;

/*******************************************************************************************************************/
/*                                                 Function Prototypes                                             */
/*******************************************************************************************************************/
/**
 * Checks if a given year is a leap year.
 *
 * @param year The year to check.
 * @return 1 if the year is a leap year, 0 otherwise.
 */
int isLeapYear(int year);

/**
 * Gets the number of days in a given month of a year.
 *
 * @param month The month (1 to 12).
 * @param year The year.
 * @return The number of days in the month.
 */
int daysInMonth(int month, int year);

/**
 * Increments the date and time stored in the DateTime structure by 200 milliseconds.
 * Handles rollover of seconds, minutes, hours, days, and months as necessary.
 *
 * @param dateTime Pointer to the DateTime structure to be incremented.
 */
void incrementTime(DateTime *dateTime);

/**
 * Formats the date stored in the DateTime structure into a string with the format "DD/MM/YYYY".
 *
 * @param dateTime Pointer to the DateTime structure containing the date to be formatted.
 * @param buffer   Pointer to the character array where the formatted date string will be stored.
 */
void formatDate(DateTime *dateTime, char *buffer);

/**
 * Formats the time stored in the DateTime structure into a string with the format "HH:MM:SS".
 *
 * @param dateTime Pointer to the DateTime structure containing the time to be formatted.
 * @param buffer   Pointer to the character array where the formatted time string will be stored.
 */
void formatTime(const DateTime *dateTime, char *buffer);

/**
 * Formats the stopwatch time stored in the DateTime structure into a string with the format "HH:MM:SS:mmm".
 *
 * @param dateTime Pointer to the DateTime structure containing the stopwatch time to be formatted.
 * @param buffer   Pointer to the character array where the formatted stopwatch time string will be stored.
 */
void formatStopWatchTime(const DateTime *dateTime, char *buffer);

/**
 * Task for updating the clock display.
 * It increments the current time, updates the LCD display with the time or date based on the mode and conditions.
 */
void Clock_RunnerTask(void);

/**
 * Callback function called when the time string for the clock is updated on the LCD.
 * It sets the cursor position on the LCD based on the Date_Counter variable.
 * If Date_Counter is 1, it sets the cursor to the second line (row 1), otherwise, it sets it to the first line (row 0).
 */
void lcd_TimeStringdone(void);

/**
 * Callback function called when the date string for the clock is updated on the LCD.
 * It sets the cursor position on the LCD to the first line (row 0).
 */
void lcd_DateStringdone(void);

/**
 * Callback function called when the cursor operation is done.
 */
void Lcd_CursorDone(void);

/**
 * Task for updating the stopwatch display.
 * It handles the stopwatch state and updates the LCD display accordingly.
 */
void Stopwatch_RunnerTask(void);

/**
 * Encodes the button state into a frame to be sent via USART.
 *
 * @param Button The button state.
 * @return The encoded frame.
 */
uint8_t EncodeFrame(uint8_t Button);

/**
 * Switch task for receiving and sending button states via USART.
 */
void Switch_runnable(void);

/**
 * Callback function called when the stopwatch time string is updated on the LCD.
 * It sets the cursor position on the LCD to the first line (row 0).
 */
void lcd_StopWatchTimeStringdone(void);

/**
 * Callback function called when a button state is received via USART.
 * It updates the Button_Recieved variable with the received button state.
 */
void recieve_callback(void);

/**
 * Decodes the received frame from USART into a button state.
 *
 * @param frame The received frame.
 * @return The decoded button state.
 */
uint8_t DecodeFrame(uint8_t frame);

/**
 * Callback function called when the LCD screen is cleared.
 * It resets the Date_Counter and updates the Command_Guard variable to indicate that the command is done.
 */
void LCD_CleanDone(void);
100
/**
 * Callback function called when the edit mode is activated on the clock.
 * It updates the Command_Guard variable to indicate that the command is in progress.
 */
void Lcd_EditDone(void);

/**
 * Callback function called when the cursor operation in edit mode is done.
 * It updates the Command_Guard variable to indicate that the command is done.
 */
void Lcd_EditCursorDone(void);

/**
 * Callback function called when the edit mode is deactivated on the clock.
 * It resets the edit cursor position and updates the Command_Guard variable to indicate that the command is in progress.
 */
void Lcd_EditOFFDone(void);

/**
 * Callback function called when the OK mode is activated in edit mode on the clock.
 * It updates the Command_Guard variable to indicate that the command is done.
 */
void Lcd_OKDone(void);

/**
 * Callback function called when the cursor position in edit mode is refreshed for time editing.
 * It updates the Command_Guard variable to indicate that the command is in progress and refreshes the time string on the LCD.
 */
void Lcd_EditCursorRefreshDoneTime(void);

/**
 * Callback function called when the cursor position in edit mode is refreshed for date editing.
 * It updates the Command_Guard variable to indicate that the command is in progress and refreshes the date string on the LCD.
 */
void Lcd_EditCursorRefreshDoneDate(void);

/**
 * Callback function called when the time string is updated during edit mode on the clock.
 * It updates the Command_Guard variable to indicate that the command is in progress and handles cursor positioning in edit mode.
 */
void lcd_TimeStringEditdone(void);
