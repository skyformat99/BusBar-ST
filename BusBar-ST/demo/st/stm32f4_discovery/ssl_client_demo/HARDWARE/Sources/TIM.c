#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "ip_info.h"
#include "TIM.h"
#include "debug.h"
#include "bsp_key.h"
#include "exti.h"
#include "function.h"
#include "lcd_dispaly.h"


//��װ��ֵ=(���ʱ��*ʱ��Ƶ��/Ԥ��Ƶ)
//    5000=0.5s * 84000000/8400

void Time3_Init(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseStructure.TIM_Period = 10000-1;           //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =8400-1;        //��Ƶϵ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //ʱ�ӷ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //������ʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);    //��ʼ����ʱ��3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );         //ʹ��TIM3�ĸ����ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	TIM_Cmd(TIM3, ENABLE);     //ʧ�ܶ�ʱ��
	
}

//�жϷ�����
void TIM3_IRQHandler()
{
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)     //����ж�
	{
	
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);       //����жϱ�־λ
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






