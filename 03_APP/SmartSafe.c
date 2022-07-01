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
#include "Stepper.h"
/* Own headers */
#include "SmartSafe.h"
#include "SmartSafe_prv.h"
#include "SmartSafe_cfg.h"
#include "SmartSafe_Lcfg.h"
// /* Tracing */
// #include "diag/Trace.h"
/* ////////////////////////////////////////////////////////////////////////////////////////// */

/*////////////////////////////////// Define //////////////////////////////////////////////////*/

/* //////////////////////////////// Global Variables //////////////////////////////////////// */
/* Tasks Stacks */
u32 SmartSafeTask_Stack[TASK_STACK_SIZE];
u32 StepperTask_Stack[TASK_STACK_SIZE];
u32 KeypadTask_Stack[TASK_STACK_SIZE];
u32 LcdTask_Stack[TASK_STACK_SIZE];
/*Clear Request for LCD*/
Lcd_Request_t Lcd_Req_Clear = {
	  .type = LCD_REQ_TYP__CMD,
	  .value = LCD_REQ__CLR_DISPLAY
};
/*Received and saved password*/
static volatile u8 EEPROM_arr_Buffer[4];
static volatile SmartSafe_enuLockState_t SmartSafe_enuLockState = SmartSafe_enuLockState_Locked;
static volatile u8 SmartSafe_u8PasswordExistance = ZERO_INIT;
/* ////////////////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////// Entry Point ////////////////////// */
int main(void) {
	/*Init the hardware*/
	RCC_enuTurnClk(RCC_u8HSI, RCC_enuOn);
	RCC_enuSelectSysClk(RCC_u8RUN_HSI);
	RCC_enuPerClk(RCC_enuGPIOA, RCC_enuOn);
	RCC_enuPerClk(RCC_enuGPIOB, RCC_enuOn);
	RCC_enuPerClk(RCC_enuUSART1, RCC_enuOn);
	RCC_enuPerClk(RCC_enuI2C1, RCC_enuOn);
	/*Init the LCD*/
	LCD_init();
	/*Init the keypad*/
	Keypad_enuInit();
  /* Init the Stepper */ 
  Stepper_vidInit();
  /*Init the EEPROM*/
	EEPROM_vidInit();
	EEPROM_ReadByte(0, (u8*)&EEPROM_arr_Buffer[0]);
	EEPROM_ReadByte(1, (u8*)&EEPROM_arr_Buffer[1]);
	EEPROM_ReadByte(2, (u8*)&EEPROM_arr_Buffer[2]);
	EEPROM_ReadByte(3, (u8*)&EEPROM_arr_Buffer[3]);

	if(EEPROM_arr_Buffer[0] != 0xFF)
	{
    SmartSafe_u8PasswordExistance = 1;
  }/* if */
  else
  {
    /* MISRA */
  }/* else */

	/* Init task smart safe*/
	OS_vidCreateTask(SmartSafe_T, 0, SmartSafeTask_Stack, TASK_STACK_SIZE);
	OS_vidCreateTask(Keypad_GetKeyValue_T, 2, KeypadTask_Stack, TASK_STACK_SIZE);
	OS_vidCreateTask(LCD_Task, 1, LcdTask_Stack, TASK_STACK_SIZE);
	OS_vidCreateTask(Stepper_vidMasterStepper_T, 3, StepperTask_Stack, TASK_STACK_SIZE);
	/* Os start */
	OS_vidStart();
	while (1);

	return (0);
}/* main */
/* //////////////////////////////////////// Tasks /////////////////////////////////////////// */
void SmartSafe_T(void) {
	/*To look at the state return from the keypad to know
	 * whether a keypressed or not
	 * */
	static volatile Keypad_tenuErrorStatus Keypad_Status;
	/*Variable to store the return key from keypad*/
	static volatile u8 Loc_u8Key = ZERO_INIT;
	/*Welcome Screen*/
	LCD_displayString((u8*)"WELCOME TO SMART");
	LCD_Goto(6, 2);
	LCD_displayString((u8*)"SAFE");
	OS_vidDelay(2000);
	/*Lcd clear the welcome screen*/
	LCD_requestRegister(Lcd_Req_Clear);
	while (1) {
    LCD_Goto(0,1);
    LCD_displayString((u8*)"A-> Lock/Unlock");
    LCD_Goto(0, 2);
    LCD_displayString((u8*)"B-> New Password");
    OS_vidDelay(500);
    /*Cheking the return value*/
    Keypad_Status = Keypad_u8GetPressedKey((u8*)&Loc_u8Key);
    /*Condition to check*/
    if (Keypad_Status == Keypad_enuOk)
    {
      if(Loc_u8Key == '+')
      {
        Login();
      }/* if */
      else if(Loc_u8Key == '-')
      {
        NewUser();
      }/* else if */
    }/* if */
	}/* while */
}/* SmartSafe */
static u32 Receive_Password(void)
{
	static volatile u8 Received_arr_Buffer[4];
	static volatile u8 Loc_u8size = 4;
	static volatile u8 Loc_u8Index = 0;
	/*To look at the state return from the keypad to know whether a keypressed or not */
	static volatile Keypad_tenuErrorStatus Keypad_Status;
	/*Variable to store the return key from keypad*/
	static u8 Loc_u8Key = ZERO_INIT;
	LCD_requestRegister(Lcd_Req_Clear);
	LCD_Goto(0,1);
	/*Display enter password for user*/
	LCD_displayString((u8*)"ENTER PASS: ");
	while(Loc_u8Index < Loc_u8size)
	{
		OS_vidDelay(1);
		/*Cheking the return value*/
		Keypad_Status = Keypad_u8GetPressedKey(&Loc_u8Key);
		/*Condition to check*/
		if (Keypad_Status == Keypad_enuOk)
		{
			LCD_displayCharacter('*');
			Received_arr_Buffer[Loc_u8Index++] = Loc_u8Key;
		}/* if */
	}/*while*/
	Loc_u8Index = 0;
	return (*((u32*)(Received_arr_Buffer)));
}/*Receive Password*/
/**/
static void Login(void)
{
	/*Checking if no password*/
	if(SmartSafe_u8PasswordExistance == ZERO_INIT)
	{
		LCD_requestRegister(Lcd_Req_Clear);
		/*Display no Password*/
		LCD_displayString((u8*)"NO SAVED");
		LCD_Goto(0,2);
		LCD_displayString((u8*)"PASSWORD");
		OS_vidDelay(1000);
		NewUser();
	}/* if */
	else
	{
		LCD_requestRegister(Lcd_Req_Clear);
		OS_vidDelay(1);
		Enter_Pass();
	}/* else */
}/* Login */
/*Enter the pass word function to fetch and read the keypad value*/
static void Enter_Pass(void)
{
	/*counter to check whether the password enter is wrong*/
	static volatile u8 Loc_u8PasswordWrong_Counter = ZERO_INIT;
	/*Checking Flag*/
	static volatile u8 Loc_u8LoopBreaker = ZERO_INIT;
	static volatile u32 ReceivePassword;
  static volatile Stepper_enuState_t Loc_enuState;
	/*****/
  /*Checking the password with the password stored in the EEPROM*/
	while(!Loc_u8LoopBreaker)
	{
		ReceivePassword = Receive_Password();
		/*Checking the EEPROM */
		if((*((u32*)(EEPROM_arr_Buffer))) == ReceivePassword)
		{
			Loc_u8LoopBreaker = 1;
			LCD_Goto(13, 2);
      LCD_displayString((u8*)"OK");
      Loc_u8PasswordWrong_Counter = ZERO_INIT;
      SmartSafe_enuLockState ^= 1;
      Loc_enuState = Stepper_vidGetState(STEPPER_u8STEPPER0);
      if(Loc_enuState != Stepper_enuState_Busy)
      {
        Stepper_vidSetDirection(STEPPER_u8STEPPER0, SmartSafe_enuLockState);
        Stepper_vidMoveAngle(STEPPER_u8STEPPER0, 90);
      }/* if */
			OS_vidDelay(1000);
			LCD_requestRegister(Lcd_Req_Clear);
		}/* if */
		else
		{
			/*Increment the counter each time the password wrong*/
			Loc_u8PasswordWrong_Counter++;
			/*Check the password is wrong for 3 times*/
			if(Loc_u8PasswordWrong_Counter == 3)
			{
				/*Erase Sector of the application*/
			}/*if*/
      else if(Loc_u8PasswordWrong_Counter == 2)
      {
				LCD_Goto(0, 2);
        LCD_displayString((u8*)"Next Try->Erase App"); 
				OS_vidDelay(2000);
				LCD_requestRegister(Lcd_Req_Clear);
      }
			else
			{
				LCD_Goto(12, 2);
        LCD_displayString((u8*)"NOK"); 
				OS_vidDelay(1000);
				LCD_requestRegister(Lcd_Req_Clear);
			}/*else*/
		}/*else*/
	}/*while*/
  Loc_u8LoopBreaker = ZERO_INIT;
}/*Enter_Pass*/
static void NewUser(void)
{
	static volatile u8 Loc_u8CheckValue = ZERO_INIT;
	static volatile u8 Loc_u8MatchingFlag = ZERO_INIT;
	/*To look at the state return from the keypad to know whether a keypressed or not */
	static volatile Keypad_tenuErrorStatus Keypad_Status;
	/*Variable to store the return key from keypad*/
	static volatile u8 Loc_u8Key = ZERO_INIT;
	static volatile u8 Loc_u8FirstEnter[4] = {ZERO_INIT};
	static volatile u8 Loc_u8SecondEnter[4] = {ZERO_INIT};
	/*Counter Variable*/
	static volatile u8 Loc_u8CounterSizePass = ZERO_INIT;
  if((SmartSafe_enuLockState == SmartSafe_enuLockState_Unlocked) || (SmartSafe_u8PasswordExistance == ZERO_INIT))
  {
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
      Loc_u8CounterSizePass = ZERO_INIT;
      /*Enter the password loop*/
      while(Loc_u8CounterSizePass < 4)
      {
        OS_vidDelay(1);
        /*Cheking the return value*/
        Keypad_Status = Keypad_u8GetPressedKey((u8*)&Loc_u8Key);
        /*Condition to check*/
        if (Keypad_Status == Keypad_enuOk)
        {
          Loc_u8FirstEnter[Loc_u8CounterSizePass] = Loc_u8Key;
          LCD_displayCharacter('*');
          Loc_u8CounterSizePass++;
        }/* if */
      }/*While*/
      LCD_Goto(12,2);
      Loc_u8CounterSizePass = ZERO_INIT;
      /*Re enter the password loop*/
      while(Loc_u8CounterSizePass < 4)
      {
        OS_vidDelay(1);
        /*Cheking the return value*/
        Keypad_Status = Keypad_u8GetPressedKey((u8*)&Loc_u8Key);
        /*Condition to check*/
        if (Keypad_Status == Keypad_enuOk)
        {
          Loc_u8SecondEnter[Loc_u8CounterSizePass] = Loc_u8Key;
          LCD_displayCharacter('*');
          Loc_u8CounterSizePass++;
        }/* if */
      }/* while */
      if((*((u32*)Loc_u8FirstEnter)) == (*((u32*)Loc_u8SecondEnter)))
      {
        Loc_u8MatchingFlag = 1;
      }/* if */
    }/* while */
    EEPROM_WriteByte(0, Loc_u8FirstEnter[0]);
    OS_vidDelay(5);
    EEPROM_ReadByte(0, (u8*)&Loc_u8CheckValue);
    while(Loc_u8CheckValue != Loc_u8FirstEnter[0]);

    EEPROM_WriteByte(1, Loc_u8FirstEnter[1]);
    OS_vidDelay(5);
    EEPROM_ReadByte(1, (u8*)&Loc_u8CheckValue);
    while(Loc_u8CheckValue != Loc_u8FirstEnter[1]);
    
    EEPROM_WriteByte(2, Loc_u8FirstEnter[2]);
    OS_vidDelay(5);
    EEPROM_ReadByte(2, (u8*)&Loc_u8CheckValue);
    while(Loc_u8CheckValue != Loc_u8FirstEnter[2]);
    
    EEPROM_WriteByte(3, Loc_u8FirstEnter[3]);
    OS_vidDelay(5);
    EEPROM_ReadByte(3, (u8*)&Loc_u8CheckValue);
    while(Loc_u8CheckValue != Loc_u8FirstEnter[3]);

    SmartSafe_u8PasswordExistance = 1;

    EEPROM_ReadByte(0, (u8*)&EEPROM_arr_Buffer[0]);
    EEPROM_ReadByte(1, (u8*)&EEPROM_arr_Buffer[1]);
    EEPROM_ReadByte(2, (u8*)&EEPROM_arr_Buffer[2]);
    EEPROM_ReadByte(3, (u8*)&EEPROM_arr_Buffer[3]);

    LCD_requestRegister(Lcd_Req_Clear);
    Loc_u8MatchingFlag = ZERO_INIT;
    OS_vidDelay(1);
  }/* if */
  else
  {
    LCD_requestRegister(Lcd_Req_Clear);
    LCD_Goto(0, 1);
    LCD_displayString((u8*)"Unlock The Safe!"); 
    OS_vidDelay(2000);
    LCD_requestRegister(Lcd_Req_Clear);
    OS_vidDelay(1);
  }/* else */
}/* NewUser */
/* ////////////////////////////////////////////////////////////////////////////////////////// */
