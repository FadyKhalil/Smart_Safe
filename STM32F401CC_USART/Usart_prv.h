/*
 * Usart_prv.h
 *
 *  Created on: Apr 12, 2022
 *      Author: 4AKER
 */

#ifndef STM32F401CC_USART_USART_PRV_H_
#define STM32F401CC_USART_USART_PRV_H_

/* *************************Type Definitions******************************************* */
/* Registers */
typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
} Usart_tstrRegisters;

typedef void (*Usart_pfSendBuffer)(u8, Std_tstrBuffer *);
/* ************************************************************************************ */

/* ////////////////////////////////// MACROS ////////////////////////////////////////// */

/* Addresses */
#define USART1_u32_BASE_ADDRESS			(0x40011000)
#define USART2_u32_BASE_ADDRESS			(0x40004400)
#define USART6_u32_BASE_ADDRESS			(0x40011400)
#define USART1_REGISTERS				((Usart_tstrRegisters *)USART1_u32_BASE_ADDRESS)
#define USART2_REGISTERS				((Usart_tstrRegisters *)USART2_u32_BASE_ADDRESS)
#define USART6_REGISTERS				((Usart_tstrRegisters *)USART6_u32_BASE_ADDRESS)

/* Usart enable */
#define USART_u16_DISABLE				((u16)0x0000)
#define USART_u16_ENABLE				((u16)0x2000)

/* Transmitter enable */
#define USART_u16_TX_DISABLE			((u16)0x0000)
#define USART_u16_TX_ENABLE				((u16)0x0008)

/* Receiver enable */
#define USART_u16_RX_DISABLE			((u16)0x0000)
#define USART_u16_RX_ENABLE				((u16)0x0004)

/* Data Register is empty interrupt */
#define USART_u16_TXE_DISABLE			((u16)0x0000)
#define USART_u16_TXE_ENABLE			((u16)0x0080)
#define USART_u16_TXE_MODE				USART_u16_TXE_ENABLE

/* Transmission complete interrupt */
#define USART_u16_TC_DISABLE			((u16)0x0000)
#define USART_u16_TC_ENABLE				((u16)0x0040)
#define USART_u16_TC_MODE				USART_u16_TC_ENABLE

#define USART_u8HIGH					((u8)0x01)
#define USART_u8LOW						((u8)0x00)

/* Bits locations */
#define USART_u8SR_PE					((u8)0x00)
#define USART_u8SR_FE					((u8)0x01)
#define USART_u8SR_NF					((u8)0x02)
#define USART_u8SR_ORE					((u8)0x03)
#define USART_u8SR_IDLE					((u8)0x04)
#define USART_u8SR_RXNE					((u8)0x05)
#define USART_u8SR_TC					((u8)0x06)
#define USART_u8SR_TXE					((u8)0x07)
#define USART_u8SR_LBD					((u8)0x08)
#define USART_u8SR_CTS					((u8)0x09)
#define USART_u8CR1_OVER8 				((u8)0x0F)

/* Bit Masks */
#define USART_u8SR_TC_MASK 				((u8) 0x40)
#define USART_u8SR_TXE_MASK 			((u8) 0x80)
#define USART_u8_SR_RXNE_MASK			((u8) 0x20)
#define USART_u8CR1_TCIE_MASK 			((u8) 0x40)
#define USART_u8CR1_TXEIE_MASK 			((u8) 0x80)
#define USART_u8_CR1_RXNEIE_MASK		((u8) 0x20)
#define USART_u16_CR1_RE_MASK			((u8) 0x04)
#define USART_CR3_DMAT_MASK				((u32) 0x00000080)

/* //////////////////////////////////////////////////////////////////////////////////// */

#endif /* STM32F401CC_USART_USART_PRV_H_ */
