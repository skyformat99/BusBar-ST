#include "exti.h"
#include "led.h" 
#include "bsp_key.h"
#include "ip_info.h"


char enter_baud[2]={0,0};


void extic_delay(int temp)
{
	while(temp--);
}

//外部中断3服务程序
void EXTI9_5_IRQHandler(void)          //down
{
	extic_delay(300000);	//消抖
	if(KEY1==0)	 
	{
			button_down++;
			lcd_rest[0]=50;
			lcd_rest[1]=25;		
		
			if(button_menu[0]==3 || button_menu[1]==5) 
			{
						if(button_down==1){}					
						else if(button_down==2)
						{
								ser=(ser/10%4)*10+(ser%10+button_up)%10;
								button_up = 0;
						}
						if(button_down>2)
						{
								ser=(ser/10%10+button_up)%4*10+ser%10;
								button_up = 0;
								button_down = 1;									
						}
			}
			else if(button_menu[0]==4 || button_menu[1]==6)   //波特率
			{
						enter_baud[0]=1;
			}
			else if(button_menu[0]==5 || button_menu[1]==7)   //L1最大值设置
			{
						if(button_down==1){}
						else if(button_down==2)
						{
								Tvol[0][2]=(Tvol[0][2]/100%10)*100+(Tvol[0][2]/10%10)*10+(Tvol[0][2]%10+button_up)%10;
								button_up = 0;
						}
						else if(button_down==3)
						{
								Tvol[0][2]=((Tvol[0][2]/100%10)%10)*100+(Tvol[0][2]/10%10+button_up)%10*10+(Tvol[0][2]%10)%10;
								button_up = 0;
						}
						else if(button_down==4)
						{
								Tvol[0][2]=((Tvol[0][2]/100%10+button_up)%4)*100+(Tvol[0][2]/10%10)*10+(Tvol[0][2]%10)%10;
								button_up = 0;
						}
						else if(button_down==5)
						{
								Tcur[0][2]=((Tcur[0][2]/100%10)%10)*100+(Tcur[0][2]/10%10+button_up)%10*10+(Tcur[0][2]%10)%10;	
								button_up = 0;
						}
						if(button_down > 5)
						{
								Tcur[0][2]=((Tcur[0][2]/100%10+button_up)%7)*100+(Tcur[0][2]/10%10)*10+(Tcur[0][2]%10)%10;
								button_up = 0;
								button_down = 1;
						}						
			}
			if(button_menu[1]==8)  //L2最大值设置
			{
								if(button_down==1){}
							  else if(button_down==2)
								{
										Tvol[1][2]=(Tvol[1][2]/100%10)*100+(Tvol[1][2]/10%10)*10+(Tvol[1][2]%10+button_up)%10;
										button_up = 0;
								}
								else if(button_down==3)
								{
										Tvol[1][2]=((Tvol[1][2]/100%10)%10)*100+(Tvol[1][2]/10%10+button_up)%10*10+(Tvol[1][2]%10)%10;
										button_up = 0;
								}
								else if(button_down==4)
								{
										Tvol[1][2]=((Tvol[1][2]/100%10+button_up)%4)*100+(Tvol[1][2]/10%10)*10+(Tvol[1][2]%10)%10;
										button_up = 0;
								}
								else if(button_down==5)
								{
										Tcur[1][2]=((Tcur[1][2]/100%10)%10)*100+(Tcur[1][2]/10%10+button_up)%10*10+(Tcur[1][2]%10)%10;	
										button_up = 0;
								}
								if(button_down > 5)
								{
										Tcur[1][2]=((Tcur[1][2]/100%10+button_up)%7)*100+(Tcur[1][2]/10%10)*10+(Tcur[1][2]%10)%10;
										button_up = 0;
										button_down = 1;
								}					
			}
			else if(button_menu[1]==9) //L3最大值设置
			{
								if(button_down==1)
								{
										
								}
							  else if(button_down==2)
								{
										Tvol[2][2]=(Tvol[2][2]/100%10)*100+(Tvol[2][2]/10%10)*10+(Tvol[2][2]%10+button_up)%10;
										button_up = 0;
								}
								else if(button_down==3)
								{
										Tvol[2][2]=((Tvol[2][2]/100%10)%10)*100+(Tvol[2][2]/10%10+button_up)%10*10+(Tvol[2][2]%10)%10;
										button_up = 0;
								}
								else if(button_down==4)
								{
										Tvol[2][2]=((Tvol[2][2]/100%10+button_up)%4)*100+(Tvol[2][2]/10%10)*10+(Tvol[2][2]%10)%10;
										button_up = 0;
								}
								else if(button_down==5)
								{
										Tcur[2][2]=((Tcur[2][2]/100%10)%10)*100+(Tcur[2][2]/10%10+button_up)%10*10+(Tcur[2][2]%10)%10;	
										button_up = 0;
								}
								if(button_down > 5)
								{
										Tcur[2][2]=((Tcur[2][2]/100%10+button_up)%7)*100+(Tcur[2][2]/10%10)*10+(Tcur[2][2]%10)%10;
										button_up = 0;
										button_down = 1;
								}				
			}
			else if(button_menu[0]==6 || button_menu[1]==10)
			{
								if(button_down==1)
								{
										
								}
							  else if(button_down==2)
								{
										tem[2]=(tem[2]/10%10)*10+(tem[2]%10+button_up)%10;
										button_up = 0;
								}
								else if(button_down==3)
								{
										tem[2]=(tem[2]/10%10+button_up)%10*10+(tem[2]%10)%10;
									  button_up = 0;
								}
								else if(button_down==4)
								{
										hum[2]=(hum[2]/10%10)*10+(hum[2]%10+button_up)%10;
										button_up = 0;								
								}
								if(button_down >4)
								{
										hum[2]=(hum[2]/10%10+button_up)%10*10+(hum[2]%10)%10;
										button_up = 0;
									  button_down = 1;
								}						
			}
			else if(button_menu[0]==1 || button_menu[1]==1) button_down=0;
			
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line5);  //清除LINE3上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)               //UP
{
	extic_delay(300000);	//消抖
	if(KEY0==0)	 
	{		
			button_up++;
			lcd_rest[0]=50;
			lcd_rest[1]=25;		
		
			
			if(button_menu[0]==3 || button_menu[1]==5) 
			{
					if(button_up>9)button_up=0;
			}
			else if(button_menu[0]==4 || button_menu[1]==6)   //波特率
			{
					enter_baud[1]=1;
			}
			else if(button_menu[0]==5 || button_menu[0]==6 || button_menu[1]==7 || button_menu[1]==8 || button_menu[1]==9 || button_menu[1]==10)   //L1/L2/L3最大值设置
			{
					if(button_up>9)button_up=0;
			}
			else if(button_menu[0]==1 || button_menu[1]==1) button_up=0;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
}
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);//PA6 连接到中断线6
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);//PA4 连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);//PA5 连接到中断线5

	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line =  EXTI_Line5 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//  NVIC_Init(&NVIC_InitStructure);//配置
//	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}












