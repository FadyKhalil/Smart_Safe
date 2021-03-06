/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	LCD
**       Description :	LCD module files 
** **************************************************************************************/
#ifndef LCD_LCD_CFG_H_
#define LCD_LCD_CFG_H_

#define LCD_NUMBER_OF_PINS              11
#define LCD_MAX_REQ_BUFFER_SIZE         256

typedef enum{
    Lcd_EN_PIN,
    Lcd_RW_PIN,
    Lcd_RS_PIN,
    Lcd_D0_PIN,
    Lcd_D1_PIN,
    Lcd_D2_PIN,
    Lcd_D3_PIN,
    Lcd_D4_PIN,
    Lcd_D5_PIN,
    Lcd_D6_PIN,
    Lcd_D7_PIN,
} Lcd_Pins;

typedef struct{
    void*       port;
    u16    pin;
} LcdCfg_t;


#endif /* LCD_LCD_CFG_H_ */
