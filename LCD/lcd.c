/******************************************************************************
 *
 * Module: lCD Driver
 *
 * Layer : HAL
 *
 * File Name: lcd.c
 *
 * Description: Program Source  file for the LCD Driver
 *
 * Author: Osama Hamdy
 *
 *******************************************************************************/

#include"Std_types.h"
#include"Bit_utils.h"
#include"RCC_interface.h"
#include"GPIO_private.h"
#include"GPIO_interface.h"
#include"lcd_cfg.h"
#include"lcd.h"

/*******************************************************************************
 *                   LCD Shared Variables                                      *
 *******************************************************************************/
/* Post Build Configuration Structure of Lcd  */
extern const Lcd_cfg_t lcd;
/*Global Variable to save the Lcd State*/
Lcd_initStates Init_State = Lcd_InitStart;
/*Global Variable to save the Lcd Asynchronous State*/
volatile Lcd_States lcd_Astate = Lcd_NotBusy;
/*Global variable to Save the User Structure Buffer */
Buffer_t* save_buffer;
/*Global Variable to Save the Lcd Postion  */
u8 save_posx, save_posy;

/*
 *Private Function
 * Description : Setting Lcd Enable Pin Value
 * Function Parameter : void
 * Function Return : void
 * */

static void lcd_SetEnablePin(u8 Copy_u8value);
/*
 *Private Function
 * Description : Sending the Lcd Command
 * Function Parameter : Lcd Command & Rs Value & Rw Value
 * Function Return : void
 * */
static void Lcd_SendCmd(u8 Copy_u8Command, u8 Copy_u8RS, u8 Copy_u8RW);

