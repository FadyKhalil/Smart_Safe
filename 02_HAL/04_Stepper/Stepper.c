/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Stepper
**       Description :	Stepper module files
** **************************************************************************************/
/* ////////////////////////////// Headers inclusion /////////////////////////////////////// */
/* LIB headers */
#include "StdTypes.h"
#include "Core.h"
/* MCAL headers */
#include "Gpio.h"
/* Own headers */
#include "Stepper.h"
#include "Stepper_cfg.h"
#include "Stepper_Lcfg.h"
#include "Stepper_prv.h"
/* ////////////////////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////// Interface Fns ///////////////////////////////////// */
/* 
  Description       :       Init the stepper
  Parameter         :       void
  return            :       void
  *********** Synchronous ***********
*/  
void Stepper_vidInit(void)
{
	static volatile u8 Loc_u8Counter = ZERO_INIT;
	static volatile GPIO_tstrPinConfiguration Loc_strConfigurator;
  for(Loc_u8Counter = ZERO_INIT; Loc_u8Counter < STEPPER_u8NUM_OF_STEPPERS; Loc_u8Counter++)
  {
    Loc_strConfigurator.GPIO_Port = Stepper_astrStepper[Loc_u8Counter].pvidPort;
    Loc_strConfigurator.GPIO_Pin= Stepper_astrStepper[Loc_u8Counter].u16PinA;
    Loc_strConfigurator.GPIO_Mode = GPIO_u8OUTPUT_PUSHPULL;
    Loc_strConfigurator.GPIO_Speed = GPIO_Speed_High;
    Gpio_enuPinConfigurationInit((GPIO_tstrPinConfiguration*)&Loc_strConfigurator);
    Loc_strConfigurator.GPIO_Port = Stepper_astrStepper[Loc_u8Counter].pvidPort;
    Loc_strConfigurator.GPIO_Pin= Stepper_astrStepper[Loc_u8Counter].u16PinB;
    Loc_strConfigurator.GPIO_Mode = GPIO_u8OUTPUT_PUSHPULL;
    Loc_strConfigurator.GPIO_Speed = GPIO_Speed_High;
    Gpio_enuPinConfigurationInit((GPIO_tstrPinConfiguration*)&Loc_strConfigurator);
    Loc_strConfigurator.GPIO_Port = GPIO_A;
    Loc_strConfigurator.GPIO_Pin= Stepper_astrStepper[Loc_u8Counter].u16PinC;
    Loc_strConfigurator.GPIO_Mode = GPIO_u8OUTPUT_PUSHPULL;
    Loc_strConfigurator.GPIO_Speed = GPIO_Speed_High;
    Gpio_enuPinConfigurationInit((GPIO_tstrPinConfiguration*)&Loc_strConfigurator);
    Loc_strConfigurator.GPIO_Port = GPIO_A;
    Loc_strConfigurator.GPIO_Pin= Stepper_astrStepper[Loc_u8Counter].u16PinD;
    Loc_strConfigurator.GPIO_Mode = GPIO_u8OUTPUT_PUSHPULL;
    Loc_strConfigurator.GPIO_Speed = GPIO_Speed_High;
    Gpio_enuPinConfigurationInit((GPIO_tstrPinConfiguration*)&Loc_strConfigurator);
  }/* for */
}/* Stepper_vidInit */
/* 
  Description       :       Set the Stepper Steps and change the state of the stepper
  Parameter1        :       The Stepper Id
  Parameter2        :       The Steps, range is from 0 to 255
  return            :       void
  *********** Synchronous ***********
*/  
void Stepper_vidSetStepperSteps(u8 Copy_u8StepperId, u16 Copy_u16Steps)
{
  if(Stepper_astrStepper[Copy_u8StepperId].Stepper_enuState == Stepper_enuState_Available)
  {
    Stepper_astrStepper[Copy_u8StepperId].Stepper_enuState = Stepper_enuState_Busy;
    Stepper_astrStepper[Copy_u8StepperId].u16Steps          = Copy_u16Steps;
  }/* if */
}/* Stepper_vidSetStepperSteps */
/* 
  Description       :       change the Stepper direction
  Parameter1        :       The Stepper Id
  Parameter2        :       The direction, options are in "Stepper.h" under "Direction"
  return            :       void
  *********** Synchronous ***********
*/  
void Stepper_vidSetDirection(u8 Copy_u8StepperId, Stepper_enuDirection_t Copy_enuDirection)
{
  Stepper_astrStepper[Copy_u8StepperId].Stepper_enuDirection = Copy_enuDirection;
}/* Stepper_vidSetDirection */
/* 
  Description       :       Get the Stepper State
  Parameter1        :       The Stepper Id
  return            :       The state, options are in "Stepper.h" under "Stepper States"
  *********** Synchronous ***********
*/  
Stepper_enuState_t Stepper_vidGetState(u8 Copy_u8StepperId)
{
	static volatile Stepper_enuState_t Loc_enuState = ZERO_INIT;
  Loc_enuState = Stepper_astrStepper[Copy_u8StepperId].Stepper_enuState;
  return(Loc_enuState);
}/* Stepper_vidGetState */
/* 
  Description       :       Set the stepper angle
  Parameter1        :       The Stepper Id
  return            :       void
  *********** Synchronous ***********
*/  
void Stepper_vidMoveAngle(u8 Copy_u8StepperId, u16 Copy_u16Angle)
{
  volatile u16 Loc_u16Steps = ((u32)Copy_u16Angle * STEPPER_u16REV_STEPS) / STEPPER_u16REV_DEGREES;
  Stepper_vidSetStepperSteps(Copy_u8StepperId, Loc_u16Steps);
}/* Stepper_vidGetState */
/* ///////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////// Runnable //////////////////////////////////// */
/* 
    Description     :       Task to master the stepper
    Parameter(s)    :       void
    Return          :       void
    /////////// Asynchronous ///////////
*/
void Stepper_vidMasterStepper_T(void)
{
	static volatile u8 Loc_u8Counter = ZERO_INIT;
	while(1)
  {
    Loc_u8Counter = ZERO_INIT;
    for(Loc_u8Counter = ZERO_INIT; Loc_u8Counter < STEPPER_u8NUM_OF_STEPPERS; Loc_u8Counter++)
    {
      if(Stepper_astrStepper[Loc_u8Counter].u16Steps != ZERO_INIT)
      {
        Gpio_enuSetPinValue(Stepper_astrStepper[Loc_u8Counter].pvidPort, Stepper_astrStepper[Loc_u8Counter].u16PinA, (Stepper_astrStepper[Loc_u8Counter].u8Pattern & STEPPER_u8FIRST_BIT ) >> STEPPER_u8ZERO_BIT );
        Gpio_enuSetPinValue(Stepper_astrStepper[Loc_u8Counter].pvidPort, Stepper_astrStepper[Loc_u8Counter].u16PinB, (Stepper_astrStepper[Loc_u8Counter].u8Pattern & STEPPER_u8SECOND_BIT) >> STEPPER_u8ONE_BIT  );
        Gpio_enuSetPinValue(GPIO_A, Stepper_astrStepper[Loc_u8Counter].u16PinC, (Stepper_astrStepper[Loc_u8Counter].u8Pattern & STEPPER_u8THIRD_BIT ) >> STEPPER_u8TWO_BIT  );
        Gpio_enuSetPinValue(GPIO_A, Stepper_astrStepper[Loc_u8Counter].u16PinD, (Stepper_astrStepper[Loc_u8Counter].u8Pattern & STEPPER_u8FOURTH_BIT) >> STEPPER_u8THREE_BIT);
        Stepper_astrStepper[Loc_u8Counter].u16Steps--;
        if(Stepper_astrStepper[Loc_u8Counter].Stepper_enuDirection == Stepper_enuDirection_CounterClockwise)
        {
          Stepper_astrStepper[Loc_u8Counter].u8Pattern = ((Stepper_astrStepper[Loc_u8Counter].u8Pattern << 1) | (Stepper_astrStepper[Loc_u8Counter].u8Pattern >> 3)) & STEPPER_u8HIGH_NIB_CLR;
        }/* if */
        else  /* Clockwise Direction */
        {
          Stepper_astrStepper[Loc_u8Counter].u8Pattern = ((Stepper_astrStepper[Loc_u8Counter].u8Pattern >> 1) | (Stepper_astrStepper[Loc_u8Counter].u8Pattern << 3)) & STEPPER_u8HIGH_NIB_CLR;
        }/* else */
        if(Stepper_astrStepper[Loc_u8Counter].u16Steps == ZERO_INIT)
        {
          Stepper_astrStepper[Loc_u8Counter].Stepper_enuState = Stepper_enuState_Available;
        }/* if */
      }/* if */    
    }/* for */
    OS_vidDelay(2);
  }/* while */
}/* Stepper_vidMasterStepper_R */
/* //////////