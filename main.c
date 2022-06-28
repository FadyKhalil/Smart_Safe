/*
 * main.c
 *
 *  Created on: Apr 11, 2022
 *      Author: fady
 */

#include "Services/Std_types.h"
#include "diag/Trace.h"
#include "Scheduler/Scheduler.h"
#include "HAL/KEYPAD/Keypad.h"
#include "HAL/LCD/Lcd.h"
#include "Application/App.h"

extern Sched_tstrRunnable AppList[];

int main(void)
{

	KeyPad_vidInit();
	LCD_init();
	Sched_vidInit();
	Sched_vidRegisterRunnable(AppList[LCD_TASK], 0);
	Sched_vidRegisterRunnable(AppList[CALCULATOR], 2);
	Sched_vidRegisterRunnable(AppList[KEYPAD], 1);
	Sched_vidStart();

	return 0;
}
