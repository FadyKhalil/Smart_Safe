/* **************************************************************************************
**       Author      :	Smart Safe Group
**       Date        :	June 1, 2022
**       Version     :	V01
**       SWC         :	EEPROM
**       Description :	EEPROM module files
** **************************************************************************************/
#include "StdTypes.h"
#include "I2C.h"
#include "Gpio.h"
#include "EEPROM.h"
#include "Core.h"
#include "Port.h"
#define EEPROM_ADDRESS		0xA0


extern u8 Timeout_Flag;

void EEPROM_vidInit(void)
{
	Port_vidDisableInterrupt();
	I2C_Config ConfigI2c = {

				.Clock_Selection = 16,
				.Clock_Stretching = CLOCK_STRETCHING_ENABLE,
				.Mode_Selection = DISABLE,
				.Protocol = I2C_1,
				.Desired_Duty_Cycle = 100000

	};

	GPIO_tstrPinConfiguration Gpio_cfg = {
				.GPIO_Mode = GPIO_u8ALTFUNC_OPENDRAIN_PULLUP,
				.GPIO_Pin = GPIO_PIN09 | GPIO_PIN06,
				.GPIO_Port = GPIO_B,
				.GPIO_Speed = GPIO_Speed_Very_High,
				.GPIO_ALTF = GPIO_ALTERNATIVE_I2C
	};


	/*Pin Configuration for I2C*/
	Gpio_enuPinConfigurationInit(&Gpio_cfg);

	/*Initialize the I2C*/
	I2C_enuVidInit(&ConfigI2c);

	Port_vidEnableInterrupt();

}

void EEPROM_WriteByte(u16 Copy_u16Address, u8 Copy_u8Data)
{
//	Port_vidDisableInterrupt();

	Timeout_Flag = 0;

	I2C_enuSendStart(I2C_1);

	I2C_enuSendAddressSynchronous((u32*)0x40005400, EEPROM_ADDRESS, I2C_WRITE);

	I2C_enuSendByteSynchronous(I2C_1, (u8)Copy_u16Address);

	I2C_enuSendByteSynchronous(I2C_1, Copy_u8Data);

	I2C_enuSendStop(I2C_1);

//	Port_vidEnableInterrupt();

}


void EEPROM_ReadByte(u16 Copy_u16Address, u8* Add_pu8Data)
{
//	Port_vidDisableInterrupt();

	Timeout_Flag = 0;

	I2C_enuSendStart(I2C_1);

	I2C_enuSendAddressSynchronous(I2C_1, EEPROM_ADDRESS, I2C_WRITE);

	I2C_enuSendByteSynchronous(I2C_1, (u8)Copy_u16Address);

//	for(volatile int i = 0; i < 2000; i++);

	I2C_enuSendStart(I2C_1);

	I2C_enuSendAddressSynchronous(I2C_1, EEPROM_ADDRESS, I2C_READ);

	I2C_enuReceiveByteSynchronous(I2C_1, Add_pu8Data);

	I2C_enuSendStop(I2C_1);

//	Port_vidEnableInterrupt();

}

