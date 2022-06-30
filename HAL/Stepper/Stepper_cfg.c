/*
 * Stepper_cfg.c
 *
 *  Created on: jun 6, 2022
 *      Author: Ahmed-Yehia
 */

#include "Stepper.h"
#include "Stepper_cfg.h"
#include "../GPIO/GPIO.h"

const StepperCfg_t Stepper_Pins_cfg[] = {
    [STEPPER_A_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_7
    },
    [STEPPER_B_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_0
    },
    [STEPPER_C_PIN] = {
        .port = GPIO_PORT_C,
        .pin = GPIO_PIN_6
    },
    [STEPPER_D_PIN] = {
        .port = GPIO_PORT_C,
        .pin = GPIO_PIN_1
    },
};
