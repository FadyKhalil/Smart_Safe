/*
 * Nvic.c
 *
 *  Created on: Apr 5, 2022
 *      Author: 4AKER
 */

#include "STD_TYPES.h"
#include "Nvic.h"
#include "Nvic_cfg.h"

typedef struct
{
	volatile u32 ISER[8];
	volatile u32 Reserved1[24];
	volatile u32 ICER[8];
	volatile u32 Reserved2[24];
	volatile u32 ISPR[8];
	volatile u32 Reserved3[24];
	volatile u32 ICPR[8];
	volatile u32 Reserved4[24];
	volatile u32 IAPR[8];
	volatile u32 Reserved5[56];
	volatile u32 IPR[60];
} Nvic_tstrRegisters;

#define NVIC_BASE_ADDRESS					(0xE000E100U)
#define NVIC_REGISTERS						((Nvic_tstrRegisters *) (NVIC_BASE_ADDRESS))
#define NVIC_PRIGROUP_REGISTER				((u32 *) (0xE000ED0CU))
#define NVIC_PRIGROUP_MASK					(0x00000700U)
#define NVIC_PRIFIELDS_PER_REGISTER			(4U)
#define NVIC_PRIFIELD_SIZE_IN_BITS			(8U)

Nvic_tenuErrorStatus Nvic_enuEnableInterrupt(u8 Copy_u8Interrupt)
{
	Nvic_tenuErrorStatus Loc_enuReturnStatus;
	u8 Loc_u8RegisterNum, Loc_u8PinNum;
	if (Copy_u8Interrupt > NVIC_INTERRUPT_COUNT)
	{
		Loc_enuReturnStatus = Nvic_enuInterruptNotFound;
	}
	else
	{
		Loc_u8RegisterNum = Copy_u8Interrupt / 32;
		Loc_u8PinNum = Copy_u8Interrupt % 32;
		NVIC_REGISTERS->ISER[Loc_u8RegisterNum] = 1 << Loc_u8PinNum;
		Loc_enuReturnStatus = Nvic_enuOK;
	}
	return Loc_enuReturnStatus;
}

Nvic_tenuErrorStatus Nvic_enuDisableInterrupt(u8 Copy_u8Interrupt)
{
	Nvic_tenuErrorStatus Loc_enuReturnStatus;
	u8 Loc_u8RegisterNum, Loc_u8PinNum;
	if (Copy_u8Interrupt > NVIC_INTERRUPT_COUNT)
	{
		Loc_enuReturnStatus = Nvic_enuInterruptNotFound;
	}
	else
	{
		Loc_u8RegisterNum = Copy_u8Interrupt / 32;
		Loc_u8PinNum = Copy_u8Interrupt % 32;
		NVIC_REGISTERS->ICER[Loc_u8RegisterNum] = 1 << Loc_u8PinNum;
		Loc_enuReturnStatus = Nvic_enuOK;
	}
	return Loc_enuReturnStatus;
}

Nvic_tenuErrorStatus Nvic_enuSetPending(u8 Copy_u8Interrupt)
{
	Nvic_tenuErrorStatus Loc_enuReturnStatus;
	u8 Loc_u8RegisterNum, Loc_u8PinNum;
	if (Copy_u8Interrupt > NVIC_INTERRUPT_COUNT)
	{
		Loc_enuReturnStatus = Nvic_enuInterruptNotFound;
	}
	else
	{
		Loc_u8RegisterNum = Copy_u8Interrupt / 32;
		Loc_u8PinNum = Copy_u8Interrupt % 32;
		NVIC_REGISTERS->ISPR[Loc_u8RegisterNum] = 1 << Loc_u8PinNum;
		Loc_enuReturnStatus = Nvic_enuOK;
	}
	return Loc_enuReturnStatus;
}

Nvic_tenuErrorStatus Nvic_enuClrPending(u8 Copy_u8Interrupt)
{
	Nvic_tenuErrorStatus Loc_enuReturnStatus;
	u8 Loc_u8RegisterNum, Loc_u8PinNum;
	if (Copy_u8Interrupt > NVIC_INTERRUPT_COUNT)
	{
		Loc_enuReturnStatus = Nvic_enuInterruptNotFound;
	}
	else
	{
		Loc_u8RegisterNum = Copy_u8Interrupt / 32;
		Loc_u8PinNum = Copy_u8Interrupt % 32;
		NVIC_REGISTERS->ICPR[Loc_u8RegisterNum] = 1 << Loc_u8PinNum;
		Loc_enuReturnStatus = Nvic_enuOK;
	}
	return Loc_enuReturnStatus;
}

Nvic_tenuErrorStatus Nvic_enuGetActiveStatus(u8 Copy_u8Interrupt,
		pu8 Add_pu8State)
{
	Nvic_tenuErrorStatus Loc_enuReturnStatus;
	u8 Loc_u8RegisterNum, Loc_u8PinNum;
	if (Copy_u8Interrupt > NVIC_INTERRUPT_COUNT)
	{
		Loc_enuReturnStatus = Nvic_enuInterruptNotFound;
	}
	else if (!Add_pu8State)
	{
		Loc_enuReturnStatus = Nvic_enuNullPointer;
	}
	else
	{
		Loc_u8RegisterNum = Copy_u8Interrupt / 32;
		Loc_u8PinNum = Copy_u8Interrupt % 32;
		*Add_pu8State = GET_BIT(NVIC_REGISTERS->IAPR[Loc_u8RegisterNum],
				Loc_u8PinNum);
		Loc_enuReturnStatus = Nvic_enuOK;
	}
	return Loc_enuReturnStatus;
}

