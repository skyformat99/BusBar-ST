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
RS=0:ָ��
RS=1:����ֵ
******************************/
void TFT_RS(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOD, GPIO_Pin_7);       //PD7=0    �滻      PB6=0
		else 
				GPIO_SetBits(GPIOD, GPIO_Pin_7);
}

void TFT_CS(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOD, GPIO_Pin_3);       //PD3=0    �滻     PD4=0
		else 
				GPIO_SetBits(GPIOD, GPIO_Pin_3);
}

void TFT_SCK(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOC, GPIO_Pin_10);       //PC10=0    �滻     PB3=0
		else 
				GPIO_SetBits(GPIOC, GPIO_Pin_10);
}

void TFT_SDI(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOC, GPIO_Pin_12);       //PC12=0    �滻     PB5=0
		else 
				GPIO_SetBits(GPIOC, GPIO_Pin_12);
}

void TFT_REST(char ch)
{
		if(ch)
				GPIO_ResetBits(GPIOG, GPIO_Pin_10);       //PG10=0    �滻     PB7=0
		else 
				GPIO_SetBits(GPIOG, GPIO_Pin_10);
}

void TFT_LEDA(char ch)			//LCD����
{
		if(ch)
				GPIO_ResetBits(GPIOB, GPIO_Pin_8);       //PB8=0    �滻     PE3=0
		else 
				GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

/**************************
ģ��SPIʱ��
***************************/
void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	      
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
	
  //GPIOFB3 ��5 ��6��7��ʼ������       
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  //PB3 ��5 ��6��7���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//����Ϊ�����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

  //GPIOFD4��ʼ������          CS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//PB6���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//����Ϊ�����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��		
	
  //GPIOFE5��ʼ������          LEDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PE5���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//����Ϊ�����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��		
}


//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ 						  
//SPI�ڳ�ʼ��
//�������Ƕ�SPI3�ĳ�ʼ��
void SPI3_Init(void)
{	
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
		
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOEʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);//ʹ��SPI3ʱ��
 
  //GPIOFC10,11,12��ʼ������        SPI_SCK��SPI_MOSI
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;//PC10��12���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3); //PC10����Ϊ SPI3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3); //PC12����Ϊ SPI3
	
  //GPIOPD7��ʼ������         RS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PB6���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//����Ϊ�����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��	
 
  //GPIOPD3��ʼ������          CS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//����Ϊ�����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��	

  //GPIOPG10��ʼ������          RES
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//����Ϊ�����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
	
  //GPIOPB8��ʼ������          LEDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//����Ϊ�����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��	
 
//	//����ֻ���SPI�ڳ�ʼ��
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,ENABLE);//��λSPI1
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3,DISABLE);//ֹͣ��λSPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI3, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI3, ENABLE); //ʹ��SPI����
	
	TFT_CS(1);
 
}  

//SPI1�ٶ����ú���
//SPI�ٶ�=fAPB2/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2ʱ��һ��Ϊ84Mhz��
void SPI3_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI3->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI3->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI3,ENABLE); //ʹ��SPI1
} 
//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI3_ReadWriteByte(u8 TxData)
{		 			 

	while((SPI3->SR&SPI_I2S_FLAG_TXE)==RESET);		//�ȴ���������	 
	if(!spi_count)
	{
		spi_count = 1;	
		DelayNop_SPI(1500);	
	}
	SPI3->DR=TxData;	 	//����һ��byte   
	
	while((SPI3->SR&SPI_I2S_FLAG_RXNE)==RESET)
	{
	}//�ȴ�������һ��byte  
	return SPI3->DR;          	     //�����յ�������				
 		    
}


/****************************************************************************
* ��    �ƣ�void  SPIv_WriteData(u8 Data)
* ��    �ܣ�STM32_ģ��SPIдһ���ֽ����ݵײ㺯��
* ��ڲ�����Data
* ���ڲ�������
* ˵    ����STM32_ģ��SPI��дһ���ֽ����ݵײ㺯��
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
			TFT_SDI(0); //�������
    else 
			TFT_SDI(1); 
		TFT_SCK(1);
    TFT_SCK(0); 
    Data<<=1; 
	}	
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



