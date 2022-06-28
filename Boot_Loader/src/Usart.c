/* **************************************************************************************
 **       Author      :	Omar Shaker
 **       Date        :	April 10, 2022
 **       Version     :	V01
 **       SWC         :	Usart
 **       Description :	Usart module file
 ** **************************************************************************************/

/* ///////////////////////////////// Headers inclusion //////////////////////////////// */
/* LIB headers */
#include "STD_TYPES.h"
/* Own headers */
#include "Usart.h"
#include "Usart_cfg.h"
#include "Usart_prv.h"
/* //////////////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////// Global Variables ///////////////////////////////// */
static tpfCallback Usart_pfarrCallBackFn[3][10] =
{ NULL };

static tstrBuffer * Usart_pstrarrDataBuffers[3] =
{ NULL };

static tstrBuffer * Usart_pstrarrReceiveBuffers[3] =
{ NULL };

static Usart_tstrRegisters * Usart_pstrarrBuses[3] =
{ USART1_REGISTERS, USART2_REGISTERS, USART6_REGISTERS };

static u8 Usart_u8arrBusyFlag[3] =
{ 0 };

static u8 Usart_u8arrReceiveBusyFlag[3] =
{ 0 };

static u8 Usart_u8DmaByte = USART_u8LOW;
/* //////////////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////// Interface Fns //////////////////////////////////// */
/*
 Usart_tenuError Usart_enuInit(Usart_tstrConfig *Add_pstrConfig)
 Description         :     Init the Usart
 Parameter1          :     Address of the configurations struct of type "Usart_tstrConfig" defined in "Usart.h"
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuInit(Usart_tstrConfig *Add_pstrConfig)
{
	Usart_tenuError Loc_enuReturnStatus;
	f32 Loc_f32Usart_Div = 0;
	f32 Loc_f32Fraction_Temp = 0;
	u8 Loc_u8Oversampling = (u8) ((Add_pstrConfig->Oversampling) >> USART_u8CR1_OVER8);
	u8 Loc_u8Div_Fraction = 0;
	u16 Loc_u16Div_Mantissa = 0;

	if (Add_pstrConfig) /* Validate Arguments */
	{
		Usart_tstrRegisters *Loc_pstrRegisters = ((Usart_tstrRegisters *) (Add_pstrConfig->BusNumber));
		Loc_pstrRegisters->CR1 = USART_u16_ENABLE;
		Loc_pstrRegisters->CR1 |= (Add_pstrConfig->Oversampling) | (Add_pstrConfig->WordLength) | (Add_pstrConfig->Parity);
		Loc_pstrRegisters->CR2 = Add_pstrConfig->StopBits;
		Loc_f32Usart_Div = (((f64) Add_pstrConfig->Frequency) * (f64) 1000000) / (8U * (2U - Loc_u8Oversampling) * (Add_pstrConfig->BaudRate * (f32) 1000)); /* The numbers are the equation numbers */
		Loc_u16Div_Mantissa = (u16) Loc_f32Usart_Div;
		Loc_f32Fraction_Temp = (f32) (Loc_f32Usart_Div - (u32) Loc_f32Usart_Div) * (f32) (16U - (Loc_u8Oversampling * 8U));
		if ((((u8) (Loc_f32Fraction_Temp * 10U)) % 10U) >= 5U)
		{
			Loc_f32Fraction_Temp++;
		} /* end of if */
		Loc_u8Div_Fraction = (u8) Loc_f32Fraction_Temp;
		if (Loc_u8Oversampling && (Loc_u8Div_Fraction > 7U)) /* Oversampling by 8 */
		{
			Loc_u8Div_Fraction = 0;
			Loc_u16Div_Mantissa++;
		} /* end of if */
		else /* Oversampling by 16 */
		{
			if (Loc_u8Div_Fraction > 15)
			{
				Loc_u8Div_Fraction = 0;
				Loc_u16Div_Mantissa++;
			} /* end of if */
		} /* end of else */
		Loc_pstrRegisters->BRR = (u32) ((Loc_u16Div_Mantissa << 4U) | Loc_u8Div_Fraction);
		Loc_pstrRegisters->CR1 |= USART_u16_TX_ENABLE;
		Loc_pstrRegisters->CR1 |= USART_u16_CR1_RE_MASK;
		Loc_enuReturnStatus = Usart_enuOk;
	} /* end of if */
	else
	{
		Loc_enuReturnStatus = Usart_enuNullPointer;
	} /* end of else */

	return Loc_enuReturnStatus;
} /* Usart_enuInit */

