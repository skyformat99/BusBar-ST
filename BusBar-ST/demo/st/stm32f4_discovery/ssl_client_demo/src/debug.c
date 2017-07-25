/**
 * @file debug.c
 * @brief Debugging facilities
 *
 * @section License
 *
 * Copyright (C) 2010-2016 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.7.2
 **/

//Dependencies
#include "stm32f4xx.h"
#include "debug.h"

/**************************************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************************************/

void USART3_CS(char cs)            //USART3
{
		if(cs)
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		else 
			GPIO_SetBits(GPIOB, GPIO_Pin_9);	
}


/* 定义每个串口结构体变量 */
#if UART1_FIFO_EN == 1
	UART_T *g_tUart1;
	uint8_t g_RxBuf1[UART1_RX_BUF_SIZE] ;		/* 接收缓冲区 */
#endif

#if UART2_FIFO_EN == 1
	UART_T g_tUart2;
	uint8_t g_TxBuf2[UART2_TX_BUF_SIZE];		/* 发送缓冲区 */
	uint8_t g_RxBuf2[UART2_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif

#if UART3_FIFO_EN == 1
	UART_T g_tUart3 __attribute__((at(0X64002800)));
	uint8_t g_RxBuf3[UART3_RX_BUF_SIZE] __attribute__((at(0X64000004)));		/* 接收缓冲区 */
#endif

#if UART4_FIFO_EN == 1
	UART_T g_tUart4;
	uint8_t g_TxBuf4[UART4_TX_BUF_SIZE];		/* 发送缓冲区 */
	uint8_t g_RxBuf4[UART4_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif

#if UART5_FIFO_EN == 1
	UART_T g_tUart5;
	uint8_t g_TxBuf5[UART5_TX_BUF_SIZE];		/* 发送缓冲区 */
	uint8_t g_RxBuf5[UART5_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif

#if UART6_FIFO_EN == 1
	UART_T g_tUart6 __attribute__((at(0X64001400)));
	uint8_t g_RxBuf6[UART6_RX_BUF_SIZE] __attribute__((at(0X64000C00)));		/* 接收缓冲区 */
#endif




/*
*********************************************************************************************************
*	函 数 名: RS485_SendBefor
*	功能说明: 发送数据前的准备工作。对于RS485通信，请设置RS485芯片为发送状态，
*			  并修改 UartVarInit()中的函数指针等于本函数名，比如 g_tUart2.SendBefor = RS485_SendBefor
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RS485_SendBefor(void)
{
	RS485_TX_EN();	/* 切换RS485收发芯片为发送模式 */
}

/*
*********************************************************************************************************
*	函 数 名: RS485_SendOver
*	功能说明: 发送一串数据结束后的善后处理。对于RS485通信，请设置RS485芯片为接收状态，
*			  并修改 UartVarInit()中的函数指针等于本函数名，比如 g_tUart2.SendOver = RS485_SendOver
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RS485_SendOver(void)
{
	RS485_RX_EN();	/* 切换RS485收发芯片为接收模式 */
}


/*
*********************************************************************************************************
*	函 数 名: RS485_SendBefor
*	功能说明: 发送数据前的准备工作。对于RS485通信，请设置RS485芯片为发送状态，
*			  并修改 UartVarInit()中的函数指针等于本函数名，比如 g_tUart2.SendBefor = RS485_SendBefor
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RS485_6_SendBefor(void)
{
	RS485_6_TX_EN();	/* 切换RS485收发芯片为发送模式 */
}

/*
*********************************************************************************************************
*	函 数 名: RS485_SendOver
*	功能说明: 发送一串数据结束后的善后处理。对于RS485通信，请设置RS485芯片为接收状态，
*			  并修改 UartVarInit()中的函数指针等于本函数名，比如 g_tUart2.SendOver = RS485_SendOver
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RS485_6_SendOver(void)
{
	RS485_6_RX_EN();	/* 切换RS485收发芯片为接收模式 */
}

