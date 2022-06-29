/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 29, 2022
**       Version     :	V1.0
**       SWC         :	SmartSafe
**       Description :	Smart Safe Application
** **************************************************************************************/
/* LIB */
#include "StdTypes.h"
/* OS */
#include "Core.h"
/* MCAL */
#include "RCC.h"
#include "Gpio.h"
/* HAL */
#include "Keypad.h"
#include "Lcd.h"
#include "EEPROM.h"
/* Own headers */
#include "SmartSafe.h"
#include "SmartSafe_prv.h"
#include "SmartSafe_cfg.h"
#include "SmartSafe_Lcfg.h"
/* Tracing */
#include "diag/Trace.h"
/* ////////////////////////////////////////////////////////////////////////////////////////// */

/* //////////////////////////////// Global Variables //////////////////////////////////////// */
/* Tasks Stacks */
u32 T1_Stack[TASK_STACK_SIZE];
u32 KeypadTask_Stack[TASK_STACK_SIZE];
u32 T3_Stack[TASK_STACK_SIZE];

//strOSSem_t* SemaphorePtr = NULL;
/* ////////////////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////// Entry Point ////////////////////// */
int main(void)
{
  RCC_enuTurnClk(RCC_u8HSI, RCC_enuOn);
  RCC_enuSelectSysClk(RCC_u8RUN_HSI);
  RCC_enuPerClk(RCC_enuGPIOA, RCC_enuOn);
  RCC_enuPerClk(RCC_enuGPIOB, RCC_enuOn);
  RCC_enuPerClk(RCC_enuUSART1, RCC_enuOn);
  RCC_enuPerClk(RCC_enuI2C1, RCC_enuOn);
  KeyPad_vidInit();

  // SemaphorePtr = OS_pstrCreateSem(enuSemType_Binary, 0);
  OS_vidCreateTask(T1, 0, T1_Stack, TASK_STACK_SIZE);
  OS_vidCreateTask(Keypad_GetKeyValue_T, 1, KeypadTask_Stack, TASK_STACK_SIZE);
  // OS_vidCreateTask(T3, 2, T3_Stack, TASK_STACK_SIZE);
  OS_vidStart();
  while(1)
  {

  }/* while */

  return(0);
}/* main */

/* //////////////////////////////////////// Tasks /////////////////////////////////////////// */
void T1(void)
{
  s8 Loc_s8Key = ZERO_INIT;
	trace_printf("T1 Started\n");
	while(1)
  {
    Keypad_u8GetPressedKey(&Loc_s8Key);
    OS_vidDelay(26);
		trace_printf("Task1 Checking\n");
    // OS_vidGiveSem(SemaphorePtr);
  }/* while */
}/* T1 */
// void T2(void)
// {
// 	trace_printf("T2 Started\n");
// 	while(1)
//   {
//     // if(OS_enuTakeSem(SemaphorePtr, 5000))
//     // {
//     //   trace_printf("T2 took Semaphore\n");
//     // }
//     // else
//     // {
//     //   trace_printf("T2 timeout\n");
//     // }
// 		trace_printf("T2\n");
//     OS_vidDelay(5000);
//   }/* while */
// }/* T2 */
void T3(void)
{
	trace_printf("T3 Started\n");
	while(1)
  {
		trace_printf("T3\n");
    OS_vidDelay(5000);
  }/* while */
}/* T3 */
/* ////////////////////////////////////////////////////////////////////////////////////////// */