/*
 Usart_tenuError Usart_enuSendByte(u8 Copy_u8BusNo, u8 Copy_u8Byte)
 Description         :     Send byte on the Usart
 Parameter1          :     The bus no, options are in "Usart.h" under "Usart IDs"
 Parameter2          :     the byte
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuSendByte(u8 Copy_u8BusId, u8 Copy_u8Byte)
{
	Usart_tenuError Loc_enuReturnStatus = Usart_enuOk;
	Usart_tstrRegisters * Loc_pstrBusRegisters = (Usart_tstrRegisters *) Usart_pstrarrBuses[Copy_u8BusId];
	if (Usart_u8arrBusyFlag[Copy_u8BusId] == USART_u8HIGH)
	{
		Loc_enuReturnStatus = Usart_enuBusy;
	}
	else
	{
		Loc_pstrBusRegisters->SR;
		Loc_pstrBusRegisters->DR = Copy_u8Byte;
		Loc_pstrBusRegisters->CR1 |= USART_u16_TC_ENABLE;
	}
	return Loc_enuReturnStatus;
} /* Usart_enuSendByte */

Usart_tenuError Usart_enuSendBufferZC(u8 Copy_u32BusId, tstrBuffer * Add_pstrBuffer)
{
	Usart_tenuError Loc_enuReturnStatus = Usart_enuOk;
	if (Add_pstrBuffer == NULL)
	{
		Loc_enuReturnStatus = Usart_enuNullPointer;
	}
	else if (Usart_u8arrBusyFlag[Copy_u32BusId] == 1)
	{
		Loc_enuReturnStatus = Usart_enuBusy;
	}
	else
	{
		Usart_u8arrBusyFlag[Copy_u32BusId] = USART_u8HIGH;
		Usart_pstrarrDataBuffers[Copy_u32BusId] = Add_pstrBuffer;
		Usart_pstrarrBuses[Copy_u32BusId]->SR;
		Usart_pstrarrBuses[Copy_u32BusId]->DR = Add_pstrBuffer->Data[Add_pstrBuffer->Used];
		Add_pstrBuffer->Used++;
		Usart_pstrarrBuses[Copy_u32BusId]->CR1 |= (USART_u8CR1_TXEIE_MASK);
	}
	return Loc_enuReturnStatus;
}

void Usart_enuStaticSendBufferZC(u8 Copy_u32BusId)
{
	if (Usart_pstrarrDataBuffers[Copy_u32BusId]->Used < Usart_pstrarrDataBuffers[Copy_u32BusId]->Size)
	{
		Usart_pstrarrBuses[Copy_u32BusId]->SR;
		Usart_pstrarrBuses[Copy_u32BusId]->DR = Usart_pstrarrDataBuffers[Copy_u32BusId]->Data[Usart_pstrarrDataBuffers[Copy_u32BusId]->Used];
		if ((++(Usart_pstrarrDataBuffers[Copy_u32BusId]->Used)) == Usart_pstrarrDataBuffers[Copy_u32BusId]->Size)
		{
			Usart_pstrarrBuses[Copy_u32BusId]->CR1 &= (u32) ~(USART_u8CR1_TXEIE_MASK);
			Usart_u8arrBusyFlag[Copy_u32BusId] = 0;
		}
	}
}

Usart_tenuError Usart_enuReceiveBufferZC(u8 Copy_u32BusId, tstrBuffer * Add_pstrBuffer)
{
	Usart_tenuError Loc_enuReturnStatus = Usart_enuOk;
	if (Add_pstrBuffer == NULL)
	{
		Loc_enuReturnStatus = Usart_enuNullPointer;
	}
	else if (Usart_u8arrReceiveBusyFlag[Copy_u32BusId] == 1)
	{
		Loc_enuReturnStatus = Usart_enuBusy;
	}
	else
	{
		Usart_u8arrReceiveBusyFlag[Copy_u32BusId] = 1;
		Usart_pstrarrReceiveBuffers[Copy_u32BusId] = Add_pstrBuffer;
		Usart_pstrarrBuses[Copy_u32BusId]->CR1 |= (USART_u8_CR1_RXNEIE_MASK);
	}
	return Loc_enuReturnStatus;
}

void Usart_enuStaticReceiveBufferZC(u8 Copy_u32BusId)
{
	if (Usart_pstrarrReceiveBuffers[Copy_u32BusId]->Used < Usart_pstrarrReceiveBuffers[Copy_u32BusId]->Size)
	{
		Usart_pstrarrReceiveBuffers[Copy_u32BusId]->Data[Usart_pstrarrReceiveBuffers[Copy_u32BusId]->Used] = (u8) Usart_pstrarrBuses[Copy_u32BusId]->DR;
		if ((++(Usart_pstrarrReceiveBuffers[Copy_u32BusId]->Used)) == Usart_pstrarrReceiveBuffers[Copy_u32BusId]->Size)
		{
			Usart_pstrarrBuses[Copy_u32BusId]->CR1 &= (u32) ~(USART_u8_CR1_RXNEIE_MASK);
			Usart_u8arrReceiveBusyFlag[Copy_u32BusId] = 0;
		}
	}
}

