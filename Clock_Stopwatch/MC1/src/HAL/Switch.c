#include "HAL/Switch.h"
#include "MCAL/GPIO.h"

#define NULL ((void*)0)


extern const Switchcfg_t Switches[_Switch_num];
uint8_t Switch_State_List[_Switch_num];

SWITCH_ERROR_STATE Switch_init(void)
{
    SWITCH_ERROR_STATE ERROR_STATE = SWITCH_ENUM_NOK;
    GPIO_CONFIG_T Switch;
    Switch.Speed = GPIO_SPEED_HIGH;
    for(uint8_t idx = 0; idx < _Switch_num; idx++)
    {
        if (Switches[idx].connection == Switch_conn_pullup)
        {
            Switch.Mode = GPIO_MODE_IN_PU;
            Switch.Pin = Switches[idx].pin;
            Switch.Port = Switches[idx].port;
            GPIO_InitPin(&Switch);
            ERROR_STATE = SWITCH_ENUM_OK;
        }
        else if (Switches[idx].connection == Switch_conn_pushdown)
        {
            Switch.Mode = GPIO_MODE_IN_PD;
            Switch.Pin = Switches[idx].pin;
            Switch.Port = Switches[idx].port;
            GPIO_InitPin(&Switch);
            ERROR_STATE = SWITCH_ENUM_OK;
        }
        else
        {
            ERROR_STATE = SWITCH_ENUM_INVALIDCONFIG;
        }
    }
    return ERROR_STATE;
}


SWITCH_ERROR_STATE Switch_getstatus(uint32_t Switch, uint8_t * Switch_state)
{
    SWITCH_ERROR_STATE ERROR_STATE = SWITCH_ENUM_NOK;
    if (Switch_state == NULL)
    {
        ERROR_STATE = SWITCH_ENUM_NULLPTR;
    }
    else
        {
        if (Switch >= _Switch_num)
        {
            ERROR_STATE = SWITCH_ENUM_INVALIDCONFIG;
        }
        else
        {
            GPIO_GetPinValue(Switches[Switch].port, Switches[Switch].pin, Switch_state);
            *Switch_state = Switch_State_List[Switch] ^ Switches[Switch].connection;
            ERROR_STATE = SWITCH_ENUM_OK;
        }
    }
    return ERROR_STATE;
}


void SW_Runnable(void)
{
	uint8_t Iterator = 0;
	uint8_t SW_CurrentState;
	static uint8_t Prev_state[_Switch_num] = {0};
	static uint8_t counts[_Switch_num] = {0};
	for(Iterator = 0 ; Iterator < _Switch_num ; Iterator++)
	{
		GPIO_GetPinValue(Switches[Iterator].port, Switches[Iterator].pin, &SW_CurrentState);
		if(SW_CurrentState == Prev_state[Iterator])
		{
			counts[Iterator]++;
		}
		else
		{
			counts[Iterator] = 0;
		}
		if(counts[Iterator] == 5) 
		{
			Switch_State_List[Iterator] = SW_CurrentState;
			counts[Iterator] = 0;
		}
		Prev_state[Iterator] = SW_CurrentState;
	}

}