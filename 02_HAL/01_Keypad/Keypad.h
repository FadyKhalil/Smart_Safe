/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Keypad
**       Description :	Keypad module files
** **************************************************************************************/
#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include  "Keypad_prv.h"

/*
 * Error type
 */

typedef enum
{
	Keypad_enuOk,
	Keypad_enuNotOk,
	Keypad_enuNullPointer,
}Keypad_tenuErrorStatus;

/*
 * Configuration type
 */
typedef struct
{
	void * Keypad_Port;
	u16 Keypad_Pin;

}Keypad_cfg_t;

/*
 * Interfacing functions prototype
 */

/*
 * Keypad_enuInit is used to initialize the keypad pins
 *
 * Inputs: It takes no input.
 *
 * Return: it returns the error status of the function with the following possibilities:
 *							1- Keypad_enuOk, if the initialization of the pins is done correctly.
 *							2- Keypad_enunNotOk, if any pin returns error from the GPIO.
 */
extern Keypad_tenuErrorStatus Keypad_enuInit();


/*
 * Keypad_enuGetKey is used to check if any button is pressed.
 *
 * Inputs: It takes one input, an address to get the data in it.
 *
 * Return: it returns the error status of the function with the following possibilities:
 *							1- Keypad_enuOk, a key is pressed and the value is in the pointer.
 *							2- Keypad_enunNotOk, no key is pressed.
 *							3- Keypad_enuNullPointer, if the pointer is pointing to null.
 */
extern Keypad_tenuErrorStatus  Keypad_u8GetPressedKey(pu8 Add_pu8PressedKey);




#endif /* HAL_KEYPAD_KEYPAD_H_ */
