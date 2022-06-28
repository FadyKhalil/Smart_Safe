/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	May 27, 2022
**       Version     :	V01
**       SWC         :	Core
**       Description :	Core files
** **************************************************************************************/
#ifndef _CORE_PRV_H
#define _CORE_PRV_H
  /* ////////////////////////////////////////////// Private Fns //////////////////////////////////////////////////////////// */
  static strTCB_t* OS_pstrTaskInit(pfTask_t Copy_pfTask, u32 Copy_u32TaskPri, u32* Copy_TaskStack, u32 Copy_TaskStackSize);
  static void OS_vidRunIdle_T(void);
  /* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#endif