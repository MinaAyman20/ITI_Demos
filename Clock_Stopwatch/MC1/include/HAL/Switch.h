#pragma once

#include "CFG/Switch_Cfg.h"
#include "MCAL/GPIO.h"

#define Switch_conn_pullup         1
#define Switch_conn_pushdown       0
#define Switch_state_on            1
#define Switch_state_off           0


typedef struct {
    uint32_t port;
    uint32_t pin;
    uint8_t connection;
}Switchcfg_t;

typedef enum{
    SWITCH_ENUM_OK,
    SWITCH_ENUM_NOK,
    SWITCH_ENUM_INVALIDCONFIG,
    SWITCH_ENUM_NULLPTR
}SWITCH_ERROR_STATE;


SWITCH_ERROR_STATE Switch_getstatus(uint32_t Switch, uint8_t * Switch_state);
SWITCH_ERROR_STATE Switch_init(void);
