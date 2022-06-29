/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	June 08, 2022
**       Version     :	V01
**       SWC         :	Semaphore
**       Description :	Semaphore Service Implementation Files
** **************************************************************************************/
#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

  /* //////////////////////////// Interface Fns //////////////////////////////// */
  strOSSem_t* OS_pstrCreateSem(enuSemType_t Copy_enuSemType, u32 Copy_u32Init);
  enuStatus_t OS_enuTakeSem(strOSSem_t* Copy_pstrSem, u32 Copy_u32Timeout);
  void OS_vidGiveSem(strOSSem_t* Copy_pstrSem);
  /* /////////////////////////////////////////////////////////////////////////// */

#endif