/*
*********************************************************************************************************
*	函 数 名: ComToUart
*	功能说明: 将COM端口号转换为 USART_TypeDef* USARTx
*	形    参: _ucPort: 端口号(COM1 - COM6)
*	返 回 值: USART_TypeDef*,  USART1, USART2, USART3, UART4, UART5
*********************************************************************************************************
*/
USART_TypeDef *ComToUSARTx(COM_PORT_E _ucPort)
{
	if (_ucPort == COM1)
	{
		#if UART1_FIFO_EN == 1
			return USART1;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM2)
	{
		#if UART2_FIFO_EN == 1
			return USART2;
		#else
			return;
		#endif
	}
	else if (_ucPort == COM3)
	{
		#if UART3_FIFO_EN == 1
			return USART3;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM4)
	{
		#if UART4_FIFO_EN == 1
			return USART4;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM5)
	{
		#if UART5_FIFO_EN == 1
			return USART5;
		#else
			return 0;
		#endif
	}
	else
	{
		/* 不做任何处理 */
		return 0;
	}
}


/*
*********************************************************************************************************
*	函 数 名: USART_SetBaudRate
*	功能说明: 修改波特率寄存器，不更改其他设置。如果使用 USART_Init函数, 则会修改硬件流控参数和RX,TX配置
*			  根据固件库中 USART_Init函数，将其中配置波特率的部分单独提出来封装为一个函数
*	形    参: USARTx : USART1, USART2, USART3, UART4, UART5
*			  BaudRate : 波特率，取值 0 - 4500000
*	返 回 值: 无
*********************************************************************************************************
*/
void USART_SetBaudRate(USART_TypeDef* USARTx, uint32_t BaudRate)
{
	uint32_t tmpreg = 0x00, apbclock = 0x00;
	uint32_t integerdivider = 0x00;
	uint32_t fractionaldivider = 0x00;
	RCC_ClocksTypeDef RCC_ClocksStatus;

	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	assert_param(IS_USART_BAUDRATE(BaudRate));  

	/*---------------------------- USART BRR Configuration -----------------------*/
	/* Configure the USART Baud Rate */
	RCC_GetClocksFreq(&RCC_ClocksStatus);

	if ((USARTx == USART1) || (USARTx == USART6))
	{
		apbclock = RCC_ClocksStatus.PCLK2_Frequency;
	}
	else
	{
		apbclock = RCC_ClocksStatus.PCLK1_Frequency;
	}

	/* Determine the integer part */
	if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
	{
		/* Integer part computing in case Oversampling mode is 8 Samples */
		integerdivider = ((25 * apbclock) / (2 * (BaudRate)));    
	}
	else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
	{
		/* Integer part computing in case Oversampling mode is 16 Samples */
		integerdivider = ((25 * apbclock) / (4 * (BaudRate)));    
	}
	tmpreg = (integerdivider / 100) << 4;

	/* Determine the fractional part */
	fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

	/* Implement the fractional part in the register */
	if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
	{
		tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
	}
	else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
	{
		tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
	}

	/* Write to USART BRR register */
	USARTx->BRR = (uint16_t)tmpreg;
}




/*
*********************************************************************************************************
*	函 数 名: UartVarInit
*	功能说明: 初始化串口相关的变量
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void UartVarInit(void)
{
#if UART1_FIFO_EN == 1
	g_tUart1->uart = USART1;						/* STM32 串口设备 */
	g_tUart1->pTxBuf = 0;					/* 发送缓冲区指针 */
	g_tUart1->pRxBuf = g_RxBuf1;					/* 接收缓冲区指针 */
	g_tUart1->usTxBufSize = 0;	/* 发送缓冲区大小 */
	g_tUart1->usRxBufSize = UART1_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUart1->usTxWrite = 0;						/* 发送FIFO写索引 */
	g_tUart1->usTxRead = 0;						/* 发送FIFO读索引 */
	g_tUart1->usRxWrite = 0;						/* 接收FIFO写索引 */
	g_tUart1->usRxRead = 0;						/* 接收FIFO读索引 */
	g_tUart1->usRxCount = 0;						/* 接收到的新数据个数 */
	g_tUart1->usTxCount = 0;						/* 待发送的数据个数 */
	g_tUart1->SendBefor = 0;						/* 发送数据前的回调函数 */
	g_tUart1->SendOver = 0;							/* 发送完毕后的回调函数  RS485_SendBefor*/
	g_tUart1->ReciveNew = 0;						/* 接收到新数据后的回调函数 RS485_SendOver*/
