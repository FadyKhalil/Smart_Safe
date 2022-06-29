/******************************************************************************
 *
 * Module     : NVIC Driver
 *
 * File Name  : STK_interface.h
 *
 * Description: Header file for the STM32 Systick Driver
 *
 * Author     : Osama Hamdy
 *
 *******************************************************************************/
#ifndef STK_INERFACE_H_
#define STK_INERFACE_H_
#include "Std_types.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef void(*STK_cbf)(void);
typedef enum {
	STK_OK,
	STK_NOK,
	STK_NullPointerError
}STK_ErrorrState;

/*******************************************************************************
 *                                 SYSTICK  MASKS                             *
 *******************************************************************************/
#define         SYSTICK_INT_ON                0X00000002
#define         SYSTICK_INT_OFF 		      0X00000000
#define         SYSTICK_AHB_CLK               0X00000004
#define         SYSTICK_AHB_DIV_8_CLK         0X00000000
#define         SYSTICK_ENABLE                0X00000001
#define         SYSTICK_DISABLE               0X00000000

/*******************************************************************************
 *                            Fuction ProtoTypes                               *
 *******************************************************************************/
/********************************************************************************************
 * Public Function
 * Description : Intialization of Systick Timer Modes
 * Function Paramters : void
 * Function Return : void
 *******************************************************************************************/
void              STK_vidInit(void);
/********************************************************************************************
 * Public Function
 * Description : Set the timer value in milliseconds
 * Function Paramters : Copy_u32TimeMS
 * Function Return : Errot Status of Systick Timer
 *******************************************************************************************/
STK_ErrorrState   STK_SetTimeMS(u32 Copy_u32TimeMS);
/********************************************************************************************
 * Public Function
 * Description : Turn on Systick Timer
 * Function Paramters : void
 * Function Return : void
 *******************************************************************************************/
void              STK_Start(void);
/********************************************************************************************
 * Public Function
 * Description : Systick Timer Call Back Function
 * Function Paramters : Pointer to Function
 * Function Return : Errot Status of Systick Timer
 *******************************************************************************************/
STK_ErrorrState   STK_RegisterCBF(STK_cbf App_Cbf);


#endif /* STK_INERFACE_H_ */
