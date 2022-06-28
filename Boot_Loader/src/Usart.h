/* **************************************************************************************
 **       Author      :	Omar Shaker
 **       Date        :	April 10, 2022
 **       Version     :	V01
 **       SWC         :	Usart
 **       Description :	Usart module file
 ** **************************************************************************************/

#ifndef STM32F401CC_USART_USART_H_
#define STM32F401CC_USART_USART_H_

/* ////////////////////////// Defined Types /////////////////////////////////////////// */
/* Error type */
typedef enum
{
	Usart_enuOk,
	Usart_enuNok,
	Usart_enuDataRegisterNotEmpty,
	Usart_enuNullPointer,
	Usart_enuBusy
} Usart_tenuError;

/* Usart configurations */
typedef struct
{
	u32 BusNumber; /* available options are in "Usart.h" under "Used Usarts" */
	f32 BaudRate; /* Set your baud rate, the unit is kbps */
	u8 StopBits; /* available options are in "Usart.h" under "Stop bits" */
	u8 Parity; /* available options are in "Usart.h" under "Parity options" */
	u16 Oversampling; /* available options are in "Usart.h" under "Oversampling options" */
	u8 WordLength; /* available options are in "Usart.h" under "Word length options"  */
	u8 Frequency; /* Set your working frequency in "MHZ" */
} Usart_tstrConfig;
/* //////////////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////// MACROS ////////////////////////////////////////// */
/* Used Usarts */
#define USART_u32BUS1				((u32)0x40011000) /* connected on APB2 */
#define USART_u32BUS2				((u32)0x40004400) /* connected on APB1 */
#define USART_u32BUS6				((u32)0x40011400) /* connected on APB2 */

/* Usart IDs */
#define USART_u8BUS1_ID				((u8)0x00)
#define USART_u8BUS2_ID				((u8)0x01)
#define USART_u8BUS6_ID				((u8)0x02)

/* Usart Flags */
#define USART_u8Flag_PE				((u8)0x00)
#define USART_u8Flag_FE				((u8)0x01)
#define USART_u8Flag_NF				((u8)0x02)
#define USART_u8Flag_ORE			((u8)0x03)
#define USART_u8Flag_IDLE			((u8)0x04)
#define USART_u8Flag_RXNE			((u8)0x05)
#define USART_u8Flag_TC				((u8)0x06)
#define USART_u8Flag_TXE			((u8)0x07)
#define USART_u8Flag_LBD			((u8)0x08)
#define USART_u8Flag_CTS			((u8)0x09)

/* Parity options */
#define USART_u16PARITY_OFF			((u16)0x0000)
#define USART_u16PARITY_EVEN		((u16)0x0400)
#define USART_u16PARITY_ODD			((u16)0x0600)

/* Oversampling options */
#define USART_u16OVERSAMP_8			((u16)0x8000)
#define USART_u16OVERSAMP_16		((u16)0x0000)

/* Word length options */
#define USART_u16_8BIT				((u16)0x0000)
#define USART_u16_9BIT				((u16)0x1000)

/* Stop bits */
#define USART_u16_ONE_BIT			((u16)0x0000)
#define USART_u16_TWO_BIT			((u16)0x2000)
/* //////////////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////// Interface Fns //////////////////////////////////// */
/*
 Usart_tenuError Usart_enuInit(Usart_tstrConfig *Add_pstrConfig);
 Description         :     Init the Usart
 Parameter1          :     Address of the configurations struct of type "Usart_tstrConfig" defined in "Usart.h"
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuInit(Usart_tstrConfig *Add_pstrConfig);

/*
 Usart_tenuError Usart_enuSendByte(u32 Copy_u8BusNo, u8 Copy_u8Byte);
 Description         :     Send byte on the Usart
 Parameter1          :     The bus no, options are in "Usart.h" under "Usart IDs"
 Parameter2          :     the byte to be sent
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuSendByte(u8 Copy_u8BusId, u8 Copy_u8Byte);

/*
 Usart_tenuError Usart_enuSendBufferZC(u8 Copy_u32BusId, tstrBuffer * Add_pstrBuffer);
 Description         :     Sends A buffer on the Usart
 Parameter1          :     The bus no, options are in "Usart.h" under "Used Usarts"
 Parameter2          :     Pointer to the buffer to be sent
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuSendBufferZC(u8 Copy_u32BusId, tstrBuffer * Add_pstrBuffer);

/*
 Usart_tenuError Usart_enuReceiveBufferZC(u8 Copy_u32BusId, tstrBuffer * Add_pstrBuffer);
 Description         :     Receives A buffer on the Usart
 Parameter1          :     The bus no, options are in "Usart.h" under "Used Usarts"
 Parameter2          :     Pointer to the buffer to be sent
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuReceiveBufferZC(u8 Copy_u32BusId, tstrBuffer * Add_pstrBuffer);

void Usart_enuSendBufferDmaZC(u8 Copy_u8BusId);

/*
 Usart_tenuError Usart_enuRegCallbackFn(tpfCallback Add_pfCallbackFn);
 Description         :     Register the Usart interrupt callback fn
 Parameter 1         :     ID of the required Usart defined in "Usart.h" under "Usart IDs"
 Parameter 2         :     The flag to assign the callback to defined in "Usart.h" under "Usart Flags"
 Parameter 3         :     Address of the callback fn
 Return              :     Error status of type "Usart_tenuError", defined in "Usart.h" under "Error type" section
 ////////////////////// Synchronous //////////////////////
 */
Usart_tenuError Usart_enuRegCallbackFn(u8 Copy_u32BusId, u8 Copy_u8Flag, tpfCallback Add_pfCallbackFn);
/* //////////////////////////////////////////////////////////////////////////////////// */

#endif /* STM32F401CC_USART_USART_H_ */
