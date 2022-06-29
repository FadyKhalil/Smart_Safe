/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	LCD
**       Description :	LCD module files 
** **************************************************************************************/
#include "Lcd.h"
#include "Lcd_cfg.h"
#include "Gpio.h"

const LcdCfg_t Lcd_Pins_cfg[] = {
    [Lcd_D0_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN07
    },
    [Lcd_D1_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN06
    },
    [Lcd_D2_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN05
    },
    [Lcd_D3_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN04
    },
    [Lcd_D4_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN03
    },
    [Lcd_D5_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN02
    },
    [Lcd_D6_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN01
    },
    [Lcd_D7_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN00
    },
    [Lcd_EN_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN11
    },
    [Lcd_RW_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN12
    },
    [Lcd_RS_PIN] = {
        .port = GPIO_A,
        .pin = GPIO_PIN08
    },
};

const Lcd_Request_t Lcd_Config[] = {
    [FUNCTION_SET] = {
        .type   = LCD_REQ_TYP__CMD,
        .value  = LCD_REQ__MODE_8_BIT | LCD_REQ__2_LINE | LCD_REQ__FONT_5_7
    },
    [DISPLAY_CTRL] = {
        .type   = LCD_REQ_TYP__CMD,
        .value  = LCD_REQ_CURSOR_OFF
    },
    [CLEAR_SCREEN] = {
        .type   = LCD_REQ_TYP__CMD,
        .value  = LCD_REQ__CLR_DISPLAY
    },
    [ENTRY_MODE] = {
        .type   = LCD_REQ_TYP__CMD,
        .value  = LCD_REQ__SCEERN_SHIFT_OFF | LCD_REQ__CURSOR_INC
    },
};
