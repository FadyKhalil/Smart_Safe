/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Keypad
**       Description :	Keypad module files
** **************************************************************************************/
#ifndef HAL_KEYPAD_KEYPAD_PRV_H_
#define HAL_KEYPAD_KEYPAD_PRV_H_
/*
 * Keypad_Task is used to check the keypad each cyclic time to check if a button is pressed and save its value.
 *
 * Inputs: it takes no input.
 *
 * Return: It returns nothing.
 *
 */
extern void Keypad_GetKeyValue_T(void);

#endif /* HAL_KEYPAD_KEYPAD_PRV_H_ */
