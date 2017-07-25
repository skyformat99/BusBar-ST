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

//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA4/5/6
 
} 

unsigned char key_driver(void) 
{ 
    static unsigned char key_state = key_state_0, key_time = 0; 
    unsigned char key_press, key_return = N_key; 

    key_press = Key_Set_Menu();                    // 读按键I/O电平 

    switch (key_state) 
    { 
      case key_state_0:                              // 按键初始态 
        if (!key_press) 
			key_state = key_state_1;      // 键被按下，状态转换到按键消抖和确认状态 
        break; 
       
      case key_state_1:                      // 按键消抖与确认态 
        if (!key_press) 
        { 
             key_time = 0;                   //  
             key_state = key_state_2;   // 按键仍然处于按下，消抖完成，状态转换到按下键时间的计时状态，但返回的还是无键事件 
        } 
        else 
             key_state = key_state_0;   // 按键已抬起，转换到按键初始态。此处完成和实现软件消抖，其实按键的按下和释放都在此消抖的。 
        break; 
       
      case key_state_2: 
        if(key_press)                    //按键按下：key_press=0
        { 
             key_return = S_key;        // 此时按键释放，说明是产生一次短操作，回送S_key 
             key_state = key_state_0;   // 转换到按键初始态 
        } 
        else if (++key_time >= 200)     // 继续按下，计时加10ms（10ms为本函数循环执行间隔） 
        { 
             key_return = L_key;        // 按下时间>1000ms，此按键为长按操作，返回长键事件 
             key_state = key_state_3;   // 转换到等待按键释放状态 
        } 
        break; 

      case key_state_3:                 // 等待按键释放状态，此状态只返回无按键事件 
        if (key_press)
			key_state = key_state_0; //按键已释放，转换到按键初始态 
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
                 key_time_1 = 0;               // 第1次单击，不返回，到下个状态判断后面是否出现双击 
                 key_m = key_state_1; 
            } 
            else 
                 key_return = key_temp;        // 对于无键、长键，返回原事件 
            break; 

        case key_state_1: 
            if (key_temp == S_key)             // 又一次单击（间隔肯定<500ms） 
            { 
                 key_return = D_key;           // 返回双击键事件，回初始状态 
                 key_m = key_state_0; 
							   
            } 
            else                                
            {                                  // 这里300ms内肯定读到的都是无键事件，因为长键>1000ms，在1s前低层返回的都是无键 
                 if(++key_time_1 >= 30) 
                 { 
                      key_return = S_key;      // 500ms内没有再次出现单键事件，返回上一次的单键事件 
                      key_m = key_state_0;     // 返回初始状态 
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
			else if(button_menu[0]==5 || button_menu[1]==7)   //波特率
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
			else if(button_menu[0]==6 || button_menu[1]==8)   //L1最大值设置
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
			if(button_menu[1]==9)  //L2最大值设置
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
			else if(button_menu[1]==10) //L3最大值设置
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
					case S_key:             //短按
					{		
							lcd_rest[0]=50;
							lcd_rest[1]=25;
							if(LINE_NUM==3)
							{
									button_menu[1]++;   //三相	
									button_menu[0]=0;
							}														  
							else 
							{
									button_menu[1]=0;
									button_menu[0]++;  //单相	
							}							
							sure_menu();
							
							break;
					}
					case L_key:                 //长按
					{
							ONorOFF_sound = !ONorOFF_sound;
							break;
					}
				}		
}














