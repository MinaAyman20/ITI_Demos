/******************************************************************************
 *
 * File Name: RunnablesList_cfg.h
 *
 * Description: Configuration file for The Runnables in the System.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-03-2024
 *
 *******************************************************************************/

#ifndef SCHED_RUNNABLES_CFG_H_
#define SCHED_RUNNABLES_CFG_H_

/************************************************************************************/
/*							User-defined Types Declaration							*/
/************************************************************************************/

/**
 *@brief : Write down the names of the Runnables that are in your system.
 */
typedef enum
{
    lcdRunnable,
	Switch_check,
	Switch_Debounce,
	Clock_Runnable,
	Stopwatch_Runnable,
	Recieve_Runnable,

	/* DO NOT DELETE THIS ↓↓↓, please :)*/
	_RunnablesNumber_
}RunnablesList_t;


#endif /* SCHED_RUNNABLES_CFG_H_ */
