#ifndef _USART_FIFO_H_
#define _USART_FIFO_H_

#include "stm32f4xx.h"

/* ����ʹ�ܵĴ���, 0 ��ʾ��ʹ�ܣ������Ӵ����С���� 1��ʾʹ�� */
#ifdef STM32_MPDU	
	/* 
		PA9/USART1_TX	 
		PA10/USART1_RX
	*/
	#define	UART1_FIFO_EN	1
	#define	UART2_FIFO_EN	0
	#define	UART3_FIFO_EN	0
	#define	UART4_FIFO_EN	0
	#define	UART5_FIFO_EN	0
	#define	UART6_FIFO_EN	0
#else
	#define	UART1_FIFO_EN	0
	#define	UART2_FIFO_EN	0
	#define	UART3_FIFO_EN	1
	#define	UART4_FIFO_EN	0
	#define	UART5_FIFO_EN	0
	#define	UART6_FIFO_EN	1

	/*USART1-RS485оƬ����ʹ��GPIO, PA11 */
	#define RCC_RS485_TXEN 	RCC_AHB1Periph_GPIOA
	#define PORT_RS485_TXEN  GPIOA
	#define PIN_RS485_TXEN	 GPIO_Pin_11

	#define RS485_RX_EN()	PORT_RS485_TXEN->BSRRH = PIN_RS485_TXEN
	#define RS485_TX_EN()	PORT_RS485_TXEN->BSRRL = PIN_RS485_TXEN
	/*USART6-RS485оƬ����ʹ��GPIO, PG15 */
	#define RCC_RS485_6_TXEN 	RCC_AHB1Periph_GPIOG
	#define PORT_RS485_6_TXEN  GPIOG
	#define PIN_RS485_6_TXEN	 GPIO_Pin_15

	#define RS485_6_RX_EN()	PORT_RS485_6_TXEN->BSRRH = PIN_RS485_6_TXEN
	#define RS485_6_TX_EN()	PORT_RS485_6_TXEN->BSRRL = PIN_RS485_6_TXEN	
#endif

/* ����˿ں� */
typedef enum
{
	COM1 = 0,	/* USART1  PA9, PA10 */
	COM2 = 1,	/* USART2, PD5,PD6 */
	COM3 = 2,	/* USART3, PB10, PB11 */
	COM4 = 3,	/* UART4, PC10, PC11 */
	COM5 = 4,	/* UART5, PC12, PD2 */
	COM6 = 5	/* USART6, PC6, PC7 */
}COM_PORT_E;

/* ���崮�ڲ����ʺ�FIFO��������С����Ϊ���ͻ������ͽ��ջ�����, ֧��ȫ˫�� */
#if UART1_FIFO_EN == 1
	#define UART1_BAUD			19200
	#define UART1_TX_BUF_SIZE	1*512
	#define UART1_RX_BUF_SIZE	1*512
#endif

#if UART2_FIFO_EN == 1
	#define UART2_BAUD			9600
	#define UART2_TX_BUF_SIZE	1
	#define UART2_RX_BUF_SIZE	2*1024
#endif

#if UART3_FIFO_EN == 1
	#define UART3_BAUD			9600
	#define UART3_TX_BUF_SIZE	1*1024
	#define UART3_RX_BUF_SIZE	1*1024
#endif

#if UART4_FIFO_EN == 1
	#define UART4_BAUD			115200
	#define UART4_TX_BUF_SIZE	1*1024
	#define UART4_RX_BUF_SIZE	1*1024
#endif

#if UART5_FIFO_EN == 1
	#define UART5_BAUD			115200
	#define UART5_TX_BUF_SIZE	1*1024
	#define UART5_RX_BUF_SIZE	1*1024
#endif

#if UART6_FIFO_EN == 1
	#define UART6_BAUD			4800
	#define UART6_TX_BUF_SIZE	1*1200
	#define UART6_RX_BUF_SIZE	1*1200
#endif

/* �����豸�ṹ�� */
typedef struct
{
	USART_TypeDef *uart;		/* STM32�ڲ������豸ָ�� */
	uint8_t *pTxBuf;			/* ���ͻ����� */
	uint8_t *pRxBuf;			/* ���ջ����� */
	uint16_t usTxBufSize;		/* ���ͻ�������С */
	uint16_t usRxBufSize;		/* ���ջ�������С */
	__IO uint16_t usTxWrite;	/* ���ͻ�����дָ�� */
	__IO uint16_t usTxRead;		/* ���ͻ�������ָ�� */
	__IO uint16_t usTxCount;	/* �ȴ����͵����ݸ��� */

	__IO uint16_t usRxWrite;	/* ���ջ�����дָ�� */
	__IO uint16_t usRxRead;		/* ���ջ�������ָ�� */
	__IO uint16_t usRxCount;	/* ��δ��ȡ�������ݸ��� */

	void (*SendBefor)(void); 	/* ��ʼ����֮ǰ�Ļص�����ָ�루��Ҫ����RS485�л�������ģʽ�� */
	void (*SendOver)(void); 	/* ������ϵĻص�����ָ�루��Ҫ����RS485������ģʽ�л�Ϊ����ģʽ�� */
	void (*ReciveNew)(uint8_t _byte);	/* �����յ����ݵĻص�����ָ�� */
}UART_T;


void bsp_InitUart(void);
void Uart_Recive_data(COM_PORT_E _ucPort,u8 *buff,int len);




#endif