#endif

#if UART2_FIFO_EN == 1
	g_tUart2.uart = USART2;						/* STM32 串口设备 */
	g_tUart2.pTxBuf = g_TxBuf2;					/* 发送缓冲区指针 */
	g_tUart2.pRxBuf = g_RxBuf2;					/* 接收缓冲区指针 */
	g_tUart2.usTxBufSize = UART2_TX_BUF_SIZE;	/* 发送缓冲区大小 */
	g_tUart2.usRxBufSize = UART2_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUart2.usTxWrite = 0;						/* 发送FIFO写索引 */
	g_tUart2.usTxRead = 0;						/* 发送FIFO读索引 */
	g_tUart2.usRxWrite = 0;						/* 接收FIFO写索引 */
	g_tUart2.usRxRead = 0;						/* 接收FIFO读索引 */
	g_tUart2.usRxCount = 0;						/* 接收到的新数据个数 */
	g_tUart2.usTxCount = 0;						/* 待发送的数据个数 */
	g_tUart2.SendBefor = 0;						/* 发送数据前的回调函数 */
	g_tUart2.SendOver = 0;						/* 发送完毕后的回调函数 */
	g_tUart2.ReciveNew = 0;						/* 接收到新数据后的回调函数 */
#endif

#if UART3_FIFO_EN == 1
	g_tUart3.uart = USART3;						/* STM32 串口设备 */
	g_tUart3.pTxBuf = 0;					/* 发送缓冲区指针 */
	g_tUart3.pRxBuf = g_RxBuf3;					/* 接收缓冲区指针 */
	g_tUart3.usTxBufSize = 0;	/* 发送缓冲区大小 */
	g_tUart3.usRxBufSize = UART3_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUart3.usTxWrite = 0;						/* 发送FIFO写索引 */
	g_tUart3.usTxRead = 0;						/* 发送FIFO读索引 */
	g_tUart3.usRxWrite = 0;						/* 接收FIFO写索引 */
	g_tUart3.usRxRead = 0;						/* 接收FIFO读索引 */
	g_tUart3.usRxCount = 0;						/* 接收到的新数据个数 */
	g_tUart3.usTxCount = 0;						/* 待发送的数据个数 */
	g_tUart3.SendBefor = 0;		/* 发送数据前的回调函数 */
	g_tUart3.SendOver = 0;			/* 发送完毕后的回调函数 */
	g_tUart3.ReciveNew = 0;		/* 接收到新数据后的回调函数 */
#endif

#if UART4_FIFO_EN == 1
	g_tUart4.uart = UART4;						/* STM32 串口设备 */
	g_tUart4.pTxBuf = g_TxBuf4;					/* 发送缓冲区指针 */
	g_tUart4.pRxBuf = g_RxBuf4;					/* 接收缓冲区指针 */
	g_tUart4.usTxBufSize = UART4_TX_BUF_SIZE;	/* 发送缓冲区大小 */
	g_tUart4.usRxBufSize = UART4_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUart4.usTxWrite = 0;						/* 发送FIFO写索引 */
	g_tUart4.usTxRead = 0;						/* 发送FIFO读索引 */
	g_tUart4.usRxWrite = 0;						/* 接收FIFO写索引 */
	g_tUart4.usRxRead = 0;						/* 接收FIFO读索引 */
	g_tUart4.usRxCount = 0;						/* 接收到的新数据个数 */
	g_tUart4.usTxCount = 0;						/* 待发送的数据个数 */
	g_tUart4.SendBefor = 0;						/* 发送数据前的回调函数 */
	g_tUart4.SendOver = 0;						/* 发送完毕后的回调函数 */
	g_tUart4.ReciveNew = 0;						/* 接收到新数据后的回调函数 */
