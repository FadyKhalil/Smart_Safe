/******************************************************************************
 *
 * Module     : Systick Driver
 *
 * File Name  : STK_prc.h
 *
 * Description: Private file for the STM32 Systick Driver
 *
 * Author     : Osama Hamdy
 *
 *******************************************************************************/

#ifndef STK_PRV_H_
#define STK_PRV_H_
typedef struct
{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;

}STK_Reg_t;

#define       STK               ((STK_Reg_t*)0xE000E010)

#endif /* STK_PRV_H_ */
