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
			.PORT = PORTA,
			.Pin  = GPIO_PIN11
	},
	[1] = {
			.Mode = SWITCH_PUSHPULL,
			.PORT = PORTA,
			.Pin  = GPIO_PIN12
	},
	[2] = {
			.Mode = SWITCH_PUSHPULL,
			.PORT = PORTA,
			.Pin  = GPIO_PIN15
	},
	[3] = {
			.Mode = SWITCH_PUSHPULL,
			.PORT = PORTB,
			.Pin  = GPIO_PIN03
	}
};

Keypad_tsConfig Keypad_Config_Input[KEYPAD_u8COLUMN_COUNT] =
{
	[0] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN04
	},
	[1] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN05
	},
	[2] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN06
	},
	[3] = {
			.Mode = GPIO_u8INPUT_PULLDOWN,
			.PORT = PORTB,
			.Pin  = GPIO_PIN07
	}
};
