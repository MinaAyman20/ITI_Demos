#include "Clock_Stopwatch.h"
/*******************************************************************************************************************/
/*                                                 Global Variable                                                 */
/*******************************************************************************************************************/
// Define the current date and time variables
DateTime currentDateTime = {0, 0, 20, 4, 17, 4, 2024}; // Initialized to April 17, 2024, 20:00:00
DateTime previousDateTime = {0, 0, 0, 0, 0, 0, 0};     // Previous date and time, initially set to zero
DateTime currentstopwatchTime = {0, 0, 0, 0, 0, 0, 0}; // Current time for the stopwatch, initially set to zero

// Counter for controlling display switching between date and time
uint8_t Date_Counter = 0;

// Mode variable to control the operation mode (clock mode or stopwatch mode)
uint8_t Mode = CLOCK_MODE;

// Variable to control stopwatch timing
uint8_t Stopwatch_Time = 0;

// Array to hold the status of various buttons
uint8_t Button_arr[7] = {0};

// Variable to store the received button value
uint8_t Button_Received = NO_BUTTON_PRESSED;

// Status variable for edit mode (ON/OFF)
uint8_t Edit_Mode_Status = EDIT_MODE_OFF;

// External declaration for the USART receive buffer
extern USART_RXBuffer rx_button_buff;

// Cursor structure to hold cursor position for editing
Cursor Edit_Cursor = {CLOCK_CURSOR_START_X, CURSOR_AT_CLOCK_Y};

// Guard variable to control the execution of commands
uint8_t Command_Guard = COMMAND_DONE;

// State variable for controlling the stopwatch (running/stopped/reset)
uint8_t Stopwatch_State = STOPWATCH_STOPPED;

// Status variable for OK mode (ON/OFF)
uint8_t OK_Mode_Status = OK_MODE_OFF;

// Buffer to hold formatted time and date strings
uint8_t TimeStr[33];
uint8_t DateStr[33];

/*******************************************************************************************************************/
/*                                                 Runnables                                                       */
/*******************************************************************************************************************/

void Clock_RunnerTask(void)
{
    // Increment the current time
    incrementTime(&currentDateTime);

    // Check if the mode is CLOCK_MODE, command guard is COMMAND_DONE, and edit mode is OFF
    if (Mode == CLOCK_MODE && Command_Guard == COMMAND_DONE && Edit_Mode_Status == EDIT_MODE_OFF)
    {
        // Check if Date_Counter is 0
        if (Date_Counter == 0)
        {
            // Check if the seconds have changed since the last update
            if (previousDateTime.seconds != currentDateTime.seconds)
            {
                // Format the current time and update the LCD asynchronously
                formatTime(&currentDateTime, TimeStr);
                LCD_enuWriteStringAsync(TimeStr, lcd_TimeStringdone);

                // Update the previousDateTime to the currentDateTime
                previousDateTime = currentDateTime;

                // Increment Date_Counter to indicate the next update should show the date
                Date_Counter++;
            }
        }
        else
        {
            // Format the current date and update the LCD asynchronously
            formatDate(&currentDateTime, DateStr);
            LCD_enuWriteStringAsync(DateStr, lcd_DateStringdone);

            // Reset Date_Counter to switch back to showing the time
            Date_Counter = 0;
        }
    }
}

