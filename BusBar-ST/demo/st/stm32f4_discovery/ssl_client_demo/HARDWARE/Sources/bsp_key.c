#include "bsp_key.h"

u8 Key_Set_Menu(void)	
{
  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == KEY_ON )            //KEY_ON	  0    KE2--CONTROL
  	{
  		return 0;
  	}
	else 
		{
			return 1;
		}	
}

void delay_key(int temp)
{
	while(temp--);
}

//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA4/5/6
 
} 

unsigned char key_driver(void) 
{ 
    static unsigned char key_state = key_state_0, key_time = 0; 
    unsigned char key_press, key_return = N_key; 

    key_press = Key_Set_Menu();                    // ������I/O��ƽ 

    switch (key_state) 
    { 
      case key_state_0:                              // ������ʼ̬ 
        if (!key_press) 
			key_state = key_state_1;      // �������£�״̬ת��������������ȷ��״̬ 
        break; 
       
      case key_state_1:                      // ����������ȷ��̬ 
        if (!key_press) 
        { 
             key_time = 0;                   //  
             key_state = key_state_2;   // ������Ȼ���ڰ��£�������ɣ�״̬ת�������¼�ʱ��ļ�ʱ״̬�������صĻ����޼��¼� 
        } 
        else 
             key_state = key_state_0;   // ������̧��ת����������ʼ̬���˴���ɺ�ʵ�������������ʵ�����İ��º��ͷŶ��ڴ������ġ� 
        break; 
       
      case key_state_2: 
        if(key_press)                    //�������£�key_press=0
        { 
             key_return = S_key;        // ��ʱ�����ͷţ�˵���ǲ���һ�ζ̲���������S_key 
             key_state = key_state_0;   // ת����������ʼ̬ 
        } 
        else if (++key_time >= 200)     // �������£���ʱ��10ms��10msΪ������ѭ��ִ�м���� 
        { 
             key_return = L_key;        // ����ʱ��>1000ms���˰���Ϊ�������������س����¼� 
             key_state = key_state_3;   // ת�����ȴ������ͷ�״̬ 
        } 
        break; 

      case key_state_3:                 // �ȴ������ͷ�״̬����״ֻ̬�����ް����¼� 
        if (key_press)
			key_state = key_state_0; //�������ͷţ�ת����������ʼ̬ 
        break; 
    } 
    return key_return; 
}


unsigned char key_read(void) 
{ 
    static unsigned char key_m = key_state_0, key_time_1 = 0; 
    unsigned char key_return = N_key,key_temp; 
     
    key_temp = key_driver(); 
     
    switch(key_m) 
    { 
        case key_state_0: 
            if (key_temp == S_key ) 
            { 
                 key_time_1 = 0;               // ��1�ε����������أ����¸�״̬�жϺ����Ƿ����˫�� 
                 key_m = key_state_1; 
            } 
            else 
                 key_return = key_temp;        // �����޼�������������ԭ�¼� 
            break; 

        case key_state_1: 
            if (key_temp == S_key)             // ��һ�ε���������϶�<500ms�� 
            { 
                 key_return = D_key;           // ����˫�����¼����س�ʼ״̬ 
                 key_m = key_state_0; 
							   
            } 
            else                                
            {                                  // ����300ms�ڿ϶������Ķ����޼��¼�����Ϊ����>1000ms����1sǰ�Ͳ㷵�صĶ����޼� 
                 if(++key_time_1 >= 30) 
                 { 
                      key_return = S_key;      // 500ms��û���ٴγ��ֵ����¼���������һ�εĵ����¼� 
                      key_m = key_state_0;     // ���س�ʼ״̬ 
                 } 
             } 
             break; 
					
    }
    return key_return; 
} 

