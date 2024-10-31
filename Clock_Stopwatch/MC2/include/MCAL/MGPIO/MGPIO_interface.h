/*
 * MGPIO_interface.h
 *
 *  Created on: Feb 13, 2024
 *      Author: Mina
 */

#ifndef MCAL_MGPIO_MGPIO_INTERFACE_H_
#define MCAL_MGPIO_MGPIO_INTERFACE_H_

#include "LIB/STD_TYPES.h"

// Definition of GPIO ports
#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3
#define GPIO_PORTE 4
#define GPIO_PORTH 5

// // Definition of GPIO pins
// #define GPIO_PIN0    0x00000000
// #define GPIO_PIN1    0x00000001
// #define GPIO_PIN2    0x00000002
// #define GPIO_PIN3    0x00000004
// #define GPIO_PIN4    0x00000008
// #define GPIO_PIN5    0x00000010
// #define GPIO_PIN6    0x00000020
// #define GPIO_PIN7    0x00000040
// #define GPIO_PIN8    0x00000080
// #define GPIO_PIN9    0x00000100
// #define GPIO_PIN10   0x00000200
// #define GPIO_PIN11   0x00000400
// #define GPIO_PIN12   0x00000800
// #define GPIO_PIN13   0x00001000
// #define GPIO_PIN14   0x00002000
// #define GPIO_PIN15   0x00004000


#define GPIO_AF_SYS                0
#define GPIO_AF_TIM_1_2            1
#define GPIO_AF_TIM_3_4_5          2
#define GPIO_AF_TIM_9_10_11        3
#define GPIO_AF_I2C                4
#define GPIO_AF_SPI_1              5
#define GPIO_AF_SPI_3              6
#define GPIO_AF_USART_1_2          7
#define GPIO_AF_USART_6            8
#define GPIO_AF_I2C_2              9

// Definition of GPIO pins
#define GPIO_PIN0    0
#define GPIO_PIN1    1
#define GPIO_PIN2    2
#define GPIO_PIN3    3
#define GPIO_PIN4    4
#define GPIO_PIN5    5
#define GPIO_PIN6    6
#define GPIO_PIN7    7
#define GPIO_PIN8    8
#define GPIO_PIN9    9
#define GPIO_PIN10   10
#define GPIO_PIN11   11
#define GPIO_PIN12   12
#define GPIO_PIN13   13
#define GPIO_PIN14   14
#define GPIO_PIN15   15

// Definition of GPIO pin modes
#define GPIO_INPUT    0x00
#define GPIO_OUTPUT   0x01
#define GPIO_AF       0x02
#define GPIO_Analog   0x03

// Definition of GPIO pin speeds
#define GPIO_LOW_SPEED    0x00  
#define GPIO_MED_SPEED    0x01  
#define GPIO_HIGH_SPEED   0x02  
#define GPIO_VHIGH_SPEED  0x03

// Definition of GPIO pin output types
#define GPIO_PUSHPULL  0
#define GPIO_OPENDRAIN 1

// Definition of GPIO pin pull-up/pull-down configurations
#define GPIO_NO_PULLUPPULLDOWN  0x00 
#define GPIO_PULLUP             0x01 
#define GPIO_PULLDOWN           0x02 

// Definition of GPIO pin output levels
#define GPIO_LOW  0
#define GPIO_HIGH 1 

// Enumeration for GPIO error status
typedef enum{
	MGPIO_enuOK,
	MGPIO_enuNOK,
	MGPIO_enuPortError,
	MGPIO_enuPinError,
	MGPIO_enuOutputTypeError,
	MGPIO_enuSpeedError,
	MGPIO_enuValueError,                
	MGPIO_enuWrongConfig
}MGPIO_enuErrorStatus_t;

// Structure for GPIO pin configuration
typedef struct 
{     
    u32  GPIOPort;           // GPIO port number
	u32  GPIOPin;            // GPIO pin number
    u32  GPIOMode;           // GPIO pin mode
	u32  GPIO_OUTPUTTYPE;    // GPIO pin output type
	u32  GPIO_INPUTTYPE;     // GPIO pin input type
	u32  GPIOSpeed;          // GPIO pin speed
	u32  GPIOAlternative;    

}MGPIO_PIN_config_t;

// Function prototypes

/*
 * Function: MGPIO_enuSetPinConfig
 * -------------------------------
 * Description:
 * Configures the specified GPIO pin based on the provided pin configuration structure. This function
 * sets the pin mode, output type, speed, and pull-up/pull-down configuration according to the
 * parameters provided in the MGPIO_PIN_config_t structure.
 *
 * Parameters:
 * - Add_strPinConfg: Pointer to the pin configuration structure containing GPIO port, pin, mode,
 *   output type, speed, and pull-up/pull-down settings.
 *
 * Returns:
 * - MGPIO_enuErrorStatus_t: Error status indicating the success or failure of the pin configuration.
 */
MGPIO_enuErrorStatus_t MGPIO_enuSetPinConfig (MGPIO_PIN_config_t* Add_strPinConfg);

/*
 * Function: MGPIO_enuSetPinValue
 * -------------------------------
 * Description:
 * Sets the value of the specified GPIO pin to the provided value (high or low).
 *
 * Parameters:
 * - Copy_u32Port: The GPIO port number.
 * - Copy_u32Pin: The GPIO pin number.
 * - Copy_u32Value: The value to set the pin (GPIO_HIGH or GPIO_LOW).
 *
 * Returns:
 * - MGPIO_enuErrorStatus_t: Error status indicating the success or failure of setting the pin value.
 */
MGPIO_enuErrorStatus_t MGPIO_enuSetPinValue(u32 Copy_u32Port, u32 Copy_u32Pin, u32 Copy_u32Value);

/*
 * Function: MGPIO_getPinValue
 * ----------------------------
 * Description:
 * Retrieves the value of the specified GPIO pin.
 *
 * Parameters:
 * - Copy_u32Port: The GPIO port number.
 * - Copy_u32Pin: The GPIO pin number.
 * - Copy_pu32Pin: Pointer to store the retrieved pin value.
 *
 * Returns:
 * - MGPIO_enuErrorStatus_t: Error status indicating the success or failure of retrieving the pin value.
 */
MGPIO_enuErrorStatus_t MGPIO_getPinValue(u32 Copy_u32Port, u32 Copy_u32Pin, u32 *Copy_pu32Pin);

#endif
