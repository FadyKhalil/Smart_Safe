/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	March 07, 2022
**       Version     :	V01
**       SWC         :	RCC
**       Description :	RCC module files for STM32F401CC
** **************************************************************************************/
#ifndef _RCC_H
#define _RCC_H
  /* ********** typedef Section ************** */
  /* PLL Configurations */
  typedef struct
  {
    u8  Source;    /* write '0' to select 'HSI' -- write '1' to select 'HSE' as the PLL source  */
    u8  P;         /* write of the range --> 2, 4, 6, 8 */
    u16 N;         /* write of the range --> 192 to 432 */
    u8  M;         /* write of the range --> 2 to 63 */
  }RCC_tstrPLLConfig;
  /* Peripherals Ids */
  typedef enum
  {
    RCC_enuGPIOA=0,
    RCC_enuGPIOB,
    RCC_enuGPIOC,
    RCC_enuGPIOD,
    RCC_enuGPIOE,
    RCC_enuGPIOH=7,
    RCC_enuDMA1=21,
    RCC_enuTIM2=32*2,
    RCC_enuTIM1=32*3,
    RCC_enuUSART1=32*3+4
  }RCC_tenuPer; 
  /* TurnStat Arguments */
  typedef enum
  {
    RCC_enuOn,
    RCC_enuOff
  }RCC_tenuTurn;
  /* Error Types */
  typedef enum
  {
    RCC_enuOk,
    RCC_enuNok
  }RCC_tenuStatus;
  /* ************** #define Section ************************* */
  /* Bus Arguments */
  #define RCC_u8APB2                  13
  #define RCC_u8APB1                  10
  #define RCC_u8AHB                   4
  /* Clk Arguments */
  #define RCC_u8HSI                   0   
  #define RCC_u8HSE_CRYSTAL           1
  #define RCC_u8HSE_RC                2
  #define RCC_u8PLL                   3
  /* Sys Clk */
  #define RCC_u8RUN_HSI               0   
  #define RCC_u8RUN_HSE_CRYSTAL       1
  #define RCC_u8RUN_HSE_RC            2
  #define RCC_u8RUN_PLL               3
  /* ************** Fns Prototypes Section ***************************** */
  /*  Control Prescalar of buses; AHB, APB1, APB2
      Parameter Options are in RCC.h under the comment "Bus Arguments"
      You should adjust the prescalar value in RCC_cfg.h under the comment "Buses Prescalar Options"
  */
  RCC_tenuStatus RCC_enuSelectBusPre(u8 Copy_u8Bus);
  /* Return readiness status of each clk as true or false
     First Parameter options are in RCC.h under the comment "Clk Arguments"
     Second Parameter is a pointer to the variable where you will receive the value
  */
  RCC_tenuStatus RCC_enuRetClkRDY(u8 Copy_u8Clk, pu8 Copy_pu8ClkRDY);
  /* Turn On/Off each Clk
     First Parameter Options are in RCC.h under the comment "Clk Arguments"
     Second Parameter Options are in RCC.h under the comment "TurnStat Arguments"
  */
  RCC_tenuStatus RCC_enuTurnClk(u8 Copy_u8Clk, RCC_tenuTurn Copy_enuTurnStat);
  /*  Control clk of each peripheral
     First Parameter Options are in RCC.h under the comment "Peripherals Ids"
     Second Parameter Options are in RCC.h under the comment "TurnStat Arguments"
  */
  RCC_tenuStatus RCC_enuPerClk(RCC_tenuPer Copy_enuPeripheral, RCC_tenuTurn Copy_enuTurnStat);
  /* Configure PLL
     return: Error Status
     Parameter Options are in RCC.h under the comment "PLL Configurations"
  */
  RCC_tenuStatus RCC_enuConfigPLL(RCC_tstrPLLConfig* Copy_pstrPLLConfig);
  /* Select system clk
     Return: Error Status
     First Parameter Options are in RCC.h under the comment "Sys Clk" which is the needed clk
  */
  RCC_tenuStatus RCC_enuSelectSysClk(u8 Copy_u8SysClk);

#endif

