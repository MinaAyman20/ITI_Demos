#include <Service/RUNNABLE.h>
#include <Service/SCHED.h>
/*---------------------------------------------------------------------------------------------------*/
/*                                           Extern Prototypes                                       */
/*---------------------------------------------------------------------------------------------------*/

extern void RUNNABLE_LCD(void);
extern void Clock_RunnerTask(void);
extern void Stopwatch_RunnerTask(void);
extern void Switch_runnable(void);
extern void SW_Runnable(void);


/*---------------------------------------------------------------------------------------------------*/
/*                                           Runnables List                                          */
/*---------------------------------------------------------------------------------------------------*/
Runnable_t Runnables_Arr [_RunnableNumber]=
{
    [LCD_RUNNABLE]=
    {
        .Name = "Lcd_runnable",
        .Periodicity = 1,
        .CB = &RUNNABLE_LCD,
    },
    [Clock_Runner]=
    {
        .Name = "Clock_runnable",
        .Periodicity = 200,
        .CB = &Clock_RunnerTask,
        .DelayMs = 200
    },
    [Stopwatch_Runner]=
    {
        .Name = "Stopwatch_runnable",
        .Periodicity = 200,
        .CB = &Stopwatch_RunnerTask,
        .DelayMs = 320
    },
    [Switch_Runner]=
    {
        .Name = "Switch_runnable",
        .Periodicity = 200,
        .CB = &Switch_runnable,
        .DelayMs = 300
    },
    [sw_runner]=
    {
        .Name = "sw_runner",
        .Periodicity = 10,
        .CB = &SW_Runnable,
        .DelayMs = 320
    }
};