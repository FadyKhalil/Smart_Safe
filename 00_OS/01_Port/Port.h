/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	May 27, 2022
**       Version     :	V01
**       SWC         :	Port
**       Description :	Port files
** **************************************************************************************/
#ifndef _PORT_H
#define _PORT_H
  /* //////////////////////////////////// Headers /////////////////////////////// */
  #include "Port_prv.h"
  /* /////////////////////////////////// MACROS ///////////////////////////////// */
  #define Port_vidDisableInterrupt()                        \
  {													                                \
    asm("MOV  R4, #0x50   ");					              		      \
    asm("MSR  BASEPRI, R4 ");					            		      \
  }     
  #define Port_vidEnableInterrupt()                         \
  {													                                \
    asm("MOV  R4, #0x00   ");							                  \
    asm("MSR  BASEPRI, R4 ");  						                  \
  }  
  /* Triggering PendSV */   
  #define Port_vidTaskSwitch()                              \
  { 												                        	      \
    SCB_pstrRegisters->ICSR |= PORT_u32SCB_PENDVS_SET_MASK; 	\
  }
  /* Triggering SVC */
  #define Port_vidStartFirstTask()                          \
  {                                                         \
    asm("svc 0");                                           \
  }
  /* //////////////////////////////////////////////////////////////////////////// */

  /* /////////////////////////////////// Interface Fns ///////////////////////////////// */
  /* 
    Description       :       Setup the systick timer
    Parameters        :       void
    Return            :       void
  */
  void Port_vidSystickSetup(void);
  /* //////////////////////////////////////////////////////////////////////////// */

  /* /////////////////////////////////// ISRs ///////////////////////////////// */
  void PendSV_Handler(void) __attribute__((naked));
  void SVC_Handler(void) __attribute__((naked));
  /* //////////////////////////////////////////////////////////////////////////// */

#endif
