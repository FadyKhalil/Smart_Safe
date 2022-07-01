/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	NVIC
**       Description :	NVIC module files
** **************************************************************************************/
#ifndef _NVIC_PRV_H
#define _NVIC_PRV_H
  /* **************************** MACROS ************************************************** */
  /* Limit of connected external peripherals */
  #define NVIC_u8EXT_PER_LIMIT                          85
  /* Register size */
  #define NVIC_u8REG_SIZE                               32
  /* Group lvls */
  #define NVIC_u8_16_LVL                                16
  #define NVIC_u8_8_LVL                                 8
  #define NVIC_u8_4_LVL                                 4
  #define NVIC_u8_2_LVL                                 2
  /* Shift masks */
  #define NVIC_u8_SHIFT_4                               4
  #define NVIC_u8_SHIFT_5                               5
  #define NVIC_u8_SHIFT_6                               6
  #define NVIC_u8_SHIFT_7                               7
  /* ************************************************************************************** */
#endif