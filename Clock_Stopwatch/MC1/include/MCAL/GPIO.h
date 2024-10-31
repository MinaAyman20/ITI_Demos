#pragma once
#include <stdint.h>

/*Macros for the GPIO pins*/
#define GPIO_PIN_0  0x00000000
#define GPIO_PIN_1  0x00000001
#define GPIO_PIN_2  0x00000002
#define GPIO_PIN_3  0x00000003
#define GPIO_PIN_4  0x00000004
#define GPIO_PIN_5  0x00000005
#define GPIO_PIN_6  0x00000006
#define GPIO_PIN_7  0x00000007
#define GPIO_PIN_8  0x00000008
#define GPIO_PIN_9  0x00000009
#define GPIO_PIN_10 0x0000000A
#define GPIO_PIN_11 0x0000000B
#define GPIO_PIN_12 0x0000000C
#define GPIO_PIN_13 0x0000000D
#define GPIO_PIN_14 0x0000000E
#define GPIO_PIN_15 0x0000000F

/*Macros for the GPIO ports*/
#define GPIO_PORT_A  0x00000000
#define GPIO_PORT_B  0x00000001
#define GPIO_PORT_C  0x00000002

/*Macros for the GPIO pin modes*/
#define GPIO_MODE_IN_FL 0x00000000
#define GPIO_MODE_IN_PU 0x00000008
#define GPIO_MODE_IN_PD 0x00000010

#define GPIO_MODE_OP_PP    0x00000001
#define GPIO_MODE_OP_PP_PU 0x00000009
#define GPIO_MODE_OP_PP_PD 0x00000011
#define GPIO_MODE_OP_OD    0x00000005
#define GPIO_MODE_OP_OD_PU 0x0000000D
#define GPIO_MODE_OP_OD_PD 0x00000015

#define GPIO_MODE_AF_PP    0x00000002
#define GPIO_MODE_AF_PP_PU 0x0000000A
#define GPIO_MODE_AF_PP_PD 0x00000012
#define GPIO_MODE_AF_OD    0x00000006
#define GPIO_MODE_AF_OD_PU 0x0000000E
#define GPIO_MODE_AF_OD_PD 0x00000016

#define GPIO_MODE_AN       0x00000003

/*Macrod for Selecting which alternative function */
#define GPIO_ALTERNATIVE_SYSTEM		0x00
#define GPIO_ALTERNATIVE_TIM1		0x01
#define GPIO_ALTERNATIVE_TIM3		0x02
#define GPIO_ALTERNATIVE_TIM9		0x03
#define GPIO_ALTERNATIVE_I2C		0x04
#define GPIO_ALTERNATIVE_SPI		0x05
#define GPIO_ALTERNATIVE_SPI3		0x06
#define GPIO_ALTERNATIVE_USART1_2	0x07
#define GPIO_ALTERNATIVE_USART6		0x08


/*Macros for the GPIO pin speeds*/
#define GPIO_SPEED_LOW     0x00000000
#define GPIO_SPEED_MED     0x00000001
#define GPIO_SPEED_HIGH    0x00000002
#define GPIO_SPEED_VHIGH   0x00000003

#define PIN_STATE_HIGH  1
#define PIN_STATE_LOW   0  

typedef struct
{
    uint32_t Port;
    uint32_t Pin;
    uint32_t Speed;
    uint32_t Mode;
    uint32_t Alternative;
}GPIO_CONFIG_T;

typedef enum
{
    GPIO_ENUM_OK,
    GPIO_ENUM_NOK,
    GPIO_ENUM_INVALID_CONFIG
}GPIO_ERROR_STATE;

GPIO_ERROR_STATE GPIO_InitPin(GPIO_CONFIG_T * Config);
GPIO_ERROR_STATE GPIO_SetPinValue(uint32_t GPIO_PORT, uint32_t GPIO_PIN, uint32_t PIN_STATE);
GPIO_ERROR_STATE GPIO_GetPinValue(uint32_t GPIO_PORT, uint32_t GPIO_PIN, uint8_t * PinValue);          

