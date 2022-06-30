/*
 * Stepper.c
 *
 *  Created on: jun 6, 2022
 *      Author: Ahmed-Yehia
 */

#include "Stepper.h"
#include "Stepper_cfg.h"
#include "../GPIO/GPIO.h"

// externed from Stepper_cfg.c
extern const StepperCfg_t Stepper_Pins_cfg[];

// current shaft position
static uint8_t Shaft_position;

// Stepper_init function is used to initialize the Stepper module
// Args:    none
// Return:  none
// example:
//          Stepper_init();
void Stepper_init()
{
    gpioPinCfg_t configurator;
    for (uint8_t pinIndex = 0; pinIndex < STEPPER_NUMBER_OF_PINS; pinIndex++)
    {
        configurator.port = Stepper_Pins_cfg[pinIndex].port;
        configurator.pin = Stepper_Pins_cfg[pinIndex].pin;
        configurator.mode = GPIO_MODE_OUTPUT_PP;
        configurator.speed = GPIO_SPEED_HIGH;
        GPIO_initPin(&configurator);
    }
    Shaft_position = STEPPER_INIT_POSITION;
}

// Stepper_step function is used to move the Stepper motor shaft
//  1 step based on the provided direction
// Args:    (StepperDir_t) the direction that the stepper moves with
// Return:  (res_t) the status of the function call 
// example:
//          Stepper_init(clockwise);
res_t Stepper_step(StepperDir_t dir)
{
    res_t returnStatus = Status_Ok;
    switch (dir)
    {
    case clockwise:
    	Shaft_position = CircularRight(Shaft_position);
        break;

    case anticlockwise:
    	Shaft_position = CircularLeft(Shaft_position);
        break;
    
    default:
        returnStatus = Status_level_Error;
        break;
    }
    GPIO_writePin(Stepper_Pins_cfg[STEPPER_A_PIN].port, Stepper_Pins_cfg[STEPPER_A_PIN].pin, (Shaft_position>>0)&0b1);
    GPIO_writePin(Stepper_Pins_cfg[STEPPER_B_PIN].port, Stepper_Pins_cfg[STEPPER_B_PIN].pin, (Shaft_position>>1)&0b1);
    GPIO_writePin(Stepper_Pins_cfg[STEPPER_C_PIN].port, Stepper_Pins_cfg[STEPPER_C_PIN].pin, (Shaft_position>>2)&0b1);
    GPIO_writePin(Stepper_Pins_cfg[STEPPER_D_PIN].port, Stepper_Pins_cfg[STEPPER_D_PIN].pin, (Shaft_position>>3)&0b1);
    return returnStatus;
}

