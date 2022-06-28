/*
 * App.c
 *
 *  Created on: Apr 17, 2022
 *      Author: fady
 */

#include "diag/Trace.h"
#include "../HAL/KEYPAD/Keypad.h"
#include "../HAL/LCD/Lcd.h"
#include "App.h"

static void Loc_vidUpdate(pu32 Loc_pu32Accumulator,pu32 Loc_pu32Number, u8 Loc_u8Sign);



static u8 Loc_u8FSM_State = DIGIT_STATE;
static u8 Loc_u8Key;
static u32 Loc_u32Number = 0;
static u32 Loc_u32Accumulator = 0;
static u8 Loc_u8Sign = '+';
static u8 ZeroDivisionFlag = 0;

Lcd_Request_t Lcd_clear = {
	.type = LCD_REQ_TYP__CMD,
	.value = LCD_REQ__CLR_DISPLAY
};


Lcd_Request_t Lcd_Equal = {
	.type = LCD_REQ_TYP__DATA,
	.value = '='
};


void Calculator(void) {

	if (Lcd_status() < 5)
		return;

	Keypad_u8GetPressedKey(&Loc_u8Key);
	if (Loc_u8Key == 0)
		return;

	ZeroDivisionFlag = 0;
	switch (Loc_u8Key) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		if (Loc_u8FSM_State != DIGIT_STATE) {
			LCD_requestRegister(Lcd_clear);
		}
		if (Loc_u8FSM_State == EQUAL_STATE) {
			Loc_u32Accumulator = 0;									// accum = 0
		}
		Loc_u32Number = (10 * Loc_u32Number) + (u32) (Loc_u8Key - '0');	// update num
		LCD_Goto(0, 1);
//		Lcd_Request_t req = {
//				.type = LCD_REQ_TYP__CMD,
//				.value = 0x80
//		};
//		LCD_requestRegister(req);
		if (Loc_u32Number)
		{

			Lcd_displayNumber(Loc_u32Number);
			trace_printf("%d", Loc_u32Number);

		}
		else
//			Lcd_enuSend(LCD_u8SEND_TYPE_DATA, LCD_u8DATA__XX_RAM_DATA_ASCII_0); /****************************/
		Loc_u8FSM_State = DIGIT_STATE;								// Goto A
		break;

	case '+':
	case '-':
	case '/':
	case '*':
		if (Loc_u8FSM_State == DIGIT_STATE) {
			if (Loc_u32Number || Loc_u8Sign != '/')
				Loc_vidUpdate(&Loc_u32Accumulator, &Loc_u32Number, Loc_u8Sign);	// update accum
			else
				ZeroDivisionFlag = 1;
			Loc_u32Number = 0;										// num = 0
		}
		Loc_u8Sign = Loc_u8Key;									// update sign
		if (ZeroDivisionFlag == 0) {
			LCD_Goto(13, 2);

			Lcd_Request_t Lcd_Number = {
				.type = LCD_REQ_TYP__DATA,
				.value = Loc_u8Key
			};

			LCD_requestRegister(Lcd_Number);
			LCD_Goto(0, 1);
			Lcd_displayNumber(Loc_u32Accumulator);
		} else {
			LCD_requestRegister(Lcd_clear);
//			Lcd_enuDisplayString("Zero Division");
		}
		Loc_u8FSM_State = SIGN_STATE;								// Goto B
		break;

	case '=':
		if (Loc_u8FSM_State == DIGIT_STATE) {
			if (Loc_u32Number || Loc_u8Sign != '/')
				Loc_vidUpdate(&Loc_u32Accumulator, &Loc_u32Number, Loc_u8Sign);	// update accum
			else
				ZeroDivisionFlag = 1;
			Loc_u32Number = 0;										// num = 0
		}
		Loc_u8Sign = '+';									// update sign = '+'
		LCD_Goto(0, 1);
		if (ZeroDivisionFlag == 0)
			Lcd_displayNumber(Loc_u32Accumulator);
		else
//			Lcd_enuDisplayString("Zero Division"); /************************/
		LCD_Goto(15, 2);

		LCD_requestRegister(Lcd_Equal);
		Loc_u8FSM_State = EQUAL_STATE;								// Goto C
		break;
	case 'C':
		LCD_requestRegister(Lcd_clear);
		Loc_u32Accumulator = 0;
		Loc_u32Number = 0;
		Loc_u8Sign = '+';
		break;
	}

}



static void Loc_vidUpdate(pu32 Loc_pu32Accumulator,pu32 Loc_pu32Number, u8 Loc_u8Sign)
{
    switch (Loc_u8Sign)
    {
    case '+':
        *Loc_pu32Accumulator += (*Loc_pu32Number);
        break;
    case '-':
        *Loc_pu32Accumulator -= (*Loc_pu32Number);
        break;
    case '*':
        *Loc_pu32Accumulator *= (*Loc_pu32Number);
        break;
    case '/':
        *Loc_pu32Accumulator /= (*Loc_pu32Number);
        break;
    }
    Loc_pu32Number = 0;
}

