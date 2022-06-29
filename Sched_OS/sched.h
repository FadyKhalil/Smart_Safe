/******************************************************************************
 *
 * Module     : SCHDULER
 *
 * File Name  : sched.h
 *
 * Description: Header file for the STM32 SCDULER OS
 *
 * Author     : Osama Hamdy
 *
 *******************************************************************************/
#include"Std_types.h"
#include"Bit_utils.h"
#include"sched_cfg.h"
#ifndef SCHED_H_
#define SCHED_H_
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef struct {
	void (*cbf)(void);
	u32 Cyclic_TimeMs;
}runnable_t;
/*******************************************************************************
 *                            Fuction ProtoTypes                               *
 *******************************************************************************/
/*
 * Public Function
 * Description : Intialization of the Schduler
 * Function Parameter : void
 * Function Return : void
 * */
void Sched_Init(void);
/*
 * Public Function
 * Description : Starting the Schduler & Systick Timer
 * Function Parameter : void
 * Function Return : void
 * */
void Sched_Start(void);
/*
 * Public Function
 * Description : Get the number of Schduler TimeMsec
 * Function Parameter : void
 * Function Return : number of TimeMsec
 * */
u32 Sched_getTimeMs(void);
/*
 * Public Function
 * Description : Incrementing the value of Operating System Flag
 * Function Parameter : void
 * Function Return : void
 * */
void Sched_OsFlag(void);
#endif /* SCHED_H_ */
