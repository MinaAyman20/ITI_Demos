/******************************************************************************
 *
 * File Name: RunnablesList_cfg.c
 *
 * Description: Configuration file for The Runnables in the System.
 *
 * Author: Shaher Shah Abdalla Kamal
 *
 * Date: 15-03-2024
 *
 *******************************************************************************/

/************************************************************************************/
/*									Includes										*/
/************************************************************************************/

#include "SERVICES/SCHED/SCHED_interface.h"

/************************************************************************************/
/*								extern Public Functions								*/
/************************************************************************************/


/* Add here The functions that you will set in the callBackFn member for the runnables */

extern void RUNNABLE_LCD(void);
extern void SW_Runnable(void);
extern void clockRunnable(void);
extern void StopwatchRunnable(void);
extern void switchesCheckRunnable (void); 
extern void receiveRunnable(void) ;





/************************************************************************************/
/*							User-defined Types Definition							*/
/************************************************************************************/


/* Description: Create array of Runnables in your system,
 * 				setting inside it the configuration you want for each Runnable.
 * Example:
 * const runnable_t arrayOfRunnables [_RunnablesNumber_] = {
	[Runnable1] = { .name = "Toggle LED each second",
							.periodicityMS = 1000,
							.callBackFn = RUNNABLE_LED_toggle
	},
	[Runnable2] = { .name = "Check the status of the switches",
							.periodicityMS = 30,
							.callBackFn = RUNNABLE_SWITCH_getSwitchState
	},
	and so on ...
};
 * Cautions: 	- Be careful when setting the periodicity of any runnable that it's not
 * 					smaller than 10 ms.
 * 				- Note that the order in which You will write the runnables in the array defines
 * 					the priority for each of them, the priority decreases as the index of the runnable
 * 					increases (Runnable in index zero is the one with the highest priority).
 * 																					*/

const runnable_t arrayOfRunnables [_RunnablesNumber_] = {
		[lcdRunnable] 			= { .name = "LCD module",
									.periodicityMS = 1,
									.firstDelay=0,
									.callBackFn = RUNNABLE_LCD
		},
		[Switch_Debounce] 		= { .name = "Switch_Debounce",
									.periodicityMS = 30,
									.firstDelay=50,
									.callBackFn = SW_Runnable
		},
		[Switch_check]			= { .name = "Switch Check",
									.periodicityMS =200,
									.firstDelay=200,
									.callBackFn = switchesCheckRunnable
		},
		[Clock_Runnable]		= { .name = "Clock_Runnable",
									.periodicityMS =10,
									.firstDelay=50,
									.callBackFn = clockRunnable
		},

		[Stopwatch_Runnable]	= { .name = "Stopwatch_Runnable",
									.periodicityMS = 20,
									.firstDelay=50,
									.callBackFn = StopwatchRunnable
		},
		[Recieve_Runnable]		= { .name = "Recieve_Runnable",
									.periodicityMS = 200,
									.firstDelay=200,
									.callBackFn = receiveRunnable
		}
};
