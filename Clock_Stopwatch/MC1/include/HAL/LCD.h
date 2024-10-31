/******************************************************************************
 *
 * Module: 	LCD driver to: 	- Initialize GPIO pins to which the LCD is connected to.
 * 							- Displaying what the user wants.
 *
 * Supported Models:	- 16 x 2 Character LCD.
 *
 * File Name: LCD.h
 *
 * Description: Driver's APIs' prototypes and typedefs' declaration.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 01-01-2024 (Edited for ARM at 18-03-2024)
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_


/************************************************************************************/
/*									Includes										*/
/************************************************************************************/



/* ِIncluding the .h file that contains all configurations */
#include "CFG/LCD_CNF.h"


/************************************************************************************/
/*								Macros Declaration									*/
/************************************************************************************/

/**
 *@brief : Clear the display and return the cursor to the upper left corner in the LCD.
 */
#define	LCD_ClearDisplay							0x01
/**
 *@brief : Return the cursor to the upper left corner in the LCD and return the display to its original position.
 */
#define	LCD_ReturnHome								0x02
/**
 *@brief : The cursor will be decremented one position backward every time you type something.
 */
#define LCD_EntryMode_CursorDecrement_ShiftOFF		0x04
/**
 *@brief : The cursor will be incremented one position forward every time you type something.
 */
#define LCD_EntryMode_CursorIncrement_ShiftOFF		0x06
/**
 *@brief : It looks as if the cursor stands still and only the display seems to shift right.
 */
#define LCD_EntryMode_CursorDecrement_ShiftON	 	0x05
/**
 *@brief : It looks as if the cursor stands still and only the display seems to shift left.
 */
#define LCD_EntryMode_CursorIncrement_ShiftON		0x07
/**
 *@brief : The display is on, but the cursor is off and there is no blinking.
 */
#define LCD_DisplayON_CursorOFF_BlinkOFF		 	0x0C
/**
 *@brief : The display is on, but the cursor is off and the current character is blinking.
 */
#define LCD_DisplayON_CursorOFF_BlinkON				0x0D
/**
 *@brief : The display is on, the cursor is on, but there is no blinking.
 */
#define LCD_DisplayON_CursorON_BlinkOFF				0x0E
/**
 *@brief : The display is on, the cursor is on and blinking.
 */
#define LCD_DisplayON_CursorON_BlinkON				0x0F
/**
 *@brief : The display is off, The display data remains in the DDRAM.
 */
#define LCD_DisplayOFF								0x08
/**
 *@brief : Shifts cursor position to the left (AC is decreased by 1).
 */
#define LCD_CursorShiftLeft							0x10
/**
 *@brief : Shifts cursor position to the right (AC is increased by 1).
 */
#define LCD_CursorShiftRight						0x14
/**
 *@brief : Shifts the entire display to the left, cursor follows the display shift.
 */
#define LCD_DisplayShiftLeft						0x18
/**
 *@brief : Shifts the entire display to the right, cursor follows the display shift.
 */
#define LCD_DisplayShiftRight						0x1C
/**
 *@brief : The used mode is four-bit mode, with 2 line display and 5x7 dots character font.
 */
#define LCD_FourBitMode_2LineDisplay_5x7			0x28
/**
 *@brief : The used mode is four-bit mode, with 2 line display and 5x10 dots character font.
 */
#define LCD_FourBitMode_2LineDisplay_5x10			0x2C
/**
 *@brief : The used mode is eight-bit mode, with 2 line display and 5x7 dots character font.
 */
#define LCD_EightBitMode_2LineDisplay_5x7			0x38
/**
 *@brief : The used mode is eight-bit mode, with 2 line display and 5x7 dots character font.
 */
#define LCD_EightBitMode_2LineDisplay_5x10			0x3C


/* GPIO ports */

// #define GPIO_PORTA						(0)	/* 	GPIOA Base Address			*/
// #define GPIO_PORTB						(1)	/* 	GPIOB Base Address			*/
// #define GPIO_PORTC						(2)	/* 	GPIOC Base Address			*/
// #define GPIO_PORTD						(3)	/* 	GPIOD Base Address			*/
// #define GPIO_PORTE						(4)	/* 	GPIOE Base Address			*/
// #define GPIO_PORTH						(5)	/* 	GPIOH Base Address			*/
// /****************************************************************************************/


// /* GPIO port's pins */

