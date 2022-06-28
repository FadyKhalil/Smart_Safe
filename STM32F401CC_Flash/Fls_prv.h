/*
 * Fls_prv.h
 *
 *  Created on: May 15, 2022
 *      Author: 4AKER
 */

#ifndef STM32F401CC_FLS_FLS_PRV_H_
#define STM32F401CC_FLS_FLS_PRV_H_

typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR;
} Fls_tstrRegisters;

typedef enum
{
	FLS_LOW = (u32) 0x00000000,
	FLS_HIGH = (u32) 0x00000001
} Fls_enuState;

typedef enum
{
	FLS_ZERO_INIT = 0
} Fls_tenuDefaultValue;

typedef union
{
	pu8 pu8Size;
	pu16 pu16Size;
	pu32 pu32Size;
	pu64 pu64Size;
} Fls_uniPtrSize;

#define FLS_PERIPHRAL_BASE_ADDRESS		((Fls_tstrRegisters *) 0x40023C00 )

#define FLS_SR_BSY_MASK				((u32) 0x00010000)
#define FLS_SR_WRPERR_MASK			((u32) 0x00000010)
#define FLS_SR_OPERR_MASK			((u32) 0x00000002)
#define FLS_SR_EOP_MASK				((u32) 0x00000001)
#define FLS_SR_PGSERR_MASK			((u32) 0x00000080)
#define FLS_SR_PGPERR_MASK			((u32) 0x00000040)
#define FLS_SR_PGAERR_MASK			((u32) 0x00000020)
#define FLS_CR_STRT_MASK			((u32) 0x00010000)
#define FLS_CR_SER_MASK				((u32) 0x00000002)
#define FLS_CR_PG_MASK				((u32) 0x00000001)
#define FLS_CR_LOCK_MASK			((u32) 0x80000000)

#endif /* STM32F401CC_FLS_FLS_PRV_H_ */
