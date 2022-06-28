/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	May 27, 2022
**       Version     :	V01
**       SWC         :	Core
**       Description :	Core files
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
#include "Core.h"
#include "Core_prv.h"
/* //////////////////////////////////////////////////////////////////////// */

/* //////////////////////// Global Variables ///////////////////////////////// */
/* TCB */
u32       OS_TCB_Index = ZERO_INIT;
strTCB_t  OS_astrTCB[OS_u8TASKS_MAX];
strTCB_t* OS_pstrReadyList       = NULL; /* linked list */
strTCB_t* OS_pstrWaitingList     = NULL; /* linked list */
strTCB_t* OS_pstrCurrentTCB      = NULL; /* one node */
strTCB_t* OS_pstrHighestReadyTCB = NULL; /* one node */
/* OS start Flag  */ 
/* Indicate the state of OS (started or not started yet) */
enuOS_State_t OS_enuOS_State = enuOS_State_Off;
/* Idle Task stack */
u32 OS_aIdleTaskStack[OS_u8IDLE_TASK_STACK_SIZE];
/* //////////////////////////////////////////////////////////////////////// */

/* //////////////////////// Interface Fns ///////////////////////////////// */
void OS_vidCreateTask(pfTask_t Copy_pfTask, u32 Copy_u32TaskPri, u32* Copy_TaskStack, u32 Copy_TaskStackSize)
{
  strTCB_t* Loc_pstrAllocatedTCB = NULL;
  /* Create and init stack and TCB */
  Loc_pstrAllocatedTCB = OS_pstrTaskInit(Copy_pfTask, Copy_u32TaskPri, Copy_TaskStack, Copy_TaskStackSize);
  if(Loc_pstrAllocatedTCB != NULL)
  {
    Port_vidDisableInterrupt();
    List_vidInsert(&OS_pstrReadyList, Loc_pstrAllocatedTCB, enuOrderType_Pri);
    if((OS_enuOS_State == enuOS_State_On) && (Loc_pstrAllocatedTCB->TaskPri < OS_pstrCurrentTCB->TaskPri))
    {
      List_vidInsert(&OS_pstrReadyList, OS_pstrCurrentTCB, enuOrderType_Pri);
      OS_pstrHighestReadyTCB = List_pstrExtractHead(&OS_pstrReadyList);
      Port_vidTaskSwitch();
    }/* if */
    Port_vidEnableInterrupt();
  }/* if */
}/* OS_vidCreateTask */
static strTCB_t* OS_pstrTaskInit(pfTask_t Copy_pfTask, u32 Copy_u32TaskPri, u32* Copy_TaskStack, u32 Copy_TaskStackSize)
{
  strTCB_t* Loc_pstrAllocatedTCB = NULL;
  if(OS_TCB_Index != OS_u8TASKS_MAX)
  {
    /* Allocation step */
    Loc_pstrAllocatedTCB = &OS_astrTCB[OS_TCB_Index];
    OS_TCB_Index++;
    /* Initialization */  
    Loc_pstrAllocatedTCB->Next = NULL;
    Loc_pstrAllocatedTCB->Prev = NULL;
    Loc_pstrAllocatedTCB->Sem  = NULL;
    Loc_pstrAllocatedTCB->Task = Copy_pfTask;
    Loc_pstrAllocatedTCB->TaskPri = Copy_u32TaskPri;
    Loc_pstrAllocatedTCB->WaitTicks = ZERO_INIT;
    Loc_pstrAllocatedTCB->TaskBasePri = ZERO_INIT;
    Loc_pstrAllocatedTCB->TaskStackSize = Copy_TaskStackSize;
    Loc_pstrAllocatedTCB->TaskSP     = (u32*)(((u32)(Copy_TaskStack + Copy_TaskStackSize)) & ((u32)0xFFFFFFFC));
    Loc_pstrAllocatedTCB->TaskSP--;
    *(Loc_pstrAllocatedTCB->TaskSP)  = (u32)(0x01000000); /* PSR */
    Loc_pstrAllocatedTCB->TaskSP--;
    *(Loc_pstrAllocatedTCB->TaskSP)  = (((u32)Copy_pfTask) & ((u32)0xFFFFFFFE)); /* PC */
    Loc_pstrAllocatedTCB->TaskSP--;
    *(Loc_pstrAllocatedTCB->TaskSP)  = (u32)(0x00); /* LR */
    Loc_pstrAllocatedTCB->TaskSP -= 5; /* R12, R3:R0 */
    Loc_pstrAllocatedTCB->TaskSP--;
    *(Loc_pstrAllocatedTCB->TaskSP)  = (u32)(0xFFFFFFFD); /* EXC_RET = PSP Thread */
    Loc_pstrAllocatedTCB->TaskSP -= 8; /* R11:R4 */
  }/* if */
  else
  {
    Loc_pstrAllocatedTCB = NULL;
  }/* else */

  return(Loc_pstrAllocatedTCB);
}/* OS_pstrTaskInit */
void OS_vidDelay(u32 Copy_u32WaitTicks)
{
  Port_vidDisableInterrupt();
  OS_pstrCurrentTCB->WaitTicks = Copy_u32WaitTicks;
  List_vidInsert(&OS_pstrWaitingList, OS_pstrCurrentTCB, enuOrderType_Tick);
  OS_pstrHighestReadyTCB = List_pstrExtractHead(&OS_pstrReadyList);
  Port_vidTaskSwitch();
  Port_vidEnableInterrupt();
}/* OS_vidDelay */
void OS_vidStart(void)
{
  Port_vidDisableInterrupt();
  OS_vidCreateTask(OS_vidRunIdle_T, (OS_u8TASKS_MAX-1), OS_aIdleTaskStack, OS_u8IDLE_TASK_STACK_SIZE);
  /* To lower interrupt latency */
  SCB_pstrRegisters->SHP[10] = 0xF0;   /* PendSV */
  SCB_pstrRegisters->SHP[11] = 0xF0;   /* Systick */
  Port_vidSystickSetup();
  OS_pstrCurrentTCB = List_pstrExtractHead(&OS_pstrReadyList);
  OS_enuOS_State = enuOS_State_On;
  Port_vidStartFirstTask();
}/* OS_vidStart */
static void OS_vidRunIdle_T(void)
{
  while(1)
  {

  }/* while */
}/* OS_vidRunIdle_T */
/* //////////////////////////////////////////////////////////////////////// */
