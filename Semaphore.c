/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Semaphore
**       Description :	Semaphore Service Implementation Files
** **************************************************************************************/
/* //////////////////////// Headers ////////////////////////////////// */
/* LIB */
#include "StdTypes.h"
#include "STM32F401CC.h"
/* Data Structures */
#include "List.h"
/* OS Configurations */
#include "OS_cfg.h"
/* Porting */
#include "Port.h"
/* Own Headers */
#include "Semaphore.h"
/* //////////////////////////////////////////////////////////////////////// */

/* //////////////////////////// Global Variables //////////////////////////////// */
strOSSem_t OS_astrSemList[OS_u8SEMAPHORES_MAX];
u32 OS_u32SemListIndex = ZERO_INIT;
extern strTCB_t* OS_pstrReadyList; /* linked list */
extern strTCB_t* OS_pstrWaitingList; /* linked list */
extern strTCB_t* OS_pstrCurrentTCB     ; /* one node */
extern strTCB_t* OS_pstrHighestReadyTCB; /* one node */
extern enuOS_State_t OS_enuOS_State;
/* //////////////////////////////////////////////////////////////////////// */

/* //////////////////////////// Interface Fns //////////////////////////////// */
strOSSem_t* OS_pstrCreateSem(enuSemType_t Copy_enuSemType, u32 Copy_u32Init)
{
  strOSSem_t* Loc_pstrSemaphore = NULL;
  if(OS_u32SemListIndex == OS_u8SEMAPHORES_MAX)
  {
    Loc_pstrSemaphore = NULL; 
  }/* if */
  else
  {
    Loc_pstrSemaphore = &OS_astrSemList[OS_u32SemListIndex];
    OS_u32SemListIndex++;
    Loc_pstrSemaphore->SemType = Copy_enuSemType;
    Loc_pstrSemaphore->SemValue = Copy_u32Init;
    Loc_pstrSemaphore->SemOwner = NULL;
  }/* else */
  return(Loc_pstrSemaphore);
}/* OS_pstrCreateSem */

void OS_vidGiveSem(strOSSem_t* Copy_pstrSem)
{
  strTCB_t* Loc_pstrTCB_Traverser = NULL;
  strTCB_t* Loc_pstrHighTCB = NULL;
  u32 Loc_u32MaxPriority = OS_u8TASKS_MAX;

  if(Copy_pstrSem != NULL)
  {
    Port_vidDisableInterrupt();
    if(Copy_pstrSem->SemType == enuSemType_Binary)
    {
      Copy_pstrSem->SemValue = 1;
      Loc_pstrTCB_Traverser = OS_pstrWaitingList;
      while(Loc_pstrTCB_Traverser != NULL)
      {
        if((Loc_pstrTCB_Traverser->Sem == Copy_pstrSem) && (Loc_pstrTCB_Traverser->TaskPri < Loc_u32MaxPriority))
        {
          Loc_pstrHighTCB = Loc_pstrTCB_Traverser;
          Loc_u32MaxPriority = Loc_pstrTCB_Traverser->TaskPri;
        }/* if */
        Loc_pstrTCB_Traverser  = Loc_pstrTCB_Traverser->Next;
      }/* while */
      if(Loc_pstrHighTCB != NULL)
      {
        List_vidDelete(&OS_pstrWaitingList, Loc_pstrHighTCB);
        Loc_pstrHighTCB->WaitTicks = ZERO_INIT;
        Loc_pstrHighTCB->Sem = NULL;
        List_vidInsert(&OS_pstrReadyList, Loc_pstrHighTCB, enuOrderType_Pri);
        if((OS_enuOS_State == enuOS_State_On) && (OS_pstrReadyList != NULL) && (OS_pstrReadyList->TaskPri < OS_pstrCurrentTCB->TaskPri))
        {
          List_vidInsert(&OS_pstrReadyList, OS_pstrCurrentTCB, enuOrderType_Pri);
          OS_pstrHighestReadyTCB = List_pstrExtractHead(&OS_pstrReadyList);
          Port_vidTaskSwitch();
        }/* if */

      }/* if */
    }/* if */
    Port_vidEnableInterrupt();
  }/* if */ 
  else
  {

  }/* else */
}/* OS_vidGiveSem */
enuStatus_t OS_enuTakeSem(strOSSem_t* Copy_pstrSem, u32 Copy_u32Timeout)
{
  enuStatus_t Loc_enuStatus = enuStatus_Nok;
  if(Copy_pstrSem != NULL)
  {
    if((Copy_pstrSem->SemValue == ZERO_INIT) && (Copy_u32Timeout > ZERO_INIT))
    {
      OS_pstrCurrentTCB->WaitTicks = Copy_u32Timeout;
      OS_pstrCurrentTCB->Sem = Copy_pstrSem;
      Port_vidDisableInterrupt();
      List_vidInsert(&OS_pstrWaitingList, OS_pstrCurrentTCB, enuOrderType_Tick);
      OS_pstrHighestReadyTCB = List_pstrExtractHead(&OS_pstrReadyList);
      Port_vidTaskSwitch();
      Port_vidEnableInterrupt();
    }/* if */
    if(Copy_pstrSem->SemValue == 1)
    {
      Copy_pstrSem->SemValue = 0;
      Loc_enuStatus = enuStatus_Ok;
    }/* if */
  }/* if */

  return(Loc_enuStatus);
}/* OS_enuTakeSem */
/* /////////////////////////////////////////////////////////////////////////// */

