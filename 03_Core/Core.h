/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	May 27, 2022
**       Version     :	V01
**       SWC         :	Core
**       Description :	Core files
** **************************************************************************************/
#ifndef _CORE_H
#define _CORE_H
  #include "Semaphore.h"
  /* //////////////////////// Interface Fns ///////////////////////////////// */
  void OS_vidCreateTask(pfTask_t Copy_pfTask, u32 Copy_u32TaskPri, u32* Copy_TaskStack, u32 Copy_TaskStackSize);
  void OS_vidDelay(u32 Copy_u32WaitTicks);
  void OS_vidStart(void);
  /* //////////////////////////////////////////////////////////////////////// */
#endif