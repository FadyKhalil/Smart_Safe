/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Keypad
**       Description :	Keypad module files 
** **************************************************************************************/
#ifndef _KEYPAD_H
#define _KEYPAD_H
  typedef u8 Keypad_ValueType;
  typedef enum
  {
    Init = 0,
    Pressed,
    Not_Pressed
  }Switch_Status_e;
  typedef enum
  {
    Keypad_enuOk = 0,
    Keypad_enuNullPointer
  }Keypad_tenuErrorStatus;
  typedef struct
  {
    void* PORT;
    u16 Pin;
    u8 Mode;
  }Keypad_tsConfig;
  #define SWITCH_PULLUP		  GPIO_u8INPUT_PULLUP
  #define SWITCH_PULLDOWN		GPIO_u8INPUT_PULLDOWN
  #define SWITCH_FLOATIN		GPIO_u8INPUT_FLOATING
  #define SWITCH_PUSHPULL		GPIO_u8OUTPUT_PUSHPULL
  #define PORTA	GPIO_A
  #define PORTB	GPIO_B
  #define PORTC	GPIO_C
  #define PORTD	GPIO_D
  #define PORTE	GPIO_E
  #define PORTH	GPIO_H
  void Keypad_GetKeyValue(void);
  Keypad_tenuErrorStatus KeyPad_vidInit(void);
  void Keypad_u8GetPressedKey(pu8 Add_pu8Key);
  
#endif
