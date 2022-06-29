/*
 * EEPROM.h
 *
 *  Created on: Jun 28, 2022
 *      Author: fady
 */

#ifndef HAL_EEPROM_EEPROM_H_
#define HAL_EEPROM_EEPROM_H_



extern void EEPROM_WriteByte(u16 Copy_u16Address, u8 Copy_u8Data);


extern void EEPROM_ReadByte(u16 Copy_u16Address, u8* Add_pu8Data);




#endif /* HAL_EEPROM_EEPROM_H_ */
