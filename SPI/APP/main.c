/*
 * main.c
 *
 *  Created on: Jul 17, 2020
 *      Author: Ahmed Ehab
 */

#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"../MCAL/DIO/DIO_Int.h"
#include"../MCAL/DIO/DIO_Config.h"
#include"../MCAL/SPI/SPI_Int.h"
#include"../MCAL/Global Interrupt/GIE_Int.h"
#include"util/delay.h"



int main(void)
{
	u8 x=0;
	DIO_VidSetPinDirection(DIO_PORTB,PIN0,OUTPUT); //LED-DIRECTION
	DIO_VidSetPinValue(DIO_PORTB,PIN0,LOW);//LED-OFF
	SPI_VidMasterInit();


	while(1)
	{
		x=SPI_u8Transfer(6);

		if(x==6)
		{
			DIO_VidSetPinValue(DIO_PORTB,PIN0,HIGH);
			_delay_ms(500);
			DIO_VidSetPinValue(DIO_PORTB,PIN0,LOW);
			_delay_ms(500);
		}
		else
		{
			DIO_VidSetPinValue(DIO_PORTB,PIN0,HIGH);
		}


	}

	return 0;
}
