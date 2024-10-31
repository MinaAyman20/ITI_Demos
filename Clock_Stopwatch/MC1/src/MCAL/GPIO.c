#include "MCAL/GPIO.h"

#define GPIOA_BASE_ADDRESS                      0x40020000                     
#define GPIOB_BASE_ADDRESS                      0x40020400
#define GPIOC_BASE_ADDRESS                      0x40020800

#define GPIO_MODER_MSK                          0x00000003
#define GPIO_OTYPER_MSK                         0x00000001
#define GPIO_OSPEEDR_MSK                        0x00000003
#define GPIO_PUPDR_MSK                          0x00000003


#define PIN_MODER_OFFSET                        0x00000002
#define PIN_OTYPER_OFFSET                       0x00000001
#define PIN_OSPEEDR_OFFSET                      0x00000002
#define PIN_PUPDR_OFFSET                        0x00000002

#define BSRR_OFFSET                             16

#define READ_MSK                                1

#define BIT_OFFSET_AF                           8
#define AF_OFFSET                               4



typedef struct 
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
}GPIO_T;

static GPIO_T *GPIO_Ports[3] = 
{
    (GPIO_T *)GPIOA_BASE_ADDRESS,  
    (GPIO_T *)GPIOB_BASE_ADDRESS,  
    (GPIO_T *)GPIOC_BASE_ADDRESS   
};


GPIO_ERROR_STATE GPIO_InitPin(GPIO_CONFIG_T * Config)
{
    GPIO_ERROR_STATE Error_State = GPIO_ENUM_NOK;    
    uint32_t Temp = GPIO_Ports[Config->Port]->MODER;

    Temp &= ~(GPIO_MODER_MSK << (Config->Pin * PIN_MODER_OFFSET));
    Temp |= ((Config->Mode & GPIO_MODER_MSK) << (Config->Pin * PIN_MODER_OFFSET));
    GPIO_Ports[Config->Port]->MODER = Temp;

    Temp = GPIO_Ports[Config->Port]->OTYPER;
    Temp &= ~(GPIO_OTYPER_MSK << (Config->Pin * PIN_OTYPER_OFFSET));
    Temp |= (((Config->Mode >> PIN_MODER_OFFSET) & GPIO_OTYPER_MSK) << (Config->Pin * PIN_OTYPER_OFFSET));
    GPIO_Ports[Config->Port]->OTYPER = Temp;

    Temp = GPIO_Ports[Config->Port]->OSPEEDR;
    Temp &= ~(GPIO_OSPEEDR_MSK << (Config->Pin * PIN_OSPEEDR_OFFSET));
    Temp |= ((Config->Speed & GPIO_OSPEEDR_MSK) << (Config->Pin * PIN_OSPEEDR_OFFSET));
    GPIO_Ports[Config->Port]->OSPEEDR = Temp;

    Temp = GPIO_Ports[Config->Port]->PUPDR;
    Temp &= ~(GPIO_PUPDR_MSK << (Config->Pin * PIN_PUPDR_OFFSET));
    Temp |= (((Config->Mode >> (PIN_MODER_OFFSET + PIN_OTYPER_OFFSET)) & GPIO_PUPDR_MSK) << (Config->Pin * PIN_PUPDR_OFFSET));
    GPIO_Ports[Config->Port]->PUPDR = Temp;

    uint32_t offset_af = (Config->Pin % BIT_OFFSET_AF) * AF_OFFSET;

    if (Config->Pin <= GPIO_PIN_7)
    {
        GPIO_Ports[Config->Port]->AFRL |= (Config->Alternative << offset_af);
    }
    else
    {
        GPIO_Ports[Config->Port]->AFRH |= (Config->Alternative << offset_af);
    }


    Error_State = GPIO_ENUM_OK;
    return Error_State;
}

GPIO_ERROR_STATE GPIO_SetPinValue(uint32_t GPIO_PORT, uint32_t GPIO_PIN, uint32_t PIN_STATE)
{
    GPIO_ERROR_STATE Error_State = GPIO_ENUM_NOK;

    if (PIN_STATE == PIN_STATE_HIGH)
    {
        GPIO_Ports[GPIO_PORT]->BSRR |= (PIN_STATE_HIGH << GPIO_PIN);
        Error_State = GPIO_ENUM_OK;
    }

    else if (PIN_STATE == PIN_STATE_LOW)
    {
        GPIO_Ports[GPIO_PORT]->BSRR |= (PIN_STATE_HIGH << (GPIO_PIN + BSRR_OFFSET));
        Error_State = GPIO_ENUM_OK;
    }

    else
    {
        Error_State = GPIO_ENUM_INVALID_CONFIG;
    }
    return Error_State;
}

GPIO_ERROR_STATE GPIO_GetPinValue(uint32_t GPIO_PORT, uint32_t GPIO_PIN, uint8_t * PinValue)
{
    GPIO_ERROR_STATE Error_State = GPIO_ENUM_NOK;
    if (GPIO_PORT > GPIO_PORT_C || GPIO_PIN > GPIO_PIN_15)
    {
        Error_State = GPIO_ENUM_INVALID_CONFIG;
    }
    else if (GPIO_PORT == GPIO_PORT_C && GPIO_PIN < GPIO_PIN_13)
    {
       Error_State = GPIO_ENUM_INVALID_CONFIG; 
    }
    else
    {
        *PinValue = (GPIO_Ports[GPIO_PORT]->IDR >> GPIO_PIN) & READ_MSK;
    }
    return Error_State;
}
