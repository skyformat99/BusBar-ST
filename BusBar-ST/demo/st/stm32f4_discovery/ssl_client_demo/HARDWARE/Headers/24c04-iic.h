#include "stm32f4xx.h"


#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C02

//unsigned char I2cRead(unsigned int addr);
//int I2cWrite(unsigned int addr,unsigned char dat);
unsigned char I2cRead(unsigned char addr);
int I2cWrite(unsigned char addr,unsigned char dat);
void IICinit(void);
void iicreaddata(void);
void iicresetdata(void);
