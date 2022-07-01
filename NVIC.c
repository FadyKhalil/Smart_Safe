/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	NVIC
**       Description :	NVIC module files
** **************************************************************************************/
/* **************************** Inclusion part ****************************************** */
/* LIB headers */
#include "StdTypes.h"
#include "STM32F401CC.h"
/* Own headers */
#include "NVIC.h"
#include "NVIC_cfg.h"
#include "NVIC_prv.h"
/* ************************************************************************************** */
/* ******************************* Interface Fns **************************************** */
/* 
  Fn          :         Enable specific Interrupt
  Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
  Return      :         The error status, options are in "NVIC.h" under "Error type"
*/
NVIC_tenuError NVIC_enuEnableIRQ(NVIC_tenuIRQn Copy_enuIRQn)
{
  NVIC_tenuError Loc_enuError = NVIC_enuOk;
  if(Copy_enuIRQn > NVIC_u8EXT_PER_LIMIT)
  {
    Loc_enuError = NVIC_enuNok;
  }/* if */
  else
  {
    NVIC_strRegisters->ISER[Copy_enuIRQn/NVIC_u8REG_SIZE] |= (1<<(Copy_enuIRQn%NVIC_u8REG_SIZE));
  }/* else */

  return(Loc_enuError);
}/* NVIC_enuEnableIRQ */
/* 
  Fn          :         Disable specific Interrupt
  Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
  Return      :         The error status, options are in "NVIC.h" under "Error type"
*/
NVIC_tenuError NVIC_enuDisableIRQ(NVIC_tenuIRQn Copy_enuIRQn)
{
  NVIC_tenuError Loc_enuError = NVIC_enuOk;
  if(Copy_enuIRQn > NVIC_u8EXT_PER_LIMIT)
  {
    Loc_enuError = NVIC_enuNok;
  }/* if */
  else
  {
    NVIC_strRegisters->ICER[Copy_enuIRQn/NVIC_u8REG_SIZE] |= (1<<(Copy_enuIRQn%NVIC_u8REG_SIZE));
  }/* else */

  return(Loc_enuError);
}/* NVIC_enuDisableIRQ */
/* 
  Fn          :         Set pending flag for specific Interrupt
  Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
  Return      :         The error status, options are in "NVIC.h" under "Error type"
*/
NVIC_tenuError NVIC_enuSetPendingIRQ(NVIC_tenuIRQn Copy_enuIRQn)
{
  NVIC_tenuError Loc_enuError = NVIC_enuOk;
  if(Copy_enuIRQn > NVIC_u8EXT_PER_LIMIT)
  {
    Loc_enuError = NVIC_enuNok;
  }/* if */
  else
  {
    NVIC_strRegisters->ISPR[Copy_enuIRQn/NVIC_u8REG_SIZE] |= (1<<(Copy_enuIRQn%NVIC_u8REG_SIZE));
  }/* else */

  return(Loc_enuError);  
}/* NVIC_enuSetPendingIRQ */
/* 
  Fn          :         clear pending flag for specific Interrupt
  Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
  Return      :         The error status, options are in "NVIC.h" under "Error type"
*/
NVIC_tenuError NVIC_enuClearPendingIRQ(NVIC_tenuIRQn Copy_enuIRQn)
{
  NVIC_tenuError Loc_enuError = NVIC_enuOk;
  if(Copy_enuIRQn > NVIC_u8EXT_PER_LIMIT)
  {
    Loc_enuError = NVIC_enuNok;
  }/* if */
  else
  {
    NVIC_strRegisters->ICPR[Copy_enuIRQn/NVIC_u8REG_SIZE] |= (1<<(Copy_enuIRQn%NVIC_u8REG_SIZE));
  }/* else */

  return(Loc_enuError);  
}/* NVIC_enuClearPendingIRQ */
/* 
  Fn          :         Get the active flag status for specific Interrupt
  Parameter1   :        The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
  Parameter2   :        Pointer to receive the active flag status, options are in "NVIC.h" under "Active flag status"
  Return      :         The error status, options are in "NVIC.h" under "Error type"
*/
NVIC_tenuError NVIC_enuGetActiveStateIRQ(NVIC_tenuIRQn Copy_enuIRQn, pu8 Copy_pu8ActiveFlag)
{
  u8 Loc_u8ActiveFlag;
  NVIC_tenuError Loc_enuError = NVIC_enuOk;
  if(Copy_enuIRQn > NVIC_u8EXT_PER_LIMIT)
  {
    Loc_enuError = NVIC_enuNok;
  }/* if */
  else
  {
    Loc_u8ActiveFlag = NVIC_strRegisters->ICPR[Copy_enuIRQn/NVIC_u8REG_SIZE] & (1<<(Copy_enuIRQn%NVIC_u8REG_SIZE));
    if(Loc_u8ActiveFlag)
    {
      *Copy_pu8ActiveFlag = NVIC_u8ACTIVE;
    }/* if */
    else
    {
      *Copy_pu8ActiveFlag = NVIC_u8NOT_ACTIVE;
    }/* else */
  }/* else */

  return(Loc_enuError);  
}/* NVIC_enuGetActiveStateIRQ */
/* 
  Fn          :         Encode the given priority
  Parameter1  :         The group priority, options are in "NVIC_cfg.h" under "group priority options"
  Parameter2  :         The subgroup priority, options are in "NVIC_cfg.h" under "subgroup priority options"
  Parameter3   :        Pointer to receive the encoded priority
  Return      :         The error status, options are in "NVIC.h" under "Error type"
  **Caution** :         The priority binary point in the register "SCB->AIRCR" must be configured
*/
NVIC_tenuError NVIC_enuEncodePriority(u8 Copy_u8GroupPri, u8 Copy_u8SubgroupPri, pu8 Copy_pu8Priority)
{
  NVIC_tenuError Loc_enuError = NVIC_enuOk;
  if(!Copy_pu8Priority)
  {
    Loc_enuError = NVIC_enuNok;
  }/* if */
  else
  {
    if(NVIC_u8G_LVLS == NVIC_u8_16_LVL)
    {
      *Copy_pu8Priority = (Copy_u8GroupPri<<NVIC_u8_SHIFT_4);
    }/* if */
    else if(NVIC_u8G_LVLS == NVIC_u8_8_LVL)
    {
      *Copy_pu8Priority = (Copy_u8GroupPri<<NVIC_u8_SHIFT_5) | (Copy_u8SubgroupPri<<NVIC_u8_SHIFT_4);
    }/* else if */
    else if(NVIC_u8G_LVLS == NVIC_u8_4_LVL)
    {
      *Copy_pu8Priority = (Copy_u8GroupPri<<NVIC_u8_SHIFT_6) | (Copy_u8SubgroupPri<<NVIC_u8_SHIFT_4);
    }/* else if */
    else if(NVIC_u8G_LVLS == NVIC_u8_2_LVL)
    {
      *Copy_pu8Priority = (Copy_u8GroupPri<<NVIC_u8_SHIFT_7) | (Copy_u8SubgroupPri<<NVIC_u8_SHIFT_4);
    }/* else if */ 
    else
    {
      Loc_enuError = NVIC_enuNok;
    }/* else */
  }/* else */

  return(Loc_enuError);  
}/* NVIC_enuEncodePriority */
/* 
  Fn          :         set the priority for specific Interrupt
  Parameter1  :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
  Parameter2  :         The priority to set, use the output of the fn "NVIC_enuEncodePriority"
  Return      :         The error status, options are in "NVIC.h" under "Error type"
  **Caution** :         The priority binary point in the register "SCB->AIRCR" must be configured
*/
NVIC_tenuError NVIC_enuSetPriorityIRQ(NVIC_tenuIRQn Copy_enuIRQn, pu8 Copy_pu8Priority)
{
  NVIC_tenuError Loc_enuError = NVIC_enuOk;
  if((!Copy_pu8Priority) || (Copy_enuIRQn > NVIC_u8EXT_PER_LIMIT)) /* Arguments Validation */
  {
    Loc_enuError = NVIC_enuNok;
  }/* if */
  else
  {
    NVIC_strRegisters->IPR[Copy_enuIRQn] = *Copy_pu8Priority;
  }/* else */

  return(Loc_enuError);  
}/* NVIC_enuSetPriorityIRQ */
/* 
  Fn          :         Enable IRQs
  Parameters  :         void
  Return      :         void
*/
void NVIC_enuEnableIRQs(void)
{
  asm("CPSIE i"); /* Enable interrupts and configurable fault handlers(clear PRIMASK)  */
}/* NVIC_enuEnableIRQs */
/* 
  Fn          :         Disable IRQs
  Parameters  :         void
  Return      :         void
*/
void NVIC_enuDisableIRQs(void)
{
  asm("CPSID i"); /* Disable interrupts and configurable fault handlers (set PRIMASK)  */

}/* NVIC_enuDisableIRQs */
/* 
  Fn          :         Enable Faults
  Parameters  :         void
  Return      :         void
*/
void NVIC_enuEnableFaults(void)
{
  asm("CPSIE f");   /* Enable interrupts and fault handlers (clear FAULTMASK) */
}/* NVIC_enuEnableFaults */
/* 
  Fn          :         Disable Faults
  Parameters  :         void
  Return      :         void
*/
void NVIC_enuDisableFaults(void)
{
  asm("CPSID f"); /* Disable interrupts and all fault handlers (set FAULTMASK)  */
}/* NVIC_enuDisableFaults */
/* ************************************************************************************** */