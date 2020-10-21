#ifndef  _SPI_INT_H_
#define  _SPI_INT_H_



void SPI_VidMasterInit(void);
void SPI_VidSlaveInit(void) ;
u8 SPI_u8Transfer(u8 LOC_u8Data);
void SPI_VidInterruptEnable(void);
void SPI_VidSetCallBack(void (*Lpfunc)(void));











#endif
