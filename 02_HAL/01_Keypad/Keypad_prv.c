/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Keypad
**       Description :	Keypad module files
** **************************************************************************************/
#include "StdTypes.h"
#include "Gpio.h"
#include "Core.h"
#include "Keypad.h"
#include "Keypad_prv.h"
#include "Keypad_cfg.h"

/*Keypad_u8PressedAvaliable is used as a flag for the Keypad_enuGetKey function*/
u8 Keypad_u8PressedAvaliable = 0;

/*Keypad_u8PressedKey is used to hold the pressed key value*/
u8 Keypad_u8PressedKey = 0;

/*Extern the keypad pins array*/
extern const Keypad_cfg_t Keypad_Pins[NUM_COLS + NUM_ROWS];

/*Extern the keypad buttons values array*/
extern const u8 Keypad_aau8ButtonIndicator[NUM_ROWS][NUM_COLS];

/*KeysState is used to save the states of each key*/
static u8 KeysState[NUM_COLS][NUM_ROWS];

/*
 * Function Implementation
 */
extern void Keypad_GetKeyValue_T(void)
{

	while(1){
		/*counter is used to hold the number of times the current status has come before*/
		static u8 counter[NUM_ROWS][NUM_COLS] = {0};

		/*prevVal is used to hold the previous status of the buttons*/
		static u8 prevVal[NUM_ROWS][NUM_COLS] = {0};

		/*currentVal is used to read the current status of each button*/
		u8 currentVal;

		/*Loc_u8ForItreatorRows is used to loop over the for loop for the rows*/
		u8 Loc_u8ForItreatorRows = 0;

		/*Loc_u8ForItreatorCols is used to loop over the for loop for the Columns*/
		u8 Loc_u8ForItreatorCols = 0;

		/*Loc_enuGpioErrorStatus is used to make sure the Gpio is done his job*/
		Gpio_tenuErrorStatus Loc_enuGpioErrorStatus = Gpio_enuOK;

		/*Loop over the rows set one by one to zero and read the columns*/
		for(Loc_u8ForItreatorRows = 0; Loc_u8ForItreatorRows < NUM_ROWS; Loc_u8ForItreatorRows++)
		{
			/*Set row number iterator to zero.*/
			Loc_enuGpioErrorStatus = Gpio_enuSetPinValue(Keypad_Pins[Loc_u8ForItreatorRows].Keypad_Port, Keypad_Pins[Loc_u8ForItreatorRows].Keypad_Pin, GPIO_u8LOW);

			/*Check the return of the Gpio function*/
			if(Loc_enuGpioErrorStatus == Gpio_enuOK)
			{
				/*Do Nothing*/
			}/*end of if(Loc_enuGpioErrorStatus == Gpio_enuOk)*/

			else
			{
				/*Error Handling.*/
			}/*end of else of if(Loc_enuGpioErrorStatus == Gpio_enuOk)*/


			/*Loop over the cols to check if any button is pressed*/
			for(Loc_u8ForItreatorCols = 0; Loc_u8ForItreatorCols < NUM_COLS; Loc_u8ForItreatorCols++)
			{
				/*Read the columns one by one to check if any is pressed*/
				Loc_enuGpioErrorStatus = Gpio_enuGetPinValue(Keypad_Pins[Loc_u8ForItreatorCols + NUM_ROWS].Keypad_Port, Keypad_Pins[Loc_u8ForItreatorCols + NUM_ROWS].Keypad_Pin, &currentVal);

				/*Check the return of the Gpio function*/
				if(Loc_enuGpioErrorStatus == Gpio_enuOK)
				{
					/*Do Nothing*/
				}/*end of if(Loc_enuGpioErrorStatus == Gpio_enuOk)*/

				else
				{
					/*Error Handling.*/
				}/*end of else of if(Loc_enuGpioErrorStatus == Gpio_enuOk)*/

				/*Check if the current value is equal to the previous value*/
				if(currentVal == prevVal[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols])
				{
					/*Increase the counter value to indicate how many times this state came before*/
					counter[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols]++;
				}/*end of if(currentVal == prevVal[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols])*/
				else
				{
					/*Set the counter to indicate that this state is the first time to appear*/
					counter[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols] = 0;
				}/*end of else of if(currentVal == prevVal[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols])*/

				/*Check if the counter value is 5 change the button state in the key array*/
				if(counter[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols] == 5)
				{
					/*Change the button state in the array with the current state*/
					KeysState[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols] = currentVal;

					/*Check if the current state is zero which means pressed save it in the flags*/
					if(currentVal == GPIO_u8LOW)
					{
						/*Raise the flag of a key is pressed.*/
						Keypad_u8PressedAvaliable = 1;

						/*Save the pressed key into the Keypad_u8PressedKey variable.*/
						Keypad_u8PressedKey = Keypad_aau8ButtonIndicator[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols];

					}/*end of if(currentVal == Gpio_Pin_Value_Off)*/
					else
					{
						/*Do Nothing*/
					}/*end of else of if(currentVal == Gpio_Pin_Value_Off)*/

				}/*end of if(counter[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols] == FIVE)*/
				else
				{
					/*Do Nothing*/
				}/*end of else of if(counter[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols] == FIVE)*/

				/*Change the previous status with the current value to be remember it for the next time*/
				prevVal[Loc_u8ForItreatorRows][Loc_u8ForItreatorCols] = currentVal;

			}/*for(Loc_u8ForItreatorCols = 0; Loc_u8ForItreatorCols < NUM_COLS; Loc_u8ForItreatorCols++)*/

			/*Set the row back to one to disable this row*/
			Loc_enuGpioErrorStatus = Gpio_enuSetPinValue(Keypad_Pins[Loc_u8ForItreatorRows].Keypad_Port, Keypad_Pins[Loc_u8ForItreatorRows].Keypad_Pin, GPIO_u8HIGH);

			/*Check the return of the Gpio function*/
			if(Loc_enuGpioErrorStatus == Gpio_enuOK)
			{
				/*Do Nothing*/
			}/*end of if(Loc_enuGpioErrorStatus == Gpio_enuOk)*/

			else
			{
				/*Error HAndling*/
			}/*end of else of if(Loc_enuGpioErrorStatus == Gpio_enuOk)*/

		}/*end of for(Loc_u8ForItreatorRows = 0; Loc_u8ForItreatorRows < NUM_ROWS; Loc_u8ForItreatorRows++)*/

	OS_vidDelay(5);

	}

}

