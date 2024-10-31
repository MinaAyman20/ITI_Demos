/******************************************************************************
*
* Module: Scheduler Driver.
*
* File Name: SCHED_interface.h
*
* Description: Driver's APIs' prototypes and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date:	15-03-2024
*
*******************************************************************************/


#ifndef SCHED_INTERFACE_H_
#define SCHED_INTERFACE_H_


/************************************************************************************/
/*									Includes										*/
/************************************************************************************/


#include "LIB/STD_TYPES.h"
#include "CFG/SCHED/SCHED_config.h"



/************************************************************************************/
/*							User-defined types Declaration							*/
/************************************************************************************/

/* The type of the call back function in the runnable, function that takes nothing (void)
 * and returns nothing (void) */
typedef void (*runnableCB_t)(void);

/* Structure that includes the necessary data for each runnable, You will need to define
 * each of these three members for each runnable in the array */
typedef struct{
	char* name;
	u32 periodicityMS;
	u32 firstDelay;
	runnableCB_t callBackFn;
}runnable_t;



/************************************************************************************/
/*								Functions' Declaration								*/
/************************************************************************************/


/**
 *@brief : Function that initializes the scheduler.
 *@param : void.
 *@return: void.
 */
void SCHED_init(void);


/**
 *@brief : Function that starts the scheduler.
 *@param : void.
 *@return: void.
 */
void SCHED_start(void);



#endif /* SCHED_INTERFACE_H_ */