void Stopwatch_RunnerTask(void)
{
    uint8_t StopWatchTimeStr[43];
    formatStopWatchTime(&currentstopwatchTime, StopWatchTimeStr);
    switch (Stopwatch_State)
    {
    case STOPWATCH_RESET:
        currentstopwatchTime.milliseconds = 0;
        currentstopwatchTime.seconds = 0;
        currentstopwatchTime.minutes = 0;
        currentstopwatchTime.hours = 0;
        if (Mode == STOPWATCH_MODE && Command_Guard == COMMAND_DONE)
        {
            Command_Guard = COMMAND_IN_PROGRESS;
            LCD_enuWriteStringAsync(StopWatchTimeStr, lcd_StopWatchTimeStringdone);
        }
        break;

    case STOPWATCH_RUNNING:
        incrementTime(&currentstopwatchTime);
        if (Mode == STOPWATCH_MODE && Command_Guard == COMMAND_DONE)
        {
            Command_Guard = COMMAND_IN_PROGRESS;
            LCD_enuWriteStringAsync(StopWatchTimeStr, lcd_StopWatchTimeStringdone);
        }
        break;

    case STOPWATCH_STOPPED:
        if (Mode == STOPWATCH_MODE && Command_Guard == COMMAND_DONE)
        {
            Command_Guard = COMMAND_IN_PROGRESS;
            LCD_enuWriteStringAsync(StopWatchTimeStr, lcd_StopWatchTimeStringdone);
        }
        break;
    }
}

