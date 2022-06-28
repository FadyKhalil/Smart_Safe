/* **************************************************************************************
**       Author      :	Michael S. Ibrahim
**       Date        :	March 07, 2022
**       Version     :	V01
**       SWC         :	RCC
**       Description :	RCC module files for STM32F401CC
** **************************************************************************************/
#include "STD_TYPES.h"
#include "RCC.h"

#include "STM32F401CC.h"

#include "RCC_prv.h"
#include "RCC_cfg.h"
/*  Control Prescalar of buses; AHB, APB1, APB2
    Parameter Options are in RCC.h under the comment "Bus Arguments"
    You should adjust the prescalar value in RCC_cfg.h under the comment "Buses Prescalar Options"
*/
RCC_tenuStatus RCC_enuSelectBusPre(u8 Copy_u8Bus)
{
  RCC_tenuStatus Loc_u8Error = RCC_enuOk; /* Initialize the error status */
  u8 Loc_u8SelectedPre;
  u8 Loc_u8Pre;
  if (Copy_u8Bus == RCC_u8AHB) /* AHB Bus need 4 bits so it's in special case */
  {
    Loc_u8SelectedPre = RCC_u8AHB_PRE; /* Take user selected prescalar */
    Loc_u8Pre = RCC_u8AHB_PRE_INIT;    /* AHB Prescalar Initial value */
    RCC_pstrRegisters->CFGR &= ~(RCC_u32AHB_PRE_M);/* clear 4 bits of the prescalar */
    /* get the actual prescalar from passed value */
    while (Loc_u8SelectedPre)
    {
      if (Loc_u8SelectedPre == 64)
      {
        Loc_u8SelectedPre /= 2;
      } /* if */
      Loc_u8Pre++;
      Loc_u8SelectedPre /= 2;
    } /* while */
  }/* if */
  else
  {
    if (Copy_u8Bus == RCC_u8APB1)
    {
      Loc_u8SelectedPre = RCC_u8APB1_PRE; /* Take user selected prescalar */
      RCC_pstrRegisters->CFGR &= ~(RCC_u32APB1_PRE_M);/* clear 3 bits of the prescalar */
    } /* if */
    else
    {
      Loc_u8SelectedPre = RCC_u8APB2_PRE; /* Take user selected prescalar */
      RCC_pstrRegisters->CFGR &= ~(RCC_u32APB2_PRE_M);/* clear 3 bits of the prescalar */
    }                               /* else */
    Loc_u8Pre = RCC_u8APB_PRE_INIT; /* Prescalar Initial value */
    /* get the actual prescalar from passed value */
    while (Loc_u8SelectedPre)
    {
      Loc_u8Pre++;
      Loc_u8SelectedPre /= 2;
    } /* while */
  }/* else */
  /* Set the value of the prescalar */
  RCC_pstrRegisters->CFGR |= (Loc_u8Pre << Copy_u8Bus);

  return (Loc_u8Error);
} /* RCC_enuSelectBusPre */

/* Return readiness status of each clk as true or false
   First Parameter options are in RCC.h under the comment "Clk Arguments"
   Second Parameter is a pointer to the variable where you will receive the value
*/
RCC_tenuStatus RCC_enuRetClkRDY(u8 Copy_u8Clk, pu8 Copy_pu8ClkRDY)
{
  RCC_tenuStatus Loc_u8Error = RCC_enuOk;
  if(Copy_pu8ClkRDY != NULL)
  {
    if(Copy_u8Clk == RCC_u8HSI)
    {
      *Copy_pu8ClkRDY = (RCC_pstrRegisters->CR) & RCC_u32HSI_RDY_M;
    }/* if */
    else if((Copy_u8Clk == RCC_u8HSE_CRYSTAL) || (Copy_u8Clk == RCC_u8HSE_RC))
    {
      *Copy_pu8ClkRDY = (RCC_pstrRegisters->CR) & RCC_u32HSE_RDY_M;
    }/* else if */
    else if(Copy_u8Clk == RCC_u8PLL)
    {
      *Copy_pu8ClkRDY = (RCC_pstrRegisters->CR) & RCC_u32PLL_RDY_M;
    }/* else if */
    else
    {
      Loc_u8Error = RCC_enuNok;
    }/* else */
  }/* if */
  else
  {
    Loc_u8Error = RCC_enuNok;
  }/* else */

  return (Loc_u8Error);
} /* RCC_enuRetClkRDY */

