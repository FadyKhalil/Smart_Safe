/* **************************************************************************************
 **       Author      :	Smart Safe Group
 **       Date        :	June 29, 2022
 **       Version     :	V1.0
 **       SWC         :	SmartSafe
 **       Description :	Smart Safe Application
 ** **************************************************************************************/
/* LIB */
#include "StdTypes.h"
/* OS */
#include "Core.h"
/* MCAL */
#include "RCC.h"
#include "Gpio.h"
/* HAL */
#include "Keypad.h"
#include "Lcd.h"
#include "I2C.h"
#include "EEPROM.h"
/* Own headers */
#include "SmartSafe.h"
#include "SmartSafe_prv.h"
#include "SmartSafe_cfg.h"
#include "SmartSafe_Lcfg.h"
/* Tracing */
#include "diag/Trace.h"
/* ////////////////////////////////////////////////////////////////////////////////////////// */

/* //////////////////////////////// Global Variables //////////////////////////////////////// */
/* Tasks Stacks */
u32 SmartSafe_Stack[TASK_STACK_SIZE];
u32 KeypadTask_Stack[TASK_STACK_SIZE];
u32 LcdTask_Stack[TASK_STACK_SIZE];

//strOSSem_t* SemaphorePtr = NULL;
/* ////////////////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////// Entry Point ////////////////////// */
int main(void) {

	/*Initialize the hardware*/
	RCC_enuTurnClk(RCC_u8HSI, RCC_enuOn);
	RCC_enuSelectSysClk(RCC_u8RUN_HSI);
	RCC_enuPerClk(RCC_enuGPIOA, RCC_enuOn);
	RCC_enuPerClk(RCC_enuGPIOB, RCC_enuOn);
	RCC_enuPerClk(RCC_enuUSART1, RCC_enuOn);
	RCC_enuPerClk(RCC_enuI2C1, RCC_enuOn);


	I2C_Config ConfigI2c = {

				.Clock_Selection = 16,
				.Clock_Stretching = CLOCK_STRETCHING_ENABLE,
				.Mode_Selection = DISABLE,
				.Protocol = I2C_1,
				.Desired_Duty_Cycle = 100000

	};

	GPIO_tstrPinConfiguration Gpio_cfg = {
				.GPIO_Mode = GPIO_u8ALTFUNC_OPENDRAIN_PULLUP,
				.GPIO_Pin = GPIO_PIN09 | GPIO_PIN06,
				.GPIO_Port = GPIO_B,
				.GPIO_Speed = GPIO_Speed_Very_High,
				.GPIO_ALTF = GPIO_ALTERNATIVE_I2C
	};


	Gpio_enuPinConfigurationInit(&Gpio_cfg);

	/*Initialize the LCD*/
	LCD_init();

	/*Initialzie the keypad*/
	Keypad_enuInit();

	/*Initialize the I2C*/
	I2C_enuVidInit(&ConfigI2c);

	/*Initialize task smart safe*/
	OS_vidCreateTask(SmartSafe_T, 0, SmartSafe_Stack, TASK_STACK_SIZE);
	OS_vidCreateTask(Keypad_GetKeyValue_T, 2, KeypadTask_Stack, TASK_STACK_SIZE);
	OS_vidCreateTask(LCD_Task, 1, LcdTask_Stack, TASK_STACK_SIZE);

	/*Os start*/
	OS_vidStart();

	while (1) {

	}/* while */

	return (0);
}/* main */

/* //////////////////////////////////////// Tasks /////////////////////////////////////////// */
void SmartSafe_T(void) {
	u8 Loc_s8Key = ZERO_INIT;
	u8 Loc_u8EEPROMvalue = ZERO_INIT;
	Keypad_tenuErrorStatus Keypad_Status;
	while (1) {
		Keypad_Status = Keypad_u8GetPressedKey(&Loc_s8Key);
		if (Keypad_Status == Keypad_enuOk)
		{

			LCD_displayCharacter(Loc_s8Key);
			EEPROM_WriteByte(0, Loc_s8Key);
			EEPROM_ReadByte(0, &Loc_u8EEPROMvalue);
		}
		OS_vidDelay(26);
	}/* while */
}/* T1 */

/* ////////////////////////////////////////////////////////////////////////////////////////// */
