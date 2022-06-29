/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	RCC
**       Description :	RCC module files for STM32F401CC
** **************************************************************************************/
#ifndef _RCC_PRV_H
#define _RCC_PRV_H
    /* *************************** Limit Values ************************************************* */
    #define RCC_u8AHB_PRE_INIT                              0b0110/* Prescalar initial value */
    #define RCC_u8APB_PRE_INIT                              0b010 /* Prescalar initial value */
    #define RCC_u8PLL_P_BASE                                0
    #define RCC_u16TIME_OUT                                 60000
    /* ******************************************************************************************** */
    /* ******************************** Masks ****************************************************** */
    #define RCC_u32AHB_PRE_M                              0x000000F0
    #define RCC_u32APB1_PRE_M                             0x00001C00
    #define RCC_u32APB2_PRE_M                             0x0000E000
    #define RCC_u32HSI_RDY_M                              0x00000002
    #define RCC_u32HSE_RDY_M                              0x00020000
    #define RCC_u32PLL_RDY_M                              0x02000000
    #define RCC_u32HSI_ON_M                               0x00000001
    #define RCC_u32HSE_CRYSTAL_ON_M                       0x00010000
    #define RCC_u32HSE_RC_ON_M                            0x00050000
    #define RCC_u32PLL_ON_M                               0x01000000
    #define RCC_u32SET_HSI_M                              0x00000000                         
    #define RCC_u32SET_HSE_M                              0x00000001      
    #define RCC_u32SET_PLL_M                              0x00000002          
    #define RCC_u32CLR_SYSCLK_M                           0xFFFFFFFC          
    #define RCC_u32TEST_SYSCLK_M                          0x0000000C      
    #define RCCu32TEST_HSI_M                              0x00000000      
    #define RCCu32TEST_HSE_M                              0x00000004      
    #define RCCu32TEST_PLL_M                              0x00000008  
    /* ******************************************************************************************** */
#endif