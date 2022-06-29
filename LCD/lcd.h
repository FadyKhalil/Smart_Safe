/******************************************************************************
 *
 * Module: LCD HAL Driver
 *
 * Layer : HAL
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD Driver
 *
 * Author: Osama Hamdy
 *
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_
#include "GPIO_interface.h"
#include "Std_types.h"
/********************************************************************************************
 *                               Types Declaration                                          *
 ********************************************************************************************/

typedef struct {
	/*
	 * Gpio Configuration Structure = {Port,Mode,pin,Speed};
	 * */
	GPIO_PinCfg_t Rs;
	GPIO_PinCfg_t Rw;
	GPIO_PinCfg_t En;
	GPIO_PinCfg_t Data[8];
} Lcd_cfg_t;

typedef enum {
	Lcd_InitPause,
	Lcd_InitStart,
	Lcd_InitFunctionSet,
	Lcd_InitDisplayCtrl,
	Lcd_InitDisplayClear,
	Lcd_InitEntryModeSet,
	Lcd_InitFinished,
} Lcd_initStates;

typedef enum {
	Lcd_NotBusy, Lcd_WritingTask,
} Lcd_States;

typedef struct {
	pu8 Data;
	u8  Size;
	u32 Used;
} Buffer_t;

typedef enum {
	Lcd_WriteStart, Lcd_WritePositionXY, Lcd_WriteString, Lcd_WriteDone
} WritingSequence_t;

typedef enum {
	Lcd_Ok,
	Lcd_Nok,
	Lcd_RowErrorNum,
	Lcd_ColErrorNum,
	Lcd_NullPointerError,
	lcd_BufferError,
} Lcd_ErrorState_t;
/*******************************************************************************
 *                           LCD Commands                                      *
 *******************************************************************************/
#define                    FUNCTION_SET                    0b00111100
#define                    DISPLAY_CTRL 				   0b00001000
#define                    DISPLAY_CLR					   0b00000001
#define                    ENTRY_MODE                      0b00000110
#define                   LCD_SET_CURSOR_LOCATION          0b10000000
/*******************************************************************************
 *                            Fuction ProtoTypes                               *
 *******************************************************************************/
/*
 * Public Function
 * Description : Initialzation of LCD
 * Function Parameter : void
 * Function Return : void
 * */
void LCD_vidInit(void) ;
/*
 * Public Function
 * Description : Display the String of  Lcd
 * Function Parameter : Buffer Address    &  Row Postion & Col Position
 * Function Return : Error Status of Switch
 * */
Lcd_ErrorState_t Lcd_vidWriteString(Buffer_t * Add_Buffer,u8 PositionX , u8 PositionY);

/*
 * Public Function
 * Description : Turn on The Runnable State
 * Function Parameter : void
 * Function Return : void
 * */

void LCD_vidSched(void);

#endif /* LCD_H_ */
