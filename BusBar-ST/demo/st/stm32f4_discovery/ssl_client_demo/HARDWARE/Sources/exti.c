#include "exti.h"
#include "led.h" 
#include "bsp_key.h"
#include "ip_info.h"


char enter_baud[2]={0,0};


void extic_delay(int temp)
{
	while(temp--);
}

//�ⲿ�ж�3�������
void EXTI9_5_IRQHandler(void)          //down
{
	extic_delay(300000);	//����
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
			else if(button_menu[0]==4 || button_menu[1]==6)   //������
			{
						enter_baud[0]=1;
			}
			else if(button_menu[0]==5 || button_menu[1]==7)   //L1���ֵ����
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
			if(button_menu[1]==8)  //L2���ֵ����
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
			else if(button_menu[1]==9) //L3���ֵ����
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
	 EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)               //UP
{
	extic_delay(300000);	//����
	if(KEY0==0)	 
	{		
			button_up++;
			lcd_rest[0]=50;
			lcd_rest[1]=25;		
		
			
			if(button_menu[0]==3 || button_menu[1]==5) 
			{
					if(button_up>9)button_up=0;
			}
			else if(button_menu[0]==4 || button_menu[1]==6)   //������
			{
					enter_baud[1]=1;
			}
			else if(button_menu[0]==5 || button_menu[0]==6 || button_menu[1]==7 || button_menu[1]==8 || button_menu[1]==9 || button_menu[1]==10)   //L1/L2/L3���ֵ����
			{
					if(button_up>9)button_up=0;
			}
			else if(button_menu[0]==1 || button_menu[1]==1) button_up=0;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}
	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);//PA6 ���ӵ��ж���6
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);//PA4 ���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);//PA5 ���ӵ��ж���5

	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line =  EXTI_Line5 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//  NVIC_Init(&NVIC_InitStructure);//����
//	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}












