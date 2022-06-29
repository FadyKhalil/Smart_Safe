/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	NVIC
**       Description :	NVIC module files
** **************************************************************************************/
#ifndef _NVIC_H
#define _NVIC_H
  /* ****************************** MACROS ************************************************ */
  /* Active flag status */
  #define NVIC_u8NOT_ACTIVE                             0
  #define NVIC_u8ACTIVE                                 1
  /* ************************************************************************************** */
  /* ****************************** Defined Types ***************************************** */
  /* peripherals IRQ numbers */
  typedef enum
  { 
    NVIC_enuWWDG = 0,
    NVIC_enuEXTI0 = 6,
    NVIC_enuDMA1_S0 = 11,
    NVIC_enuADC = 18,
    NVIC_enuUSART1 = 37
  }NVIC_tenuIRQn;
  /* Error type */
  typedef enum
  {
    NVIC_enuOk,
    NVIC_enuNok
  }NVIC_tenuError;
  /* ************************************************************************************** */
  /* ***************************** Interface Fns ****************************************** */
  /* 
    Fn          :         Enable specific Interrupt
    Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
    Return      :         The error status, options are in "NVIC.h" under "Error type"
  */
  NVIC_tenuError NVIC_enuEnableIRQ(NVIC_tenuIRQn Copy_enuIRQn);
  /* 
    Fn          :         Disable specific Interrupt
    Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
    Return      :         The error status, options are in "NVIC.h" under "Error type"
  */
  NVIC_tenuError NVIC_enuDisableIRQ(NVIC_tenuIRQn Copy_enuIRQn);
  /* 
    Fn          :         Set pending flag for specific Interrupt
    Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
    Return      :         The error status, options are in "NVIC.h" under "Error type"
  */
  NVIC_tenuError NVIC_enuSetPendingIRQ(NVIC_tenuIRQn Copy_enuIRQn);
  /* 
    Fn          :         clear pending flag for specific Interrupt
    Parameter   :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
    Return      :         The error status, options are in "NVIC.h" under "Error type"
  */
  NVIC_tenuError NVIC_enuClearPendingIRQ(NVIC_tenuIRQn Copy_enuIRQn);
  /* 
    Fn          :         Get the active flag status for specific Interrupt
    Parameter1   :        The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
    Parameter2   :        Pointer to receive the active flag status, options are in "NVIC.h" under "Active flag status"
    Return      :         The error status, options are in "NVIC.h" under "Error type"
  */
  NVIC_tenuError NVIC_enuGetActiveStateIRQ(NVIC_tenuIRQn Copy_enuIRQn, pu8 Copy_pu8ActiveFlag);
  /* 
    Fn          :         Encode the given priority
    Parameter1  :         The group priority, options are in "NVIC_cfg.h" under "group priority options"
    Parameter2  :         The subgroup priority, options are in "NVIC_cfg.h" under "subgroup priority options"
    Parameter3   :        Pointer to receive the encoded priority
    Return      :         The error status, options are in "NVIC.h" under "Error type"
    **Caution** :         The priority binary point in the register "SCB->AIRCR" must be configured
  */
  NVIC_tenuError NVIC_enuEncodePriority(u8 Copy_u8GroupPri, u8 Copy_u8SubgroupPri, pu8 Copy_pu8Priority);
  /* 
    Fn          :         set the priority for specific Interrupt
    Parameter1  :         The IRQ number, options are in "NVIC.h" under "peripherals IRQ numbers"
    Parameter2  :         The priority to set, use the output of the fn "NVIC_enuEncodePriority"
    Return      :         The error status, options are in "NVIC.h" under "Error type"
    **Caution** :         The priority binary point in the register "SCB->AIRCR" must be configured
  */
  NVIC_tenuError NVIC_enuSetPriorityIRQ(NVIC_tenuIRQn Copy_enuIRQn, pu8 Copy_pu8Priority);
  /* 
    Fn          :         Enable IRQs
    Parameters  :         void
    Return      :         void
  */
  void NVIC_enuEnableIRQs(void);
  /* 
    Fn          :         Disable IRQs
    Parameters  :         void
    Return      :         void
  */
  void NVIC_enuDisableIRQs(void);
  /* 
    Fn          :         Enable Faults
    Parameters  :         void
    Return      :         void
  */
  void NVIC_enuEnableFaults(void);
  /* 
    Fn          :         Disable Faults
    Parameters  :         void
    Return      :         void
  */
  void NVIC_enuDisableFaults(void);

  /* ************************************************************************************** */


#endif