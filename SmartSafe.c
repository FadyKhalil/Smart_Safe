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
#include "Port.h"
/* MCAL */
#include "RCC.h"
/* HAL */
#include "Keypad.h"
#include "Lcd.h"
#include "EEPROM.h"
/* Own headers */
#include "SmartSafe.h"
#include "SmartSafe_prv.h"
#include "SmartSafe_cfg.h"
#include "SmartSafe_Lcfg.h"
/* Tracing */
#include "diag/Trace.h"
/* ////////////////////////////////////////////////////////////////////////////////////////// */
/*////////////////////////////////// Define //////////////////////////////////////////////////*/
#define SIZE_OF_MAX_PASSWORD	4
/* //////////////////////////////// Global Variables //////////////////////////////////////// */
/* Tasks Stacks */
u32 SmartSafe_Stack[TASK_STACK_SIZE];
u32 KeypadTask_Stack[TASK_STACK_SIZE];
u32 LcdTask_Stack[TASK_STACK_SIZE];

/*Clear Request for LCD*/
Lcd_Request_t Lcd_Req_Clear = {
	  .type = LCD_REQ_TYP__CMD,
	  .value = LCD_REQ__CLR_DISPLAY
};

/*Flag to check on saved password*/
u8 Smart_u8Password_Exist = 1;
static u8 EEPROM_arr_Buffer[4];
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


	/*Initialize the LCD*/
	LCD_init();

	/*Initialzie the keypad*/
	Keypad_enuInit();

	/*Intialize the EEPROM*/
	Port_vidDisableInterrupt();
	EEPROM_vidInit();
	Port_vidEnableInterrupt();

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


	/*To look at the state return from the keypad to know
	 * whether a keypressed or not
	 * */
	static volatile Keypad_tenuErrorStatus Keypad_Status;

	/*Variable to store the return key from keypad*/
	static u8 Loc_u8Key = ZERO_INIT;

	/*Welcome Screen*/
	LCD_displayString((u8*)"WELCOME TO SMART");
	LCD_Goto(6, 2);
	LCD_displayString((u8*)"SAFE");

	OS_vidDelay(500);

	/*Lcd clear the welcome screen*/
	LCD_requestRegister(Lcd_Req_Clear);



	while (1) {


		LCD_Goto(0,1);
		LCD_displayString((u8*)"A -> Login");
		LCD_Goto(0, 2);
		LCD_displayString((u8*)"B -> New User");

		OS_vidDelay(50);

		/*Cheking the return value*/
		Keypad_Status = Keypad_u8GetPressedKey(&Loc_u8Key);

		/*Condition to check*/
		if (Keypad_Status == Keypad_enuOk)
		{
			if((Loc_u8Key == '+') && (Smart_u8Password_Exist == 1))
			{
				LogIn();
			}
			else if(Loc_u8Key == '-')
			{
				NewUser();
			}
		}

		OS_vidDelay(26);
	}/* while */
}/* SmartSafe */




/*Enter the pass word function to fetch and read the keypad value*/
static void Enter_Pass(void)
{


	/*counter to check whether the password enter is wrong*/
	static volatile u8 Loc_u8PasswordWrong_Counter = 0;

	/*Checking Flag*/
	static volatile u8 Loc_u8LoopBreaker = 0;

	/*Received and saved password*/
	static volatile u32 ReceivePassword;

	Loc_u8LoopBreaker = 0;

	/*Checking the password with the password stored in the EEPROM*/
	while(!Loc_u8LoopBreaker)
	{

		ReceivePassword = Receive_Password();

		trace_printf("%d", EEPROM_arr_Buffer[4]);
		/*Checking the EEPROM */
		if((*((u32*)(EEPROM_arr_Buffer))) == ReceivePassword)
		{
			Loc_u8LoopBreaker = 1;

			LCD_Goto(13, 2);
			LCD_displayCharacter('O');
			LCD_displayCharacter('K');

			OS_vidDelay(1000);

			LCD_requestRegister(Lcd_Req_Clear);

		}/*If*/

		else
		{
			/*Increment the counter each time the password wrong*/
			Loc_u8PasswordWrong_Counter++;

			/*Check the password is wrong for 3 times*/
			if(Loc_u8PasswordWrong_Counter == 3)
			{
				/*Erase Sector of the application*/

			}/*if*/

			else
			{
				LCD_Goto(12, 2);
				LCD_displayCharacter('N');
				LCD_displayCharacter('O');
				LCD_displayCharacter('K');

				OS_vidDelay(1000);

				LCD_requestRegister(Lcd_Req_Clear);

			}/*else*/

		}/*else*/

	}/*while*/

}/*Enter_Pass*/


static u32 Receive_Password(void)
{

	static volatile u8 Received_arr_Buffer[4];

	static volatile u8 Loc_u8size = 4;

	static volatile u8 Loc_u8Index = 0;

	/*To look at the state return from the keypad to know
	 * whether a keypressed or not
	 * */
	static volatile Keypad_tenuErrorStatus Keypad_Status;

	/*Variable to store the return key from keypad*/
	static u8 Loc_u8Key = ZERO_INIT;

	LCD_requestRegister(Lcd_Req_Clear);

	LCD_Goto(0,1);

	/*Display enter password for user*/
	LCD_displayString((u8*)"ENTER PASS: ");

	OS_vidDelay(100);

	while(Loc_u8Index < Loc_u8size)
	{

		/*Cheking the return value*/
		OS_vidDelay(5);
		Keypad_Status = Keypad_u8GetPressedKey(&Loc_u8Key);

		/*Condition to check*/
		if (Keypad_Status == Keypad_enuOk)
		{
			LCD_displayCharacter('*');
			Received_arr_Buffer[Loc_u8Index++] = Loc_u8Key;
		}

	}/*while*/

	Loc_u8Index = 0;

	return (*((u32*)(Received_arr_Buffer)));

}/*Receive Password*/


