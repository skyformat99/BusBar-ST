#include "spi3.h"

char spi_count=0;


void DelayNop_SPI(int cm)
{
		int i=0;
		for(i=0;i<cm;i++)
		{
		}
}


/********************
RS=0:指令
RS=1:像素值
******************************/
void TFT_RS(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOD, GPIO_Pin_7);       //PD7=0    替换      PB6=0
		else 
				GPIO_SetBits(GPIOD, GPIO_Pin_7);
}

void TFT_CS(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOD, GPIO_Pin_3);       //PD3=0    替换     PD4=0
		else 
				GPIO_SetBits(GPIOD, GPIO_Pin_3);
}

void TFT_SCK(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOC, GPIO_Pin_10);       //PC10=0    替换     PB3=0
		else 
				GPIO_SetBits(GPIOC, GPIO_Pin_10);
}

void TFT_SDI(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOC, GPIO_Pin_12);       //PC12=0    替换     PB5=0
		else 
				GPIO_SetBits(GPIOC, GPIO_Pin_12);
}

void TFT_REST(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOG, GPIO_Pin_10);       //PG10=0    替换     PB7=0
		else 
				GPIO_SetBits(GPIOG, GPIO_Pin_10);
}

void TFT_LEDA(char ch)			//LCD背光
{
		if(ch)
				GPIO_ResetBits(GPIOB, GPIO_Pin_8);       //PB8=0    替换     PE3=0
		else 
				GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

/**************************
模拟SPI时序
***************************/
void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	      
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	
  //GPIOFB3 、5 、6、7初始化设置       
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  //PB3 、5 、6、7复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//配置为输出口
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//无上下拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化

  //GPIOFD4初始化设置          CS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//PB6复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//配置为输出口
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//无上下拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化		
	
  //GPIOFE5初始化设置          LEDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PE5复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//配置为输出口
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上下拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化		
}


//以下是SPI模块的初始化代码，配置成主机模式 						  
//SPI口初始化
//这里针是对SPI3的初始化
void SPI3_Init(void)
{	
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
		
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOE时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);//使能SPI3时钟
 
  //GPIOFC10,11,12初始化设置        SPI_SCK、SPI_MOSI
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;//PC10、12复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3); //PC10复用为 SPI3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3); //PC12复用为 SPI3
	
  //GPIOPD7初始化设置         RS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PB6复用功能输出	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//配置为输出口
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上下拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化	
 
  //GPIOPD3初始化设置          CS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//配置为输出口
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//无上下拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化	

  //GPIOPG10初始化设置          RES
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//配置为输出口
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上下拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化
	
  //GPIOPB8初始化设置          LEDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//配置为输出口
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上下拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化	
 
//	//这里只针对SPI口初始化
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);//复位SPI1
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,DISABLE);//停止复位SPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI3, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI3, ENABLE); //使能SPI外设
	
	TFT_CS(1);
 
}  

//SPI1速度设置函数
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI3->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI3->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI3,ENABLE); //使能SPI1
} 
//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI3_ReadWriteByte(u8 TxData)
{		 			 

	while((SPI3->SR&SPI_I2S_FLAG_TXE)==RESET);		//等待发送区空	 
	if(!spi_count)
	{
		spi_count = 1;	
		DelayNop_SPI(1500);	
	}
	SPI3->DR=TxData;	 	//发送一个byte   
	
	while((SPI3->SR&SPI_I2S_FLAG_RXNE)==RESET)
	{
	}//等待接收完一个byte  
	return SPI3->DR;          	     //返回收到的数据				
 		    
}


/****************************************************************************
* 名    称：void  SPIv_WriteData(u8 Data)
* 功    能：STM32_模拟SPI写一个字节数据底层函数
* 入口参数：Data
* 出口参数：无
* 说    明：STM32_模拟SPI读写一个字节数据底层函数
****************************************************************************/
void  SPIv_WriteData(u8 Data)
{
	unsigned char i=0;		

	if(!spi_count)
	{
		spi_count = 1;	
		DelayNop_SPI(310);
	}
	
	for(i=8;i>0;i--)
	{	 
		if(Data&0x80)	
			TFT_SDI(0); //输出数据
    else 
			TFT_SDI(1); 
		TFT_SCK(1);
    TFT_SCK(0); 
    Data<<=1; 
	}	
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