Nvic_tenuErrorStatus Nvic_enuSetPriority(u8 Copy_u8Interrupt,
		u8 Copy_u8GroubPriority, u8 Copy_u8SubGroubPriority)
{
	Nvic_tenuErrorStatus Loc_enuReturnStatus;
	u8 Loc_u8PriGroupStatus;
	u8 Loc_u8RegisterNum, Loc_u8PriorityFieldOffset;
	if (Copy_u8Interrupt > NVIC_INTERRUPT_COUNT)
	{
		Loc_enuReturnStatus = Nvic_enuInterruptNotFound;
	}
	else
	{
		Loc_u8RegisterNum = Copy_u8Interrupt / NVIC_PRIFIELDS_PER_REGISTER;
		Loc_u8PriorityFieldOffset = (Copy_u8Interrupt
				% NVIC_PRIFIELDS_PER_REGISTER) * NVIC_PRIFIELD_SIZE_IN_BITS;
		//*NVIC_PRIGROUP_REGISTER = 0x5FA0500U;
		Loc_u8PriGroupStatus = ((*NVIC_PRIGROUP_REGISTER) & NVIC_PRIGROUP_MASK)
				>> 8;
		switch (Loc_u8PriGroupStatus)
		{
		case 0:
			if (Copy_u8GroubPriority > NVIC_GROUP_LEVEL_15)
			{
				Loc_enuReturnStatus = Nvic_enuGroupPriorityOutOfBound;
			}
			else if (Copy_u8SubGroubPriority != NVIC_SUBGROUP_LEVEL_NONE)
			{
				Loc_enuReturnStatus = Nvic_enuSubGroupPriorityOutOfBound;
			}
			else
			{
				NVIC_REGISTERS->IPR[Loc_u8RegisterNum] |= (Copy_u8GroubPriority
						<< ((Loc_u8PriorityFieldOffset) + 4));
			}
			break;

		case 4:
			if (Copy_u8GroubPriority > NVIC_GROUP_LEVEL_7)
			{
				Loc_enuReturnStatus = Nvic_enuGroupPriorityOutOfBound;
			}
			else if (Copy_u8SubGroubPriority > NVIC_SUBGROUP_LEVEL_1)
			{
				Loc_enuReturnStatus = Nvic_enuSubGroupPriorityOutOfBound;
			}
			else
			{
				NVIC_REGISTERS->IPR[Loc_u8RegisterNum] |= (Copy_u8GroubPriority
						<< ((Loc_u8PriorityFieldOffset) + 4 + 1))
						| (Copy_u8SubGroubPriority
								<< ((Loc_u8PriorityFieldOffset) + 4));
			}
			break;

		case 5:
			if (Copy_u8GroubPriority > NVIC_GROUP_LEVEL_3)
			{
				Loc_enuReturnStatus = Nvic_enuGroupPriorityOutOfBound;
			}
			else if (Copy_u8SubGroubPriority > NVIC_SUBGROUP_LEVEL_3)
			{
				Loc_enuReturnStatus = Nvic_enuSubGroupPriorityOutOfBound;
			}
			else
			{
				NVIC_REGISTERS->IPR[Loc_u8RegisterNum] |= (Copy_u8GroubPriority
						<< ((Loc_u8PriorityFieldOffset) + 4 + 2))
						| (Copy_u8SubGroubPriority
								<< ((Loc_u8PriorityFieldOffset) + 4));
			}
			break;

		case 6:
			if (Copy_u8GroubPriority > NVIC_GROUP_LEVEL_1)
			{
				Loc_enuReturnStatus = Nvic_enuGroupPriorityOutOfBound;
			}
			else if (Copy_u8SubGroubPriority > NVIC_SUBGROUP_LEVEL_7)
			{
				Loc_enuReturnStatus = Nvic_enuSubGroupPriorityOutOfBound;
			}
			else
			{
				NVIC_REGISTERS->IPR[Loc_u8RegisterNum] |= (Copy_u8GroubPriority
						<< ((Loc_u8PriorityFieldOffset) + 4 + 3))
						| (Copy_u8SubGroubPriority
								<< ((Loc_u8PriorityFieldOffset) + 4));
			}
			break;

		case 7:
			if (Copy_u8GroubPriority != NVIC_GROUP_LEVEL_NONE)
			{
				Loc_enuReturnStatus = Nvic_enuGroupPriorityOutOfBound;
			}
			else if (Copy_u8SubGroubPriority > NVIC_SUBGROUP_LEVEL_15)
			{
				Loc_enuReturnStatus = Nvic_enuSubGroupPriorityOutOfBound;
			}
			else
			{
				NVIC_REGISTERS->IPR[Loc_u8RegisterNum] |=
						(Copy_u8SubGroubPriority
								<< ((Loc_u8PriorityFieldOffset) + 4));
			}
			break;

		default:
			break;
		}
		Loc_enuReturnStatus = Nvic_enuOK;
	}
	return Loc_enuReturnStatus;
}
