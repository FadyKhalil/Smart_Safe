/******************************************************************************
 *
 * Module     : GPIO Driver
 *
 * File Name  : GPIO_private.h
 *
 * Description: Header file for the STM32 GPIO Private Registers
 *
 * Author     : Osama Hamdy
 *
 *******************************************************************************/

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/*******************************************************************************
 *                          GPIO Registers                                     *
 *******************************************************************************/
typedef struct {
	volatile u32 GPIOx_MODER;
	volatile u32 GPIOx_OTYPER;
	volatile u32 GPIOx_OSPEEDR;
	volatile u32 GPIOx_PUPDR;
	volatile u32 GPIOx_IDR;
	volatile u32 GPIOx_ODR;
	volatile u32 GPIOx_BSRR;
	volatile u32 GPIOx_LCKR;
	volatile u32 GPIOx_AFRL;
	volatile u32 GPIOx_AFRH;
}GPIOx_Register_t;


#endif /* GPIO_PRIVATE_H_ */
