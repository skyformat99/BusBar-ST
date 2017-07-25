#ifndef _SPI3_H_
#define _SPI3_H_

#include "sys.h"

void SPI3_Init(void);
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler);
void TFT_RS(char ch);
void TFT_CS(char ch);
void TFT_SCK(char ch);
void TFT_SDI(char ch);
void TFT_REST(char ch);
void TFT_LEDA(char ch);
u8 SPI3_ReadWriteByte(u8 TxData);

#endif




