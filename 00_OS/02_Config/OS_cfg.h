/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	OS
**       Description :	OS files
** **************************************************************************************/
#ifndef _OS_CFG_H
#define _OS_CFG_H
  /* ///////////////////////////////// MACROS ////////////////////////////// */
  #define OS_u8TASKS_MAX                      ((u8)(10))
  #define OS_u8SEMAPHORES_MAX                 ((u8)(10))
  #define OS_u8IDLE_TASK_STACK_SIZE           ((u8)(85))
  /* ****Caution**** : Don't forget to configure the systick clock with your system clock */
  #define OS_u16TICK_TIME                     ((u16)(1))
  /* /////////////////////////////////////////////////////////////////////// */
#endif