#endif

#if UART5_FIFO_EN == 1
	g_tUart5.uart = UART5;						/* STM32 串口设备 */
	g_tUart5.pTxBuf = g_TxBuf5;					/* 发送缓冲区指针 */
	g_tUart5.pRxBuf = g_RxBuf5;					/* 接收缓冲区指针 */
	g_tUart5.usTxBufSize = UART5_TX_BUF_SIZE;	/* 发送缓冲区大小 */
	g_tUart5.usRxBufSize = UART5_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUart5.usTxWrite = 0;						/* 发送FIFO写索引 */
	g_tUart5.usTxRead = 0;						/* 发送FIFO读索引 */
	g_tUart5.usRxWrite = 0;						/* 接收FIFO写索引 */
	g_tUart5.usRxRead = 0;						/* 接收FIFO读索引 */
	g_tUart5.usRxCount = 0;						/* 接收到的新数据个数 */
	g_tUart5.usTxCount = 0;						/* 待发送的数据个数 */
	g_tUart5.SendBefor = 0;						/* 发送数据前的回调函数 */
	g_tUart5.SendOver = 0;						/* 发送完毕后的回调函数 */
	g_tUart5.ReciveNew = 0;						/* 接收到新数据后的回调函数 */
#endif


#if UART6_FIFO_EN == 1
	g_tUart6.uart = USART6;						/* STM32 串口设备 */
	g_tUart6.pTxBuf = 0;					/* 发送缓冲区指针 */
	g_tUart6.pRxBuf = g_RxBuf6;					/* 接收缓冲区指针 */
	g_tUart6.usTxBufSize = 0;	/* 发送缓冲区大小 */
	g_tUart6.usRxBufSize = UART6_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUart6.usTxWrite = 0;						/* 发送FIFO写索引 */
	g_tUart6.usTxRead = 0;						/* 发送FIFO读索引 */
	g_tUart6.usRxWrite = 0;						/* 接收FIFO写索引 */
	g_tUart6.usRxRead = 0;						/* 接收FIFO读索引 */
	g_tUart6.usRxCount = 0;						/* 接收到的新数据个数 */
	g_tUart6.usTxCount = 0;						/* 待发送的数据个数 */
	g_tUart6.SendBefor = 0;						/* 发送数据前的回调函数 */ //RS485_6_SendBefor
	g_tUart6.SendOver = 0;						/* 发送完毕后的回调函数 *///RS485_6_SendOver
	g_tUart6.ReciveNew = 0;						/* 接收到新数据后的回调函数 */
#endif
}

/*
*********************************************************************************************************
*	函 数 名: InitHardUart
*	功能说明: 配置串口的硬件参数（波特率，数据位，停止位，起始位，校验位，中断使能）适合于STM32-F4开发板
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void InitHardUart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

#if UART1_FIFO_EN == 1		/* 串口1 TX = PA9   RX = PA10 或 TX = PB6   RX = PB7*/

		/* 配置 PA11为推挽输出，用于切换 RS485芯片的收发状态 */
		{
			RCC_AHB1PeriphClockCmd(RCC_RS485_TXEN, ENABLE);

			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* 设为输出口 */
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为推挽模式 */
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* 上下拉电阻不使能 */
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO口最大速度 */

			GPIO_InitStructure.GPIO_Pin = PIN_RS485_TXEN;
			GPIO_Init(PORT_RS485_TXEN, &GPIO_InitStructure);
		}	
	
	/* 第1步： 配置GPIO */
//	#if 1	/* TX = PA9   RX = PA10 */
		/* 打开 GPIO 时钟 */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

		/* 打开 UART 时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

		/* 将 PA9 映射为 USART1_TX */
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

		/* 将 PA10 映射为 USART1_RX */
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

		/* 配置 USART Tx 为复用功能 */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* 配置 USART Rx 为复用功能 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