void sure_menu(void)
{
			if(button_menu[0]==4 || button_menu[1]==6) //ser
			{
					if(button_down==1)
					{
								button_iic_write=1;
								ser=(ser/10%4)*10+(ser%10+button_up)%10;
					}
					else if(button_down==2)
					{
								button_iic_write=1;
								ser=(ser/10%10+button_up)%4*10+ser%10;
					}
					else 
							button_up=0;									
			}		
			else if(button_menu[0]==5 || button_menu[1]==7)   //������
			{
					if(enter_baud[0] > 0 || enter_baud[1] > 0)
					{
						 button_iic_write=1;
						 enter_baud[0]=enter_baud[1]=0;
					}
					else
					{
							button_up=0;
					}					
			}
			else if(button_menu[0]==6 || button_menu[1]==8)   //L1���ֵ����
			{
					if(button_down>0)
					{
							if(button_down==1)
							{
									button_iic_write=1;
									Tvol[0][2]=(Tvol[0][2]/100%10)*100+(Tvol[0][2]/10%10)*10+(Tvol[0][2]%10+button_up)%10;		
							}
							else if(button_down==2)
							{
									button_iic_write=1;
									Tvol[0][2]=((Tvol[0][2]/100%10)%10)*100+(Tvol[0][2]/10%10+button_up)%10*10+(Tvol[0][2]%10)%10;
							}
							else if(button_down==3)
							{
									button_iic_write=1;
									Tvol[0][2]=((Tvol[0][2]/100%10+button_up)%4)*100+(Tvol[0][2]/10%10)*10+(Tvol[0][2]%10)%10;
							}
							else if(button_down==4)
							{
									button_iic_write=1;
									Tcur[0][2]=((Tcur[0][2]/100%10)%10)*100+(Tcur[0][2]/10%10+button_up)%10*10+(Tcur[0][2]%10)%10;
							}
							else if(button_down==5)
							{
									button_iic_write=1;
									Tcur[0][2]=((Tcur[0][2]/100%10+button_up)%7)*100+(Tcur[0][2]/10%10)*10+(Tcur[0][2]%10)%10;
							}
							else
							{
									button_up = 0;	
									if(LINE_NUM==1)button_menu[0]=1;
							}
					}
					else 
					{
						button_up = 0;						
					}						
			}
			if(button_menu[1]==9)  //L2���ֵ����
			{
					if(button_down>0)
					{
							if(button_down==1)
							{
									button_iic_write=1;
									Tvol[1][2]=(Tvol[1][2]/100%10)*100+(Tvol[1][2]/10%10)*10+(Tvol[1][2]%10+button_up)%10;		
							}
							else if(button_down==2)
							{
									button_iic_write=1;
									Tvol[1][2]=((Tvol[1][2]/100%10)%10)*100+(Tvol[1][2]/10%10+button_up)%10*10+(Tvol[1][2]%10)%10;
							}
							else if(button_down==3)
							{
									button_iic_write=1;
									Tvol[1][2]=((Tvol[1][2]/100%10+button_up)%4)*100+(Tvol[1][2]/10%10)*10+(Tvol[1][2]%10)%10;
							}
							else if(button_down==4)
							{
									button_iic_write=1;
									Tcur[1][2]=((Tcur[1][2]/100%10)%10)*100+(Tcur[1][2]/10%10+button_up)%10*10+(Tcur[1][2]%10)%10;
							}
							else if(button_down==5)
							{
									button_iic_write=1;
									Tcur[1][2]=((Tcur[1][2]/100%10+button_up)%7)*100+(Tcur[1][2]/10%10)*10+(Tcur[1][2]%10)%10;
							}
					}
					else 
						button_up = 0;					
			}
			else if(button_menu[1]==10) //L3���ֵ����
			{
					if(button_down>0)
					{
							if(button_down==1)
							{
									button_iic_write=1;
									Tvol[2][2]=(Tvol[2][2]/100%10)*100+(Tvol[2][2]/10%10)*10+(Tvol[2][2]%10+button_up)%10;		
							}
							else if(button_down==2)
							{
									button_iic_write=1;
									Tvol[2][2]=((Tvol[2][2]/100%10)%10)*100+(Tvol[2][2]/10%10+button_up)%10*10+(Tvol[2][2]%10)%10;
							}
							else if(button_down==3)
							{
									button_iic_write=1;
									Tvol[2][2]=((Tvol[2][2]/100%10+button_up)%4)*100+(Tvol[2][2]/10%10)*10+(Tvol[2][2]%10)%10;
							}
							else if(button_down==4)
							{
									button_iic_write=1;
									Tcur[2][2]=((Tcur[2][2]/100%10)%10)*100+(Tcur[2][2]/10%10+button_up)%10*10+(Tcur[2][2]%10)%10;
							}
							else if(button_down==5)
							{
									button_iic_write=1;
									Tcur[2][2]=((Tcur[2][2]/100%10+button_up)%7)*100+(Tcur[2][2]/10%10)*10+(Tcur[2][2]%10)%10;
							}
							else
							{
									button_up=0;
									button_menu[1] = 1;
							}							
					}
					else
					{
							button_up=0;						
					}					
			}
			if(button_menu[0]==7 || button_menu[1]==11)	
			{
						if(button_down==1)
						{
								button_iic_write=1;
								tem[2]=(tem[2]/10%10)*10+(tem[2]%10+button_up)%10;
						}
						else if(button_down==2)
						{
								button_iic_write=1;
								tem[2]=(tem[2]/10%10+button_up)%10*10+(tem[2]%10)%10;
						}
						else if(button_down==3)
						{
								button_iic_write=1;
								hum[2]=(hum[2]/10%10)*10+(hum[2]%10+button_up)%10;
						}
						else if(button_down==4)
						{
								button_iic_write=1;
								hum[2]=(hum[2]/10%10+button_up)%10*10+(hum[2]%10)%10;							
						}	
						else
						{
								button_up=0;
								if(LINE_NUM==3)
								{
										button_menu[0]=0;
										button_menu[1] = 1;										
								}
								else
								{
										button_menu[0]=1;
										button_menu[1] = 0;											
								}
						}					
			}					
}


void key_scan(void)
{
        switch(key_read())
				{
					case S_key:             //�̰�
					{		
							lcd_rest[0]=50;
							lcd_rest[1]=25;
							if(LINE_NUM==3)
							{
									button_menu[1]++;   //����	
									button_menu[0]=0;
							}														  
							else 
							{
									button_menu[1]=0;
									button_menu[0]++;  //����	
							}							
							sure_menu();
							
							break;
					}
					case L_key:                 //����
					{
							ONorOFF_sound = !ONorOFF_sound;
							break;
					}
				}		
}














