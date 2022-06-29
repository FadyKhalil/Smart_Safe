/******************************************************************************
 *
 * Module: KEYPAD HAL Driver
 *
 * Layer : HAL
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad Driver
 *
 * Author: Osama Hamdy
 *
 *******************************************************************************/
#include "Std_types.h"
#ifndef KEYPAD_H_
#define KEYPAD_H_

/********************************************************************************************
 *                               Types Declaration                                          *
 ********************************************************************************************/

typedef enum{
	Keypad_NullPointerErr,
	Keypad_status_OK,
	Keypad_status_NOK,
	Keypad_NoValidatedVal,
}Keypad_tenuErrorStatus;


/*******************************************************************************
 *                            Fuction ProtoTypes                               *
 *******************************************************************************/

/*
 * Public Function
 * Description : Initialzation of keypad
 * Function Parameter : void
 * Function Return : void
 * */
void Keypad_vidInit(void);

/*
 * Public Function
 * Function Name :  Keypad_Task
 * Description : Get key pressed and Check on switches debouncing
 * Function return : void
 *----------------------
 */
extern void vidKeypad_Task(void);


/*
 *  Public Function
 *  Function Name :  Keypad_enuPressedKeyGetter
 *  Function Inputs: pointer to u32 variable to return the pressed key after checking on deouncing
 *  Function Description : check validation flag , then return value , else return status value not validated
 *  returns: Error status if any happens and OK if passed successfully.
 *  check---> Keypad_tenuErrorStatus
 *
 */
Keypad_tenuErrorStatus Keypad_enuPressedKeyGetter(pu8 Add_pu8PressedKey);

/*
 * Function Name:  Keypad_enuGetKeyPressed
 *
 * Function Inputs: pointer to u32 variable to return the pressed key in.
 *
 * Function Description : iterate on each row and col to get which key is pressed.
 *
 *  returns: Error status if any happens and OK if passed successfully.
 *  check---> Keypad_tenuErrorStatus
 *
 */
Keypad_tenuErrorStatus Keypad_enuGetKeyPressed(pu32 Add_pu8PressedKKey);
#endif /* KEYPAD_H_ */
