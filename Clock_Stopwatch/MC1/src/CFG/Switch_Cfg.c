#include "HAL/Switch.h"

const Switchcfg_t Switches[_Switch_num]=
{
    [UP_Switch]=
    {
        .port=GPIO_PORT_B,
        .pin=GPIO_PIN_5,
        .connection= Switch_conn_pullup,
    },
    [DOWN_Switch]=
    {
        .port=GPIO_PORT_B,
        .pin=GPIO_PIN_6,
        .connection= Switch_conn_pullup,
    },
    [LEFT_Switch]=
    {
        .port=GPIO_PORT_B,
        .pin=GPIO_PIN_7,
        .connection= Switch_conn_pullup,
    },
    [RIGHT_Switch]=
    {
        .port=GPIO_PORT_B,
        .pin=GPIO_PIN_8,
        .connection= Switch_conn_pullup,
    },
    [OK_Switch]=
    {
        .port=GPIO_PORT_B,
        .pin=GPIO_PIN_9,
        .connection= Switch_conn_pullup,
    },
    [MODE_Switch]=
    {
        .port=GPIO_PORT_B,
        .pin=GPIO_PIN_10,
        .connection= Switch_conn_pullup,
    },
    [EDIT_Switch]=
    {
        .port=GPIO_PORT_B,
        .pin=GPIO_PIN_12,
        .connection= Switch_conn_pullup,
    }
};