// #define GPIO_PIN0						(0)
// #define GPIO_PIN1						(1)
// #define GPIO_PIN2						(2)
// #define GPIO_PIN3						(3)
// #define GPIO_PIN4						(4)
// #define GPIO_PIN5						(5)
// #define GPIO_PIN6						(6)
// #define GPIO_PIN7						(7)
// #define GPIO_PIN8						(8)
// #define GPIO_PIN9						(9)
// #define GPIO_PIN10						(10)
// #define GPIO_PIN11						(11)
// #define GPIO_PIN12						(12)
// #define GPIO_PIN13						(13)
// #define GPIO_PIN14						(14)
// #define GPIO_PIN15						(15)
// /****************************************************************************************/


#define D0		0
#define D1		1
#define D2		2
#define D3		3
#define D4		4
#define D5		5
#define D6		6
#define D7		7
#define RS		8
#define	RW		9
#define	E		10

#define D4_4BITMODE		0
#define D5_4BITMODE		1
#define D6_4BITMODE		2
#define D7_4BITMODE		3
#define RS_4BITMODE		4
#define	RW_4BITMODE		5
#define	E_4BITMODE		6



#define LCD_FOUR_BITS_MODE		0
#define	LCD_EIGHT_BITS_MODE		1



/************************************************************************************/
/*								User-defined Declaration							*/
/************************************************************************************/

/**
 *@brief : The Error List Type
 */
typedef enum
{
	/**
	 *@brief : Everything OK, Function had Performed Correctly.
	 */
	LCD_enuOk = 0,
	/**
	 *@brief : Something went wrong in the function.
	 */
	LCD_enuNotOk,
	/**
	 *@brief : NULL Pointer is passed.
	 */
	LCD_enuNullPointer,
	/**
	 *@brief : If the entered Row number is not exist in the LCD.
	 */
	LCD_enuWrongRowNumber,
	/**
	 *@brief : If the entered Column number is not exist in the LCD.
	 */
	LCD_enuWrongColumnNumber,
	/**
	 *@brief : If the entered Block number is not exist in the CGRAM.
	 */
	LCD_enuWrongBlockNumber,
	/**
	 *@brief : If a problem happen when setting the value or the direction of one of the pin that the LCD is connected to.
	 */
	LCD_enuWrongPinConfiguration

}LCD_enuError_t;


/**
 *@brief : The available Rows in the LCD
 */
typedef enum
{
	/**
	 *@brief : First row in the LCD.
	 */
	LCD_enuFirstRow = 0,
	/**
	 *@brief : Second row in the LCD.
	 */
	LCD_enuSecondRow

}LCD_enuRowNumber_t;


/**
 *@brief : The available Columns in the LCD
 */
