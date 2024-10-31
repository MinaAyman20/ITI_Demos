#include "MCAL/MGPIO/MGPIO_interface.h"
#include "HAL/HSWITCH/HSWITCH_interface.h"
#include "CFG/HSWITCH/HSWITCH_config.h"

/*
 * Array: SWITCHES
 * ---------------
 * Description:
 * This array contains the configuration settings for each switch used in the system.
 * It is a constant array of Switch_CFG_t structures.
 * Each element of the array corresponds to a specific switch enumerated in Switches_t.
 * The configuration includes the GPIO port, pin, connection type, and optionally the initial status of each switch.
 * The array size is determined by the total number of switches (_Switch_Num).
 * Unused elements are left uninitialized.
 */
const Switch_CFG_t SWITCHES [_Switch_Num]=
{
[UP_START_BUTTON]=
{
    .Switch_Port=GPIO_PORTB,
    .Switch_Pin=GPIO_PIN0,
    .Switch_Connection=SWITCH_CONN_PULLUP,
    //.Switch_InitStatus=SWITCH_STATUS_RELEASED,
},
[DOWN_STOP_BUTTON]=
{
    .Switch_Port=GPIO_PORTB,
    .Switch_Pin=GPIO_PIN1,
    .Switch_Connection=SWITCH_CONN_PULLUP,
    //.Switch_InitStatus=SWITCH_STATUS_RELEASED,
},
[LEFT_RESET_BUTTON]=
{
    .Switch_Port=GPIO_PORTB,
    .Switch_Pin=GPIO_PIN10,
    .Switch_Connection=SWITCH_CONN_PULLUP,
    //.Switch_InitStatus=SWITCH_STATUS_RELEASED,
},
[RIGHT_BUTTON]=
{
    .Switch_Port=GPIO_PORTA,
    .Switch_Pin=GPIO_PIN8,
    .Switch_Connection=SWITCH_CONN_PULLUP,
    //.Switch_InitStatus=SWITCH_STATUS_RELEASED,
},
[OK_BUTTON]=
{
    .Switch_Port=GPIO_PORTB,
    .Switch_Pin=GPIO_PIN8,
    .Switch_Connection=SWITCH_CONN_PULLUP,
    //.Switch_InitStatus=SWITCH_STATUS_RELEASED,
},
[MODE_BUTTON]=
{
    .Switch_Port=GPIO_PORTB,
    .Switch_Pin=GPIO_PIN7,
    .Switch_Connection=SWITCH_CONN_PULLUP,
    //.Switch_InitStatus=SWITCH_STATUS_RELEASED,
},
[EDIT_BUTTON]=
{
    .Switch_Port=GPIO_PORTB,
    .Switch_Pin=GPIO_PIN5,
    .Switch_Connection=SWITCH_CONN_PULLUP,
    //.Switch_InitStatus=SWITCH_STATUS_RELEASED,
}
};