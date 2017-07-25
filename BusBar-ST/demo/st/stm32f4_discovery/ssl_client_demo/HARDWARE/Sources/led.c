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
//**函数信息 ：void IWDGInit(void)                         // WAN.CG // 2011.3.16
//**功能描述 ：独立看门狗初始化函数,此处设置为1秒钟喂狗一次，否则复位
//**输入参数 ：无
//**输出参数 ：无
//**调用提示 ：
//** Tout=((4×2^prer) ×rlr) /40  prer:预分频值               rlr:装载值
//********************************************************************************************************/
void IWDG_Init(void)
{	 
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  	//允许看门狗寄存器写入功能  
		IWDG_SetPrescaler(IWDG_Prescaler_256);	 	    //IWDG_Prescaler_128 ：6
		IWDG_SetReload(4095);				            //喂狗时间0.8ms*1250=1s,注意不能大于0xfff(4095）	 ((4×2^6) ×4095) /40 = 26208ms=26s
		IWDG_ReloadCounter();		   					//重启计数器，即喂狗	 
		IWDG_Enable();				 				    //使能看门狗
}







