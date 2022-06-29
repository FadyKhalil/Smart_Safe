/*
 * Sched_cfg.c
 *
 *  Created on: Apr 2, 2022
 *      Author: fady
 */

#include "Scheduler.h"
#include "Sched_cfg.h"
#include "../HAL/LCD/Lcd.h"
#include "../HAL/KEYPAD/Keypad.h"
#include "../Application/App.h"


const Sched_tstrRunnable AppList[TASKS] = {

		[LCD_TASK]= {
			.CallBack_t = LCD_Task,
			.CyclicTime_ms = 1
		},

		[CALCULATOR] = {
			.CallBack_t = Calculator,
			.CyclicTime_ms = 20
		},

		[KEYPAD] =
		{
				.CallBack_t = Keypad_GetKeyValue,
				.CyclicTime_ms = 5
		}

};

