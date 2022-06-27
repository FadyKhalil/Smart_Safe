/*
 * Lcd.h
 *
 *  Created on: Apr 9, 2022
 *      Author: Ahmed-Yehia
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include "../Utils/std_types.h"

#define LCD_REQ_TYP__CMD                                    0x00
#define LCD_REQ_TYP__DATA                                   0x02

#define LCD_REQ__CLR_DISPLAY                                0x01
#define LCD_REQ__RTN_HOME                                   0x02

#define LCD_REQ__CURSOR_INC                                 0x07
#define LCD_REQ__CURSOR_DEC                                 0x05
#define LCD_REQ__SCEERN_SHIFT_ON                            0x05
#define LCD_REQ__SCEERN_SHIFT_OFF                           0x04

#define LCD_REQ__DISPLAY_OFF                                0x08
#define LCD_REQ__DISPLAY_ON                                 0x0C
#define LCD_REQ_CURSOR_OFF                                  0x0C
#define LCD_REQ__CURSOR_ON                                  0x0E
#define LCD_REQ__BLINK_OFF                                  0x0E
#define LCD_REQ__BLINK_ON                                   0x0F

#define LCD_REQ__CURSOR_SHFT_LEFT                           0x10
#define LCD_REQ__CURSOR_SHFT_RIGHT                          0x14
#define LCD_REQ__DISPLAY_SHFT_LEFT                          0x18
#define LCD_REQ__DISPLAY_SHFT_RIGHT                         0x1C

#define LCD_REQ__MODE_4_BIT                                 0x20
#define LCD_REQ__MODE_8_BIT                                 0x30
#define LCD_REQ__1_LINE                                     0x20
#define LCD_REQ__2_LINE                                     0x28
#define LCD_REQ__FONT_5_7                                   0x20
#define LCD_REQ__FONT_5_10                                  0x24

#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_0                   0x40
#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_1                   0x48
#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_2                   0x50
#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_3                   0x58
#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_4                   0x60
#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_5                   0x68
#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_6                   0x70
#define LCD_REQ__CUSTOM_CHARACTER_SHAPE_7                   0x78

// DD RAM addresses 
#define LCD_REQ__DISPLAY_LINE1_BASE_ADDRESS                 0x00
#define LCD_REQ__DISPLAY_LINE2_OFFSET                       0x40

typedef struct
{
    uint8_t type;
    uint8_t value;
} Lcd_Request_t;

typedef enum
{
    // initialization states
    START       ,
    FUNCTION_SET,
    DISPLAY_CTRL,
    CLEAR_SCREEN,
    ENTRY_MODE  ,
    // running states
    RUNNING     ,
    IDLE        ,
} Lcd_state_t;


// LCD_init (sync) function is used to initialize the LCD module
//  (set of instructions sent to the Lcd in order to 
//  configure it) 
// Args:    none
// Return:  none
// example:
//          Lcd_init();
extern void LCD_init();

// LCD_Task (sync) function is scheduled by the OS to prform LCD 
// module operations
// the periodicity of the task is configured on the OS
// note: this function can't be called by the user
// Args:    none
// Return:  none
// example:
//          ----
extern void LCD_Task();

// LCD_requestRegister (async) function is used to register a new
// request to be performed on Lcd module (write data - send command)
// note:
//      - the registered request will not performed immediately
//        after the call as it works asynchronously
//      - the registeration request can be rejected if the internal
//        requests buffer is filled with previous requests (it needs
//        to be registered later) 
// Args:    request         :(Lcd_Request_t) the request to be registered
// Return:  retuenStatus    :(res_t) the status of the 
//                          registeration call 
//                          (Status_Ok: register,
//                          Status_busy: not registered)
// example:
//          Lcd_Request_t req = {
//              .type = LCD_REQ_TYP__CMD,
//              .value = LCD_REQ__CLR_DISPLAY
//          };
//          LCD_requestRegister(req);
extern res_t LCD_requestRegister(Lcd_Request_t request);


// LCD_sendCharacter (async) function is used to send a request to 
// display a character
// note:
//      - this function needs to be used inside a task scheduled to os
//        schedule in order to work correctly
// Args:    data            :(uint8_t) the displayed data
// Return:  returnStatus    :(res_t) the status of the call 
//                          (Status_Ok: register,
//                          Status_busy: not registered)
// example:
//          LCD_sendCharacter('A');
res_t LCD_sendCharacter(uint8_t data);

// LCD_sendCharacter (async) function is used to move the cursor
//  on display 
// note:
//      - this function needs to be used inside a task scheduled to os
//        schedule in order to work correctly
// Args:    x            :(uint8_t) the targeted x value
//          y            :(uint8_t) the targeted y value
// Return:  returnStatus    :(res_t) the status of the call 
//                          (Status_Ok: register,
//                          Status_busy: not registered)
// example:
//          LCD_Goto(4,1);
res_t LCD_Goto(uint8_t x, uint8_t y);

#endif /* LCD_LCD_H_ */
