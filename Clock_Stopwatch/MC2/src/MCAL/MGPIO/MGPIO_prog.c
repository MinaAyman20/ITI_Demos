/*
 * MGPIO_prog.c
 *
 *  Created on: Feb 13, 2024
 *      Author: Mina
 */

#include "MCAL/MGPIO/MGPIO_interface.h"

#define GPIO_MODE_MASK                0x00000003 
#define GPIO_MODE_SHIFTING_MASK       0x00000002

#define GPIO_OUTPUT_TYPE_MASK         0x00000001 

#define GPIO_SPEED_MASK               0x00000003 
#define GPIO_SPEED_SHIFTING_MASK      0x00000002

#define GPIO_PUPD_MASK                0x00000003 
#define GPIO_PUPD_SHIFTING_MASK       0x00000002

#define GPIO_IDR_MASK                 0x00000001

#define GPIO_SHIFTING_VALUE_ONE       0x00000001

#define AF_SHIFT_VALUE                0x04
#define AF_PINS_PER_PORT              0x08

#define GPIO_PORT_MAX                 5 
#define GPIO_PIN_MAX                  16 

#define GPIO_BSBR_RESET_SHFTING_MASK  0x00000010


#define GPIOA_BASE_ADDRESS           (u32)0x40020000
#define GPIOB_BASE_ADDRESS           (u32)0x40020400
#define GPIOC_BASE_ADDRESS           (u32)0x40020800
#define GPIOD_BASE_ADDRESS           (u32)0x40020C00
#define GPIOE_BASE_ADDRESS           (u32)0x40021000
#define GPIOH_BASE_ADDRESS           (u32)0x40021C00


typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOReg_t;

static GPIOReg_t* const GPIO_PORTS[] = {
    ( GPIOReg_t* const)(GPIOA_BASE_ADDRESS),
    ( GPIOReg_t* const)(GPIOB_BASE_ADDRESS),
    ( GPIOReg_t* const)(GPIOC_BASE_ADDRESS),
    ( GPIOReg_t* const)(GPIOD_BASE_ADDRESS),
    ( GPIOReg_t* const)(GPIOE_BASE_ADDRESS),
    ( GPIOReg_t* const)(GPIOH_BASE_ADDRESS)
};