//	#else	/* TX = PB6   RX = PB7  */
//		/* 打开 GPIO 时钟 */
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

//		/* 打开 UART 时钟 */
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

//		/* 将 PB6 映射为 USART1_TX */
//		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

//		/* 将 PB7 映射为 USART1_RX */
//		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

//		/* 配置 USART Tx 为复用功能 */
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);

//		/* 配置 USART Rx 为复用功能 */
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);
//	#endif

	/* 第2步： 配置串口硬件参数 */
	USART_InitStructure.USART_BaudRate = UART1_BAUD;	/* 波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	*/
	USART_Cmd(USART1, ENABLE);		/* 使能串口 */

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USART1, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif

#if UART2_FIFO_EN == 1		/* 串口2 TX = PD5   RX = PD6 或  TX = PA2， RX = PA3  */
//	/* 第1步： 配置GPIO */
//	#if 0	/* 串口2 TX = PD5   RX = PD6 */
//		/* 打开 GPIO 时钟 */
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

//		/* 打开 UART 时钟 */
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

//		/* 将 PD5 映射为 USART2_TX */
//		GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);

//		/* 将 PD6 映射为 USART2_RX */
//		GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

//		/* 配置 USART Tx 为复用功能 */
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(GPIOD, &GPIO_InitStructure);

//		/* 配置 USART Rx 为复用功能 */
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//		GPIO_Init(GPIOD, &GPIO_InitStructure);

//	#else	/* 串口2   TX = PA2， RX = PA3 */
//		/* 打开 GPIO 时钟 */
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

//		/* 打开 UART 时钟 */
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

//		/* 将 PA2 映射为 USART2_TX. 在STM32-V5板中，PA2 管脚用于以太网 */
//		//GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

//		/* 将 PA3 映射为 USART2_RX */
//		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

//		/* 配置 USART Tx 为复用功能 */
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

//		//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//		//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		//GPIO_Init(GPIOA, &GPIO_InitStructure);

//		/* 配置 USART Rx 为复用功能 */
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//	#endif

//	/* 第2步： 配置串口硬件参数 */
//	USART_InitStructure.USART_BaudRate = UART2_BAUD;	/* 波特率 */
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx;		/* 仅选择接收模式 */
//	USART_Init(USART2, &USART_InitStructure);

//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
//	/*
//		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
//		注意: 不要在此处打开发送中断
//		发送中断使能在SendUart()函数打开
//	*/
//	USART_Cmd(USART2, ENABLE);		/* 使能串口 */

//	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
//		如下语句解决第1个字节无法正确发送出去的问题 */
//	USART_ClearFlag(USART2, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif

#if UART3_FIFO_EN == 1			/* 串口3 TX = PB10   RX = PB11 */

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
	
  //串口2引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10与GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PA2，PA3
	
	//PB9推挽输出，485模式控制  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //GPIOB9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB9
	

   //USART3 初始化设置
	USART_InitStructure.USART_BaudRate = UART3_BAUD;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure); //初始化串口2
	
  USART_Cmd(USART3, ENABLE);  //使能串口 3
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启接受中断
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
#endif

#if UART4_FIFO_EN == 1			/* 串口4 TX = PC10   RX = PC11 */
//	/* 第1步： 配置GPIO */

//	/* 打开 GPIO 时钟 */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

//	/* 打开 UART 时钟 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

//	/* 将 PC10 映射为 UART4_TX */
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART1);

//	/* 将 PC11 映射为 UART4_RX */
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART1);

//	/* 配置 USART Tx 为复用功能 */
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);

//	/* 配置 USART Rx 为复用功能 */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);

//	/* 第2步： 配置串口硬件参数 */
//	USART_InitStructure.USART_BaudRate = UART1_BAUD;	/* 波特率 */
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(UART4, &USART_InitStructure);

//	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
//	/*
//		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
//		注意: 不要在此处打开发送中断
//		发送中断使能在SendUart()函数打开
//	*/
//	USART_Cmd(UART4, ENABLE);		/* 使能串口 */

