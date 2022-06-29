/*
 * Keypad.c
 *
 *  Created on: Apr 14, 2022
 *      Author:
 */

#include "StdTypes.h"
#include "Gpio.h"
#include "Keypad.h"
#include "Keypad_prv.h"
#include "Keypad_cfg.h"


/*Extern the keypad pins*/
extern const Keypad_cfg_t Keypad_Pins[NUM_COLS + NUM_ROWS];

/*Keypad_u8PressedAvaliable is used as a flag for the Keypad_enuGetKey function*/
extern u8 Keypad_u8PressedAvaliable;

/*Keypad_u8PressedKey is used to hold the pressed key value*/
extern u8 Keypad_u8PressedKey;


/*
 * Function implementation
 */

extern Keypad_tenuErrorStatus Keypad_enuInit()
{
	/*Loc_enuReturnStatus is used to hold the error status of the function*/
	Keypad_tenuErrorStatus Loc_enuReturnStatus = Keypad_enuOk;

	/*Loc_u8ForCounter is used as a counter for the for loop.*/
	u8 Loc_u8ForCounter = 0;

	/*Loc_enuGpioConfig is used to configure the pins of the keypad*/
	GPIO_tstrPinConfiguration Loc_enuGpioConfig;

	/*Loc_enuGpioErrorStatus is used to check the initialization of the pins.*/
	Gpio_tenuErrorStatus Loc_enuGpioErrorStatus = Gpio_enuOK;


	/*Initialize the row pins as output*/
	for(Loc_u8ForCounter = 0; Loc_u8ForCounter < NUM_ROWS; Loc_u8ForCounter++)
	{
		/*Set the row pins to be output with high speed*/
		Loc_enuGpioConfig.GPIO_Mode = GPIO_u8OUTPUT_PUSHPULL;
		Loc_enuGpioConfig.GPIO_Speed = GPIO_Speed_Medium;

		Loc_enuGpioConfig.GPIO_Port = Keypad_Pins[Loc_u8ForCounter].Keypad_Port;
		Loc_enuGpioConfig.GPIO_Pin = Keypad_Pins[Loc_u8ForCounter].Keypad_Pin;

		/*Initialize the pin*/
		Loc_enuGpioErrorStatus = Gpio_enuPinConfigurationInit(&Loc_enuGpioConfig);

		/*Check the error status of the gpio_init function*/
		if(Loc_enuGpioErrorStatus != Gpio_enuOK)
		{
			/*Set Keypad_enuNotOk to Loc_enuReturnStatus as the the function called initialize the pin.*/
			Loc_enuReturnStatus = Keypad_enuNotOk;
		}/*end of if(Loc_enuGpioErrorStatus != Gpio_enuOk)*/
		else
		{
			/*Do nothing*/
		}/*end of else of if(Loc_enuGpioErrorStatus != Gpio_enuOk)*/


	}/*end of for(Loc_u8ForCounter = ZERO; Loc_u8ForCounter < NUM_ROWS; Loc_u8ForCounter++)*/

	/*Initialize the column pins as input*/
	for(Loc_u8ForCounter = NUM_ROWS; Loc_u8ForCounter < (NUM_COLS + NUM_ROWS); Loc_u8ForCounter++)
	{
		/*Set the row pins to be input pull up with high speed*/
		Loc_enuGpioConfig.GPIO_Mode = GPIO_u8INPUT_PULLUP;
		Loc_enuGpioConfig.GPIO_Speed = GPIO_Speed_Medium;

		Loc_enuGpioConfig.GPIO_Port = Keypad_Pins[Loc_u8ForCounter].Keypad_Port;
		Loc_enuGpioConfig.GPIO_Pin = Keypad_Pins[Loc_u8ForCounter].Keypad_Pin;

		/*Initialize the pin*/
		Loc_enuGpioErrorStatus = Gpio_enuPinConfigurationInit(&Loc_enuGpioConfig);

		/*Check the error status of the gpio_init function*/
		if(Loc_enuGpioErrorStatus != Gpio_enuOK)
		{
			/*Set Keypad_enuNotOk to Loc_enuReturnStatus as the the function called initialize the pin.*/
			Loc_enuReturnStatus = Keypad_enuNotOk;
		}/*end of if(Loc_enuGpioErrorStatus != Gpio_enuOk)*/
		else
		{
			/*Do nothing*/
		}/*end of else of if(Loc_enuGpioErrorStatus != Gpio_enuOk)*/


	}/*end of for(Loc_u8ForCounter = NUM_ROWS; Loc_u8ForCounter < (NUM_COLS + NUM_ROWS); Loc_u8ForCounter++)*/

	/*Return the error status to the caller*/
	return Loc_enuReturnStatus;
}


extern Keypad_tenuErrorStatus  Keypad_u8GetPressedKey(pu8 Add_pu8PressedKey)
{
	/*Loc_enuReturnStatus is used to hold the error status of the function*/
	Keypad_tenuErrorStatus Loc_enuReturnStatus = Keypad_enuOk;

	if(Keypad_u8PressedAvaliable == 1)
	{
		/*Check if the pointer is pointing to null*/
		if(Add_pu8PressedKey == NULL)
		{
			/*Set Keypad_enuNullPointer to Loc_enuReturnStatus as the pointer is pointing to null.*/
			Loc_enuReturnStatus = Keypad_enuNullPointer;

		}/*end of if(Add_pu8PressedKey == NULL)*/
		else
		{
			/*Save the value of the pressed key into the pointer.*/
			*Add_pu8PressedKey = Keypad_u8PressedKey;

			/*Clear the flag that indicates a pressed key.*/
			Keypad_u8PressedAvaliable = 0;

		}/*end of else of if(Add_pu8PressedKey == NULL)*/

	}/*end of if(Keypad_u8PressedAvaliable == ONE)*/
	else
	{
		/*Set s to Loc_enuReturnStatus as now key has been pressed.*/
		Loc_enuReturnStatus = Keypad_enuNotOk;

	}/*end of else of if(Keypad_u8PressedAvaliable == ONE)*/

	/*Return the error status to the caller*/
	return Loc_enuReturnStatus;
}

