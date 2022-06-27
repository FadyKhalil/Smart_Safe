

void Loc_vidUpdate(pu32 Loc_pu32Accumulator,pu32 Loc_pu32Number, u8 Loc_u8Sign)
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

enum // FSM states
{
	DIGIT_STATE = 1,
	SIGN_STATE,
	EQUAL_STATE,
}


int main(void)
{
	u8 Loc_u8FSM_State = DIGIT_STATE;
	u8 Loc_u8Key;
	u32 Loc_u32Number = 0;
	u32 Loc_u32Accumulator = 0;
	u8 Loc_u8Sign = '+';
	u8 ZeroDivisionFlag = 0;
	Port_vidInit();
	Lcd_vidInit();
	while (1)
	{
		Loc_u8Key Keypad_u8GetPressedKey();
		ZeroDivisionFlag = 0;
		switch (Loc_u8Key)
		{
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
				if (Loc_u8FSM_State != DIGIT_STATE)
				{
					Lcd_enuSend(LCD_u8SEND_TYPE_CMD, LCD_u8CMD__CLR_DISPLAY);
				}
				if (Loc_u8FSM_State == EQUAL_STATE)
				{
					Loc_u32Accumulator = 0;												// accum = 0
				}
				Loc_u32Number = (10*Loc_u32Number) + (u32)(Loc_u8Key-'0');				// update num
				Lcd_enuGoto(0,0);
				if (Loc_u32Number)
					Lcd_enuDisplayNumber(Loc_u32Number);
				else
					Lcd_enuSend(LCD_u8SEND_TYPE_DATA, LCD_u8DATA__XX_RAM_DATA_ASCII_0);
				Loc_u8FSM_State = DIGIT_STATE;											// Goto A
				break;

			case '+':
			case '-':
			case '/':
			case '*':
				if (Loc_u8FSM_State == DIGIT_STATE)
				{
					if (Loc_u32Number || Loc_u8Sign != '/')
						Loc_vidUpdate(&Loc_u32Accumulator, &Loc_u32Number, Loc_u8Sign);		// update accum
					else
						ZeroDivisionFlag = 1;
					Loc_u32Number = 0;													// num = 0
				}
				Loc_u8Sign = Loc_u8Key;													// update sign
				if (ZeroDivisionFlag == 0)
				{
					Lcd_enuGoto(15,1);
					Lcd_enuSend(LCD_u8SEND_TYPE_DATA, Loc_u8Key);
					Lcd_enuGoto(0,0);
					Lcd_enuDisplayNumber(Loc_u32Accumulator);
				}
				else
				{
					Lcd_enuSend(LCD_u8SEND_TYPE_CMD, LCD_u8CMD__CLR_DISPLAY);
					Lcd_enuDisplayString("Zero Division");
				}
				Loc_u8FSM_State = SIGN_STATE;											// Goto B
				break;

			case '=':
				if (Loc_u8FSM_State == DIGIT_STATE)
				{
					if (Loc_u32Number || Loc_u8Sign != '/')
						Loc_vidUpdate(&Loc_u32Accumulator, &Loc_u32Number, Loc_u8Sign);		// update accum
					else
						ZeroDivisionFlag = 1;
					Loc_u32Number = 0;													// num = 0
				}
				Loc_u8Sign = '+';														// update sign = '+'
				Lcd_enuGoto(0,0);
				if (ZeroDivisionFlag == 0)
					Lcd_enuDisplayNumber(Loc_u32Accumulator);
				else
					Lcd_enuDisplayString("Zero Division");
				Lcd_enuGoto(15,1);
				Lcd_enuSend(LCD_u8SEND_TYPE_DATA, '=');
				Loc_u8FSM_State = EQUAL_STATE;											// Goto C
				break;
			case 'C':
				Lcd_enuSend(LCD_u8SEND_TYPE_CMD, LCD_u8CMD__CLR_DISPLAY);
				Loc_u32Accumulator = 0;
				Loc_u32Number = 0;
				Loc_u8Sign = '+';
				break;
		}
	}
}