//	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
//		如下语句解决第1个字节无法正确发送出去的问题 */
//	USART_ClearFlag(UART4, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif

#if UART5_FIFO_EN == 1			/* 串口5 TX = PC12   RX = PD2 */
//	/* 第1步： 配置GPIO */

//	/* 打开 GPIO 时钟 */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC |RCC_AHB1Periph_GPIOD, ENABLE);

//	/* 打开 UART 时钟 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

//	/* 将 PC12 映射为 UART5_TX */
//	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);

//	/* 将 PD2 映射为 UART5_RX */
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

//	/* 配置 UART Tx 为复用功能 */
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);

//	/* 配置 UART Rx 为复用功能 */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);

//	/* 第2步： 配置串口硬件参数 */
//	USART_InitStructure.USART_BaudRate = UART5_BAUD;	/* 波特率 */
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(UART5, &USART_InitStructure);

//	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
//	/*
//		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
//		注意: 不要在此处打开发送中断
//		发送中断使能在SendUart()函数打开
//	*/
//	USART_Cmd(UART5, ENABLE);		/* 使能串口 */

//	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
//		如下语句解决第1个字节无法正确发送出去的问题 */
//	USART_ClearFlag(UART5, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif

#if UART6_FIFO_EN == 1			/* PC6/USART6_TX , PC7/USART6_RX,PG8/USART6_RTS, PG15/USART6_CTS */
	/* 第1步： 配置GPIO */

	/* 打开 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* 打开 UART 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	/* 将 PC6 映射为 USART6_tX *//* 将 PC7 映射为 USART6_RX */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

   //Configure USART6_TX (PC6) and USART6_RX (PC7)
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);	

	/* 第2步： 配置串口硬件参数 */
	USART_InitStructure.USART_BaudRate = UART6_BAUD;	/* 波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Even ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	/* 不要硬件流控 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	*/
	USART_Cmd(USART6, ENABLE);		/* 使能串口 */

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USART6, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif
}

/*
*********************************************************************************************************
*	函 数 名: ConfigUartNVIC
*	功能说明: 配置串口硬件中断.
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static void ConfigUartNVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */
	/*	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  --- 在 bsp.c 中 bsp_Init() 中配置中断优先级组 */

#if UART1_FIFO_EN == 1
	/* 使能串口1中断 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART2_FIFO_EN == 1
	/* 使能串口2中断 */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART3_FIFO_EN == 1
	/* 使能串口3中断t */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART4_FIFO_EN == 1
	/* 使能串口4中断t */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART5_FIFO_EN == 1
	/* 使能串口5中断t */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART6_FIFO_EN == 1
	/* 使能串口6中断t */
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}

/*
*********************************************************************************************************
*	函 数 名: bsp_InitUart
*	功能说明: 初始化串口硬件，并对全局变量赋初值.
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitUart(void)
{
	UartVarInit();		/* 必须先初始化全局变量,再配置硬件 */

	InitHardUart();		/* 配置串口的硬件参数(波特率等) */

	ConfigUartNVIC();	/* 配置串口中断 */
}





/*
*********************************************************************************************************
*	函 数 名: ComToUart
*	功能说明: 将COM端口号转换为UART指针
*	形    参: _ucPort: 端口号(COM1 - COM6)
*	返 回 值: uart指针
*********************************************************************************************************
*/
UART_T *ComToUart(COM_PORT_E _ucPort)
{
	if (_ucPort == COM1)
	{
		#if UART1_FIFO_EN == 1
			return g_tUart1;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM2)
	{
		#if UART2_FIFO_EN == 1
			return &g_tUart2;
		#else
			return;
		#endif
	}
	else if (_ucPort == COM3)
	{
		#if UART3_FIFO_EN == 1
			return &g_tUart3;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM4)
	{
		#if UART4_FIFO_EN == 1
			return &g_tUart4;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM5)
	{
		#if UART5_FIFO_EN == 1
			return &g_tUart5;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM6)
	{
		#if UART6_FIFO_EN == 1
			return &g_tUart6;
		#else
			return 0;
		#endif
	}
	else
	{
		/* 不做任何处理 */
		return 0;
	}
}

