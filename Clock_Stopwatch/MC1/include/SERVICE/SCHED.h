#ifndef _SCHED_H
#define _SCHED_H


/********************************************************Includes:************************************************/
#include <stdint.h>
#include <ErrorStatus.h>


/********************************************************Defines:*************************************************/
#define SCHED_TICK_TIME             1


/********************************************************Types:***************************************************/
typedef void (*CallBacK_Pointer_t) (void);

typedef struct
{
    char* Name;                                 //name of runnable
    uint32_t DelayMs;                           //delay will apply before the first run
    uint32_t Periodicity;                       //periodicity of your runnable
    CallBacK_Pointer_t CB;                      //pointer pointed on your runnable
}Runnable_t;


/********************************************************APIs:****************************************************/

/**
 * @brief Call this function at the start to initialize the scheduler.
 * @param NoThing
 * @return NoThing 
 */
void SCHED_Init (void);

/**
 * @brief this function to start the schedular after initialize it.
 * @param NoThing
 * @return NoThing 
 */
void SCHED_Start (void);

#endif