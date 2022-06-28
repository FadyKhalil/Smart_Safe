/*
 * lec_cfg.c
 *
 *  Created on: Mar 27, 2022
 *      Author: fady
 */

#include "../../MCAL/GPIO/Gpio.h"
#include "Led_cfg.h"
#include "Led.h"

const Led_tstrConfiguration Led_astrleds[LED_NUMBER] =
{
		[LED_ALARM] =
		{
			.Pin = GPIO_PIN02,
			.Active_states = LED_CLOSE,
			.Port = PORTA,
			.Otype = LED_OTYPE_PP,
			.Speed = LED_LOW_SPEED
		},


};
