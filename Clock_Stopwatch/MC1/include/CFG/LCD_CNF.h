/******************************************************************************
 *
 * Module: 	LCD driver to: 	- Initialize GPIO pins to which the LCD is connected to.
 * 							- Displaying what the user wants.
 *
 * Supported Models:	- 16 x 2 Character LCD.
 *
 * File Name: LCD_cfg.h
 *
 * Description: Configuration file for LCD Driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 01-01-2024 (Edited for ARM at 18-03-2024)
 *
 *******************************************************************************/

#ifndef LCD_CFG_H_
#define LCD_CFG_H_


/****************************************************************************************/
/*							Configuration Macros Declaration							*/
/****************************************************************************************/

/* Description: Choose whether you are using FOUR_BIT_MODE or EIGHT_BIT_MODE
 * Options:		LCD_FOUR_BITS_MODE
 * 		or		LCD_EIGHT_BITS_MODE						*/

#define	LCD_DATA_BITS_MODE		LCD_FOUR_BITS_MODE
/*****************************************************************************************/

#endif /* LCD_CFG_H_ */