/*
 * Stepper_cfg.h
 *
 *  Created on: jun 6, 2022
 *      Author: Ahmed-Yehia
 */

#ifndef STEPPER_CFG_H_
#define STEPPER_CFG_H_

#include "Stepper.h"


typedef enum{
    STEPPER_A_PIN,
    STEPPER_B_PIN,
    STEPPER_C_PIN,
    STEPPER_D_PIN,
    STEPPER_NUMBER_OF_PINS
} Stepper_Pins;

typedef struct{
    void*       port;
    uint16_t    pin;
} StepperCfg_t;


#endif /* STEPPER_CFG_H_ */
