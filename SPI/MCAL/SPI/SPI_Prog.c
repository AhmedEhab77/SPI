#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"SPI_Priv.h"
#include"SPI_Config.h"
#include"../DIO/DIO_Int.h"
#include"../DIO/DIO_Config.h"
#include"../Global Interrupt/GIE_Config.h"




/**GLOBAL POINTER TO FUNCTION**/
static void (*Gpfunc1)(void)=NULL;
/********CALL BACK FUNCTION*****/
void SPI_VidSetCallBack(void (*Lpfunc)(void))
{
	Gpfunc1=Lpfunc;
}
/*************ISR FOR SPI**********/
ISR(__vector_12)
{
	if(Gpfunc1 != NULL)
	{
		Gpfunc1();
	}
}


void SPI_VidMasterInit(void)
{
	
	DIO_VidSetPinDirection(DIO_PORTB,PIN5,OUTPUT);//MOSI OUTPUT
	DIO_VidSetPinDirection(DIO_PORTB,PIN6,INPUT); //MISO INPUT
	DIO_VidSetPinDirection(DIO_PORTB,PIN4,OUTPUT);//SS OUTPUT
	DIO_VidSetPinDirection(DIO_PORTB,PIN7,OUTPUT);//CLK OUTPUT

	SET_BIT(SPCR,SPE);                            //Enable SPI
	SET_BIT(SPCR,DORD);                           //The LSB of the data word is transmitted first
	SET_BIT(SPCR,MSTR);                           //SPI AS MASTER
	SET_BIT(SPCR,CPOL);                           //Leading falling
	SET_BIT(SPCR,CPHA);                           //Setup-->Sample
												  
	SET_BIT(SPCR,SPR0);                           //Fosc/16
	CLR_BIT(SPCR,SPR1); 	
}

void SPI_VidSlaveInit(void)
{
	
	DIO_VidSetPinDirection(DIO_PORTB,PIN5,INPUT);  //MOSI INPUT
	DIO_VidSetPinDirection(DIO_PORTB,PIN6,OUTPUT); //MISO OUTPUT
	DIO_VidSetPinDirection(DIO_PORTB,PIN4,INPUT);  //SS INPUT
	
	SET_BIT(SPCR,SPE);                            //Enable SPI
	SET_BIT(SPCR,DORD);                           //The LSB of the data word is transmitted first
	CLR_BIT(SPCR,MSTR);                           //SPI AS MASTER
	SET_BIT(SPCR,CPOL);                           //Leading falling
	SET_BIT(SPCR,CPHA);                           //Setup-->Sample
												  
	SET_BIT(SPCR,SPR0);                           //Fosc/16
	CLR_BIT(SPCR,SPR1); 	
}

u8 SPI_u8Transfer(u8 LOC_u8Data)
{
	SPDR=LOC_u8Data;
	while((GET_BIT(SPSR,SPIF))==0){}
	return SPDR;
}

void SPI_VidInterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}
