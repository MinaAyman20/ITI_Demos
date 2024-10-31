#include "MCAL/SYSTICK.h"

#define SYSTICK_BASE_ADDRESS       0xE000E010 
#define STK_SOURCE_BIT             0x00000004   
#define STK_TICKINT_BIT            0x00000002 
#define STK_ENABLE_BIT             0x00000001 
#define AHB_PRESCALAR_VALUE        8
#define MS_DIVISION_FACTOR         1000
#define EXTRA_TICK                 1
#define MAX_TIMER_VALUE            0x00FFFFFF

typedef struct 
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
}SYSTICK_T;

uint8_t Loc_STK_Mode = STK_MODE_ONESHOT;
uint32_t Loc_STK_Freq = 0;
static systickcfg_t Systick_Loc_Callback = 0;
static SYSTICK_T * const STK = (SYSTICK_T*)SYSTICK_BASE_ADDRESS;


STK_ERROR_STATE STK_Init(uint32_t SOURCE)
{
    STK_ERROR_STATE ERROR_STATE = STK_ENUM_NOK;
    if ((SOURCE != SOURCE_AHB) && (SOURCE != SOURCE_AHB_DIV_8))
    {
        ERROR_STATE = STK_ENUM_INVALIDCONFIG;
    }
    else
    {
        STK->VAL = 0;
        if (SOURCE == SOURCE_AHB)
        {
            STK->CTRL |= SOURCE;
            Loc_STK_Freq = SOURCE_AHB;
        }
        else
        {
            STK->CTRL &= SOURCE;
            Loc_STK_Freq = SOURCE_AHB_DIV_8;
        }
        ERROR_STATE = STK_ENUM_OK;
    }
    return ERROR_STATE;
}



STK_ERROR_STATE STK_SetTimeMS(uint32_t Time_Value)
{
    STK_ERROR_STATE ERROR_STATE = STK_ENUM_NOK;
    if (Loc_STK_Freq == SOURCE_AHB_DIV_8)
    {
        Time_Value = (CLOCK_FREQUENCY_AHB / AHB_PRESCALAR_VALUE) * Time_Value;
    }
    else
    {
        Time_Value = CLOCK_FREQUENCY_AHB * Time_Value;
    }
    Time_Value = (Time_Value / MS_DIVISION_FACTOR) - EXTRA_TICK;
    if (Time_Value > MAX_TIMER_VALUE)
    {
        ERROR_STATE = STK_ENUM_INVALID_TIME;
    }
    else
    {
        STK->LOAD = Time_Value;
        ERROR_STATE = STK_ENUM_OK;
    }
    return ERROR_STATE;
}



void STK_EnableInterrupt()
{
    STK->CTRL |= STK_TICKINT_BIT;
}



void STK_DisableInterrupt()
{
    STK->CTRL &= ~STK_TICKINT_BIT; 
}



STK_ERROR_STATE STK_Start(uint32_t STK_MODE)
{
    STK_ERROR_STATE ERROR_STATE = STK_ENUM_NOK;
    if ((STK_MODE != STK_MODE_ONESHOT) && (STK_MODE != STK_MODE_PERIODIC))
    {
        ERROR_STATE = STK_ENUM_INVALIDCONFIG;
    }
    else
    {
        Loc_STK_Mode = STK_MODE;
        STK->CTRL |= STK_ENABLE_BIT;
        ERROR_STATE = STK_ENUM_OK;
    }
    return ERROR_STATE;
}



void STK_Stop()
{
    STK->CTRL &= ~STK_ENABLE_BIT;
}


STK_ERROR_STATE STK_SetCallback(systickcfg_t Callback)
{
    STK_ERROR_STATE ERROR_STATE = STK_ENUM_NOK;
    if (!Callback)
    {
        ERROR_STATE = STK_ENUM_NULL;
    }
    else
    {
        Systick_Loc_Callback = Callback;
        ERROR_STATE = STK_ENUM_OK;
    }
    return ERROR_STATE;   
}



void SysTick_Handler(void)
{
    if (Systick_Loc_Callback)
	{
        if (Loc_STK_Mode == STK_MODE_ONESHOT)
        {
            STK->CTRL &= ~STK_ENABLE_BIT;   
        }
        else
        {

        }
		Systick_Loc_Callback();
	}
	else
	{
	}
}