/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Keypad
**       Description :	Keypad module files
** **************************************************************************************/
#include "StdTypes.h"
#include "Gpio.h"
#include "Keypad.h"
#include "Keypad_cfg.h"
const Keypad_cfg_t Keypad_Pins[NUM_COLS + NUM_ROWS] =
	   {
			   [KEYPAD_ROW0] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN12
			   },

			   [KEYPAD_ROW1] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN13
			   },

			   [KEYPAD_ROW2] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN14
			   },

			   [KEYPAD_ROW3] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN15
			   },

			   [KEYPAD_COL0] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN05
			   },

			   [KEYPAD_COL1] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN07
			   },

			   [KEYPAD_COL2] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN08
			   },

			   [KEYPAD_COL3] =
			   {
					   .Keypad_Port = GPIO_B,
					   .Keypad_Pin = GPIO_PIN10
			   },
	   };



/*
 * Button indications
 */
/*Fill the 2D array with the button indication, what each button indicates what.*/

const u8 Keypad_aau8ButtonIndicator[NUM_ROWS][NUM_COLS] = {{'1', '2', '3', '+'},
														   {'4', '5', '6', '-'},
														   {'7', '8', '9', '*'},
														   {'%', '0', '=', '/'}};


