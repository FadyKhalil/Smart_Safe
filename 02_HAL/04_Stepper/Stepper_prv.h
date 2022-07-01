/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Stepper
**       Description :	Stepper module files
** **************************************************************************************/
#ifndef _STEPPER_PRV_H
#define _STEPPER_PRV_H
  /* /////////////////////// MACROS //////////////////////////// */
  /* Bits slicers */
  #define STEPPER_u8FIRST_BIT                   ((u8)(0x01))
  #define STEPPER_u8SECOND_BIT                  ((u8)(0x02))
  #define STEPPER_u8THIRD_BIT                   ((u8)(0x04))
  #define STEPPER_u8FOURTH_BIT                  ((u8)(0x08))
  /* High Nibble clear */
  #define STEPPER_u8HIGH_NIB_CLR                ((u8)(0x0F))
  /* Bits Shifters */
  #define STEPPER_u8ZERO_BIT                    ((u8)(0))
  #define STEPPER_u8ONE_BIT                     ((u8)(1))
  #define STEPPER_u8TWO_BIT                     ((u8)(2))
  #define STEPPER_u8THREE_BIT                   ((u8)(3))
  /* Revolution Values */
  /* 
    The stride angle = 5.625/64 ---> so to complete 360 degrees, you need 64 stride angle.
    To make the stride angle itself, you have to make: 
                                                      64 steps in half-step mode (Software choice)
                                                      32 steps in full-step mode (Software choice)
  */
  #define STEPPER_u16REV_STEPS                ((u16)(2048)) /* full-step mode needed steps to complete 360 degrees */
  #define STEPPER_u16REV_DEGREES              ((u16)(360))
  /* /////////////////////////////////////////////////////////// */
#endif