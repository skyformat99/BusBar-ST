#include "usart1.h"

u8 USART1_RX_BUF[16];     //接收缓冲,最大200个字节.  USART1
u8 RSART1_RX_CNT=0;

void USART1_CS(char cs)            //USART1
{
		if(cs)
			GPIO_ResetBits(GPIOA, GPIO_Pin_11);
		else 
			GPIO_SetBits(GPIOA, GPIO_Pin_11);	
}

void usart_init(uint32_t baudrate)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;

   //Enable GPIOC clock
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
   //Enable USART1 clock
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

   //Configure USART1_TX (PA9) and USART1_RX (PA10)
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
	

   //Remap USART1_TX and USART1_RX pins to PA9 and PA10
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	 

   //Configure USART1
   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   USART_Init(USART1, &USART_InitStructure);
	  
	 
	/*******/
	//485USART1片选
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


   //Enable USART1
   USART_Cmd(USART1, ENABLE); 
	 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	


}


void USART1_IRQHandler(void)                	
{
	u8 Res;
	
	if(USART1->SR&(1<<5))//接收到数据
	{	 
		Res=USART1->DR; 
		if(RSART1_RX_CNT<=8)
		{		
				USART1_RX_BUF[RSART1_RX_CNT]=Res;
				RSART1_RX_CNT++;						//接收数据增加1 
		}
	}
}

/*****************************************
串口1发送一个字节的字符
******************************************/
void Send_One_Byte(u8 data)
{
	 USART1_CS(0);
	 USART_SendData(USART1,data );         //向串口1发送数据
	 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
   USART1_CS(1);
}

/***************************
串口1发送一个字符串
****************************/
void uart1_send_data(u8 *buff,int len)
{
		while(len--)
		{
			Send_One_Byte(*buff);
			buff++;
		}
}