/* Turn On/Off each Clk
   First Parameter Options are in RCC.h under the comment "Clk Arguments"
   Second Parameter Options are in RCC.h under the comment "TurnStat Arguments"
*/
RCC_tenuStatus RCC_enuTurnClk(u8 Copy_u8Clk, RCC_tenuTurn Copy_enuTurnStat)
{
  RCC_tenuStatus Loc_enuError = RCC_enuOk;
  switch (Copy_enuTurnStat)
  {
  case (RCC_enuOn):
    if(Copy_u8Clk == RCC_u8HSI)
    {
      (RCC_pstrRegisters->CR) |= (RCC_u32HSI_ON_M);
    }/* if */
    else if(Copy_u8Clk == RCC_u8HSE_CRYSTAL)
    {
      (RCC_pstrRegisters->CR) |= (RCC_u32HSE_CRYSTAL_ON_M);
    }/* else if */
    else if(Copy_u8Clk == RCC_u8HSE_RC)
    {
      (RCC_pstrRegisters->CR) |= (RCC_u32HSE_RC_ON_M);
    }/* else if */
    else if(Copy_u8Clk == RCC_u8PLL)
    {
      (RCC_pstrRegisters->CR) |= (RCC_u32PLL_ON_M);
    }/* else if */
    else
    {
      Loc_enuError = RCC_enuNok;
    }/* else */
    break;
  case (RCC_enuOff):
    if(Copy_u8Clk == RCC_u8HSI)
    {
      (RCC_pstrRegisters->CR) &= ~(RCC_u32HSI_ON_M);
    }/* if */
    else if(Copy_u8Clk == RCC_u8HSE_CRYSTAL)
    {
      (RCC_pstrRegisters->CR) &= ~(RCC_u32HSE_CRYSTAL_ON_M);
    }/* else if */
    else if(Copy_u8Clk == RCC_u8HSE_RC)
    {
      (RCC_pstrRegisters->CR) &= ~(RCC_u32HSE_RC_ON_M);
    }/* else if */
    else if(Copy_u8Clk == RCC_u8PLL)
    {
      (RCC_pstrRegisters->CR) &= ~(RCC_u32PLL_ON_M);
    }/* else if */
    else
    {
      Loc_enuError = RCC_enuNok;
    }/* else */
    break;
  default:
    Loc_enuError = RCC_enuNok;
  } /* switch */

  return (Loc_enuError);
} /* RCC_enuTurnClk */