MGPIO_enuErrorStatus_t MGPIO_enuSetPinConfig (MGPIO_PIN_config_t* Add_strPinConfg) 
{
	 MGPIO_enuErrorStatus_t Ret_enuRCC_ErrorStatus = MGPIO_enuOK;
	 u32  LOC_u32MODEValue = 0;
	 u32  LOC_u32OutputTypeValue =0;
	 u32  LOC_u32InputTypeValue =0;
	 u32  LOC_u32SpeedValue =0;
	 
	if(Add_strPinConfg->GPIOPort > GPIO_PORT_MAX )
	{
       Ret_enuRCC_ErrorStatus = MGPIO_enuPortError;
	}
	if(Add_strPinConfg->GPIOPin > GPIO_PIN_MAX )
	{
       Ret_enuRCC_ErrorStatus = MGPIO_enuPinError;
	}

	volatile GPIOReg_t *GPIO_PORT = GPIO_PORTS[Add_strPinConfg->GPIOPort] ;
     
	 LOC_u32MODEValue =  GPIO_PORT-> MODER ;
     LOC_u32MODEValue &= ~((GPIO_MODE_MASK) << (Add_strPinConfg->GPIOPin * GPIO_MODE_SHIFTING_MASK));
	 LOC_u32MODEValue |= (Add_strPinConfg->GPIOMode <<(Add_strPinConfg->GPIOPin * GPIO_MODE_SHIFTING_MASK));
     GPIO_PORT-> MODER = LOC_u32MODEValue;

	 if(Add_strPinConfg->GPIOMode == GPIO_OUTPUT || Add_strPinConfg->GPIOMode == GPIO_AF )
	 { 
		LOC_u32OutputTypeValue =  GPIO_PORT-> OTYPER ;
		LOC_u32OutputTypeValue &= ~ (GPIO_OUTPUT_TYPE_MASK << Add_strPinConfg->GPIOPin);
        LOC_u32OutputTypeValue |= ( Add_strPinConfg->GPIO_OUTPUTTYPE << Add_strPinConfg->GPIOPin);
        GPIO_PORT-> OTYPER =  LOC_u32OutputTypeValue;
        
		LOC_u32SpeedValue = GPIO_PORT-> OSPEEDR ;
		LOC_u32SpeedValue &= ~ ((GPIO_SPEED_MASK)<<(GPIO_SPEED_SHIFTING_MASK* Add_strPinConfg->GPIOPin));
        LOC_u32SpeedValue |=   (Add_strPinConfg->GPIOSpeed<<(GPIO_SPEED_SHIFTING_MASK* Add_strPinConfg->GPIOPin));
        GPIO_PORT-> OSPEEDR = LOC_u32SpeedValue;

		LOC_u32InputTypeValue = GPIO_PORT-> PUPDR;
		LOC_u32InputTypeValue &= ~((GPIO_PUPD_MASK)<<( GPIO_PUPD_SHIFTING_MASK* Add_strPinConfg->GPIOPin));
		LOC_u32InputTypeValue |= (Add_strPinConfg->GPIO_INPUTTYPE<<(GPIO_PUPD_SHIFTING_MASK * Add_strPinConfg->GPIOPin));
        GPIO_PORT-> PUPDR = LOC_u32InputTypeValue;
		
		if(Add_strPinConfg->GPIOMode == GPIO_AF)
		{
			u32 AF_PIN_OFFSET = 0;
            AF_PIN_OFFSET = ((Add_strPinConfg->GPIOPin) % (AF_PINS_PER_PORT)) * AF_SHIFT_VALUE;

			if(Add_strPinConfg->GPIOPin <= GPIO_PIN7)
			{
				 GPIO_PORT-> AFRL |= Add_strPinConfg-> GPIOAlternative << AF_PIN_OFFSET ;
			}
			else
			{
				 GPIO_PORT-> AFRH |= Add_strPinConfg-> GPIOAlternative << AF_PIN_OFFSET ;
			}
		}
	 }
	 else if (Add_strPinConfg->GPIOMode == GPIO_INPUT)
	 { 
		LOC_u32InputTypeValue = GPIO_PORT-> PUPDR;
		LOC_u32InputTypeValue &= ~((GPIO_PUPD_MASK)<<(GPIO_PUPD_SHIFTING_MASK * Add_strPinConfg->GPIOPin));
		LOC_u32InputTypeValue |= ((Add_strPinConfg->GPIO_INPUTTYPE)<<(GPIO_PUPD_SHIFTING_MASK * Add_strPinConfg->GPIOPin));
        GPIO_PORT-> PUPDR = LOC_u32InputTypeValue;
	 }
	 
	 else
	 {

	 }
       
	   return Ret_enuRCC_ErrorStatus ;

}


MGPIO_enuErrorStatus_t MGPIO_enuSetPinValue(u32 Copy_u32Port, u32 Copy_u32Pin, u32 Copy_u32Value)
{   
	MGPIO_enuErrorStatus_t Ret_enuGPIO_ErrorStatus = MGPIO_enuOK;
	if(Copy_u32Port > GPIO_PORT_MAX )
	{
       Ret_enuGPIO_ErrorStatus = MGPIO_enuPortError;
	}
	if( Copy_u32Pin > GPIO_PIN_MAX )
	{
       Ret_enuGPIO_ErrorStatus = MGPIO_enuPinError;
	}
	volatile GPIOReg_t *GPIO_PORT = GPIO_PORTS[Copy_u32Port] ;

	if (Copy_u32Value == GPIO_LOW) {

        GPIO_PORT->BSRR = (GPIO_SHIFTING_VALUE_ONE  << (Copy_u32Pin + GPIO_BSBR_RESET_SHFTING_MASK));

    } else if (Copy_u32Value == GPIO_HIGH) {

        GPIO_PORT->BSRR = (GPIO_SHIFTING_VALUE_ONE  << Copy_u32Pin);
    } else {
        Ret_enuGPIO_ErrorStatus = MGPIO_enuValueError;
    }

    return Ret_enuGPIO_ErrorStatus; 

}

MGPIO_enuErrorStatus_t MGPIO_getPinValue(u32 Copy_u32Port, u32 Copy_u32Pin, u32 *Copy_pu32Pin) 
{    
	MGPIO_enuErrorStatus_t Ret_enuGPIO_ErrorStatus = MGPIO_enuOK;
    if (Copy_u32Port > GPIO_PORT_MAX || Copy_u32Pin > GPIO_PIN_MAX || Copy_pu32Pin == NULL) {
        Ret_enuGPIO_ErrorStatus = MGPIO_enuNOK;
       
    }
    volatile GPIOReg_t *GPIO_PORT = GPIO_PORTS[Copy_u32Port];
    *Copy_pu32Pin = (GPIO_PORT->IDR >> Copy_u32Pin) & GPIO_IDR_MASK;

	return Ret_enuGPIO_ErrorStatus;
}


