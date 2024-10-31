#pragma once

#include <stdio.h>
#include "CFG/SYSTICK_Cfg.h"

#define STK_MODE_ONESHOT                0
#define STK_MODE_PERIODIC               1
#define SOURCE_AHB                      0x00000004
#define SOURCE_AHB_DIV_8                0xFFFFFFFB


typedef void (*systickcfg_t)(void);

typedef enum
{
    STK_ENUM_OK,
    STK_ENUM_NOK,
    STK_ENUM_INVALIDCONFIG,
    STK_ENUM_NULL,
    STK_ENUM_INVALID_TIME
}STK_ERROR_STATE;


STK_ERROR_STATE STK_Init(uint32_t SOURCE);
STK_ERROR_STATE STK_SetTimeMS(uint32_t Time_Value);                     
void STK_EnableInterrupt();
void STK_DisableInterrupt();
STK_ERROR_STATE STK_Start(uint32_t STK_MODE);
void STK_Stop();
STK_ERROR_STATE STK_SetCallback(systickcfg_t Callback);
