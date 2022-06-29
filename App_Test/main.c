/*
 * main.c
 *
 *  Created on: Apr 11, 2022
 *      Author: fady
 */

#include "Std_types.h"
#include "Bit_utils.h"
#include "diag/Trace.h"
#include "RCC_interface.h"
#include "lcd.h"
#include "sched.h"
#include "app.h"
void lcd_print(void)
{
	static Buffer_t string={"osama",7,0};
	Lcd_vidWriteString(&string,0,0);
}
int main(void)
{
	Rcc_Enable_clock(HSI_CLK);
	Rcc_Control_system_clk(HSI_CLK);
	LCD_vidInit();
	Sched_Init();
	Sched_Start();

	return 0;
}
