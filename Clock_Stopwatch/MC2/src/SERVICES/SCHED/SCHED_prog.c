/******************************************************************************
*
* Module: Scheduler Driver.
*
* File Name: SCHED_prog.c
*
* Description: Driver's APIs' Implementation and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date:	15-03-2024
*
*******************************************************************************/


/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/


#include "MCAL/MSYSTICK/MSYSTICK_interface.h"
#include "SERVICES/SCHED/SCHED_interface.h"

/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/* Periodicity of our Scheduler */
#define SCHED_PERIODICITY_MS		1



/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


/* The reason of "const" is that the scheduler can not add tasks in the runtime */
extern const runnable_t arrayOfRunnables [_RunnablesNumber_];

typedef struct {
	u8 delayFlag;
}privateDelayFlag;



/****************************************************************************************/
/*									Variables's Declaration								*/
/****************************************************************************************/


/* The reason of "volatile" is that */
static volatile u32 pendingTasks = 0;

privateDelayFlag arrayOfRunnablesDelayFlag [_RunnablesNumber_] = {0};

/****************************************************************************************/
/*								Static Functions' Declaration							*/
/****************************************************************************************/


/**
 *@brief : Function that initializes the scheduler.
 *@param : void.
 *@return: void.
 */
static void SCHED_sched(void)
{
	u32 index;
	static u32 timeStamp = 0;
	for(index = 0; index < _RunnablesNumber_; index++)
	{
		if (timeStamp >= arrayOfRunnables[index].firstDelay && arrayOfRunnablesDelayFlag[index].delayFlag == 0)
		{
			timeStamp = 0;
			arrayOfRunnablesDelayFlag[index].delayFlag = 1;
		}
		/* Check on the CallBack pointer that it isn't a NULL pointer and check
		 * if the time of this runnable comes */
		if((arrayOfRunnables[index].callBackFn)\
				&& ((timeStamp % (arrayOfRunnables[index].periodicityMS)) == 0) && (arrayOfRunnablesDelayFlag[index].delayFlag == 1))
		{
			/* If everything is OK, call the CallBackFn of this runnable */
			arrayOfRunnables[index].callBackFn();
		}
	}
	/* Plus the periodicity of our scheduler to the timeStamp variable because when this function
	 * be called next time, the time passed will be equal to the scheduler's periodicity  */
	timeStamp += SCHED_PERIODICITY_MS;
}



/****************************************************************************************/
/*								Functions' Implementation								*/
/****************************************************************************************/


/**
 *@brief : Function that .
 *@param : void.
 *@return: void.
 */
void tickCallBack(void)
{
	pendingTasks++;
}


/**
 *@brief : Function that initializes the scheduler.
 *@param : void.
 *@return: void.
 */
void SCHED_init(void)
{
	MSYSTICK_vidInit();
	MSYSTICK_enuSetTimeMS(SCHED_PERIODICITY_MS);
	MSYSTICK_enuSetCallback(tickCallBack);
}


/**
 *@brief : Function that starts the scheduler.
 *@param : void.
 *@return: void.
 */
void SCHED_start(void)
{
	MSYSTICK_enuStart(SYSTICK_PERIODIC);
	while (1)
	{
		if(pendingTasks)
		{
			pendingTasks--;
			SCHED_sched();
		}
	}
}
