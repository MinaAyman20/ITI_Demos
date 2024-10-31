#ifndef NVIC_H
#define NVIC_H
/**************************************************************Includes:******************************************************************/
#include <stdint.h>
#include <ErrorStatus.h>
#include <STM32f401CC_peripherals_interrupt.h>
/**************************************************************Defines:*******************************************************************/
/*defines Group Bits*/
#define GroupBits_0         0x05FA0300
#define GroupBits_1         0x05FA0400
#define GroupBits_2         0x05FA0500
#define GroupBits_3         0x05FA0600
#define GroupBits_4         0x05FA0700
/**************************************************************Typedefs:******************************************************************/


/**************************************************************APIs:**********************************************************************/
/**
*@brief  : function to enable any IRQ in the system.
*@param  : name of IRQ 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_EnableIRQ(uint8_t Copy_IRQ);

/**
*@brief  : function to disable any IRQ in the system.
*@param  : name of IRQ 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_DisableIRQ(uint8_t Copy_IRQ);

/**
*@brief  : function to set pending.
*@param  : name of IRQ 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_SetPending(uint8_t Copy_IRQ);

/**
*@brief  : function to clear pending.
*@param  : name of IRQ 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_ClearPending(uint8_t Copy_IRQ);

/**
*@brief  : Reads the pending status of interrupt or exception.
*@param  : name of IRQ, pointer to return pending status.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_GetPending(uint8_t Copy_IRQ, uint8_t* Pending_status);

/**
*@brief  : Reads the active status of interrupt or exception.
*@param  : name of IRQ, pointer to return active status.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_GetActive(uint8_t Copy_IRQ, uint8_t* Active_status);

/**
 * @brief : function to trigger software interrupt 
 * @param : name of IRQ
 * @return : Error state -return 0 means that function done successfully-
 */
ErrorStatus_t NVIC_TriggerIRQ(uint32_t copy_IRQ);

/**
 * @brief : function to set Number of Group priority bits.
 * @param : Number of group priority bits.
 * @return : Error state -return 0 means that function done successfully-
 */
ErrorStatus_t NVIC_SetGroupPriorityBits(uint32_t Copy_GroupBits);

/**
 * @brief : Function to set the priority of a specific interrupt.
 * @param : name of IRQ.
 * @param : Preemption priority level [0:15]
 * @param : Group priority level [0:15]
 * @return : Error state -return 0 means that function done successfully-
 * @note : before this function you should call  NVIC_SetGroupPriorityBits API to set group bits.
 */
ErrorStatus_t NVIC_SetIRQPriority(uint8_t copy_IRQ, uint8_t Copy_PreemptionPriority, uint8_t copy_GroupPriority);

#endif