/******************************************************************************
 *
 * Module: 	LCD driver to: 	- Initialize GPIO pins to which the LCD is connected to.
 * 							- Displaying what the user wants.
 *
 * Supported Models:	- 16 x 2 Character LCD.
 *
 * File Name: LCD_cfg.c
 *
 * Description: Configuration file for LCD Driver.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 01-01-2024 (Edited for ARM at 18-03-2024)
 *
 *******************************************************************************/

#include "LIB/STD_TYPES.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
/* ِIncluding the .h file that contains all configurations */
#include "HAL/HLCD/HLCD_interface.h"
#include "CFG/HLCD/HLCD_config.h"


/********************************************************************************************/
/*									LCD Pins Configuration									*/
/********************************************************************************************/

/* Description: Choose the port to which the pin is connected to
 * Options:		GPIO_PORTA
 * 		or		GPIO_PORTB
 * 		or		GPIO_PORTC
 * 		or		GPIO_PORTD
 * 		or		GPIO_PORTE
 * 		or		GPIO_PORTH						*/

/* Description: Choose the I/O pin to which the pin is connected to
 * Options:		GPIO_PIN0
 * 		or		GPIO_PIN1
 * 		or		GPIO_PIN2
 * 		or		GPIO_PIN3
 * 		or		GPIO_PIN4
 * 		or		GPIO_PIN5
 * 		or		GPIO_PIN6
 * 		or		GPIO_PIN7
 * 		or		GPIO_PIN8
 * 		or		GPIO_PIN9
 * 		or		GPIO_PIN10
 * 		or		GPIO_PIN11
 * 		or		GPIO_PIN12
 * 		or		GPIO_PIN13
 * 		or		GPIO_PIN14
 * 		or		GPIO_PIN15						*/

#if (LCD_DATA_BITS_MODE == LCD_EIGHT_BITS_MODE)

LCD_strLCDPinConfig_t arrayofLCDPinConfig [11] = {
	/* Write the port and the pin that the D0 pin is connected to */
	[D0] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN10	},
	/* Write the port and the pin that the D1 pin is connected to */
	[D1] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN11	},
	/* Write the port and the pin that the D2 pin is connected to */
	[D2] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN12	},
	/* Write the port and the pin that the D3 pin is connected to */
	[D3] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN7	},
	/* Write the port and the pin that the D4 pin is connected to */
	[D4] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN0	},
	/* Write the port and the pin that the D5 pin is connected to */
	[D5] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN1	},
	/* Write the port and the pin that the D6 pin is connected to */
	[D6] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN2	},
	/* Write the port and the pin that the D7 pin is connected to */
	[D7] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN3	},
	/* Write the port and the pin that the Register Select (RS) pin is connected to */
	[RS] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN4	},
	/* Write the port and the pin that the Read/Write (R/w) pin is connected to */
	[RW] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN5	},
	/* Write the port and the pin that the Enable (E) pin is connected to */
	[E] = 	{ 	.LCD_port_number = GPIO_PORTA,
				.LCD_pin_number = GPIO_PIN6	}
};

#elif (LCD_DATA_BITS_MODE == LCD_FOUR_BITS_MODE)

LCD_strLCDPinConfig_t arrayofLCDPinConfig [7] = {
	/* Write the port and the pin that the D4 pin is connected to */
	[D4_4BITMODE] = 	{ 	.LCD_port_number = GPIO_PORTA,
							.LCD_pin_number = GPIO_PIN0	},
	/* Write the port and the pin that the D5 pin is connected to */
	[D5_4BITMODE] = 	{ 	.LCD_port_number = GPIO_PORTA,
							.LCD_pin_number = GPIO_PIN1	},
	/* Write the port and the pin that the D6 pin is connected to */
	[D6_4BITMODE] = 	{ 	.LCD_port_number = GPIO_PORTA,
							.LCD_pin_number = GPIO_PIN2	},
	/* Write the port and the pin that the D7 pin is connected to */
	[D7_4BITMODE] = 	{ 	.LCD_port_number = GPIO_PORTA,
							.LCD_pin_number = GPIO_PIN3	},
	/* Write the port and the pin that the Register Select (RS) pin is connected to */
	[RS_4BITMODE] = 	{ 	.LCD_port_number = GPIO_PORTA,
							.LCD_pin_number = GPIO_PIN4	},
	/* Write the port and the pin that the Read/Write (R/w) pin is connected to */
	[RW_4BITMODE] = 	{ 	.LCD_port_number = GPIO_PORTA,
							.LCD_pin_number = GPIO_PIN5	},
	/* Write the port and the pin that the Enable (E) pin is connected to */
	[E_4BITMODE] = 	{ 	.LCD_port_number = GPIO_PORTA,
						.LCD_pin_number = GPIO_PIN6	}
};

#endif /* #if (LCD_DATA_BITS_MODE == LCD_EIGHT_BITS_MODE) */