/*
*********************************************************************************************************
*	函 数 名: UartGetChar
*	功能说明: 从串口接收缓冲区读取1字节数据 （用于主程序调用）
*	形    参: _pUart : 串口设备
*			  _pByte : 存放读取数据的指针
*	返 回 值: 0 表示无数据  1表示读取到数据
*********************************************************************************************************
*/
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte)
{
	uint16_t usCount;

	/* usRxWrite 变量在中断函数中被改写，主程序读取该变量时，必须进行临界区保护 */
	DISABLE_INT();
	usCount = _pUart->usRxCount;
	ENABLE_INT();

	/* 如果读和写索引相同，则返回0 */
	//if (_pUart->usRxRead == usRxWrite)
	if (usCount == 0)	/* 已经没有数据 */
	{
		return 0;
	}
	else
	{
		*_pByte = _pUart->pRxBuf[_pUart->usRxRead];		/* 从串口接收FIFO取1个数据 */

		/* 改写FIFO读索引 */
		DISABLE_INT();
		if (++_pUart->usRxRead >= _pUart->usRxBufSize)
		{
			_pUart->usRxRead = 0;
		}
		_pUart->usRxCount--;
		ENABLE_INT();
		return 1;
	}
}

/*
*********************************************************************************************************
*	函 数 名: comGetChar
*	功能说明: 从接收缓冲区读取1字节，非阻塞。无论有无数据均立即返回。
*	形    参: _ucPort: 端口号(COM1 - COM5)
*			  _pByte: 接收到的数据存放在这个地址
*	返 回 值: 0 表示无数据, 1 表示读取到有效字节
*********************************************************************************************************
*/
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return 0;
	}

	return UartGetChar(pUart, _pByte);
}

void Uart_Recive_data(COM_PORT_E _ucPort,u8 *buff,int len)
{	
	while(len--)
	{
		comGetChar(_ucPort,buff);
		buff++;
	}
}

/*
*********************************************************************************************************
*	函 数 名: UartIRQ
*	功能说明: 供中断服务程序调用，通用串口中断处理函数
*	形    参: _pUart : 串口设备
*	返 回 值: 无
*********************************************************************************************************
*/
static void UartIRQ(UART_T *_pUart)
{
	/* 处理接收中断  */
	if (USART_GetITStatus(_pUart->uart, USART_IT_RXNE) != RESET)
	{
		/* 从串口接收数据寄存器读取数据存放到接收FIFO */
		uint8_t ch;

		ch = USART_ReceiveData(_pUart->uart);
		_pUart->pRxBuf[_pUart->usRxWrite] = ch;
		if (++_pUart->usRxWrite >= _pUart->usRxBufSize)
		{
			_pUart->usRxWrite = 0;
		}
		if (_pUart->usRxCount < _pUart->usRxBufSize)
		{
			_pUart->usRxCount++;
		}

		/* 回调函数,通知应用程序收到新数据,一般是发送1个消息或者设置一个标记 */
		//if (_pUart->usRxWrite == _pUart->usRxRead)
		//if (_pUart->usRxCount == 1)
		{
			if (_pUart->ReciveNew)
			{
				_pUart->ReciveNew(ch);
			}
		}
	}

}

