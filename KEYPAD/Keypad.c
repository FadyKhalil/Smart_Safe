/******************************************************************************
 *
 * Module: KEYPAD Driver
 *
 * Layer : HAL
 *
 * File Name: keypad.c
 *
 * Description: Program Source file for the Keypad Driver
 *
 * Author: Osama Hamdy
 *
 *******************************************************************************/

#include"Std_types.h"
#include"Bit_utils.h"
#include"RCC_interface.h"
#include"GPIO_private.h"
#include"GPIO_interface.h"
#include "Keypad.h"
#include "Keypad_cfg.h"
#include "Keypad_prv.h"

/*Private Static Variable to save the button pressed value*/
static u8 ButtonStatus;
static u8 Validated = 0;

/*
 * Public Function
 * Description : Initialzation of keypad
 * Function Parameter : void
 * Function Return : void
 * */
void Keypad_vidInit(void) {
	/*Enable clock for the keypad Gpio used Peripheral */
	if (KEYPAD_PORT == GPIOA_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOA_ENABLE);
	} else if (KEYPAD_PORT == GPIOB_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOB_ENABLE);
	} else if (KEYPAD_PORT == GPIOC_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOC_ENABLE);
	} else if (KEYPAD_PORT == GPIOD_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOD_ENABLE);
	} else if (KEYPAD_PORT == GPIOE_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOE_ENABLE);
	} else if (KEYPAD_PORT == GPIOH_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOH_ENABLE);
	}

	/*Initialize Keypad ROW Pins*/
	GPIO_PinCfg_t Keypad_RowPins;
	Keypad_RowPins.pin = Keypad_Rows_pins;
	Keypad_RowPins.port = GPIOB_BASE_ADDRESS;
	Keypad_RowPins.Mode = GPIO_u32MODE_OUTPUT_PP_PU;
	Keypad_RowPins.Speed = GPIO_u8SPEED_VERY_HIGH;
	GPIO_Init(&Keypad_RowPins);

	/*Initialize Keypad COL Pins*/
	GPIO_PinCfg_t Keypad_ColPins;
	Keypad_ColPins.pin = Keypad_Cols_pins;
	Keypad_ColPins.port = GPIOB_BASE_ADDRESS;
	Keypad_ColPins.Mode = GPIO_u32MODE_INPUT_PU;
	Keypad_ColPins.Speed = GPIO_u8SPEED_VERY_HIGH;
	GPIO_Init(&Keypad_ColPins);
}

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
Keypad_tenuErrorStatus Keypad_enuGetKeyPressed(pu32 Add_pu8PressedKKey) {
	/*Local Variable to save the keypad error status*/
	Keypad_tenuErrorStatus LOC_enuReturnStatus = Keypad_status_OK;
	/*Local Variable  of Gpio Configuration Structure */
	GPIO_PinCfg_t Loc_Cfg_t;
	/*Declaration of Iterator and Pin  Reading Variables*/
	u32 LOC_u32PinReading = GPIO_u8HIGH;
	u8 LOC_u8RowIterator = ZERO;
	u8 LOC_u8ColIterator = ZERO;
	u8 LOC_u8RowIteratorHigh = ZERO;
	/*CHECK ON POINTER SENT TO RETURN THE VALUE IN */
	if (Add_pu8PressedKKey == NULL_PTR) {
		LOC_enuReturnStatus = Keypad_NullPointerErr;
	}

	else {
		/*checking the pressed key and then Return it's value*/
		for (LOC_u8RowIterator = ZERO; LOC_u8RowIterator < Keypad_No_Rows;
				LOC_u8RowIterator++) {
			/*SET ALL ROWS WITH HIGH*/
			for (LOC_u8RowIteratorHigh = ZERO;
					LOC_u8RowIteratorHigh < Keypad_No_Rows;
					LOC_u8RowIteratorHigh++) {
				Loc_Cfg_t.port = GPIOB_BASE_ADDRESS;
				Loc_Cfg_t.pin = Keypad_Rows[LOC_u8RowIteratorHigh];
				Loc_Cfg_t.Speed = GPIO_u8SPEED_VERY_HIGH;
				Loc_Cfg_t.Mode = GPIO_u32MODE_INPUT_PU;
				GPIO_WritePinValue(&Loc_Cfg_t, GPIO_u8HIGH);
			}
			/*SET SELECTED ROW WITH LOW VALUE THEN CHECK COLUMNS*/
			Loc_Cfg_t.pin = Keypad_Rows[LOC_u8RowIterator];
			Gpio_enuSetPinValue(&Loc_Cfg_t, GPIO_u8LOW);
			/*CHECK ON COLUMNS WHICH HAS READING OF ZERO WHICH INDICATES THE PRESSED KEY*/
			for (LOC_u8ColIterator = ZERO;
					LOC_u8ColIterator < Keypad_No_Cols && LOC_u32PinReading;
					LOC_u8ColIterator++) {
				Loc_Cfg_t.port = GPIOB_BASE_ADDRESS;
				Loc_Cfg_t.pin = Keypad_Cols[LOC_u8ColIterator];
				GPIO_ReadPinValue(&Loc_Cfg_t, &LOC_u32PinReading);
			}
			/*CHECK IF PIN READING IS LOW THEN IT IS PRESSED */
			if (LOC_u32PinReading == GPIO_u8LOW) {
				/*RETURN THE ROW AND COL VALUE DEPENDS ON ARRAY*/
				*Add_pu8PressedKKey = KeypadOutput[(LOC_u8RowIterator
						* Keypad_No_Rows) + LOC_u8ColIterator - 1];
				/*BREAK LOOP*/
				break;
			}

		}

	}

	return LOC_enuReturnStatus;
}

