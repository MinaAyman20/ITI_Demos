#ifndef HAL_SWITCH_HAL_INTERFACE_H_
#define HAL_SWITCH_HAL_INTERFACE_H_

#include "LIB/STD_TYPES.h"     // Include standard data types header
#include "CFG/HSWITCH/HSWITCH_config.h"  // Include switch configuration header

// Define switch status constants
#define SWITCH_STATUS_PRESSED   1
#define SWITCH_STATUS_RELEASED  0

// Define switch connection types
#define SWITCH_CONN_PULLUP      1
#define SWITCH_CONN_PULLDOWN    2

// Define configuration structure for a switch
typedef struct
{
    u32 Switch_Port;            // Port where the switch is connected
    u32 Switch_Pin;             // Pin number of the switch
    u32 Switch_Connection;      // Connection type of the switch (pull-up or pull-down)
    u32 Switch_InitStatus;      // Initial status of the switch
}Switch_CFG_t;

// Define error status enumeration for switch functions
typedef enum{
    HSWITCH_enuOK,                   // Operation successful
    HSWITCH_enuNOK,                  // Operation unsuccessful
    HSWITCH_enuNULLPOINTER,          // Null pointer error
    HSWITCH_enuInvalidConnection,    // Invalid switch connection type
    HSWITCH_enuInvalidSwitchNum,     // Invalid switch number
}HSWITCH_enuErrorStatus_t;

/*
 * Function: HSWITCH_vSwitchInit
 * ------------------------------
 * Initializes all the switches configured in the Switch_CFG_t array SWITCHES.
 * Configures each switch pin as input according to its configuration.
 * This function uses the MGPIO_enuSetPinConfig function to configure GPIO pins.
 * 
 * Parameters: None
 * 
 * Returns: None
 */
void HSWITCH_vSwitchInit(void);

/*
 * Function: HSWITCH_u32GetSwitchState
 * ------------------------------------
 * Gets the state of the specified switch by reading its GPIO pin value.
 * 
 * Parameters:
 *     Switch: The index of the switch in the SWITCHES array.
 * 
 * Returns:
 *     The state of the switch (0 for released, 1 for pressed).
 */
u32 HSWITCH_u32GetSwitchState(u32 Switch);

/*
 * Function: HSWITCH_enuGetSwitchState
 * ------------------------------------
 * Gets the state of the specified switch and stores it in the provided memory location.
 * 
 * Parameters:
 *     Copy_u8SwitchName: The index of the switch in the SWITCHES array.
 *     Add_u8State: Pointer to a variable where the switch state will be stored.
 * 
 * Returns:
 *     HSWITCH_enuErrorStatus_t value indicating the status of the operation.
 */

//HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchState(u8 Copy_u8SwitchName, u8* Add_u8State);


#endif







