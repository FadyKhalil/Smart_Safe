/*
 * Keypad_cfg.h
 *
 *  Created on: Jun 28, 2022
 *      Author: hp
 */

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

/*ROWS AND COLS CHOSEN PORTS*/
#define KEYPAD_PORT	 GPIOB_BASE_ADDRESS
#define Keypad_No_Rows 4
#define Keypad_No_Cols 4
/*PORT used y keypad to be enabled in RCC*/
#define Keypad_RCC_enabled_PORT RCC_u32AHB1_GPIOA
/*Rows' Pins*/
#define Keypad_u8R0PIN GPIO_PIN_00
#define Keypad_u8R1PIN GPIO_PIN_01
#define Keypad_u8R2PIN GPIO_PIN_02
#define Keypad_u8R3PIN GPIO_PIN_03
/*Columns' Pins*/
#define Keypad_u8C0PIN GPIO_PIN_04
#define Keypad_u8C1PIN GPIO_PIN_05
#define Keypad_u8C2PIN GPIO_PIN_06
#define Keypad_u8C3PIN GPIO_PIN_07

#define Keypad_Rows_pins	(u16)(Keypad_u8R0PIN | Keypad_u8R1PIN | Keypad_u8R2PIN |Keypad_u8R3PIN)
#define Keypad_Cols_pins	(u16)( Keypad_u8C0PIN | Keypad_u8C1PIN | Keypad_u8C2PIN | Keypad_u8C3PIN)

/*Keypad Keys Values*/
#define Keypad_u8R0C0_KEY 	'/'
#define Keypad_u8R0C1_KEY 	'x'
#define Keypad_u8R0C2_KEY 	'-'
#define Keypad_u8R0C3_KEY 	'+'
#define Keypad_u8R1C0_KEY 	'='
#define Keypad_u8R1C1_KEY 	'9'
#define Keypad_u8R1C2_KEY 	'6'
#define Keypad_u8R1C3_KEY 	'3'
#define Keypad_u8R2C0_KEY 	'0'
#define Keypad_u8R2C1_KEY 	'8'
#define Keypad_u8R2C2_KEY 	'5'
#define Keypad_u8R2C3_KEY 	'2'
#define Keypad_u8R3C0_KEY 	'.'
#define Keypad_u8R3C1_KEY 	'7'
#define Keypad_u8R3C2_KEY 	'4'
#define Keypad_u8R3C3_KEY 	'1'


/*ARRAY OF KEYPAD VALUES */
static u8 KeypadOutput[] = {Keypad_u8R0C0_KEY ,
							Keypad_u8R0C1_KEY ,
							Keypad_u8R0C2_KEY ,
							Keypad_u8R0C3_KEY ,
							Keypad_u8R1C0_KEY ,
							Keypad_u8R1C1_KEY ,
							Keypad_u8R1C2_KEY ,
							Keypad_u8R1C3_KEY ,
							Keypad_u8R2C0_KEY ,
							Keypad_u8R2C1_KEY ,
							Keypad_u8R2C2_KEY ,
							Keypad_u8R2C3_KEY ,
							Keypad_u8R3C0_KEY ,
							Keypad_u8R3C1_KEY ,
							Keypad_u8R3C2_KEY ,
							Keypad_u8R3C3_KEY };



#endif /* KEYPAD_CFG_H_ */