/*  Control clk of each peripheral
   First Parameter Options are in RCC.h under the comment "Peripherals Ids"
   Second Parameter Options are in RCC.h under the comment "TurnStat Arguments"
*/
RCC_tenuStatus RCC_enuPerClk(RCC_tenuPer Copy_enuPeripheral, RCC_tenuTurn Copy_enuTurnStat)
{
  RCC_tenuStatus Loc_enuError = RCC_enuOk;
  switch (Copy_enuTurnStat)
  {
  case (RCC_enuOn):
    if ((Copy_enuPeripheral >= (32 * 3)) && (Copy_enuPeripheral < (32 * 4)))
    {
      (RCC_pstrRegisters->APB2ENR) |= (1 << (Copy_enuPeripheral % 32));
    } /* if */
    else if(Copy_enuPeripheral >= (32 * 2))
    {
      (RCC_pstrRegisters->APB1ENR) |= (1 << (Copy_enuPeripheral % 32));
    } /* else if */
    else if(Copy_enuPeripheral >= (32 * 1))
    {
      (RCC_pstrRegisters->AHB2ENR) |= (1 << (Copy_enuPeripheral % 32));
    }/* else if */
    else
    {
      (RCC_pstrRegisters->AHB1ENR) |= (1 << (Copy_enuPeripheral % 32));
    }/* else */
    break;
  case (RCC_enuOff):
    if ((Copy_enuPeripheral >= (32 * 3)) && (Copy_enuPeripheral < (32 * 4)))
    {
      (RCC_pstrRegisters->APB2ENR) &= ~(1 << (Copy_enuPeripheral % 32));
    } /* if */
    else if(Copy_enuPeripheral >= (32 * 2))
    {
      (RCC_pstrRegisters->APB1ENR) &= ~(1 << (Copy_enuPeripheral % 32));
    } /* else if */
    else if(Copy_enuPeripheral >= (32 * 1))
    {
      (RCC_pstrRegisters->AHB2ENR) &= ~(1 << (Copy_enuPeripheral % 32));
    }/* else if */
    else
    {
      (RCC_pstrRegisters->AHB1ENR) &= ~(1 << (Copy_enuPeripheral % 32));
    }/* else */
    break;
  default:
    Loc_enuError = RCC_enuNok;
  } /* switch */

  return (Loc_enuError);
} /* RCC_enuPerClk */
/* Configure PLL
   return: Error Status
   Parameter Options are in RCC.h under the comment "PLL Configurations"
*/
RCC_tenuStatus RCC_enuConfigPLL(RCC_tstrPLLConfig* Copy_pstrPLLConfig)
{
  u32 Loc_u32Temp = 0x24000000;/* PLLCFGR register initial value to work on */
  RCC_tenuStatus Loc_enuError = RCC_enuOk;
  u8 Loc_u8Pll_P = RCC_u8PLL_P_BASE + ((Copy_pstrPLLConfig->P)/2-1);
  if(Copy_pstrPLLConfig != NULL)
  {
    Loc_u32Temp |= (((Copy_pstrPLLConfig->Source)<<22) | (Loc_u8Pll_P<<16) | ((Copy_pstrPLLConfig->N)<<6) | (Copy_pstrPLLConfig->M));
    RCC_pstrRegisters->PLLCFGR = Loc_u32Temp;
  }/* if */
  else
  {
    Loc_enuError = RCC_enuNok;
  }/* else */

  return (Loc_enuError);
} /* RCC_enuConfigPLL */
/* Select system clk
    Describtion: Select the system clk but if you want PLL, you have to full configure it before and configure HSE also if you will need it
    Return: Error Status
    First Parameter Options are in RCC.h under the comment "Sys Clk" which is the needed clk
*/
RCC_tenuStatus RCC_enuSelectSysClk(u8 Copy_u8SysClk)
{
  RCC_tenuStatus Loc_enuError = RCC_enuOk;
  u8 Loc_u8RDY = 0;
  u16 Loc_u16TimeOut = 0;
  u32 Loc_u32Temp;
  switch(Copy_u8SysClk)
  {
  case(RCC_u8RUN_HSI):
    RCC_enuTurnClk(RCC_u8HSI, RCC_enuOn);
    RCC_enuRetClkRDY(RCC_u8HSI, &Loc_u8RDY);
    Loc_u16TimeOut = 0;
    while(!Loc_u8RDY && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      RCC_enuRetClkRDY(RCC_u8HSI, &Loc_u8RDY);
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    Loc_u32Temp = RCC_pstrRegisters->CFGR & RCC_u32CLR_SYSCLK_M;
    Loc_u32Temp |= RCC_u32SET_HSI_M;
    RCC_pstrRegisters->CFGR = Loc_u32Temp;
    Loc_u16TimeOut = 0;
    while(((RCC_pstrRegisters->CFGR & RCC_u32TEST_SYSCLK_M) != RCCu32TEST_HSI_M) && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    break;
  case(RCC_u8RUN_HSE_CRYSTAL):
    RCC_enuTurnClk(RCC_u8HSE_CRYSTAL, RCC_enuOn);
    RCC_enuRetClkRDY(RCC_u8HSE_CRYSTAL, &Loc_u8RDY);
    Loc_u16TimeOut = 0;
    while(!Loc_u8RDY && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      RCC_enuRetClkRDY(RCC_u8HSE_CRYSTAL, &Loc_u8RDY);
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    Loc_u32Temp = RCC_pstrRegisters->CFGR & RCC_u32CLR_SYSCLK_M;
    Loc_u32Temp |= RCC_u32SET_HSE_M;
    RCC_pstrRegisters->CFGR = Loc_u32Temp;
    Loc_u16TimeOut = 0;
    while(((RCC_pstrRegisters->CFGR & RCC_u32TEST_SYSCLK_M) != RCCu32TEST_HSE_M) && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    break;
  case(RCC_u8RUN_HSE_RC):
    RCC_enuTurnClk(RCC_u8HSE_RC, RCC_enuOn);
    RCC_enuRetClkRDY(RCC_u8HSE_RC, &Loc_u8RDY);
    Loc_u16TimeOut = 0;
    while(!Loc_u8RDY && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      RCC_enuRetClkRDY(RCC_u8HSE_RC, &Loc_u8RDY);
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    Loc_u32Temp = RCC_pstrRegisters->CFGR & RCC_u32CLR_SYSCLK_M;
    Loc_u32Temp |= RCC_u32SET_HSE_M;
    RCC_pstrRegisters->CFGR = Loc_u32Temp;
    Loc_u16TimeOut = 0;
    while(((RCC_pstrRegisters->CFGR & RCC_u32TEST_SYSCLK_M) != RCCu32TEST_HSE_M) && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    break;
  case(RCC_u8RUN_PLL):
    RCC_enuTurnClk(RCC_u8PLL, RCC_enuOn);
    RCC_enuRetClkRDY(RCC_u8PLL, &Loc_u8RDY);
    Loc_u16TimeOut = 0;
    while(!Loc_u8RDY && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      RCC_enuRetClkRDY(RCC_u8PLL, &Loc_u8RDY);
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    Loc_u32Temp = RCC_pstrRegisters->CFGR & RCC_u32CLR_SYSCLK_M;
    Loc_u32Temp |= RCC_u32SET_PLL_M;
    RCC_pstrRegisters->CFGR = Loc_u32Temp;
    Loc_u16TimeOut = 0;
    while(((RCC_pstrRegisters->CFGR & RCC_u32TEST_SYSCLK_M) != RCCu32TEST_PLL_M) && (Loc_u16TimeOut != RCC_u16TIME_OUT))
    {
      Loc_u16TimeOut++;
    }/* while */
    if(Loc_u16TimeOut == RCC_u16TIME_OUT)
    {
      Loc_enuError = RCC_enuNok;
    }/* if */
    break;
  default:
    Loc_enuError = RCC_enuNok;
  }/* switch */

  return(Loc_enuError);
}/* RCC_enuSelectSysClk */
