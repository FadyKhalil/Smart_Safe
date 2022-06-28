

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC.h"
#include "GPIO_interface.h"
#include "Systick.h"
#include "USART.h"
#include "Fls.h"
#include "Nvic.h"

void Parser_vidParseRecord(u8* Copy_u8Buffer_Data );

u8  u8RecBuffer[100]   ;
volatile u8  u8RecCounter    = 0;
volatile u8  u8TimeOutFlag   = 0;
volatile u16 u16TimerCounter = 0;
volatile u8  u8BLWriteReq    = 1;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08008000;

	addr_to_call = *(Function_t*)(0x08008195);
	addr_to_call();
}


void main(void)
{
	u8 Local_u8RecStatus;



	RCC_enuTurnClk(RCC_u8HSI, RCC_enuOn);
	RCC_enuSelectSysClk(RCC_u8RUN_HSI);
	RCC_enuPerClk(RCC_enuUSART1,RCC_enuOn);
	RCC_enuPerClk(RCC_enuGPIOA,RCC_enuOn);


	GPIO_PinCfg_t Loc_enuGpio_Config ;
	Loc_enuGpio_Config.Mode= GPIO_u32MODE_AF_PP;
	Loc_enuGpio_Config.port=GPIOA_REG;
	Loc_enuGpio_Config.pin=GPIO_PIN_09;

	GPIO_enuInitPin(& Loc_enuGpio_Config);
	GPIO_SetAF(&Loc_enuGpio_Config, GPIO_u8ALTERNATE_FUNC_07);

	Loc_enuGpio_Config.pin=GPIO_PIN_10;
	GPIO_enuInitPin(& Loc_enuGpio_Config);
	GPIO_SetAF(&Loc_enuGpio_Config, GPIO_u8ALTERNATE_FUNC_07);


	Usart_tstrConfig Loc_enuUsart_Config=
	{
			.BusNumber = USART_u32BUS1,
			.BaudRate = (f32) 9.6,
			.StopBits = USART_u16_ONE_BIT,
			.Parity = USART_u16PARITY_OFF,
			.Oversampling = USART_u16OVERSAMP_8,
			.WordLength = USART_u16_8BIT,
			.Frequency = 16,
	};
	Usart_enuInit(& Loc_enuUsart_Config);

	Fls_tstrConfig Loc_enuFLASH_Config =
	{
			.ProgrammingSize = FLS_PROGRAM_PARALLELISM_X16,
			.Interrupts = FLS_INTERRUPT_DISABLED
	};
	Fls_enuInit(& Loc_enuFLASH_Config);


	/* Init the systick timer */
	Systick_enuInit(SYSTICK_u8AHB, SYSTICK_u8ON_INT);
	/* Set the systick callback fn timestamp */
	Systick_enuSetTickTimeMS(15000);
	/* Registering the systick callback fn */
	Systick_vidRegCallbackFn(func);
	/* Starting the systick timer */
	Systick_enuStart();

	tstrBuffer Buffer;
	Buffer.Data= u8RecBuffer ;
	Buffer.Size= 100;
	Buffer.Used=0;

	tstrBuffer Buffer1;
	Buffer1.Data= (u8 *)"OK" ;
	Buffer1.Size= 2;
	Buffer1.Used=0;

	Nvic_enuClrPending(37);
	Nvic_enuEnableInterrupt(37);

	while(u8TimeOutFlag == 0)
	{

		Local_u8RecStatus =Usart_enuReceiveBufferZC(USART_u8BUS1_ID,  & Buffer );
		if (Local_u8RecStatus == 1)
		{
			Systick_vidStop();

			if(u8RecBuffer[u8RecCounter] == '\n')
			{
				if (u8BLWriteReq == 1)
				{
					Fls_enuErase(FLS_MEMORY_SECTOR_2);
					Fls_enuErase(FLS_MEMORY_SECTOR_3);
					Fls_enuErase(FLS_MEMORY_SECTOR_4);
					Fls_enuErase(FLS_MEMORY_SECTOR_5);
					u8BLWriteReq = 0;
				}


				/* Parse */
				Parser_vidParseRecord(u8RecBuffer );
				Usart_enuSendBufferZC(USART_u8BUS1_ID,& Buffer1);
				u8RecCounter = 0;
			}

			else
			{
				u8RecCounter ++ ;
			}

			/* Set the systick callback fn timestamp */
			Systick_enuSetTickTimeMS(15000);
			/* Starting the systick timer */
			Systick_enuStart();
		}

		else
		{

		}
	}
}

