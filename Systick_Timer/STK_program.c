/******************************************************************************
 *
 * Module     : Systick Driver
 *
 * File Name  : STK_program.c
 *
 * Description: Source file for the STM32 Systick Driver
 *
 * Author     : Osama Hamdy
 *
 *******************************************************************************/
#include"Std_types.h"
#include"Bit_utils.h"
#include"STK_prv.h"
#include"STK_config.h"
#include"STK_inerface.h"
static STK_cbf CBF=NULL_PTR;
/*******************************************************************************
 *                            Fuction Definitions                              *
 *******************************************************************************/
/********************************************************************************************
 * Public Function
 * Description : Intialization of Systick Timer Modes
 * Function Paramters : void
 * Function Return : void
 *******************************************************************************************/
void STK_vidInit(void) {
	/* Configure Interrupt Mode */
	STK->STK_CTRL|= STK_INT;
	/*Configure Clock type  */
	STK->STK_CTRL|=STK_CLK;
}
/********************************************************************************************
 * Public Function
 * Description : Set the timer value in milliseconds
 * Function Paramters : Copy_u32TimeMS
 * Function Return : Errot Status of Systick Timer
 *******************************************************************************************/
STK_ErrorrState STK_SetTimeMS(u32 Copy_u32TimeMS) {
	/*Local Variable to store the Systick Error State*/
	STK_ErrorrState loc_Error_t = STK_OK;
	/*Check the type of Systick timer Clock Source Due to PreBuild Configuration*/
      if(STK_CLK == SYSTICK_AHB_CLK)
      {
    	  /* Insert the Time value in Load Register */
    	  STK->STK_LOAD = (Copy_u32TimeMS * CLK_VAL) / (MILLI_SEC);
      }
      else
      {
    	  /* Insert the Time value in Load Register */
    	  STK->STK_LOAD = (Copy_u32TimeMS * CLK_VAL) / (MILLI_SEC * 8);
      }
	return loc_Error_t;
}
/********************************************************************************************
 * Public Function
 * Description : Turn on Systick Timer
 * Function Paramters : void
 * Function Return : void
 *******************************************************************************************/
void STK_Start(void) {
	/* Clear the last value In Value Register */
	STK->STK_VAL=0;
	/* Enable the Systick timer*/
	STK->STK_CTRL |= SYSTICK_ENABLE;
}
/********************************************************************************************
 * Public Function
 * Description : Systick Timer Call Back Function
 * Function Paramters : Pointer to Function
 * Function Return : Errot Status of Systick Timer
 *******************************************************************************************/
STK_ErrorrState STK_RegisterCBF(STK_cbf App_Cbf) {
	/*Local Variable to store the Systick Error State*/
	STK_ErrorrState loc_Error_t;
	/* Checking the validity of Function Address*/
	if(App_Cbf != NULL_PTR)
	{
		STK_ErrorrState loc_Error_t = STK_OK;
		/* Calling the Call back Function in Systick Handler */
		CBF=App_Cbf;
	}
	else{
		/*Return Sytick Timer Null pointer Error*/
		loc_Error_t=STK_NullPointerError;
	}

	return loc_Error_t;
}
/********************************************************************************************
 * Public Function
 * Description : Systick Timer Interrupt Handler Function
 * Function Paramters : void
 * Function Return : void
 *******************************************************************************************/
void SysTick_Handler(void) {
	/* Systic Timer Interrupt Handler Call Back Function  */
	if(CBF != NULL_PTR)
	{
		CBF();
	}
}
