#include "led.h" 

void run_led(char ch)
{
		if(ch)
			GPIO_ResetBits(GPIOF, GPIO_Pin_6);
		else 
			GPIO_SetBits(GPIOF, GPIO_Pin_6);
}

void  run_alm(char ch)
{
		if(ch)
			GPIO_ResetBits(GPIOF, GPIO_Pin_7);
		else 
			GPIO_SetBits(GPIOF, GPIO_Pin_7);
}

void run_mw(char ch)
{
		if(ch)
			GPIO_ResetBits(GPIOF, GPIO_Pin_8);
		else 
			GPIO_SetBits(GPIOF, GPIO_Pin_8);
}

void beel(char ch)
{
		if(ch)	
		{
				GPIO_SetBits(GPIOF, GPIO_Pin_11);
		}
		else 
		{
				GPIO_ResetBits(GPIOF, GPIO_Pin_11);
		}
}

void LED_Init()
{
		GPIO_InitTypeDef  GPIO_InitStructure;
    /* GPIOD Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	  
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_11|GPIO_Pin_7|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);	
		
		run_alm(0);
		run_mw(0);
		run_led(0);
		
}

void devicedown()
{
		NVIC_SystemReset();
}

///********************************************************************************************************
//**������Ϣ ��void IWDGInit(void)                         // WAN.CG // 2011.3.16
//**�������� ���������Ź���ʼ������,�˴�����Ϊ1����ι��һ�Σ�����λ
//**������� ����
//**������� ����
//**������ʾ ��
//** Tout=((4��2^prer) ��rlr) /40  prer:Ԥ��Ƶֵ               rlr:װ��ֵ
//********************************************************************************************************/
void IWDG_Init(void)
{	 
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  	//�����Ź��Ĵ���д�빦��  
		IWDG_SetPrescaler(IWDG_Prescaler_256);	 	    //IWDG_Prescaler_128 ��6
		IWDG_SetReload(4095);				            //ι��ʱ��0.8ms*1250=1s,ע�ⲻ�ܴ���0xfff(4095��	 ((4��2^6) ��4095) /40 = 26208ms=26s
		IWDG_ReloadCounter();		   					//��������������ι��	 
		IWDG_Enable();				 				    //ʹ�ܿ��Ź�
}







