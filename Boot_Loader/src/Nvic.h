/*
 * Nvic.h
 *
 *  Created on: Apr 5, 2022
 *      Author: 4AKER
 */

#ifndef STM32F401CC_NVIC_NVIC_H_
#define STM32F401CC_NVIC_NVIC_H_

typedef enum
{
	Nvic_enuOK,
	Nvic_enuInterruptNotFound,
	Nvic_enuNullPointer,
	Nvic_enuGroupPriorityOutOfBound,
	Nvic_enuSubGroupPriorityOutOfBound
} Nvic_tenuErrorStatus;

#define NVIC_GROUP_LEVEL_0				0x0U
#define NVIC_GROUP_LEVEL_1              0x1U
#define NVIC_GROUP_LEVEL_2             	0x2U
#define NVIC_GROUP_LEVEL_3             	0x3U
#define NVIC_GROUP_LEVEL_4             	0x4U
#define NVIC_GROUP_LEVEL_5             	0x5U
#define NVIC_GROUP_LEVEL_6             	0x6U
#define NVIC_GROUP_LEVEL_7             	0x7U
#define NVIC_GROUP_LEVEL_8             	0x8U
#define NVIC_GROUP_LEVEL_9             	0x9U
#define NVIC_GROUP_LEVEL_10             0xAU
#define NVIC_GROUP_LEVEL_11             0xBU
#define NVIC_GROUP_LEVEL_12             0xCU
#define NVIC_GROUP_LEVEL_13             0xDU
#define NVIC_GROUP_LEVEL_14             0xEU
#define NVIC_GROUP_LEVEL_15             0xFU
#define NVIC_GROUP_LEVEL_NONE           0xFFU

#define NVIC_SUBGROUP_LEVEL_0			0x0U
#define NVIC_SUBGROUP_LEVEL_1           0x1U
#define NVIC_SUBGROUP_LEVEL_2          	0x2U
#define NVIC_SUBGROUP_LEVEL_3          	0x3U
#define NVIC_SUBGROUP_LEVEL_4          	0x4U
#define NVIC_SUBGROUP_LEVEL_5          	0x5U
#define NVIC_SUBGROUP_LEVEL_6           0x6U
#define NVIC_SUBGROUP_LEVEL_7           0x7U
#define NVIC_SUBGROUP_LEVEL_8           0x8U
#define NVIC_SUBGROUP_LEVEL_9           0x9U
#define NVIC_SUBGROUP_LEVEL_10          0xAU
#define NVIC_SUBGROUP_LEVEL_11          0xBU
#define NVIC_SUBGROUP_LEVEL_12          0xCU
#define NVIC_SUBGROUP_LEVEL_13          0xDU
#define NVIC_SUBGROUP_LEVEL_14          0xEU
#define NVIC_SUBGROUP_LEVEL_15          0xFU
#define NVIC_SUBGROUP_LEVEL_NONE        0xFFU

Nvic_tenuErrorStatus Nvic_enuEnableInterrupt(u8 Copy_u8Interrupt);

Nvic_tenuErrorStatus Nvic_enuDisableInterrupt(u8 Copy_u8Interrupt);

Nvic_tenuErrorStatus Nvic_enuSetPending(u8 Copy_u8Interrupt);

Nvic_tenuErrorStatus Nvic_enuClrPending(u8 Copy_u8Interrupt);

Nvic_tenuErrorStatus Nvic_enuGetActiveStatus(u8 Copy_u8Interrupt,
		pu8 Add_pu8State);

Nvic_tenuErrorStatus Nvic_enuSetPriority(u8 Copy_u8Interrupt,
		u8 Copy_u8GroubPriority, u8 Copy_u8SubGroubPriority);

#endif /* STM32F401CC_NVIC_NVIC_H_ */