/*
 * Public Function
 * Function Name :  Keypad_Task
 * Description : Get key pressed and Check on switches debouncing
 * Function return : void
 *----------------------
 */
extern void vidKeypad_Task(void) {
	/*local variable to save the button status*/
	u32 Loc_u32CurButtonStatus = ZERO;
	/*Private local variable to save the previous button status */
	static u8 Loc_u8PrevButtonStatus;
	/*private local variable to count the number of pressing */
	static u8 Counter;
	/*Get Button Pressed Value */
	Keypad_enuGetKeyPressed(&Loc_u32CurButtonStatus);
	/*Check the Debouncing */
	if (Loc_u32CurButtonStatus == Loc_u8PrevButtonStatus) {
		Counter++;
	} else {
		Counter = ZERO;
		Validated = ZERO;
	}

	/*IF NO DEOUNCING AFTER 5 READINGS THEN CONFIRM VALUE */
	if (Counter == NUM_OF_CHECK) {
		/*RESTART COUNTER FOR NEXT READING*/
		Counter = ZERO;
		Validated = ONE;
		ButtonStatus = (u8) Loc_u32CurButtonStatus;
	}
	/*SAVE LAST READING*/
	Loc_u8PrevButtonStatus = (u8) Loc_u32CurButtonStatus;
}

/*
 *  Public Function
 *  Function:  Keypad_enuPressedKeyGetter
 *  Function Inputs: pointer to u32 variable to return the pressed key after checking on deouncing
 *  Function Description : check validation flag , then return value , else return status value not validated
 *  returns: Error status if any happens and OK if passed successfully.
 *  check---> Keypad_tenuErrorStatus
 *
 */
Keypad_tenuErrorStatus Keypad_enuPressedKeyGetter(pu8 Add_pu8PressedKey) {
	/*Local Variable to save the error status */
	Keypad_tenuErrorStatus LOC_enuReturnStatus = Keypad_status_OK;
	if (Validated) {
		*Add_pu8PressedKey = ButtonStatus;
	} else {
		LOC_enuReturnStatus = Keypad_NoValidatedVal;
	}
	return LOC_enuReturnStatus;

}

