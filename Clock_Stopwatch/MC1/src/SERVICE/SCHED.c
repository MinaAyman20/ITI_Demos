/*---------------------------------------------------------------------------------------------------*/
/*                                           Includes:                                               */
/*---------------------------------------------------------------------------------------------------*/
#include <MCAL/SYSTICK.h>
#include <Service/RUNNABLE.h>
#include <Service/SCHED.h>

/*---------------------------------------------------------------------------------------------------*/
/*                                           Typedefs:                                               */
/*---------------------------------------------------------------------------------------------------*/
typedef struct
{
    Runnable_t* Runnable;
    uint32_t RemainingTime;
}ExtraRunnableInfo_t;


/*---------------------------------------------------------------------------------------------------*/
/*                                           Variables:                                              */
/*---------------------------------------------------------------------------------------------------*/
static volatile uint32_t SCHED_PendingTicks = 1 ;

/*---------------------------------------------------------------------------------------------------*/
/*                                           Extern:                                                 */
/*---------------------------------------------------------------------------------------------------*/
extern Runnable_t Runnables_Arr [_RunnableNumber];
ExtraRunnableInfo_t Runnable_Info_Array [_RunnableNumber];
/*---------------------------------------------------------------------------------------------------*/
/*                                           Static Function:                                        */
/*---------------------------------------------------------------------------------------------------*/
static void TickIncrement (void)
{
    SCHED_PendingTicks++;
}

static void SCHED (void)
{
    static uint32_t Current_Runnable = 0;
    for(Current_Runnable =0 ; Current_Runnable < _RunnableNumber ; Current_Runnable++)
    {
        /**check if the delay time is passed and call back function is set*/
        if((Runnables_Arr[Current_Runnable].CB) && (Runnable_Info_Array[Current_Runnable].RemainingTime == 0))
        {
         
            Runnables_Arr[Current_Runnable].CB();
            Runnable_Info_Array[Current_Runnable].RemainingTime = Runnable_Info_Array[Current_Runnable].Runnable->Periodicity;
        }
         Runnable_Info_Array[Current_Runnable].RemainingTime -= SCHED_TICK_TIME;
    }
}

/*---------------------------------------------------------------------------------------------------*/
/*                                           APIs:                                                   */
/*---------------------------------------------------------------------------------------------------*/

/**
 * @brief Call this function at the start to initialize the scheduler.
 * @param NoThing
 * @return NoThing 
 */
void SCHED_Init (void)
{
    STK_Init(SOURCE_AHB);
    STK_SetTimeMS(SCHED_TICK_TIME);
    STK_SetCallback(TickIncrement);
    STK_EnableInterrupt();

    for(uint32_t itr =0 ; itr < _RunnableNumber ; itr++)
    {
        Runnable_Info_Array[itr].Runnable = &Runnables_Arr[itr];
        Runnable_Info_Array[itr].RemainingTime = Runnables_Arr[itr].DelayMs;
    }
}

/**
 * @brief this function to start the schedular after initialize it.
 * @param NoThing
 * @return NoThing 
 */
void SCHED_Start (void)
{
    STK_Start(STK_MODE_PERIODIC);
    while (1)
    {
        if(SCHED_PendingTicks)
        {
            SCHED_PendingTicks--;
            SCHED();
        }
    }
    
}