void Usart_enuSendBufferDmaZC(u8 Copy_u8BusId)
{
	Usart_pstrarrBuses[Copy_u8BusId]->CR3 |= USART_CR3_DMAT_MASK;
}

/*
 Usart_tenuError Usart_enuRegCallbackFn(tpfCallback Add_pfCallbackFn)
 Description         :     Register the Usart interrupt callback fn
 Parameter           :     Address of the callback fn
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuRegCallbackFn(u8 Copy_u32BusId, u8 Copy_u8Flag, tpfCallback Add_pfCallbackFn)
{
	Usart_tenuError Loc_enuReturnStatus;
	if (Add_pfCallbackFn) /* Validating Parameters */
	{
		Usart_pfarrCallBackFn[Copy_u32BusId][Copy_u8Flag] = Add_pfCallbackFn;
		Loc_enuReturnStatus = Usart_enuOk;
	}
	else
	{
		Loc_enuReturnStatus = Usart_enuNullPointer;
	}
	return Loc_enuReturnStatus;
} /* Usart_enuRegCallbackFn */
/* //////////////////////////////////////////////////////////////////////////////////// */

/*
 void USART1_IRQHandler(void);
 Description         :     The Usart handler
 Parameter           :     void
 Return              :     void
 ////////////////////// Synchronous //////////////////////
 */
void USART1_IRQHandler(void)
{
	/* MUST CHECK IF THE INTERRUPT IS ENABLED FIRST 139 -> 202 */
//	if ((((USART1_REGISTERS->SR) >> (USART_u8SR_CTS)) & (STDTYPES_u8BIT_SLICERS_00)) == USART_u8HIGH)
//	{
//		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_CTS])
//		{
//			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_CTS]();
//		}
//	}
//	if ((((USART1_REGISTERS->SR) >> (USART_u8SR_LBD)) & (STDTYPES_u8BIT_SLICERS_00)) == USART_u8HIGH)
//	{
//		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_LBD])
//		{
//			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_LBD]();
//		}
//	}
	if (((USART1_REGISTERS->CR1) & USART_u8CR1_TXEIE_MASK) && ((USART1_REGISTERS->SR) & USART_u8SR_TXE_MASK))
	{
		if (Usart_u8arrBusyFlag[0] == USART_u8HIGH)
		{
			Usart_enuStaticSendBufferZC(USART_u8BUS1_ID);
		}
		else if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_TXE])
		{
			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_TXE]();
		}
	}
	if (((USART1_REGISTERS->CR1) & USART_u8CR1_TCIE_MASK) && ((USART1_REGISTERS->SR) & USART_u8SR_TC_MASK))
	{
		USART1_REGISTERS->SR &= (u32) ~USART_u8SR_TC_MASK;
		if (Usart_u8DmaByte == USART_u8HIGH)
		{
			Usart_u8arrBusyFlag[0] = USART_u8LOW;
			Usart_u8DmaByte = USART_u8LOW;
		}
		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_TC])
		{
			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_TC]();
		}
	}
	if (((USART1_REGISTERS->CR1) & USART_u8_CR1_RXNEIE_MASK) && ((USART1_REGISTERS->SR) & USART_u8_SR_RXNE_MASK))
	{
		Usart_enuStaticReceiveBufferZC(USART_u8BUS1_ID);
	}
//	if ((((USART1_REGISTERS->SR) >> (USART_u8SR_IDLE)) & (STDTYPES_u8BIT_SLICERS_00)) == USART_u8HIGH)
//	{
//		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_IDLE])
//		{
//			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_IDLE]();
//		}
//	}
//	if ((((USART1_REGISTERS->SR) >> (USART_u8SR_ORE)) & (STDTYPES_u8BIT_SLICERS_00)) == USART_u8HIGH)
//	{
//		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_ORE])
//		{
//			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_ORE]();
//		}
//	}
//	if ((((USART1_REGISTERS->SR) >> (USART_u8SR_NF)) & (STDTYPES_u8BIT_SLICERS_00)) == USART_u8HIGH)
//	{
//		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_NF])
//		{
//			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_NF]();
//		}
//	}
//	if ((((USART1_REGISTERS->SR) >> (USART_u8SR_FE)) & (STDTYPES_u8BIT_SLICERS_00)) == USART_u8HIGH)
//	{
//		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_FE])
//		{
//			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_FE]();
//		}
//	}
//	if ((((USART1_REGISTERS->SR) >> (USART_u8SR_PE)) & (STDTYPES_u8BIT_SLICERS_00)) == USART_u8HIGH)
//	{
//		if (Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_PE])
//		{
//			Usart_pfarrCallBackFn[USART_u8BUS1_ID][USART_u8Flag_PE]();
//		}
//	}
}
/* //////////////////////////////////////////////////////////////////////////////////// */
