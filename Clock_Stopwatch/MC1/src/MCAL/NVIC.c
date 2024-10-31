/**************************************************************Includes:******************************************************************/
#include <MCAL/NVIC.h>
/**************************************************************Defines:*******************************************************************/
#define NVIC_BASE_ADDRESS               0xE000E100
#define IMPLEMENTED_BITS                4
#define Group_Bits_MASK                 0x00000700
/**************************************************************NVIC Registers Struct:*****************************************************/
typedef struct 
{
    volatile uint32_t ISER[8];          /*INTERRUPT SET ENABLE REGISTER*/
    uint32_t RESERVED0[24];             /*FROM 0XE000E11F TO 0XE000E180*/
    volatile uint32_t ICER[8];          /*INTERRUPT CLEAR ENABLE REGISTER*/
    uint32_t RESERVED1[24];             /*FROM 0XE000E19F TO 0XE000E200*/
    volatile uint32_t ISPR[8];          /*INTERRUPT SET PENDING REGISTER*/
    uint32_t RESERVED2[24];             /*FROM 0XE000E21F TO 0XE000E280*/
    volatile uint32_t ICPR[8];          /*INTERRUPT CLEAR PENDING REGISTER*/
    uint32_t RESERVED3[24];             /*FROM 0XE000E29F TO 0XE000E300*/
    volatile uint32_t IABR[8];          /*INTERRUPT ACTIVE BIT REGISTER*/
    uint32_t RESERVED4[56];             /*FROM 0XE000E31F TO 0XE000E400*/
    volatile uint32_t IPR[60];          /*INTERRUPT PRIORITY REGISTER*/
    uint32_t RESERVED5[644];            /*FROM 0XE000E4EF TO 0XE000EF00*/
    volatile uint32_t STIR;             /*SOFTWARE TRIGGER INTERRUPT REGISTER*/
}NVIC_Type;

NVIC_Type *const NVIC = (NVIC_Type*) NVIC_BASE_ADDRESS;

/**************************************************************SCB Registers:*************************************************************/
#define AIRCR *((volatile uint32_t*) 0xE000ED0C)

/**************************************************************Global Variables:**********************************************************/
static uint32_t Global_Group_Bits = 0; 
/**************************************************************static functions:**********************************************************/
static uint8_t MaximumNumberOfPriority(uint8_t Number)
{
    uint8_t Result =1;
    for (uint8_t itr = 0; itr < Number; itr++)
    {
        Result = Result * 2;
    }
    return Result;
}


/**************************************************************APIs:**********************************************************************/
/**
*@brief  : function to enable any IRQ in the system.
*@param  : name of peripheral 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_EnableIRQ(uint8_t Copy_IRQ)
{
    ErrorStatus_t Loc_Return = Ok;
    if((Copy_IRQ > SPI4_IRQ)||(Copy_IRQ < WWDG_IRQ))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        NVIC->ISER[Copy_IRQ/32] |= 1 << (Copy_IRQ%32);
        Loc_Return = Ok;
    }
    return Loc_Return;
}

/**
*@brief  : function to disable any IRQ in the system.
*@param  : name of peripheral 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_DisableIRQ(uint8_t Copy_IRQ)
{
    ErrorStatus_t Loc_Return = Ok;
    if((Copy_IRQ > SPI4_IRQ)||(Copy_IRQ < WWDG_IRQ))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        NVIC->ICER[Copy_IRQ/32] |= 1 << (Copy_IRQ%32);
        Loc_Return = Ok;
    }
    return Loc_Return;
}


/**
*@brief  : function to set pending.
*@param  : name of peripheral 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_SetPending(uint8_t Copy_IRQ)
{
    ErrorStatus_t Loc_Return = Ok;
    if((Copy_IRQ > SPI4_IRQ)||(Copy_IRQ < WWDG_IRQ))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        NVIC->ISPR[Copy_IRQ/32] |= 1 << (Copy_IRQ%32);
        Loc_Return = Ok;
    }
    return Loc_Return;
}

/**
*@brief  : function to clear pending.
*@param  : name of peripheral 
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_ClearPending(uint8_t Copy_IRQ)
{
    ErrorStatus_t Loc_Return = Ok;
    if((Copy_IRQ > SPI4_IRQ)||(Copy_IRQ < WWDG_IRQ))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        NVIC->ISPR[Copy_IRQ/32] |= 1 << (Copy_IRQ%32);
        Loc_Return = Ok;
    }
    return Loc_Return;
}


/**
*@brief  : Reads the pending status of interrupt or exception.
*@param  : name of peripheral, pointer to return pending status.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_GetPending(uint8_t Copy_IRQ, uint8_t* Pending_status)
{
    ErrorStatus_t Loc_Return = Ok;
    if ((Copy_IRQ > SPI4_IRQ)||(Copy_IRQ < WWDG_IRQ))
    {
        Loc_Return = ArgumentError;
    }
    else if (Pending_status == NULL)
    {
        Loc_Return = NullPointerError;
    }
    else
    {
        Loc_Return = Ok;
        *Pending_status = NVIC->ISPR[Copy_IRQ/32] & (1 << (Copy_IRQ % 32));
    }
    return Loc_Return;
}

/**
*@brief  : Reads the active status of interrupt or exception.
*@param  : name of peripheral, pointer to return active status.
*@return : Error state -return 0 means that function done successfully-
*/
ErrorStatus_t NVIC_GetActive(uint8_t Copy_IRQ, uint8_t* Active_status)
{
    ErrorStatus_t LocReturn = Ok;
    if(Active_status == NULL)
    {
        LocReturn = NullPointerError;
    }
    else if ((Copy_IRQ > SPI4_IRQ)||(Copy_IRQ < WWDG_IRQ))
    {
        LocReturn = ArgumentError;
    }
    else 
    {
        LocReturn = Ok;
        *Active_status = NVIC->IABR[Copy_IRQ/32] & (1 << (Copy_IRQ % 32));
    }
    return LocReturn;
}

