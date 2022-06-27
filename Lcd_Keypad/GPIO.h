/*
 * GPIO.h
 *
 *  Created on: Mar 16, 2022
 *      Author: Ahmed-Yehia
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "../Utils/std_types.h"


typedef struct{
    void* port;
    uint16_t pin;
    uint8_t mode;                   // mode (2bits) + otype (1bit) + pull_upDown (2bits)
    uint32_t speed;
} gpioPinCfg_t;


/*--------GPIO Registers--------*/
/*
*   GPIOA:  0x40020000
*   GPIOB:  0x40020400
*   GPIOC:  0x40020800
*   GPIOD:  0x40020C00
*   GPIOE:  0x40021000
*   GPIOH:  0x40021C00
*
*/
/*
_Mode_Register                      0x00             
_Output_Type_Register               0x04
_Output_Speed_Register              0x08
_Pull_UpDown_Register               0x0C
_Input_Data_Register                0x10
_Output_Data_Register               0x14
_Set_Reset_Data_Register            0x18
_Lock_Register                      0x1C
_Alternate_Function_Low_Register    0x20
_Alternate_Function_High_Register   0x24
*/

// ports that can the user uses
#define GPIO_PORT_A                                 (void*)0x40020000
#define GPIO_PORT_B                                 (void*)0x40020400
#define GPIO_PORT_C                                 (void*)0x40020800
#define GPIO_PORT_D                                 (void*)0x40020C00
#define GPIO_PORT_E                                 (void*)0x40021000
#define GPIO_PORT_H                                 (void*)0x40021C00

// pins that can the user uses
#define GPIO_PIN_0                                  0x0001
#define GPIO_PIN_1                                  0x0002
#define GPIO_PIN_2                                  0x0004
#define GPIO_PIN_3                                  0x0008
#define GPIO_PIN_4                                  0x0010
#define GPIO_PIN_5                                  0x0020
#define GPIO_PIN_6                                  0x0040
#define GPIO_PIN_7                                  0x0080
#define GPIO_PIN_8                                  0x0100
#define GPIO_PIN_9                                  0x0200
#define GPIO_PIN_10                                 0x0400
#define GPIO_PIN_11                                 0x0800
#define GPIO_PIN_12                                 0x1000
#define GPIO_PIN_13                                 0x2000
#define GPIO_PIN_14                                 0x4000
#define GPIO_PIN_15                                 0x8000

#define GPIO_PIN_ALL                                0xFFFF

// speed values that can the user uses
#define GPIO_SPEED_LOW                              0x00
#define GPIO_SPEED_MID                              0x01
#define GPIO_SPEED_HIGH                             0x02
#define GPIO_SPEED_VERY_HIGH                        0x03

// mode values that can the user uses
// sequence: Mode-otype-pu/d
#define GPIO_MODE_OUTPUT_PP                         0x08
#define GPIO_MODE_OUTPUT_PP_PU                      0x09
#define GPIO_MODE_OUTPUT_PP_PD                      0x0A
#define GPIO_MODE_OUTPUT_OD                         0x0C
#define GPIO_MODE_OUTPUT_OD_PU                      0x0D
#define GPIO_MODE_OUTPUT_OD_PD                      0x0E

#define GPIO_MODE_ALT_FUNC_PP                       0x10
#define GPIO_MODE_ALT_FUNC_PP_PU                    0x11
#define GPIO_MODE_ALT_FUNC_PP_PD                    0x12
#define GPIO_MODE_ALT_FUNC_OD                       0x14
#define GPIO_MODE_ALT_FUNC_OD_PU                    0x15
#define GPIO_MODE_ALT_FUNC_OD_PD                    0x16

#define GPIO_MODE_INPUT_FLOAT                       0x00
#define GPIO_MODE_INPUT_PU                          0x01
#define GPIO_MODE_INPUT_PD                          0x02

#define GPIO_MODE_ANALOG                            0x18

#define GPIO_ALT_FUNC_0                             0x00
#define GPIO_ALT_FUNC_1                             0x01
#define GPIO_ALT_FUNC_2                             0x02
#define GPIO_ALT_FUNC_3                             0x03
#define GPIO_ALT_FUNC_4                             0x04
#define GPIO_ALT_FUNC_5                             0x05
#define GPIO_ALT_FUNC_6                             0x06
#define GPIO_ALT_FUNC_7                             0x07
#define GPIO_ALT_FUNC_8                             0x08
#define GPIO_ALT_FUNC_9                             0x09
#define GPIO_ALT_FUNC_10                            0x0A
#define GPIO_ALT_FUNC_11                            0x0B
#define GPIO_ALT_FUNC_12                            0x0C
#define GPIO_ALT_FUNC_13                            0x0D
#define GPIO_ALT_FUNC_14                            0x0E
#define GPIO_ALT_FUNC_15                            0x0F

#define GPIO_Level_HIGH                             1
#define GPIO_Level_LOW                              0

// GPIO_initPin function is used to give a given pin(s) intial configuration
// Args:    targetedPin : (pointer to gpioPinCfg_t) holds the pin(s) configuration
// Return:  none    
// example:
//  gpioPinCfg_t Lcd_E = {
//      .port   = GPIO_PORT_A,
//      .pin    = GPIO_PIN_6,
//      .speed  = GPIO_SPEED_HIGH,
//      .mode   = GPIO_MODE_OUTPUT_OD_PD,
//  };
//  GPIO_initPin(&Lcd_E);
extern void GPIO_initPin(gpioPinCfg_t* targetedPin);

// GPIO_writePin function is used to write a level for the given pin(s)
// Args:    GPIO_PORT_X     : (pointer to void) holds the port identifier
//          GPIO_PIN_X      : (uint16_t) holds the pin identifier
//          GPIO_Level_X    : (uint8_t) holds the pin value
// Return:  error_status: (res_t)
//              Status_Ok
//              Status_NULL_ptr_Error
//              Status_invalid_port_Error 
//              Status_invalid_pin_Error
//              Status_level_Error
// example:
//  GPIO_writePin(GPIO_PORT_B, GPIO_PIN_12, GPIO_Level_HIGH);
//  GPIO_writePin(GPIO_PORT_C, GPIO_PIN_ALL, GPIO_Level_LOW);
extern res_t GPIO_writePin(void* GPIO_PORT, uint16_t GPIO_PIN, uint8_t GPIO_Level);

// GPIO_readPin function is used to read the level of the given pin
// note that this function supports only 1 bit reading at a time and if the provided
//  pin number is for multiple pins the output will be:
//                  high if any provided pin is high
//                  low else
// Args:    GPIO_PORT_X     : (pointer to void) holds the port identifier
//          GPIO_PIN_X      : (uint16_t) holds the pin identifier
//          GPIO_Level      : (pointer to uint8_t) holds a pointer to level value to be read
// Return:  error_status: (res_t)
//              Status_Ok
//              Status_NULL_ptr_Error
//              Status_invalid_port_Error 
//              Status_invalid_pin_Error
// example:
//  uint8_t* pinLevel;
//  GPIO_readPin(GPIO_PORT_E, GPIO_PIN_2, pinLevel);
extern res_t GPIO_readPin(void* GPIO_PORT, uint16_t GPIO_PIN, uint8_t* GPIO_Level);

#endif /* GPIO_H_ */
