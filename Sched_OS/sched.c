/******************************************************************************
 *
 * Module     : SCHDULER
 *
 * File Name  : sched.c
 *
 * Description: Source file for the STM32 SCDULER OS
 *
 * Author     : Osama Hamdy
 *
 *******************************************************************************/
#include"STK_inerface.h"
#include"sched_cfg.h"
#include"sched.h"

/*Post Build Configuration Struture of Schduler */
extern const runnable_t runnablelist[MAX_TASKS];

/*Global Variable to Indicate the OS flag value*/
u8 Os_flag=0;
/*Static global variable to count the scheduler ticks */
static u32 Time_Ms;

/*
 * Private Function
 * Description : Calling the Function of the current Scheduler Task
 * Function Parameter : void
 * Function Return : void
 * */
static void Sched_Handler(void);

/*******************************************************************************
 *                            Fuction Definitions                              *
 *******************************************************************************/

/*
 * Public Function
 * Description : Intialization of the Schduler
 * Function Parameter : void
 * Function Return : void
 * */
void Sched_Init(void){
	/*Systick Timer Intialzation */
	STK_vidInit();
	/*Set the value of TickMsec to Systick Timer */
	STK_SetTimeMS(TICK_MS );
	/*starting the Systick  Handler */
	STK_RegisterCBF(Sched_OsFlag);
}
/*
 * Public Function
 * Description : Starting the Schduler & Systick Timer
 * Function Parameter : void
 * Function Return : void
 * */
void Sched_Start(void){
	/*Enable the Systick Timer to Start the schduler */
	STK_Start();
	while(1)
	{
		/*Checking the value of the operating system flag*/
		if(Os_flag==1)
		{
			Os_flag=0;
			/*Starting the Scheduler Handler */
			Sched_Handler();
		}

	}
}
/*
 * Public Function
 * Description : Get the number of Schduler TimeMsec
 * Function Parameter : void
 * Function Return : number of TimeMsec
 * */
u32 Sched_getTimeMs(void){
	/*Getting the value of the Scheduler tick */
	return Time_Ms;
}
/*
 * Public Function
 * Description : Incrementing the value of Operating System Flag
 * Function Parameter : void
 * Function Return : void
 * */
void Sched_OsFlag(void){
	/*Incrementing the value of the operating system flag*/
	Os_flag=1;
}

/*
 * Private Function
 * Description : Calling the Function of the current Scheduler Task
 * Function Parameter : void
 * Function Return : void
 * */

void  Sched_Handler(void){

	/*Local variable to save the Number of Schduler Loop Iteration*/
	u8 loc_RunnableIterator=0;

	for(loc_RunnableIterator=0;loc_RunnableIterator<MAX_TASKS;loc_RunnableIterator++)
	{
		/* Check the Schduler Cyclic time */
		if(Time_Ms % runnablelist[loc_RunnableIterator].Cyclic_TimeMs == 0)
		{
			/*Calling the Current Schduler Function */
			runnablelist[loc_RunnableIterator].cbf();
		}

	}

	/*Updating the value of Schduler TimeMsec*/

	Time_Ms += TICK_MS;
}
