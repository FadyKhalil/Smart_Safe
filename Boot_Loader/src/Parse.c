/*
 * Parse.c
 *
 *  Created on: Jun 23, 2022
 *      Author: Marwa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Fls.h"

u32 address = 0x08000000;
u16 Half_word[100]={0};


u8 Parser_u8Asci_toHEX (u8 Copy_u8Asci )
{
	//x=x+30;

	//return x ;
	u8 Result;
		if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
		{
			Result = Copy_u8Asci - 48;
		}

		else
		{
			Result = Copy_u8Asci - 55;
		}

		return Result;
}
void Parser_vidParse_Data (u8* Copy_u8Buffer_Data)
{
	u8 char_count1,char_count2,cc;
	u8 address1,address2,address3,address4;
	u8 Digit1,Digit2,Digit3,Digit4;
	u8 counter=0;


	/* GET CHARCTER COUNT */
	char_count1 = Parser_u8Asci_toHEX(Copy_u8Buffer_Data[1]);
	char_count2 = Parser_u8Asci_toHEX(Copy_u8Buffer_Data[2]);
	/* CONCATINATE THE TWO NUMBERS */
	cc = (char_count1<<4)|char_count2;

	/* GET ADDRESS */
	address1=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[3]);
	address2=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[4]);
	address3=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[5]);
	address4=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[6]);

	address &= 0xFFFF0000;
	address= (address1<<12) |  (address2<<8) |  (address3<<4) |  address4 ;


	/* GET DATA */
	for (int i =0 ; i<cc/2;i++)
	{
		Digit1=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[4*i+9]);
		Digit2=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[4*i+10]);
		Digit3=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[4*i+11]);
		Digit4=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[4*i+12]);

		Half_word[counter] = (Digit1<<4) |  (Digit2) |  (Digit3<<12) |  (Digit4<<8) ;
		counter++;
	}

	/* PASS THE ARRAY TO FLASH DRIVER */
	Fls_enuWrite((pu32)address, (pu8)Half_word, cc/2);



}

void Parser_vidExtended_Add (u8* Copy_u8Buffer_Data)
{
	u8 address1,address2,address3,address4;

	/* GET ADDRESS */
		address1=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[9]);
		address2=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[10]);
		address3=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[11]);
		address4=Parser_u8Asci_toHEX(Copy_u8Buffer_Data[12]);

		address &= 0x000FFFF;
		address= (address1<<28) |  (address2<<24) |  (address3<<20) |  (address4<<16);

}


void Parser_vidParseRecord(u8* Copy_u8Buffer_Data )
{
	switch(Copy_u8Buffer_Data[8]){
	case '0':

		/* DATA RECORD */
		Parser_vidParse_Data(Copy_u8Buffer_Data);


		break;
	case '1':

		/* END OF FILE */

		break;
	case '4':

		/* EXTENDED ADDRESS */
		Parser_vidExtended_Add (Copy_u8Buffer_Data);

		break;
	case '5':

		/* FULL ADDRESS */

		break;

	}

}