typedef enum
{
	/**
	 *@brief : First column in the LCD.
	 */
	LCD_enuColumn_1 = 0,
	/**
	 *@brief : Second column in the LCD.
	 */
	LCD_enuColumn_2,
	/**
	 *@brief : Third column in the LCD.
	 */
	LCD_enuColumn_3,
	/**
	 *@brief : Column number 4 in the LCD.
	 */
	LCD_enuColumn_4,
	/**
	 *@brief : Column number 5 in the LCD.
	 */
	LCD_enuColumn_5,
	/**
	 *@brief : Column number 6 in the LCD.
	 */
	LCD_enuColumn_6,
	/**
	 *@brief : Column number 7 in the LCD.
	 */
	LCD_enuColumn_7,
	/**
	 *@brief : Column number 8 in the LCD.
	 */
	LCD_enuColumn_8,
	/**
	 *@brief : Column number 9 in the LCD.
	 */
	LCD_enuColumn_9,
	/**
	 *@brief : Column number 10 in the LCD.
	 */
	LCD_enuColumn_10,
	/**
	 *@brief : Column number 11 in the LCD.
	 */
	LCD_enuColumn_11,
	/**
	 *@brief : Column number 12 in the LCD.
	 */
	LCD_enuColumn_12,
	/**
	 *@brief : Column number 13 in the LCD.
	 */
	LCD_enuColumn_13,
	/**
	 *@brief : Column number 14 in the LCD.
	 */
	LCD_enuColumn_14,
	/**
	 *@brief : Column number 15 in the LCD.
	 */
	LCD_enuColumn_15,
	/**
	 *@brief : Column number 16 in the LCD.
	 */
	LCD_enuColumn_16,
	/**
	 *@brief : Column number 17 in the LCD.
	 */
	LCD_enuColumn_17,
	/**
	 *@brief : Column number 18 in the LCD.
	 */
	LCD_enuColumn_18,
	/**
	 *@brief : Column number 19 in the LCD.
	 */
	LCD_enuColumn_19,
	/**
	 *@brief : Column number 20 in the LCD.
	 */
	LCD_enuColumn_20,
	/**
	 *@brief : Column number 21 in the LCD.
	 */
	LCD_enuColumn_21,
	/**
	 *@brief : Column number 22 in the LCD.
	 */
	LCD_enuColumn_22,
	/**
	 *@brief : Column number 23 in the LCD.
	 */
	LCD_enuColumn_23,
	/**
	 *@brief : Column number 24 in the LCD.
	 */
	LCD_enuColumn_24,
	/**
	 *@brief : Column number 25 in the LCD.
	 */
	LCD_enuColumn_25,
	/**
	 *@brief : Column number 26 in the LCD.
	 */
	LCD_enuColumn_26,
	/**
	 *@brief : Column number 27 in the LCD.
	 */
	LCD_enuColumn_27,
	/**
	 *@brief : Column number 28 in the LCD.
	 */
	LCD_enuColumn_28,
	/**
	 *@brief : Column number 29 in the LCD.
	 */
	LCD_enuColumn_29,
	/**
	 *@brief : Column number 30 in the LCD.
	 */
	LCD_enuColumn_30,
	/**
	 *@brief : Column number 31 in the LCD.
	 */
	LCD_enuColumn_31,
	/**
	 *@brief : Column number 32 in the LCD.
	 */
	LCD_enuColumn_32,
	/**
	 *@brief : Column number 33 in the LCD.
	 */
	LCD_enuColumn_33,
	/**
	 *@brief : Column number 34 in the LCD.
	 */
	LCD_enuColumn_34,
	/**
	 *@brief : Column number 35 in the LCD.
	 */
	LCD_enuColumn_35,
	/**
	 *@brief : Column number 36 in the LCD.
	 */
	LCD_enuColumn_36,
	/**
	 *@brief : Column number 37 in the LCD.
	 */
	LCD_enuColumn_37,
	/**
	 *@brief : Column number 38 in the LCD.
	 */
	LCD_enuColumn_38,
	/**
	 *@brief : Column number 39 in the LCD.
	 */
	LCD_enuColumn_39,
	/**
	 *@brief : Column number 40 in the LCD.
	 */
	LCD_enuColumn_40,

}LCD_enuColumnNumber_t;


/* Structure that will be used when setting the direction and the value of any of the LCD's pins */
typedef struct {
	uint32_t LCD_port_number;
	uint32_t LCD_pin_number;
}LCD_strLCDPinConfig_t;

/************************************************************************************/
/*								Functions' Declaration								*/
/************************************************************************************/


/**
 *@brief : Function that initializes the LCD.
 *@param : a callback function you want to be called after finishing your request.
 *@return: Error State.
 */
LCD_enuError_t LCD_enuInitAsync(void (*callBackFn)(void));


/**
 *@brief : Function that returns to you the current state of the LCD.
 *@param : pointer inside which We will return to you the state of the LCD.
 *@return: Error State.
 */
LCD_enuError_t LCD_enuGetState(uint8_t* State);


/**
 *@brief : Function that clears the screen.
 *@param : a callback function you want to be called after finishing your request.
 *@return: Error State.
 */
LCD_enuError_t LCD_enuClearScreenAsync(void (*callBackFn)(void));


/**
 *@brief : Function that sets the cursor's position.
 *@param : The row and the column you want the cursor to go at, and a callback function
 *			you want to be called after finishing your request.
 *@return: Error State.
 */
LCD_enuError_t LCD_enuSetCursorAsync(LCD_enuRowNumber_t row, uint8_t column, void (*callBackFn)(void));


/**
 *@brief : Function that prints a string on the LCD.
 *@param : String you want to print, a callback function you want to be called after finishing
 *			your request.
 *@return: Error State.
 */
LCD_enuError_t LCD_enuWriteStringAsync(uint8_t* string, void (*callBackFn)(void));

/**
 *@brief : Function that prints a certain number on the LCD.
 *@param : Number you want to print.
 *@return: Error State.
 */
LCD_enuError_t LCD_enuWriteNumberAsync(uint64_t Copy_uint64Number, void (callBackFn)(void));


/**
 *@brief : Function that sends a command to the LCD.
 *@param : A command and a callback function you want to be called after finishing your request.
 *@return: Error State.
 */
LCD_enuError_t LCD_enuSendCommandAsync(uint8_t Copy_uint8Command ,void (*callBackFn)(void));


#endif /* LCD_H_ */
