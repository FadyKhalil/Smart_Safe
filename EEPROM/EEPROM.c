/*
 * EEPROM.c
 *
 *  Created on: Jun 28, 2022
 *      Author: fady
 */


#include "../../Services/Std_types.h"
#include "../../MCAL/I2C/I2C.h"
#include "EEPROM.h"


#define EEPROM_ADDRESS		0xA0


void EEPROM_WriteByte(u16 Copy_u16Address, u8 Copy_u8Data)
{
	I2C_enuSendStart(I2C_1);

	I2C_enuSendAddressSynchronous(I2C_1, EEPROM_ADDRESS, I2C_WRITE);

	I2C_enuSendByteSynchronous(I2C_1, (u8)Copy_u16Address);

	I2C_enuSendByteSynchronous(I2C_1, Copy_u8Data);

	I2C_enuSendStop(I2C_1);

	for(volatile int i = 0; i < 2000; i++)
	{

	}
}


void EEPROM_ReadByte(u16 Copy_u16Address, u8* Add_pu8Data)
{
	I2C_enuSendStart(I2C_1);

	I2C_enuSendAddressSynchronous(I2C_1, EEPROM_ADDRESS, I2C_WRITE);

	I2C_enuSendByteSynchronous(I2C_1, (u8)Copy_u16Address);

	I2C_enuSendStart(I2C_1);

	I2C_enuSendAddressSynchronous(I2C_1, EEPROM_ADDRESS, I2C_READ);

	I2C_enuReceiveByteSynchronous(I2C_1, Add_pu8Data);

	I2C_enuSendStop(I2C_1);

}

