/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	Flash
**       Description :	Flash module files
** **************************************************************************************/
#include "StdTypes.h"
#include "Fls.h"
#include "Fls_prv.h"
static u32 Fls_u8ProgrammingSize = FLS_ZERO_INIT;
Fls_tenuError Fls_enuInit(const Fls_tstrConfig * Add_pstrConfig)
{
	Fls_tenuError Loc_enuReturnStatus = FLS_ERROR_OK;
	Fls_tstrRegisters *Loc_pstrRegisters = FLS_PERIPHRAL_BASE_ADDRESS;
	if (Add_pstrConfig == NULL)
	{
		Loc_enuReturnStatus = FLS_ERROR_ARGUMENT;
	}
	else
	{
		Loc_pstrRegisters->KEYR = (u32) 0x45670123;
		Loc_pstrRegisters->KEYR = (u32) 0xCDEF89AB;
		Fls_u8ProgrammingSize = Add_pstrConfig->ProgrammingSize;
		Loc_pstrRegisters->CR |= Add_pstrConfig->Interrupts | Add_pstrConfig->ProgrammingSize;
		Loc_pstrRegisters->CR |= FLS_CR_LOCK_MASK;
	}
	return Loc_enuReturnStatus;
}

Fls_tenuError Fls_enuErase(Fls_tenuSector Copy_enuSector)
{
	Fls_tenuError Loc_enuReturnStatus = FLS_ERROR_OK;
	Fls_tstrRegisters *Loc_pstrRegisters = FLS_PERIPHRAL_BASE_ADDRESS;
	u8 Loc_u8TimeOut = 255;
	u32 Loc_u32OperationStatus;
	if (Loc_pstrRegisters->SR & FLS_SR_BSY_MASK)
	{
		Loc_enuReturnStatus = FLS_ERROR_BUSY;
	}
	else
	{
		Loc_pstrRegisters->KEYR = (u32) 0x45670123;
		Loc_pstrRegisters->KEYR = (u32) 0xCDEF89AB;
		Loc_pstrRegisters->CR |= Copy_enuSector;
		Loc_pstrRegisters->CR |= FLS_CR_STRT_MASK;
		Loc_pstrRegisters->CR |= FLS_CR_LOCK_MASK;
		while (Loc_u8TimeOut && (Loc_pstrRegisters->SR & FLS_SR_BSY_MASK))
		{
			Loc_u8TimeOut--;
		}
		Loc_u32OperationStatus = Loc_pstrRegisters->SR;
		if (Loc_u32OperationStatus & FLS_SR_BSY_MASK)
		{
			Loc_enuReturnStatus = FLS_ERROR_TIMED_OUT;
		}
		else if (Loc_u32OperationStatus & FLS_SR_WRPERR_MASK)
		{
			Loc_enuReturnStatus = FLS_ERROR_WRITE_PROTECTION;
		}
		else if (Loc_u32OperationStatus & FLS_SR_OPERR_MASK)
		{
			Loc_enuReturnStatus = FLS_ERROR_OPERATION;
		}
	}
	return Loc_enuReturnStatus;
}

