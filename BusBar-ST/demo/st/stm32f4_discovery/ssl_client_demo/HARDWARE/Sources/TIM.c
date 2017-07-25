#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "ip_info.h"
#include "TIM.h"
#include "debug.h"
#include "bsp_key.h"
#include "exti.h"
#include "function.h"
#include "lcd_dispaly.h"


//重装载值=(溢出时间*时钟频率/预分频)
//    5000=0.5s * 84000000/8400

void Time3_Init(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
	TIM_TimeBaseStructure.TIM_Period = 10000-1;           //自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler =8400-1;        //分频系数  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //时钟分频因子
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //计数方式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    //初始化定时器3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );         //使能TIM3的更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	TIM_Cmd(TIM3, ENABLE);     //失能定时器
	
}

//中断服务函数
void TIM3_IRQHandler()
{
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)     //溢出中断
	{
	
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);       //清除中断标志位
}





void Time2_Init(void)
{

				NVIC_InitTypeDef NVIC_InitStructure; 
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                                                                                                          
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;          
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
        TIM_DeInit(TIM2);
        TIM_TimeBaseStructure.TIM_Period=100-1;                                                                                                                  
        TIM_TimeBaseStructure.TIM_Prescaler= 8400-1;                                  
        TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;                   
        TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);                                                  
        TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
        TIM_Cmd(TIM2, ENABLE);  
}				

void TIM2_IRQHandler(void)
{
    if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
    { 
			  key_scan();
					
     }
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update); 
}




void Time4_Init(void)
{

				NVIC_InitTypeDef NVIC_InitStructure; 
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                                                                                                          
        NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;          
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
        TIM_DeInit(TIM4);
        TIM_TimeBaseStructure.TIM_Period=999;                                                                                                                  
        TIM_TimeBaseStructure.TIM_Prescaler= 8400-1;                                  
        TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;                   
        TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       
        TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
        TIM_ClearFlag(TIM4, TIM_FLAG_Update);                                                  
        TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
        TIM_Cmd(TIM4, DISABLE);  
}				
       
void TIM4_IRQHandler(void)
{
    if ( TIM_GetITStatus(TIM4 , TIM_IT_Update) != RESET ) 
    { 
//				if(RecUartCmd())
//				{
//					changer=1;
//				}
    }
		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update); 
}




void Time5_Init(void)
{

				NVIC_InitTypeDef NVIC_InitStructure; 
        TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
        
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                                                                                                          
        NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;          
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);
        TIM_DeInit(TIM5);
        TIM_TimeBaseStructure.TIM_Period=2;                                                                                                                  
        TIM_TimeBaseStructure.TIM_Prescaler= 8400-1;                                  
        TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;                   
        TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       
        TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
        TIM_ClearFlag(TIM5, TIM_FLAG_Update);                                                  
        TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
        TIM_Cmd(TIM5, DISABLE);  
}				

void TIM5_IRQHandler(void)
{
	static char count=0;
 
    if ( TIM_GetITStatus(TIM5 , TIM_IT_Update) != RESET ) 
    { 						
			
    }
		TIM_ClearITPendingBit(TIM5 , TIM_FLAG_Update); 
}






