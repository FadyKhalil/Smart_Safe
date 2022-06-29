/******************************************************************************
 *
 * Module: Keypad Driver
 *
 * File Name: Keypad_prv.h
 *
 * Description: Private Header file for the Keypad Driver
 *
 * Author: Osama Hamdy
 *
 *******************************************************************************/

#ifndef KEYPAD_PRV_H_
#define KEYPAD_PRV_H_

#define ONE 	1
#define ZERO 	0

#define NUM_OF_CHECK 5
/*ARRAY OF KEYPAD ROWS TO ITERATE THROUGH*/
u8 Keypad_Rows[Keypad_No_Rows] = { Keypad_u8R0PIN, Keypad_u8R1PIN,
		Keypad_u8R2PIN, Keypad_u8R3PIN };
/*ARRAY OF KEYPAD COLS TO ITERATE THROUGH*/
u8 Keypad_Cols[Keypad_No_Cols] = { Keypad_u8C0PIN, Keypad_u8C1PIN,
		Keypad_u8C2PIN, Keypad_u8C3PIN };


#endif /* KEYPAD_PRV_H_ */