Fls_tenuError Fls_enuWrite(pu32 Add_pu32TargetAddress, const pu8 Add_pu8DataAddress, u16 Copy_u8Length)
{
	Fls_tenuError Loc_enuReturnStatus = FLS_ERROR_OK;
	Fls_tstrRegisters *Loc_pstrRegisters = FLS_PERIPHRAL_BASE_ADDRESS;
	u32 Loc_u32OperationStatus;
	u16 Loc_u16Iterator = 0;
	Fls_uniPtrSize Loc_uniCurrentTargetAddress;
	Fls_uniPtrSize Loc_uniCurrentDataAddress;
	if (Loc_pstrRegisters->SR & FLS_SR_BSY_MASK)
	{
		Loc_enuReturnStatus = FLS_ERROR_BUSY;
	}
	if ((Add_pu32TargetAddress == NULL) || (Add_pu8DataAddress == NULL))
	{
		Loc_enuReturnStatus = FLS_ERROR_ARGUMENT;
	}
	else
	{
		Loc_pstrRegisters->KEYR = (u32) 0x45670123;
		Loc_pstrRegisters->KEYR = (u32) 0xCDEF89AB;
		Loc_pstrRegisters->CR |= FLS_CR_PG_MASK;
		Loc_pstrRegisters->CR |= FLS_CR_LOCK_MASK;
		switch (Fls_u8ProgrammingSize)
		{
		case FLS_PROGRAM_PARALLELISM_X08:
			Loc_uniCurrentTargetAddress.pu8Size = (pu8) Add_pu32TargetAddress;
			Loc_uniCurrentDataAddress.pu8Size = (pu8) Add_pu8DataAddress;
			for (Loc_u16Iterator = 0; Loc_u16Iterator < Copy_u8Length; Loc_u16Iterator++)
			{
				*(Loc_uniCurrentTargetAddress.pu8Size) = *(Loc_uniCurrentDataAddress.pu8Size);
				Loc_uniCurrentTargetAddress.pu8Size++;
				Loc_uniCurrentDataAddress.pu8Size++;
			}
			break;

		case FLS_PROGRAM_PARALLELISM_X16:
			Loc_uniCurrentTargetAddress.pu16Size = (pu16) Add_pu32TargetAddress;
			Loc_uniCurrentDataAddress.pu16Size = (pu16) Add_pu8DataAddress;
			for (Loc_u16Iterator = 0; Loc_u16Iterator < Copy_u8Length; Loc_u16Iterator++)
			{
				*(Loc_uniCurrentTargetAddress.pu16Size) = *(Loc_uniCurrentDataAddress.pu16Size);
				Loc_uniCurrentTargetAddress.pu16Size++;
				Loc_uniCurrentDataAddress.pu16Size++;
			}
			break;

		case FLS_PROGRAM_PARALLELISM_X32:
			Loc_uniCurrentTargetAddress.pu32Size = (pu32) Add_pu32TargetAddress;
			Loc_uniCurrentDataAddress.pu32Size = (pu32) Add_pu8DataAddress;
			for (Loc_u16Iterator = 0; Loc_u16Iterator < Copy_u8Length; Loc_u16Iterator++)
			{
				*(Loc_uniCurrentTargetAddress.pu32Size) = *(Loc_uniCurrentDataAddress.pu32Size);
				Loc_uniCurrentTargetAddress.pu32Size++;
				Loc_uniCurrentDataAddress.pu32Size++;
			}
			break;

		case FLS_PROGRAM_PARALLELISM_X64:
			Loc_uniCurrentTargetAddress.pu64Size = (pu64) Add_pu32TargetAddress;
			Loc_uniCurrentDataAddress.pu64Size = (pu64) Add_pu8DataAddress;
			for (Loc_u16Iterator = 0; Loc_u16Iterator < Copy_u8Length; Loc_u16Iterator++)
			{
				*(Loc_uniCurrentTargetAddress.pu64Size) = *(Loc_uniCurrentDataAddress.pu64Size);
				Loc_uniCurrentTargetAddress.pu64Size++;
				Loc_uniCurrentDataAddress.pu64Size++;
			}
			break;
		}
		Loc_u32OperationStatus = Loc_pstrRegisters->SR;
		if (Loc_u32OperationStatus & FLS_SR_BSY_MASK)
		{
			Loc_enuReturnStatus = FLS_ERROR_TIMED_OUT;
		}
		else if (Loc_u32OperationStatus & FLS_SR_PGSERR_MASK)
		{
			Loc_enuReturnStatus = FLS_ERROR_PGSERR;
		}
		else if (Loc_u32OperationStatus & FLS_SR_PGPERR_MASK)
		{
			Loc_enuReturnStatus = FLS_ERROR_PGPERR;
		}
		else if (Loc_u32OperationStatus & FLS_SR_PGAERR_MASK)
		{
			Loc_enuReturnStatus = FLS_ERROR_PGAERR;
		}
	}
	return Loc_enuReturnStatus;
}
