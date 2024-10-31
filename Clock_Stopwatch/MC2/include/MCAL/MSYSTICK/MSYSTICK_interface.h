#ifndef D__PIO_ARM_WS_MCAL_MSYSTICK_DRIVER_INC_MCAL_MSYSTICK_MSYSTICK_INTERFACE_H_
#define D__PIO_ARM_WS_MCAL_MSYSTICK_DRIVER_INC_MCAL_MSYSTICK_MSYSTICK_INTERFACE_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LIB/STD_TYPES.h" 
#include "CFG/MSYSTICK/MSYSTICK_config.h" 

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define SYSTICK_INTERRUPT_ON             0x00000002 // Define value for enabling SysTick interrupt
#define SYSTICK_INTERRUPT_OFF            0x00000000 // Define value for disabling SysTick interrupt

#define SYSTICK_CLK_SRC_AHB              0x00000004 // Define value for AHB clock source
#define SYSTICK_CLK_SRC_AHB_DIV_BY_8     0x00000000 // Define value for AHB/8 clock source

#define SYSTICK_SINGLETIME               0          // Define value for single-time mode
#define SYSTICK_PERIODIC                 1          // Define value for periodic mode

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef void (*SYSTICK_CBF_t)(void);  // Define a function pointer type for SysTick callback function

typedef enum{
    MSYSTICK_enuOK                 , // Enumeration for operation success
    MSYSTICK_enuNOK                , // Enumeration for operation failure
    MSYSTICK_enuNULLPOINTER        , // Enumeration for NULL pointer error
    MSYSTICK_enuWRONG_TIMER_TYPE   , // Enumeration for wrong timer type error
}MSYSTICK_enuErrorStatus;            // Enumeration for error status

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

/**
 * @brief Initialize the SysTick timer.
 */
void MSYSTICK_vidInit(void);

/**
 * @brief Set the time in milliseconds for SysTick timer.
 * 
 * @param Copy_u32MS_TIME: Time in milliseconds
 * @return MSYSTICK_enuErrorStatus: Status of the operation (OK or NOK)
 */
MSYSTICK_enuErrorStatus MSYSTICK_enuSetTimeMS(u32 Copy_u32MS_TIME);

/**
 * @brief Start the SysTick timer.
 * 
 * @param Copy_u8TimerType: Timer type (Single-time or Periodic)
 * @return MSYSTICK_enuErrorStatus: Status of the operation (OK or NOK)
 */
MSYSTICK_enuErrorStatus MSYSTICK_enuStart(u8 Copy_u8TimerType);

/**
 * @brief Set the callback function for SysTick interrupt.
 * 
 * @param Copy_pfvCBFunc: Pointer to the callback function
 * @return MSYSTICK_enuErrorStatus: Status of the operation (OK or NOK)
 */
MSYSTICK_enuErrorStatus MSYSTICK_enuSetCallback(void (*Copy_pfvCBFunc)(void));

/**
 * @brief Stop the SysTick timer.
 */
void MSYSTICK_enuStop(void);

/**
 * @brief Get the elapsed time of the SysTick timer.
 * 
 * @return u32: Elapsed time in milliseconds
 */
u32  MSYSTICK_u32GetElapsedTime(void);

/**
 * @brief Get the remaining time of the SysTick timer.
 * 
 * @return u32: Remaining time in milliseconds
 */
u32  MSYSTICK_u32GetRemainingTime(void);










#endif 