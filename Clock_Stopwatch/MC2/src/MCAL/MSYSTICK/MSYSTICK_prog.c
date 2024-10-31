/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LIB/STD_TYPES.h"
#include "MCAL/MSYSTICK/MSYSTICK_interface.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define SYSTICK_BASE_ADDRESS    0xE000E010 // Base address of the SysTick timer register

#define SYSTICK_ENABLE 0 // Bit position for enabling the SysTick timer
#define TICK_INT       1 // Bit position for enabling SysTick interrupt
#define CLK_SOURCE     2 // Bit position for selecting SysTick clock source
#define COUNT_FLAG    16 // Bit position for reading the COUNTFLAG status bit

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct 
{
    volatile u32 STK_CTRL;  // SysTick Control and Status Register
    volatile u32 STK_LOAD;  // SysTick Reload Value Register
    volatile u32 STK_VAL;   // SysTick Current Value Register
    volatile u32 STK_CALIB; // SysTick Calibration Value Register
}SYSTICK_t;                 // Structure representing SysTick registers

#define SYSTICK ((volatile SYSTICK_t*)(SYSTICK_BASE_ADDRESS)) // Pointer to SysTick registers

/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
static SYSTICK_CBF_t SYSTICK_CALLBACKFUNCTION ; // Pointer to SysTick callback function
static u8 G_u8SingleFlag  ;                     // Flag for single-time mode

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
// No static functions prototypes defined

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


void MSYSTICK_vidInit(void)
{
   SYSTICK->STK_CTRL |= SYSTICK_CLK_SRC ;  // Configure SysTick clock source
   SYSTICK->STK_CTRL |= SYSTICK_INTERRUPT; // Enable SysTick interrupt
}


MSYSTICK_enuErrorStatus MSYSTICK_enuSetTimeMS(u32 Copy_u32MS_TIME)
{
     MSYSTICK_enuErrorStatus Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuNOK; 
     u32 LOC_u32Ticks=0;
    #if  SYSTICK_CLK_SRC == SYSTICK_CLK_SRC_AHB
    LOC_u32Ticks = ((u64)Copy_u32MS_TIME * (u64)CLK_SRC)/(u64)1000; // Calculate the number of ticks for the given time
    Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuOK;
    #elif SYSTICK_CLK_SRC ==SYSTICK_CLK_SRC_AHB_DIV_BY_8
    LOC_u32Ticks = ((u64)Copy_u32MS_TIME * (u64)CLK_SRC)/(u64)8000; // Calculate the number of ticks for the given time
    Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuOK;
    #endif

    SYSTICK->STK_LOAD = LOC_u32Ticks;                              // Load the calculated value into the SysTick Load register

    return Ret_enuSYSTICK_ErrorStatus;
}


MSYSTICK_enuErrorStatus MSYSTICK_enuStart(u8 Copy_u8TimerType)
{
   MSYSTICK_enuErrorStatus Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuNOK; 
   if(Copy_u8TimerType != SYSTICK_SINGLETIME && Copy_u8TimerType != SYSTICK_PERIODIC )
   {
     Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuWRONG_TIMER_TYPE; 
   }
   if(Copy_u8TimerType == SYSTICK_SINGLETIME)
   {
       G_u8SingleFlag = 1;
       Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuOK;
   }
   else
   {
        G_u8SingleFlag = 0;
        Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuOK;
   }

   SYSTICK->STK_VAL=0;                       // Clear the current value register
   SYSTICK->STK_CTRL |= 1 << SYSTICK_ENABLE; // Enable the SysTick timer

     return Ret_enuSYSTICK_ErrorStatus;
}


void MSYSTICK_enuStop(void)
{
      SYSTICK->STK_CTRL &= ~( 1 << SYSTICK_ENABLE); // Disable the SysTick timer
}


u32  MSYSTICK_u32GetElapsedTime(void)
{
     u32 LOC_u32ElapsedTime=0;
     LOC_u32ElapsedTime = (SYSTICK->STK_LOAD) - (SYSTICK->STK_VAL) ; // Calculate the elapsed time
     return LOC_u32ElapsedTime ;
}


u32  MSYSTICK_u32GetRemainingTime(void)
{  
   u32 LOC_u32RemainingTime=0;
   LOC_u32RemainingTime = SYSTICK->STK_VAL;     // Get the remaining time
   return LOC_u32RemainingTime;
}


MSYSTICK_enuErrorStatus MSYSTICK_enuSetCallback(void (*Copy_pfvCBFunc)(void))
{
  MSYSTICK_enuErrorStatus Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuNOK; 
  if(Copy_pfvCBFunc == NULL)
  {
    Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuNULLPOINTER; 
  }
  else
  {
    SYSTICK_CALLBACKFUNCTION = Copy_pfvCBFunc ;      // Set the callback function
    Ret_enuSYSTICK_ErrorStatus = MSYSTICK_enuOK; 
  }
  return Ret_enuSYSTICK_ErrorStatus;
}


void SysTick_Handler (void){

	if(SYSTICK_CALLBACKFUNCTION != NULL )
  {
		SYSTICK_CALLBACKFUNCTION();       // Call the callback function
	}
  if (G_u8SingleFlag)
  {
    G_u8SingleFlag =0;
    MSYSTICK_enuStop();              // Stop the SysTick timer if it's in single-time mode
  }
}