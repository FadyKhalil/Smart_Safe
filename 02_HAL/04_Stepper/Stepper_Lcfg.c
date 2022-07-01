/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Stepper
**       Description :	Stepper module files
** **************************************************************************************/
/* /////////////////////////// Headers inclusion ////////////////////////////////////// */
/* STD headers */
#include "StdTypes.h"
/* MCAL headers */
#include "Gpio.h"
/* Own headers */
#include "Stepper.h"
#include "Stepper_cfg.h"
/* //////////////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////// Global Section ///////////////////////////////////////////// */
volatile Stepper_strConfig_t Stepper_astrStepper[] =
{
  [STEPPER_u8STEPPER0] =
  {
    .Stepper_enuState     = Stepper_enuState_Available,
    .Stepper_enuDirection = Stepper_enuDirection_Clockwise,
    .pvidPort             = GPIO_B,
    .u16PinA              = GPIO_PIN01,
    .u16PinB              = GPIO_PIN02, 
    .u16PinC              = GPIO_PIN09,
    .u16PinD              = GPIO_PIN10,
    .u16Steps             = ZERO_INIT,
    .u8Pattern            = STEPPER_u8START_PATTERN
  }
};
/* //////////////////////////////////////////////////////////////////////////////////////