void LCD_vidInit(void) {
	/*Assign Lcd State As Start State */
	Init_State = Lcd_InitStart;
	/*Local Varaible to Save The Lcd Iterator Number */
	u8 Lcd_Iterator;
	/*Gpio Intitialzation for LCD RS PIN */
	GPIO_Init(&(lcd.Rs));
	/*Gpio Intitialzation for LCD RW PIN */
	GPIO_Init(&(lcd.Rw));
	/*Gpio Intitialzation for LCD ENABLE PIN */
	GPIO_Init(&(lcd.En));
	/*Gpio Intitialzation for LCD DATA PINS */
	for (Lcd_Iterator = 0; Lcd_Iterator < MAX_DATA_PIN; Lcd_Iterator++) {
		GPIO_Init(&(lcd.Data[Lcd_Iterator]));
	}
	/*Enable Clock For RS PIN */
	if (lcd.Rs.port == GPIOA_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOA_ENABLE);
	} else if (lcd.Rs.port == GPIOB_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOB_ENABLE);
	} else if (lcd.Rs.port == GPIOC_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOC_ENABLE);
	} else if (lcd.Rs.port == GPIOD_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOD_ENABLE);
	} else if (lcd.Rs.port == GPIOE_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOE_ENABLE);
	} else if (lcd.Rs.port == GPIOH_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOH_ENABLE);
	}
	/*Enable Clock For RW PIN */
	if (lcd.Rw.port == GPIOA_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOA_ENABLE);
	} else if (lcd.Rw.port == GPIOB_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOB_ENABLE);
	} else if (lcd.Rw.port == GPIOC_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOC_ENABLE);
	} else if (lcd.Rw.port == GPIOD_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOD_ENABLE);
	} else if (lcd.Rw.port == GPIOE_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOE_ENABLE);
	} else if (lcd.Rw.port == GPIOH_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOH_ENABLE);
	}
	/*Enable Clock For ENABLE PIN */
	if (lcd.En.port == GPIOA_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOA_ENABLE);
	} else if (lcd.En.port == GPIOB_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOC_ENABLE);
	} else if (lcd.En.port == GPIOA_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOD_ENABLE);
	} else if (lcd.En.port == GPIOA_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOE_ENABLE);
	} else if (lcd.En.port == GPIOH_BASE_ADDRESS) {
		Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOH_ENABLE);
	}

	/*Enable Clock For DATA PINS */
	for (Lcd_Iterator = 0; Lcd_Iterator < MAX_DATA_PIN; Lcd_Iterator++) {
		if (lcd.Data[Lcd_Iterator].port == GPIOA_BASE_ADDRESS) {
			Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOA_ENABLE);
		} else if (lcd.Data[Lcd_Iterator].port == GPIOB_BASE_ADDRESS) {
			Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOB_ENABLE);
		} else if (lcd.Data[Lcd_Iterator].port == GPIOC_BASE_ADDRESS) {
			Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOC_ENABLE);
		} else if (lcd.Data[Lcd_Iterator].port == GPIOD_BASE_ADDRESS) {
			Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOD_ENABLE);
		} else if (lcd.Data[Lcd_Iterator].port == GPIOE_BASE_ADDRESS) {
			Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOE_ENABLE);
		} else if (lcd.Data[Lcd_Iterator].port == GPIOH_BASE_ADDRESS) {
			Rcc_EnablePeripheral(AHB_BUS, PERI_AHB_GPIOH_ENABLE);
		}
	}

}
Lcd_ErrorState_t Lcd_vidWriteString(Buffer_t * Add_Buffer, u8 Copy_u8PosX,
		u8 Copy_u8PosY) {
	Lcd_ErrorState_t loc_ErrorState = Lcd_Ok;
	if (Add_Buffer == NULL_PTR) {
		loc_ErrorState = Lcd_NullPointerError;

	} else if (lcd_Astate == Lcd_NotBusy) {
		save_buffer = Add_Buffer;
		save_posx = Copy_u8PosX;
		save_posy = Copy_u8PosY;
		lcd_Astate = Lcd_WritingTask;
	}

	return loc_ErrorState;

}
void LCD_vidSched(void) {
	static u32 Time_MS;
	static WritingSequence_t writingState;
	if (Init_State != Lcd_InitPause && Init_State != Lcd_InitFinished) {
		switch (Init_State) {
		case Lcd_InitStart:
			Time_MS++;
			if (Time_MS == 30) {
				Init_State = Lcd_InitFunctionSet;
				Time_MS = 0;
			}
			break;
		case Lcd_InitFunctionSet:
			if (Time_MS == 0) {
				lcd_SetEnablePin(GPIO_u8HIGH);
				Lcd_SendCmd(FUNCTION_SET, GPIO_u8LOW, GPIO_u8LOW);
				Time_MS++;
			} else if (Time_MS == 1) {
				lcd_SetEnablePin(GPIO_u8LOW);
				Init_State = Lcd_InitDisplayCtrl;
				Time_MS = 0;
			}
			break;
		case Lcd_InitDisplayCtrl:
			if (Time_MS == 0) {
				lcd_SetEnablePin(GPIO_u8HIGH);
				Lcd_SendCmd(DISPLAY_CTRL, GPIO_u8LOW, GPIO_u8LOW);
				Time_MS++;
			} else if (Time_MS == 1) {
				lcd_SetEnablePin(GPIO_u8LOW);
				Init_State = Lcd_InitDisplayClear;
				Time_MS = 0;
			}
			break;
		case Lcd_InitDisplayClear:
			if (Time_MS == 0) {
				lcd_SetEnablePin(GPIO_u8HIGH);
				Lcd_SendCmd(DISPLAY_CLR, GPIO_u8LOW, GPIO_u8LOW);
				Time_MS++;
			} else if (Time_MS == 1) {
				lcd_SetEnablePin(GPIO_u8LOW);
				Time_MS++;
			} else if (Time_MS == 2) {
				Init_State = Lcd_InitEntryModeSet;
				Time_MS = 0;
			}
			break;
		case Lcd_InitEntryModeSet:
			if (Time_MS == 0) {
				lcd_SetEnablePin(GPIO_u8HIGH);
				Lcd_SendCmd(ENTRY_MODE, GPIO_u8LOW, GPIO_u8LOW);
				Time_MS++;
			} else if (Time_MS == 1) {
				lcd_SetEnablePin(GPIO_u8LOW);				Time_MS++;

			} else if (Time_MS == 2) {
				Init_State = Lcd_InitFinished;
				Time_MS = 0;
			}
			break;

		}

	} else {
		switch (lcd_Astate) {
		case Lcd_WritingTask:
			if (Time_MS == 0) {
				lcd_SetEnablePin(GPIO_u8HIGH);
				/*Change Cursor Postion*/
				switch (save_posx) {
				u8 cmd;
			case LCD_FIRST_ROW:
				cmd = save_posy;
				Lcd_SendCmd(cmd| LCD_SET_CURSOR_LOCATION, GPIO_u8LOW, GPIO_u8LOW);
				break;
			case LCD_SCND_ROW:
				cmd = 0x40 + save_posy;
				Lcd_SendCmd(cmd | LCD_SET_CURSOR_LOCATION, GPIO_u8LOW,
				GPIO_u8LOW);
				break;
				}
			} else if (Time_MS == 1) {
				lcd_SetEnablePin(GPIO_u8LOW);
				Time_MS++;
			} else if (Time_MS == 2) {
				if (save_buffer->Used != save_buffer->Size
						&& save_buffer->Data[save_buffer->Used] != '\0') {
					/*Draw Char*/
					Lcd_SendCmd(save_buffer->Data[save_buffer->Used],
					GPIO_u8HIGH, GPIO_u8LOW);
					save_buffer->Used++;
					Time_MS--;
				} else {
					lcd_Astate = Lcd_NotBusy;
				}
			}
			break;
		}
	}
}

/*
 *Private Function
 * Description : Setting Lcd Enable Pin Value
 * Function Parameter : void
 * Function Return : void
 * */

static void lcd_SetEnablePin(u8 Copy_u8value) {
	GPIO_WritePinValue(&(lcd.En), Copy_u8value);

}

/*
 *Private Function
 * Description : Sending the Lcd Command
 * Function Parameter : Lcd Command & Rs Value & Rw Value
 * Function Return : void
 * */

static void Lcd_SendCmd(u8 Copy_u8Command, u8 Copy_u8RS, u8 Copy_u8RW) {
	u8 Lcd_Iterator;
	GPIO_WritePinValue(&(lcd.Rs), Copy_u8RS);
	GPIO_WritePinValue(&(lcd.Rw), Copy_u8RW);
	for (Lcd_Iterator = 0; Lcd_Iterator < MAX_DATA_PIN; Lcd_Iterator++) {
		GPIO_WritePinValue(&(lcd.Data[Lcd_Iterator]),
				GET_BIT(Copy_u8Command, Lcd_Iterator));
	}

}
