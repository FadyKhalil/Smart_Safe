/*
 * GPIO.c
 *
 *  Created on: Mar 16, 2022
 *      Author: Ahmed-Yehia
 */

#include "../Rcc/Rcc.h"
#include "../GPIO/GPIO.h"

typedef struct{
uint32_t Mode_Register;             
uint32_t Output_Type_Register;
uint32_t Output_Speed_Register;
uint32_t Pull_UpDown_Register;
uint32_t Input_Data_Register;
uint32_t Output_Data_Register;
uint32_t Set_Reset_Data_Register;
uint32_t Lock_Register;
uint32_t Alternate_Function_Low_Register;
uint32_t Alternate_Function_High_Register;
} GPIO_t;

// private definitions
#define GPIO_prv_Word                       32
#define GPIO_prv_Half_Word                  16
#define GPIO_prv_2bits_mask                 0x03
#define GPIO_prv_mode_offset                3
#define GPIO_prv_otype_offset               2
#define GPIO_prv_otype_mask                 0x04
#define GPIO_prv_pupd_offset                0

// prv_Set_N_Bits function is used to extend a given sequence of bits given a certain pattern
// example:
//      seq:        0x5  = 0b101
//      pattern:    0x3  = 0b11
//      output:     0x33 = 0b110011
// Args:    outputReg   : (pointer to uint32_t) holds the output extended bits register
//          inputReg    : (uint32_t) input register to be extended 
//          setValue    : (uint8_t) the setted value
//          N           : (uint8_t) number of bits of the setted value
//          where max(setValue) < 2^N
// Return:  none  
void prv_Set_N_Bits(uint32_t* outputReg, uint32_t* outputMask, uint32_t inputReg, uint8_t setValue, uint8_t N)
{
    uint32_t local_temp = inputReg;
    uint8_t iterator = 0;
    uint8_t mask = (1<<N)-1;
    *outputReg = 0x0;
    *outputMask = 0x0;
    while (iterator < GPIO_prv_Word)                      
    {                                          
        if (local_temp % 2 == 1)
            *outputReg  |= setValue<<N*iterator;
        else
            *outputMask |= mask<<N*iterator;
        iterator++;      
        local_temp >>= 1;
    }
}

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
extern void GPIO_initPin(gpioPinCfg_t* targetedPin)
{
    // 
    // targetedPin need to be checked against NULL
    // 

    uint32_t Loc_temp_register_value, Loc_temp_register_mask;
    
    // set speed value
    prv_Set_N_Bits(
        &Loc_temp_register_value,                                           // the targeted register
        &Loc_temp_register_mask,                                            // the targeted register mask
        targetedPin->pin,                                                   // the targeted pin(s)
        targetedPin->speed,                                                 // the given speed value
        2                                                                   // number of bits extended
        );
    ((GPIO_t*)(targetedPin->port))->Output_Speed_Register &= Loc_temp_register_mask;
    ((GPIO_t*)(targetedPin->port))->Output_Speed_Register |= Loc_temp_register_value;
    
    // set pin pull up/pull down configuration
    prv_Set_N_Bits(
        &Loc_temp_register_value,                                           // the targeted register
        &Loc_temp_register_mask,                                            // the targeted register mask
        targetedPin->pin,                                                   // the targeted pin(s)
        ((targetedPin->mode)>>GPIO_prv_pupd_offset) & GPIO_prv_2bits_mask,  // the given pull up/pull down
                                                                            // inside mode value
        2                                                                   // number of bits extended
        );
    ((GPIO_t*)(targetedPin->port))->Pull_UpDown_Register &= Loc_temp_register_mask;
    ((GPIO_t*)(targetedPin->port))->Pull_UpDown_Register |= Loc_temp_register_value;
    
    // set pin output tpye
    // clear mode bits
    ((GPIO_t*)(targetedPin->port))->Output_Type_Register &= ~(targetedPin->pin);
    if ( ((targetedPin->mode) & GPIO_prv_otype_mask) == GPIO_prv_otype_mask)
    {
        // set mode bits
        ((GPIO_t*)(targetedPin->port))->Output_Type_Register |= targetedPin->pin;
    }
    
    // set pin direction (mode)
    prv_Set_N_Bits(
        &Loc_temp_register_value,                                           // the targeted register
        &Loc_temp_register_mask,                                            // the targeted register mask
        targetedPin->pin,                                                   // the targeted pin(s)
        ((targetedPin->mode)>>GPIO_prv_mode_offset) & GPIO_prv_2bits_mask, // the given mode inside mode value
        2                                                                   // number of bits extended
        );
    ((GPIO_t*)(targetedPin->port))->Mode_Register &= Loc_temp_register_mask;
    ((GPIO_t*)(targetedPin->port))->Mode_Register |= Loc_temp_register_value;
    
    
}

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
extern res_t GPIO_writePin(void* GPIO_PORT, uint16_t GPIO_PIN, uint8_t GPIO_Level)
{
    res_t Loc_returnStatus = Status_Ok;
    if (GPIO_PORT == NULL)
    {
        Loc_returnStatus = Status_NULL_ptr_Error;
    }
    else if (GPIO_PORT != GPIO_PORT_A &&
            GPIO_PORT != GPIO_PORT_B &&
            GPIO_PORT != GPIO_PORT_C &&
            GPIO_PORT != GPIO_PORT_D &&
            GPIO_PORT != GPIO_PORT_E &&
            GPIO_PORT != GPIO_PORT_H)
    {
        Loc_returnStatus = Status_invalid_port_Error;
    }
    
    // The pin value can't be invalid because of overflow on GPIO_PIN variable of 16bit size
    // no need to: Loc_returnStatus = Status_invalid_pin_Error;
    
    else if (GPIO_Level != GPIO_Level_HIGH && GPIO_Level != GPIO_Level_LOW)
    {
        Loc_returnStatus = Status_level_Error;
    }
    else
    {
        if (GPIO_Level == GPIO_Level_LOW)
        {
            // clear output pins using set/reset register
            ((GPIO_t*)GPIO_PORT)->Set_Reset_Data_Register = GPIO_PIN<<GPIO_prv_Half_Word;
        }
        else
        {
            // set output pins using set/reset register
            ((GPIO_t*)GPIO_PORT)->Set_Reset_Data_Register = GPIO_PIN;
        }
    }
    return Loc_returnStatus;
}

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
extern res_t GPIO_readPin(void* GPIO_PORT, uint16_t GPIO_PIN, uint8_t* GPIO_Level)
{
    res_t Loc_returnStatus = Status_Ok;
    if (GPIO_PORT == NULL || GPIO_Level == NULL)
    {
        Loc_returnStatus = Status_NULL_ptr_Error;
    }
    else if (GPIO_PORT != GPIO_PORT_A &&
            GPIO_PORT != GPIO_PORT_B &&
            GPIO_PORT != GPIO_PORT_C &&
            GPIO_PORT != GPIO_PORT_D &&
            GPIO_PORT != GPIO_PORT_E &&
            GPIO_PORT != GPIO_PORT_H)
    {
        Loc_returnStatus = Status_invalid_port_Error;
    }
    
    // The pin value can't be invalid because of overflow on GPIO_PIN variable of 16bit size
    // no need to: Loc_returnStatus = Status_invalid_pin_Error;
    
    else
    {
        // read pin value
        if (((GPIO_t*)GPIO_PORT)->Input_Data_Register & GPIO_PIN)
        {
            *GPIO_Level = GPIO_Level_HIGH;
        }
        else
        {
            *GPIO_Level = GPIO_Level_LOW;
        }
    }
    return Loc_returnStatus;
}
