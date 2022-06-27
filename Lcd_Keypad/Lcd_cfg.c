/*
 * Lcd_cfg.c
 *
 *  Created on: Apr 9, 2022
 *      Author: Ahmed-Yehia
 */

#include "Lcd.h"
#include "Lcd_cfg.h"
#include "../GPIO/GPIO.h"

const LcdCfg_t Lcd_Pins_cfg[] = {
    [Lcd_D0_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_7
    },
    [Lcd_D1_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_6
    },
    [Lcd_D2_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_5
    },
    [Lcd_D3_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_4
    },
    [Lcd_D4_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_3
    },
    [Lcd_D5_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_2
    },
    [Lcd_D6_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_1
    },
    [Lcd_D7_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_0
    },
    [Lcd_EN_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_10
    },
    [Lcd_RW_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_9
    },
    [Lcd_RS_PIN] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_8
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