/**
 * @brief : function to trigger software interrupt 
 * @param : name of IRQ
 * @return : Error state -return 0 means that function done successfully-
 */
ErrorStatus_t NVIC_TriggerIRQ(uint32_t copy_IRQ)
{
    ErrorStatus_t Loc_Return = Ok;
    if((copy_IRQ > SPI4_IRQ)||(copy_IRQ < WWDG_IRQ))
    {
        Loc_Return = ArgumentError;
    }
    else
    {
        Loc_Return = Ok;
        NVIC->STIR = copy_IRQ;
    }
    return Loc_Return;
}

/**
 * @brief : function to set Number of Group priority bits.
 * @param : Number of group priority bits.
 * @return : Error state -return 0 means that function done successfully-
 */
ErrorStatus_t NVIC_SetGroupPriorityBits(uint32_t Copy_GroupBits)
{
    ErrorStatus_t Loc_Return = Ok;
    if(Copy_GroupBits != GroupBits_0
        && Copy_GroupBits != GroupBits_1
        && Copy_GroupBits != GroupBits_2
        && Copy_GroupBits != GroupBits_3
        && Copy_GroupBits != GroupBits_4)
    {
        Loc_Return = ArgumentError;
    }
    else 
    {
        
        Global_Group_Bits = ((Copy_GroupBits & 0x00000700) >> 8) - 3; //3 because this is only 4 bits implemented.
        AIRCR = Copy_GroupBits;
    }
    return Loc_Return;
}


/**
 * @brief : Function to set the priority of a specific interrupt.
 * @param : name of IRQ.
 * @param : Preemption priority level [0:15]
 * @param : Group priority level [0:15]
 * @return : Error state -return 0 means that function done successfully-
 */
ErrorStatus_t NVIC_SetIRQPriority(uint8_t copy_IRQ, uint8_t Copy_PreemptionPriority, uint8_t copy_GroupPriority)
{
    ErrorStatus_t loc_return = Ok;
    if((copy_IRQ > SPI4_IRQ)||(copy_IRQ < WWDG_IRQ))
    {
        loc_return = ArgumentError;
    }
    else if (copy_GroupPriority > (MaximumNumberOfPriority(Global_Group_Bits)))
    {
        loc_return = ArgumentError;
    }
    else if (Copy_PreemptionPriority > (MaximumNumberOfPriority(IMPLEMENTED_BITS-Global_Group_Bits))) 
    {
        loc_return = ArgumentError;
    }
    else
    {
        loc_return = Ok;
        uint32_t Loc_tempReg = NVIC->IPR[copy_IRQ/4];
        Loc_tempReg = Loc_tempReg & ( 0x00 << ((copy_IRQ % 4) * 8));               /* 8 is the number of priority bits in IPR register*/ 
        Loc_tempReg = Loc_tempReg | ((copy_GroupPriority) << (((copy_IRQ % 4) * 8) + IMPLEMENTED_BITS));  
        Loc_tempReg = Loc_tempReg | ((Copy_PreemptionPriority) << ((((copy_IRQ % 4) * 8) + IMPLEMENTED_BITS) + Global_Group_Bits));   
        NVIC->IPR[copy_IRQ/4] = Loc_tempReg;
    }
    return loc_return;
}