void Switch_runnable(void)
{
    /* Button Recieve Part */
    Button_Received = DecodeFrame(Button_Received);
    switch (Button_Received)
    {
    case MODE_BUTTON:
        Mode = !Mode;
        Command_Guard = COMMAND_IN_PROGRESS;
        Edit_Mode_Status = EDIT_MODE_OFF;
        OK_Mode_Status = OK_MODE_OFF;
        LCD_enuClearScreenAsync(LCD_CleanDone);
        Button_Received = NO_BUTTON_PRESSED;
        break;

    case EDIT_BUTTON:
        if (Mode == CLOCK_MODE)
        {
            Edit_Mode_Status = !Edit_Mode_Status;
        }
        if (Edit_Mode_Status == EDIT_MODE_ON)
        {
            if (Mode == CLOCK_MODE)
            {
                Command_Guard = COMMAND_IN_PROGRESS;
                LCD_enuSendCommandAsync(LCD_DisplayON_CursorOFF_BlinkON, Lcd_EditDone);
            }
        }
        else if (Edit_Mode_Status == EDIT_MODE_OFF)
        {
            if (Mode == CLOCK_MODE)
            {
                Command_Guard = COMMAND_IN_PROGRESS;
                LCD_enuSendCommandAsync(LCD_DisplayON_CursorOFF_BlinkOFF, Lcd_EditOFFDone);
                OK_Mode_Status = OK_MODE_OFF;
            }
        }
        Button_Received = NO_BUTTON_PRESSED;
        break;

    case UP_START_BUTTON:
        if (Mode == STOPWATCH_MODE)
        {
            Stopwatch_State = STOPWATCH_RUNNING;
        }
        else
        {
            if (Edit_Mode_Status == EDIT_MODE_ON && OK_Mode_Status == OK_MODE_OFF)
            {
                Edit_Cursor.Y = !Edit_Cursor.Y;
                Command_Guard = COMMAND_IN_PROGRESS;
                LCD_enuSetCursorAsync(Edit_Cursor.Y, Edit_Cursor.X, Lcd_EditCursorDone);
            }
            if (Edit_Mode_Status == EDIT_MODE_ON && OK_Mode_Status == OK_MODE_ON)
            {
                switch (Edit_Cursor.Y)
                {
                case CURSOR_AT_CLOCK_Y:
                    switch (Edit_Cursor.X)
                    {
                    case HOUR_EDIT_POSITION:
                        currentDateTime.hours++;
                        if (currentDateTime.hours > 23)
                        {
                            currentDateTime.hours = 0;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_CLOCK_Y, CLOCK_CURSOR_START_X, Lcd_EditCursorRefreshDoneTime);
                        break;

                    case MINUTE_EDIT_POSITION:
                        currentDateTime.minutes++;
                        if (currentDateTime.minutes > 59)
                        {
                            currentDateTime.minutes = 0;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_CLOCK_Y, CLOCK_CURSOR_START_X, Lcd_EditCursorRefreshDoneTime);
                        break;

                    case SECOND_EDIT_POSITION:
                        currentDateTime.seconds++;
                        if (currentDateTime.seconds > 59)
                        {
                            currentDateTime.seconds = 0;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_CLOCK_Y, CLOCK_CURSOR_START_X, Lcd_EditCursorRefreshDoneTime);
                        break;
                    }
                    break;
                case CURSOR_AT_DATE_Y:
                    switch (Edit_Cursor.X)
                    {
                    case DAY_EDIT_POSITION:
                        currentDateTime.day++;
                        if (currentDateTime.day > daysInMonth(currentDateTime.month, currentDateTime.year))
                        {
                            currentDateTime.day = 1;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case MONTH_EDIT_POSITION:
                        currentDateTime.month++;
                        if (currentDateTime.month > 12)
                        {
                            currentDateTime.month = 1;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case YEAR_EDIT_POSITION:
                        currentDateTime.year++;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case DECADE_EDIT_POSITION:
                        currentDateTime.year += 10;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case CENTURY_EDIT_POSITION:
                        currentDateTime.year += 100;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case MILLENIUM_EDIT_POSITION:
                        currentDateTime.year += 1000;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;
                    }
                    break;
                }
                break;
            }
        }
        Button_Received = NO_BUTTON_PRESSED;
        break;

    case DOWN_STOP_BUTTON:
        if (Mode == STOPWATCH_MODE)
        {
            Stopwatch_State = STOPWATCH_STOPPED;
        }
        else
        {
            if (Edit_Mode_Status == EDIT_MODE_ON && OK_Mode_Status == OK_MODE_OFF)
            {
                Edit_Cursor.Y = !Edit_Cursor.Y;
                Command_Guard = COMMAND_IN_PROGRESS;
                LCD_enuSetCursorAsync(Edit_Cursor.Y, Edit_Cursor.X, Lcd_EditCursorDone);
            }
            if (Edit_Mode_Status == EDIT_MODE_ON && OK_Mode_Status == OK_MODE_ON)
            {
                switch (Edit_Cursor.Y)
                {
                case CURSOR_AT_CLOCK_Y:
                    switch (Edit_Cursor.X)
                    {
                    case HOUR_EDIT_POSITION:
                        currentDateTime.hours--;
                        if (currentDateTime.hours < 0)
                        {
                            currentDateTime.hours = 23;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_CLOCK_Y, CLOCK_CURSOR_START_X, Lcd_EditCursorRefreshDoneTime);
                        break;

                    case MINUTE_EDIT_POSITION:
                        currentDateTime.minutes--;
                        if (currentDateTime.minutes < 0)
                        {
                            currentDateTime.minutes = 59;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_CLOCK_Y, CLOCK_CURSOR_START_X, Lcd_EditCursorRefreshDoneTime);
                        break;

                    case SECOND_EDIT_POSITION:
                        currentDateTime.seconds--;
                        if (currentDateTime.seconds < 0)
                        {
                            currentDateTime.seconds = 59;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_CLOCK_Y, CLOCK_CURSOR_START_X, Lcd_EditCursorRefreshDoneTime);
                        break;
                    }
                    break;
                case CURSOR_AT_DATE_Y:
                    switch (Edit_Cursor.X)
                    {
                    case DAY_EDIT_POSITION:
                        currentDateTime.day--;
                        if (currentDateTime.day < 1)
                        {
                            currentDateTime.day = daysInMonth(currentDateTime.month, currentDateTime.year);
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case MONTH_EDIT_POSITION:
                        currentDateTime.month--;
                        if (currentDateTime.month < 1)
                        {
                            currentDateTime.month = 12;
                        }
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case YEAR_EDIT_POSITION:
                        currentDateTime.year--;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case DECADE_EDIT_POSITION:
                        currentDateTime.year -= 10;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case CENTURY_EDIT_POSITION:
                        currentDateTime.year -= 100;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;

                    case MILLENIUM_EDIT_POSITION:
                        currentDateTime.year -= 1000;
                        Command_Guard = COMMAND_IN_PROGRESS;
                        LCD_enuSetCursorAsync(CURSOR_AT_DATE_Y, DATE_CURSOR_START_X, Lcd_EditCursorRefreshDoneDate);
                        break;
                    }
                    break;
                }
            }
        }
        Button_Received = NO_BUTTON_PRESSED;
        break;

    case LEFT_RESET_BUTTON:
        if (Mode == STOPWATCH_MODE)
        {
            Stopwatch_State = STOPWATCH_RESET;
        }
        else if (Mode == CLOCK_MODE && Edit_Mode_Status == EDIT_MODE_ON)
        {
            Edit_Cursor.X--;
            if (Edit_Cursor.Y == CURSOR_AT_CLOCK_Y && Edit_Cursor.X < CLOCK_CURSOR_START_X)
            {
                Edit_Cursor.X = CLOCK_CURSOR_END_X;
            }
            else if (Edit_Cursor.Y == CURSOR_AT_DATE_Y && Edit_Cursor.X < DATE_CURSOR_START_X)
            {
                Edit_Cursor.X = DATE_CURSOR_END_X;
            }
            Command_Guard = COMMAND_IN_PROGRESS;
            LCD_enuSetCursorAsync(Edit_Cursor.Y, Edit_Cursor.X, Lcd_EditCursorDone);
        }
        Button_Received = NO_BUTTON_PRESSED;
        break;

    case RIGHT_BUTTON:
        if (Mode == CLOCK_MODE && Edit_Mode_Status == EDIT_MODE_ON)
        {
            Edit_Cursor.X++;
            if (Edit_Cursor.Y == CURSOR_AT_CLOCK_Y && Edit_Cursor.X > CLOCK_CURSOR_END_X)
            {
                Edit_Cursor.X = CLOCK_CURSOR_START_X;
            }
            else if (Edit_Cursor.Y == CURSOR_AT_DATE_Y && Edit_Cursor.X > DATE_CURSOR_END_X)
            {
                Edit_Cursor.X = DATE_CURSOR_START_X;
            }
            Command_Guard = COMMAND_IN_PROGRESS;
            LCD_enuSetCursorAsync(Edit_Cursor.Y, Edit_Cursor.X, Lcd_EditCursorDone);
            Button_Received = NO_BUTTON_PRESSED;
        }
        break;

    case OK_BUTTON:
        if (Mode == CLOCK_MODE && Edit_Mode_Status == EDIT_MODE_ON)
        {
            OK_Mode_Status = !OK_Mode_Status;
            Command_Guard = COMMAND_IN_PROGRESS;
        }
        if (OK_Mode_Status == OK_MODE_ON && Edit_Mode_Status == EDIT_MODE_ON && Mode == CLOCK_MODE)
        {
            Command_Guard = COMMAND_IN_PROGRESS;
            LCD_enuSendCommandAsync(LCD_DisplayON_CursorON_BlinkOFF, Lcd_OKDone);
        }
        else if (OK_Mode_Status == OK_MODE_OFF && Edit_Mode_Status == EDIT_MODE_ON && Mode == CLOCK_MODE)
        {
            Command_Guard = COMMAND_IN_PROGRESS;
            LCD_enuSendCommandAsync(LCD_DisplayON_CursorOFF_BlinkON, Lcd_OKDone);
        }
        Button_Received = NO_BUTTON_PRESSED;
        break;
    }
    /* Button Send Part */
    uint8_t Button_Send = 0;
    Switch_getstatus(UP_Switch, &Button_arr[UP_START_BUTTON_STATE]);
    Switch_getstatus(DOWN_Switch, &Button_arr[DOWN_STOP_BUTTON_STATE]);
    Switch_getstatus(LEFT_Switch, &Button_arr[LEFT_RESET_BUTTON_STATE]);
    Switch_getstatus(RIGHT_Switch, &Button_arr[RIGHT_BUTTON_STATE]);
    Switch_getstatus(OK_Switch, &Button_arr[OK_BUTTON_STATE]);
    Switch_getstatus(MODE_Switch, &Button_arr[MODE_BUTTON_STATE]);
    Switch_getstatus(EDIT_Switch, &Button_arr[EDIT_BUTTON_STATE]);

    if (Button_arr[UP_START_BUTTON_STATE] == 1)
    {
        Button_Send = EncodeFrame(UP_START_BUTTON);
        USART_SendByteAsynchronous(USART1, Button_Send);
        Button_arr[UP_START_BUTTON_STATE] = 0;
    }
    else if (Button_arr[DOWN_STOP_BUTTON_STATE] == 1)
    {
        Button_Send = EncodeFrame(DOWN_STOP_BUTTON);
        USART_SendByteAsynchronous(USART1, Button_Send);
        Button_arr[DOWN_STOP_BUTTON_STATE] = 0;
    }
    else if (Button_arr[LEFT_RESET_BUTTON_STATE] == 1)
    {
        Button_Send = EncodeFrame(LEFT_RESET_BUTTON);
        USART_SendByteAsynchronous(USART1, Button_Send);
        Button_arr[LEFT_RESET_BUTTON_STATE] = 0;
    }
    else if (Button_arr[RIGHT_BUTTON_STATE] == 1)
    {
        Button_Send = EncodeFrame(RIGHT_BUTTON);
        USART_SendByteAsynchronous(USART1, Button_Send);
        Button_arr[RIGHT_BUTTON_STATE] = 0;
    }
    else if (Button_arr[OK_BUTTON_STATE] == 1)
    {
        Button_Send = EncodeFrame(OK_BUTTON);
        USART_SendByteAsynchronous(USART1, Button_Send);
        Button_arr[OK_BUTTON_STATE] = 0;
    }
    else if (Button_arr[MODE_BUTTON_STATE] == 1)
    {
        Button_Send = EncodeFrame(MODE_BUTTON);
        USART_SendByteAsynchronous(USART1, Button_Send);
        Button_arr[MODE_BUTTON_STATE] = 0;
    }
    else if (Button_arr[EDIT_BUTTON_STATE] == 1)
    {
        Button_Send = EncodeFrame(EDIT_BUTTON);
        USART_SendByteAsynchronous(USART1, Button_Send);
        Button_arr[EDIT_BUTTON_STATE] = 0;
    }
}

/*******************************************************************************************************************/
/*                                                 Helper Functions                                                */
/*******************************************************************************************************************/

void incrementTime(DateTime *dateTime)
{
    // Increment milliseconds by 200
    dateTime->milliseconds += 200;

    // Check if milliseconds have rolled over to a full second
    if (dateTime->milliseconds >= 1000)
    {
        dateTime->milliseconds -= 1000; // Reset milliseconds to 0

        // Increment seconds
        if (++dateTime->seconds >= 60)
        {
            dateTime->seconds = 0; // Reset seconds to 0

            // Increment minutes
            if (++dateTime->minutes >= 60)
            {
                dateTime->minutes = 0; // Reset minutes to 0

                // Increment hours
                if (++dateTime->hours >= 24)
                {
                    dateTime->hours = 0; // Reset hours to 0

                    // Increment day and check for month rollover
                    dateTime->day++;
                    if (dateTime->day > daysInMonth(dateTime->month, dateTime->year))
                    {
                        dateTime->day = 1; // Reset day to 1
                        dateTime->month++; // Increment month

                        // Check for year rollover
                        if (dateTime->month > 12)
                        {
                            dateTime->month = 1; // Reset month to 1
                            dateTime->year++;    // Increment year
                        }
                    }
                }
            }
        }
    }
}

void formatDate(DateTime *dateTime, char *buffer)
{
    if (dateTime->day > daysInMonth(dateTime->month, dateTime->year))
    {
        dateTime->day = 1; // Reset day to 1
    }
    // Use sprintf to format the date into the buffer
    sprintf(buffer, "%02d/%02d/%04d", dateTime->day, dateTime->month, dateTime->year);
}

void formatTime(const DateTime *dateTime, char *buffer)
{
    // Use sprintf to format the time into the buffer
    sprintf(buffer, "%02d:%02d:%02d", dateTime->hours, dateTime->minutes, dateTime->seconds);
}

void formatStopWatchTime(const DateTime *dateTime, char *buffer)
{
    // Use sprintf to format the stopwatch time into the buffer
    sprintf(buffer, "%02d:%02d:%02d:%03d", dateTime->hours, dateTime->minutes, dateTime->seconds, dateTime->milliseconds);
}

int isLeapYear(int year)
{
    // If the year is not divisible by 4, it's not a leap year
    if (year % 4 != 0)
    {
        return 0;
    }
    // If the year is not divisible by 100, it's a leap year
    else if (year % 100 != 0)
    {
        return 1;
    }
    // If the year is not divisible by 400, it's not a leap year
    else if (year % 400 != 0)
    {
        return 0;
    }
    // If the year is divisible by 400, it's a leap year
    return 1;
}

int daysInMonth(int month, int year)
{
    // Array storing the number of days in each month (0-based index)
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // If it's February and it's a leap year, return 29 days
    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }

    // Return the number of days for the given month
    return days[month - 1];
}

void Lcd_CursorDone(void)
{
    Command_Guard = COMMAND_DONE;
}

void lcd_TimeStringdone(void)
{
    // Check if Date_Counter is 1
    if (Date_Counter == 1)
    {
        // Set the cursor position to the second line (row 1) on the LCD
        LCD_enuSetCursorAsync(1, 0, Lcd_CursorDone);
    }
    else
    {
        // Set the cursor position to the first line (row 0) on the LCD
        LCD_enuSetCursorAsync(0, 0, Lcd_CursorDone);
    }
}

void lcd_DateStringdone(void)
{
    LCD_enuSetCursorAsync(0, 0, Lcd_CursorDone);
}

void lcd_StopWatchTimeStringdone(void)
{
    LCD_enuSetCursorAsync(0, 0, Lcd_CursorDone);
}

uint8_t EncodeFrame(uint8_t Button)
{
    return (Button << 4) | Button;
}

uint8_t DecodeFrame(uint8_t frame)
{
    uint8_t result = 0;
    if (((frame >> 4) ^ (frame & 0x0F)) == 0)
    {
        result = frame >> 4;
    }
    return result;
}

void recieve_callback()
{
    Button_Received = rx_button_buff.Data;
    USART_ReceiveBuffer(&rx_button_buff);
}

void LCD_CleanDone(void)
{
    Date_Counter = 0;
    Command_Guard = COMMAND_DONE;
}

void Lcd_EditDone(void)
{
    Command_Guard = COMMAND_IN_PROGRESS;
    LCD_enuSetCursorAsync(CURSOR_AT_CLOCK_Y, CLOCK_CURSOR_START_X, Lcd_EditCursorDone);
}

void Lcd_EditCursorDone(void)
{
    Command_Guard = COMMAND_DONE;
}

void Lcd_EditOFFDone(void)
{
    Command_Guard = COMMAND_IN_PROGRESS;
    Date_Counter = 0;
    Edit_Cursor.X = CLOCK_CURSOR_START_X;
    Edit_Cursor.Y = CURSOR_AT_CLOCK_Y;
    LCD_enuSetCursorAsync(0, 0, Lcd_EditCursorDone);
}

void Lcd_OKDone(void)
{
    Command_Guard = COMMAND_DONE;
}

void Lcd_EditCursorRefreshDoneTime(void)
{
    Command_Guard = COMMAND_IN_PROGRESS;
    formatTime(&currentDateTime, TimeStr);
    LCD_enuWriteStringAsync(TimeStr, lcd_TimeStringEditdone);
}

void Lcd_EditCursorRefreshDoneDate(void)
{
    Command_Guard = COMMAND_IN_PROGRESS;
    formatDate(&currentDateTime, DateStr);
    LCD_enuWriteStringAsync(DateStr, lcd_TimeStringEditdone);
}

void lcd_TimeStringEditdone(void)
{
    Command_Guard = COMMAND_IN_PROGRESS;
    LCD_enuSetCursorAsync(Edit_Cursor.Y, Edit_Cursor.X, Lcd_EditCursorDone);
}