/**/
static void LogIn(void)
{
	/*variable for checking EEPROM*/
	static u8 Loc_Checking_Password ;

//	OS_vidDelay(5);
	/*Check the first byte in the EEPROM*/
	Port_vidDisableInterrupt();
	EEPROM_ReadByte(0, &Loc_Checking_Password);
	Port_vidEnableInterrupt();
//	while(Timeout_Flag == 1)
//	{
//		EEPROM_ReadByte(0, &Loc_Checking_Password);
//	}

	/*Checking if no password*/
	if(Loc_Checking_Password == 0xFF)
	{
		LCD_requestRegister(Lcd_Req_Clear);
		/*Display no Password*/
		LCD_displayString((u8*)"NO SAVED");
		LCD_Goto(0,2);
		LCD_displayString((u8*)"PASSWORD");
		OS_vidDelay(1000);

		/*Add flag*/
		Smart_u8Password_Exist = 0;

		NewUser();

	}
	else
	{
		Enter_Pass();
	}
}


static void NewUser(void)
{
	static volatile u8 Loc_u8MatchingFlag = 0;

	/*To look at the state return from the keypad to know
	 * whether a keypressed or not
	 * */
	static volatile Keypad_tenuErrorStatus Keypad_Status;

	/*Variable to store the return key from keypad*/
	static u8 Loc_u8Key = ZERO_INIT;
	static volatile u8 Loc_u8FirstEnter[4] = {ZERO_INIT};
	static volatile u8 Loc_u8SecondEnter[4] = {ZERO_INIT};
	/*Counter Variable*/
	static volatile u8 Loc_u8CounterSizePass = ZERO_INIT;
	LCD_requestRegister(Lcd_Req_Clear);

	static u8 variable_check = 0;

	OS_vidDelay(5);

	while(!Loc_u8MatchingFlag)
	{
		*((u32*)Loc_u8FirstEnter) = 0x00000000;
		*((u32*)Loc_u8SecondEnter) = 0x00000000;
		LCD_requestRegister(Lcd_Req_Clear);
		LCD_Goto(0, 1);
		LCD_displayString((u8*)"Enter Pass: ");
		LCD_Goto(0, 2);
		LCD_displayString((u8*)"Re-Enter: ");
		LCD_Goto(12,1);
		OS_vidDelay(5);
		Loc_u8CounterSizePass = ZERO_INIT;

		/*Enter the password loop*/
		while(Loc_u8CounterSizePass < 4)
		{
			/*Cheking the return value*/
			Keypad_Status = Keypad_u8GetPressedKey(&Loc_u8Key);

			/*Condition to check*/
			if (Keypad_Status == Keypad_enuOk)
			{
				Loc_u8FirstEnter[Loc_u8CounterSizePass] = Loc_u8Key;
				LCD_displayCharacter('*');
				Loc_u8CounterSizePass++;
			}
			OS_vidDelay(5);

		}/*While*/

		LCD_Goto(12,2);
		OS_vidDelay(5);
		Loc_u8CounterSizePass = ZERO_INIT;

		/*Re enter the password loop*/
		while(Loc_u8CounterSizePass < 4)
		{
			OS_vidDelay(5);
			/*Cheking the return value*/
			Keypad_Status = Keypad_u8GetPressedKey(&Loc_u8Key);

			/*Condition to check*/
			if (Keypad_Status == Keypad_enuOk)
			{
				Loc_u8SecondEnter[Loc_u8CounterSizePass] = Loc_u8Key;
				LCD_displayCharacter('*');
				Loc_u8CounterSizePass++;
			}
		}/* while */


		if((*((u32*)Loc_u8FirstEnter)) == (*((u32*)Loc_u8SecondEnter)))
		{
			Loc_u8MatchingFlag = 1;
		}
	}/* while */

	EEPROM_WriteByte(0, Loc_u8FirstEnter[0]);
	OS_vidDelay(5);
	EEPROM_ReadByte(0, &variable_check);
	while(variable_check != Loc_u8FirstEnter[0]);

	EEPROM_WriteByte(1, Loc_u8FirstEnter[1]);
	OS_vidDelay(5);
	EEPROM_ReadByte(1, &variable_check);
	while(variable_check != Loc_u8FirstEnter[1]);

	EEPROM_WriteByte(2, Loc_u8FirstEnter[2]);
	OS_vidDelay(5);
	EEPROM_ReadByte(2, &variable_check);
	while(variable_check != Loc_u8FirstEnter[2]);

	EEPROM_WriteByte(3, Loc_u8FirstEnter[3]);
	OS_vidDelay(5);
	EEPROM_ReadByte(3, &variable_check);
	while(variable_check != Loc_u8FirstEnter[3]);

	Smart_u8Password_Exist = 1;

	/*Fetch the password in the EEPROM*/

	EEPROM_ReadByte(0, &EEPROM_arr_Buffer[0]);
	EEPROM_ReadByte(1, &EEPROM_arr_Buffer[1]);
	EEPROM_ReadByte(2, &EEPROM_arr_Buffer[2]);
	EEPROM_ReadByte(3, &EEPROM_arr_Buffer[3]);

	LCD_requestRegister(Lcd_Req_Clear);
}

/* ////////////////////////////////////////////////////////////////////////////////////////// */
