/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 29, 2022
**       Version     :	V1.0
**       SWC         :	SmartSafe
**       Description :	Smart Safe Application
** **************************************************************************************/
#ifndef _SMARTSAFE_PRV_H
#define _SMARTSAFE_PRV_H
	/* ////////////////////////////////// MACROS //////////////////////////////////////////////// */
	#define SIZE				                            ((u8)(10))
	#define TASK_STACK_SIZE			                    ((u8)(100))
	/* /////////////////////////////////////////////////////////////////////////////////////////// */


	/*//////////////////////////////Function Prototype ///////////////////////////////////////////*/
	static void Enter_Pass(void);
	static u32 Receive_Password(void);
	static void LogIn(void);
	static void NewUser(void);

#endif
