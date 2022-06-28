/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	March 23, 2022
**       Version     :	V01
**       SWC         :	Systick
**       Description :	Systick timer module files
** **************************************************************************************/
/* ************************** Headers inclusion   ************************************** */
/* LIB headers */
#include "STD_TYPES.h"
#include "STM32F401CC.h"
/* Own headers */
#include "Systick.h"
#include "Systick_cfg.h"
#include "Systick_prv.h"
/* ****************************** Global *********************************************** */
static Systick_tpfCallback Systick_pfCallback;
static u32 Systick_u32OverflowsNumber;
static u32 Systick_u32TempOverflowsNumber;
static u32 Systick_u32ReloadValue;
/* ************************************************************************************* */
/* **************************** Interface Fns ****************************************** */
/* 
  Fn           :     Init the systick timer
  Parameter1   :     The Source clk, options are in "Systick.h" under "Timer Clk Sources" 
  Parameter2   :     Interrupt Activation, options are in "Systick.h" under "Timer Interrupt Activation" 
  Return       :     The status error, options are in "Systick.h" under "Error Type" 
*/
Systick_tenuError Systick_enuInit(u8 Copy_u8TimerSrc, u8 Copy_u8IntActivation)
{
  Systick_tenuError Loc_enuError = Systick_enuOk;
  /* Input validation */
  if((Copy_u8TimerSrc > SYSTICK_u8AHB) || (Copy_u8IntActivation > SYSTICK_u8ON_INT))
  {
    Loc_enuError = Systick_enuNok;
  }/* if */
  else
  {
    /* Selecting the clock source */
    if(Copy_u8TimerSrc == SYSTICK_u8AHB_OVER_8)
    {
      Systick_pstrRegisters->CTRL &= ~SYSTICK_u32CLK_SRC;
    }/* if */
    else
    {
        Systick_pstrRegisters->CTRL |= SYSTICK_u32CLK_SRC;
    }/* else */
    /* Activate/Deactivate the interrupt */
    if(Copy_u8IntActivation == SYSTICK_u8OFF_INT)
    {
      Systick_pstrRegisters->CTRL &= ~SYSTICK_u32INT;
    }/* if */
    else
    {
      Systick_pstrRegisters->CTRL |= SYSTICK_u32INT;
    }/* else */
  }/* else */

  return(Loc_enuError);
}/* Systick_enuInit */
/* 
  Fn           :     Start timer with specific delay
  Parameter    :     The delay time in milliseconds
  Return       :     The status error, options are in "Systick.h" under "Error Type" 
*/  
Systick_tenuError Systick_enuSetTickTimeMS(u32 Copy_u32Time_MS)
{
  Systick_tenuError Loc_enuError = Systick_enuOk;
  f64 Loc_f64TickTime;
  u64 Loc_u64NeededTicks;

  Loc_f64TickTime = (f64)1 / (SYSTICK_u8CLOCK * (u64)1000); /* The tick time in Milliseconds */
  Loc_u64NeededTicks = Copy_u32Time_MS / Loc_f64TickTime; /* Needed ticks to achieve required delay */
  Systick_u32OverflowsNumber = (Loc_u64NeededTicks / (u32)SYSTICK_u32MAX_RELOAD); /* Number of needed overflows */
  if(Systick_u32OverflowsNumber > 0)
  {
    Systick_u32OverflowsNumber -= 1;
  }
  Systick_u32TempOverflowsNumber = Systick_u32OverflowsNumber;
  Systick_u32ReloadValue = (Loc_u64NeededTicks % SYSTICK_u32MAX_RELOAD); /* Number of reload value */
  if(Systick_u32OverflowsNumber > 0)
  {
    Systick_pstrRegisters->LOAD = SYSTICK_u32MAX_RELOAD-1; /* You have to encounter the overflow time */
  }/* if */
  else
  {
    Systick_pstrRegisters->LOAD = Systick_u32ReloadValue-1; 
  }/* else */
  
  return(Loc_enuError);/* returning the error status */
}/* Systick_enuDelay */
/* 
  Fn         :   Register the callback fn
  Parameter1 :   Address of the callback fn
  Return     :   Error status of the fn, Error type is in "Systick.h" under "Error Type"
*/
Systick_tenuError Systick_vidRegCallbackFn(Systick_tpfCallback Copy_pfCallback)
{
  Systick_tenuError Loc_enuError = Systick_enuOk;
  if(Copy_pfCallback)
  {
    Systick_pfCallback = Copy_pfCallback;
  }/* if */
  else
  {
    Loc_enuError = Systick_enuNok;
  }/* else */

  return(Loc_enuError);/* return error status */
}/* Systick_vidRegCallbackFn */
/* 
  Fn           :     Start timer
  **caution**  :     You should set the tick time before using the "Systick_enuSetTickTimeMS" fn in "Systick.h"
*/  
void Systick_enuStart(void)
{
  /* Enable the systick */
  Systick_pstrRegisters->CTRL |= SYSTICK_u32ENABLE;
}/* Systick_enuStart */
/* ************************************************************************************* */
/* ***************************** Systick Timer Handler ********************************* */
void SysTick_Handler(void)
{
  if(Systick_u32TempOverflowsNumber)
  {
    if(Systick_u32TempOverflowsNumber == Systick_u32OverflowsNumber + 1)
    {
      Systick_pfCallback();
      Systick_pstrRegisters->LOAD = SYSTICK_u32MAX_RELOAD-1;
      Systick_pstrRegisters->VAL  = SYSTICK_u32VAL_CLEAR;
    }/* if */
    Systick_u32TempOverflowsNumber--;
  }/* if */
  else
  {
    if(Systick_u32OverflowsNumber)
    {
      Systick_pstrRegisters->LOAD = Systick_u32ReloadValue - 1;
      Systick_pstrRegisters->VAL  = SYSTICK_u32VAL_CLEAR;
      Systick_u32TempOverflowsNumber = Systick_u32OverflowsNumber + 1;
    }/* if */
    else
    {
      Systick_pfCallback();
    }/* else */
  }/* else */
}/* SysTick_Handler */
/* ************************************************************************************* */
void Systick_vidStop(void)
{
	 Systick_pstrRegisters->CTRL &= ~1U;
}
