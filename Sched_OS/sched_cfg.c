/******************************************************************************
 *
 * Module     : SCHUDLER
 *
 * File Name  : sched_cfg.c
 *
 * Description: Configuration file for the STM32 SCHUDLER OS
 *
 * Author     : Osama Hamdy
 *
 *******************************************************************************/
#include "lcd.h"
#include"sched_cfg.h"
#include"sched.h"
#include "app.h"

const runnable_t runnablelist[MAX_TASKS]={
	[0]={
			.cbf=LCD_vidSched,
		    .Cyclic_TimeMs=2,
	},
	[1]={
			.cbf=lcd_print,
			.Cyclic_TimeMs=10
	}

};
