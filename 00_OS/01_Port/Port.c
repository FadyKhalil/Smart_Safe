/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	May 27, 2022
**       Version     :	V01
**       SWC         :	Port
**       Description :	Port files
** **************************************************************************************/
/* /////////////////////////////////// Headers //////////////////////////////// */
/* LIB */
#include "StdTypes.h"
#include "STM32F401CC.h"
/* MCAL */
#include "Systick.h"
/* Data Structures */
#include "List.h"
/* OS Configurations */
#include "OS_cfg.h"
/* Own */
#include "Port.h"
#include "Port_prv.h"
/* //////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////// Global Variables ////////////////////////// */
extern strTCB_t* OS_pstrReadyList      ; /* linked list */
extern strTCB_t* OS_pstrWaitingList    ; /* linked list */
extern strTCB_t* OS_pstrCurrentTCB     ; /* one node */
extern strTCB_t* OS_pstrHighestReadyTCB; /* one node */
extern enuOS_State_t OS_enuOS_State;
/* //////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////// Interface Fns ////////////////////////// */
/* 
  Description       :       Setup the systick timer
  Parameters        :       void
  Return            :       void
*/
void Port_vidSystickSetup(void)
{
  /* Init the systick timer */
  Systick_enuInit(SYSTICK_u8AHB, SYSTICK_u8ON_INT);
  /* Set the systick callback fn timestamp */
  Systick_enuSetTickTimeMS(OS_u16TICK_TIME);
  /* Registering the systick callback fn */
  Systick_vidRegCallbackFn(Port_vidSystickCallback);
  /* Starting the systick timer */
  Systick_enuStart();/* Starting the systick timer */
}/* Port_vidSystickSetup */
/* //////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////// Private Fns ////////////////////////// */
/* 
  Description       :       Systick callback fn
  Parameters        :       void
  Return            :       void
*/
void Port_vidSystickCallback(void)
{
  /* traverse tasks, decrement ticks
    if task_ticks == 0 --> move it in ready list
    if top of ready pri < current pri ---> move current to ready, make top of ready in highest pointer then Context_Switching
  */
  strTCB_t* Loc_pstrTCB_Traverser = OS_pstrWaitingList; 
  Port_vidDisableInterrupt();
  while(Loc_pstrTCB_Traverser != NULL)
  {
    Loc_pstrTCB_Traverser->WaitTicks--;
    if(Loc_pstrTCB_Traverser->WaitTicks == ZERO_INIT)
    {
      Loc_pstrTCB_Traverser = List_pstrExtractHead(&OS_pstrWaitingList);
      List_vidInsert(&OS_pstrReadyList, Loc_pstrTCB_Traverser, enuOrderType_Pri);
      if(Loc_pstrTCB_Traverser->Sem != NULL)
      {
        Loc_pstrTCB_Traverser->Sem = NULL;
      }/* if */
      Loc_pstrTCB_Traverser = OS_pstrWaitingList;
    }/* if */
    else
    {
      Loc_pstrTCB_Traverser = Loc_pstrTCB_Traverser->Next;
    }/* else */
  }/* while */
  if((OS_enuOS_State == enuOS_State_On) && (OS_pstrReadyList != NULL) && (OS_pstrReadyList->TaskPri < OS_pstrCurrentTCB->TaskPri))
  {
    List_vidInsert(&OS_pstrReadyList, OS_pstrCurrentTCB, enuOrderType_Pri);
    OS_pstrHighestReadyTCB = List_pstrExtractHead(&OS_pstrReadyList);
    Port_vidTaskSwitch();
  }/* if */
  Port_vidEnableInterrupt();
}/* Port_vidSystickCallback */
/* //////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////// ISRs ////////////////////////// */
void SVC_Handler(void)
{
  /* Context Unstacking */
  asm("  .ALIGN 4                          ");
  asm("  LDR R0, =OS_pstrCurrentTCB        "); /* Address of the Current TCB */
  asm("  LDR R0, [R0]                      "); /* Address of the Task SP (Pointer address) */
  asm("  LDR R0, [R0]                      "); /* Task SP (the pointer itself) */
  asm("  LDMIA R0!, {R4-R11, R14}          "); /* Poping from the task stack, Instruction is load multiple increment after */
  asm("  MSR PSP, R0                       "); /* put the psp value of the current task stack */
  asm("  MOV R1, #0x00                     "); /* preparing to enable interrupt */
  asm("  MSR BASEPRI, R1                   "); /* enable interrupt */  
  asm("  BX R14                            "); /* return to thread PSP */
}/* SVC_Handler */
void PendSV_Handler(void)
{
  /* Context Switching */
  /* Saving Current Task Context */
  asm("  .ALIGN 4                          ");
  asm("  MRS R0, PSP                       ");
  asm("  LDR R3, =OS_pstrCurrentTCB        "); /* &OS_pstrCurrentTCB */
  asm("  LDR R2, [R3]                      "); /* OS_pstrCurrentTCB */
  asm("  STMDB R0!, {R4-R11, R14}          ");
  asm("  STR R0, [R2]                      "); /* Saving Task SP */
  /* Get Highest Task Context */
  asm("  LDR R1, =OS_pstrHighestReadyTCB   ");
  asm("  LDR R1, [R1]                      ");/* OS_pstrHighestReadyTCB */
  asm("  STR R1, [R3]                      ");/* put the highest TCB instead of Current */
  asm("  LDR R0, [R1]                      ");/* OS_pstrHighestReadyTCB Task SP*/
  asm("  LDMIA R0!, {R4-R11, R14}          ");
  asm("  MSR PSP, R0                       ");
  asm("  BX R14                            ");
}/* PendSV_Handler */
/* //////////////////////////////////////////////////////////////////////////// */
