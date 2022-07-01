/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Stepper
**       Description :	Stepper module files
** **************************************************************************************/
#ifndef _STEPPER_H
#define _STEPPER_H
  /* //////////////////////////// Headers inclusion ////////////////////////////////// */
  #include "Stepper_cfg.h"
  /* ///////////////////////////////////////////////////////////////////////////////// */

  /* //////////////////////////// MACROS ///////////////////////////////////////////// */
  #define STEPPER_u8START_PATTERN                            ((u8)(0x01))
  /* ///////////////////////////////////////////////////////////////////////////////// */

  /* //////////////////////////// Defined types ////////////////////////////////////// */
  /* Direction */  
  typedef enum
  {
    Stepper_enuDirection_CounterClockwise,  
    Stepper_enuDirection_Clockwise
  }Stepper_enuDirection_t;
  /* Stepper States */
  typedef enum
  {
    Stepper_enuState_Available, 
    Stepper_enuState_Busy
  }Stepper_enuState_t;   
  /* Stepper Structure */
  typedef struct
  {
    Stepper_enuState_t     Stepper_enuState;      /* The stepper state, Initialize it by "Stepper_enuState_Available" */
    Stepper_enuDirection_t Stepper_enuDirection;  /* The stepper direction, options are in "Stepper.h" under "Direction" */
    void*                  pvidPort;               /* Set the Port, options are in "Gpio.h" */
    u16                    u16PinA;                /* Set the Connection Pins, options are in "Gpio.h" */
    u16                    u16PinB;                /* Set the Connection Pins, options are in "Gpio.h" */
    u16                    u16PinC;                /* Set the Connection Pins, options are in "Gpio.h" */
    u16                    u16PinD;                /* Set the Connection Pins, options are in "Gpio.h" */
    u16                    u16Steps;               /* Initialize it by "ZERO_INIT" */
    u8                     u8Pattern;             /* Initialize it by "STEPPER_u8START_PATTERN" */
  }Stepper_strConfig_t;
  /* ///////////////////////////////////////////////////////////////////////////////// */

  /* ///////////////////////////// Interface Fns ///////////////////////////////////// */
  /* 
    Description       :       Init the stepper
    Parameter         :       void
    return            :       void
    *********** Synchronous ***********
  */  
  void Stepper_vidInit(void);
  /* 
    Description       :       Set the Stepper Steps and change the state of the stepper
    Parameter1        :       The Stepper Id
    Parameter2        :       The Steps, range is from 0 to 255
    return            :       void
    *********** Synchronous ***********
  */  
  void Stepper_vidSetStepperSteps(u8 Copy_u8StepperId, u16 Copy_u16Steps);
  /* 
    Description       :       change the Stepper direction
    Parameter1        :       The Stepper Id
    Parameter2        :       The direction, options are in "Stepper.h" under "Direction"
    return            :       void
    *********** Synchronous ***********
  */  
  void Stepper_vidSetDirection(u8 Copy_u8StepperId, Stepper_enuDirection_t Copy_enuDirection);
  /* 
    Description       :       Get the Stepper State
    Parameter1        :       The Stepper Id
    return            :       The state, options are in "Stepper.h" under "Stepper States"
    *********** Synchronous ***********
  */  
  Stepper_enuState_t Stepper_vidGetState(u8 Copy_u8StepperId);
  /* 
    Description       :       Set the stepper angle
    Parameter1        :       The Stepper Id
    return            :       void
    *********** Synchronous ***********
  */  
  void Stepper_vidMoveAngle(u8 Copy_u8StepperId, u16 Copy_u16Angle);
  /* ///////////////////////////////////////////////////////////////////////////////// */
  
  /* /////////////////////////////////// Runnable //////////////////////////////////// */
  /* 
      Description     :       Runnable to master the stepper
      Parameter(s)    :       void
      Return          :       void
      /////////// Asynchronous ///////////
  */
  void Stepper_vidMasterStepper_T(void);
  /* ///////////////////////////////////////////////////////////////////////////////// */

#endif