/*
*********************************************************************************************************
*	函 数 名: USART1_IRQHandler  USART2_IRQHandler USART3_IRQHandler UART4_IRQHandler UART5_IRQHandler
*	功能说明: USART中断服务程序
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
#if UART1_FIFO_EN == 1
void USART1_IRQHandler(void)
{
	UartIRQ(g_tUart1);
}
#endif

#if UART2_FIFO_EN == 1
void USART2_IRQHandler(void)
{
	UartIRQ(&g_tUart2);
}
#endif

#if UART3_FIFO_EN == 1
void USART3_IRQHandler(void)
{
	UartIRQ(&g_tUart3);
}
#endif

#if UART4_FIFO_EN == 1
void UART4_IRQHandler(void)
{
	UartIRQ(&g_tUart4);
}
#endif

#if UART5_FIFO_EN == 1
void UART5_IRQHandler(void)
{
	UartIRQ(&g_tUart5);
}
#endif

#if UART6_FIFO_EN == 1
void USART6_IRQHandler(void)
{
	UartIRQ(&g_tUart6);
}
#endif

/**
 * @brief Display the contents of an array
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @param[in] prepend String to prepend to the left of each line
 * @param[in] data Pointer to the data array
 * @param[in] length Number of bytes to display
 **/

void debugDisplayArray(FILE *stream,
   const char_t *prepend, const void *data, size_t length)
{
//   uint_t i;

//   for(i = 0; i < length; i++)
//   {
//      //Beginning of a new line?
//      if((i % 16) == 0)
//         fprintf(stream, "%s", prepend);
//      //Display current data byte
//      fprintf(stream, "%02" PRIX8 " ", *((uint8_t *) data + i));
//      //End of current line?
//      if((i % 16) == 15 || i == (length - 1))
//         fprintf(stream, "\r\n");
//   }
}


/**
 * @brief Write character to stream
 * @param[in] c The character to be written
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @return On success, the character written is returned. If a writing
 *   error occurs, EOF is returned
 **/

int_t fputc(int_t c, FILE *stream)
{
//   //Standard output?
//   if(stream == stdout)
//   {
//      //On success, the character written is returned
//      return c;
//   }
//   //Standard error output?
//   else if(stream == stderr)
//   {
//      //Wait for the transmitter to be ready
//      while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//      //Send character
//      USART_SendData(USART3, c);
//      //Wait for the transfer to complete
//      while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

//      //On success, the character written is returned
//      return c;
//   }
//   //Unknown output?
//   else
//   {
//      //If a writing error occurs, EOF is returned
//      return EOF;
//   }
}


/*****************************************
串口6发送一个字节的字符
******************************************/
void Send_One_Byte6(u8 data,int len)
{
	 USART_SendData(USART6,data );         //向串口1发送数据
	 while(USART_GetFlagStatus(USART6,USART_FLAG_TC)!=SET);//等待发送结束
	 if(len==1)osDelayTask(10);
}

/***************************
串口6发送一个字符串
****************************/
void uart6_send_data(u8 *buff,int len)
{
		osDelayTask(10);
		while(len--)
		{
			Send_One_Byte6(*buff,len);
			buff++;
		}
}


/*****************************************
串口1发送一个字节的字符
******************************************/
void Send_One_Byte3(u8 data,int len)
{
		 USART3_CS(0);
		 USART_SendData(USART3,data );         //向串口3发送数据
		 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束 
		 if(len==1)osDelayTask(10);
		 USART3_CS(1);
}

/***************************
串口1发送一个字符串
****************************/
void uart3_send_data(u8 *buff,int len)
{
		osDelayTask(10);
		while(len--)
		{
				Send_One_Byte3(*buff,len);
				buff++;
		}
}




/*
*********************************************************************************************************
*	函 数 名: comClearTxFifo
*	功能说明: 清零串口发送缓冲区
*	形    参: _ucPort: 端口号(COM1 - COM6)
*	返 回 值: 无
*********************************************************************************************************
*/
void comClearTxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usTxWrite = 0;
	pUart->usTxRead = 0;
	pUart->usTxCount = 0;
}

/*
*********************************************************************************************************
*	函 数 名: comClearRxFifo
*	功能说明: 清零串口接收缓冲区
*	形    参: _ucPort: 端口号(COM1 - COM6)
*	返 回 值: 无
*********************************************************************************************************
*/
void comClearRxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usRxWrite = 0;
	pUart->usRxRead = 0;
	pUart->usRxCount = 0;
}


/**************************************************************************************************************************************************************************************/
/**************************************************************************************************************************************************************************************/








































































