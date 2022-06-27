/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	March 23, 2022
**       Version     :	V01
**       SWC         :	Systick
**       Description :	Systick timer module files
** **************************************************************************************/
#ifndef _SYSTICK_H
#define _SYSTICK_H
  /* ************************** Arguments MACROS  **************************************** */
  /* Timer Clk Sources */
  #define SYSTICK_u8AHB_OVER_8          0
  #define SYSTICK_u8AHB                 1 
  /* Timer Interrupt Activation */
  #define SYSTICK_u8OFF_INT             0
  #define SYSTICK_u8ON_INT              1
  /* ************************************************************************************* */
  /* *************************** Defined Types ******************************************* */
  /* callback fn pointer type */
  typedef void (*Systick_tpfCallback)(void);
  /* Error Type */
  typedef enum
  {
    Systick_enuOk,
    Systick_enuNok
  }Systick_tenuError;
  /* ************************************************************************************* */
  /* ************************** Interface Fns Headers ************************************ */
  /* 
    Fn           :     Init the systick timer
    Parameter1   :     The Source clk, options are in "Systick.h" under "Timer Clk Sources" 
    Parameter2   :     Interrupt Activation, options are in "Systick.h" under "Timer Interrupt Activation" 
    Return       :     The status error, options are in "Systick.h" under "Error Type" 
  */
  extern Systick_tenuError Systick_enuInit(u8 Copy_u8TimerSrc, u8 Copy_u8IntActivation);
  /* 
    Fn           :     Start timer with specific delay
    Parameter    :     The delay time in milliseconds
    Return       :     The status error, options are in "Systick.h" under "Error Type" 
  */  
  extern Systick_tenuError Systick_enuSetTickTimeMS(u32 Copy_u32Time_MS);
  /* 
    Fn           :     Start timer
    **caution**  :     You should set the tick time before using the "Systick_enuSetTickTimeMS" fn in "Systick.h"
  */  
  extern void Systick_enuStart(void);
  /* 
    Fn         :   Register the callback fn
    Parameter1 :   Address of the callback fn
    Return     :   Error status of the fn, Error type is in "Systick.h" under "Error Type"
  */
  extern Systick_tenuError Systick_vidRegCallbackFn(Systick_tpfCallback Copy_pfCallback);
  /* ************************************************************************************* */

#endif
