/******************************************************************************
 *
 * Module: LCD HAL Driver
 *
 * Layer : HAL
 *
 * File Name: lcd_cfg.c
 *
 * Description: Configuration Source file for the LCD Driver
 *
 * Author: Osama Hamdy
 *
 *******************************************************************************/

#include "Std_types.h"
#include"GPIO_private.h"
#include"GPIO_interface.h"
#include"lcd_cfg.h"
#include"lcd.h"

const Lcd_cfg_t lcd = {

/*Configuration of Control PINS */

.Rs={ GPIOA_BASE_ADDRESS, GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_00, GPIO_u8SPEED_HIGH },
.Rw={ GPIOA_BASE_ADDRESS, GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_01,GPIO_u8SPEED_HIGH },
.En={ GPIOA_BASE_ADDRESS,GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_02, GPIO_u8SPEED_HIGH },

		/*Configuration of Data PINS */

		.Data[0]={ GPIOB_BASE_ADDRESS, GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_00,GPIO_u8SPEED_HIGH },
		.Data[1]={ GPIOB_BASE_ADDRESS,GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_01, GPIO_u8SPEED_HIGH },
		.Data[2]={GPIOB_BASE_ADDRESS, GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_02,GPIO_u8SPEED_HIGH },
		.Data[3]={ GPIOB_BASE_ADDRESS,GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_03, GPIO_u8SPEED_HIGH },
		.Data[4]={GPIOA_BASE_ADDRESS, GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_04,GPIO_u8SPEED_HIGH },
		.Data[5]={ GPIOB_BASE_ADDRESS,GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_05, GPIO_u8SPEED_HIGH },
		.Data[6]={GPIOB_BASE_ADDRESS, GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_06,GPIO_u8SPEED_HIGH },
		.Data[7]={GPIOB_BASE_ADDRESS, GPIO_u32MODE_OUTPUT_PP, GPIO_PIN_07,GPIO_u8SPEED_HIGH } ,};
