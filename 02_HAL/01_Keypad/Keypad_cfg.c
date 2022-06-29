/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Keypad
**       Description :	Keypad module files 
** **************************************************************************************/
#include "Gpio.h"
#include "Keypad.h"
#include "Keypad_cfg.h"

Keypad_tsConfig Keypad_Config_Ouput[KEYPAD_u8ROW_COUNT] =
{
	[0] = {
			.Mode = SWITCH_PUSHPULL,
			.PORT = PORTB,
			.Pin  = GPIO_PIN12
	},
	[1] = {
			.Mode = SWITCH_PUSHPULL,
			.PORT = PORTB,
			.Pin  = GPIO_PIN13
	},
	[2] = {
			.Mode = SWITCH_PUSHPULL,
			.PORT = PORTB,
			.Pin  = GPIO_PIN14
	},
	[3] = {
			.Mode = SWITCH_PUSHPULL,
			.PORT = PORTB,
			.Pin  = GPIO_PIN15
	}
};

Keypad_tsConfig Keypad_Config_Input[KEYPAD_u8COLUMN_COUNT] =
{
	[0] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN05
	},
	[1] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN07
	},
	[2] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN08
	},
	[3] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN10
	}
};