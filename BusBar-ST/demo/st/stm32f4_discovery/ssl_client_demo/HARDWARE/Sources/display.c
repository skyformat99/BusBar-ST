#include "lcd_dispaly.h"


u8 auto_hand_action=0;
u8 auto_tem_dis=0;
char once_clear=0;
char button_iic_write=0;
char lcd_rest[2]={0,0};

u16 Back_Ground = CYAN;
//自检函数
void auto_action(void)
{
		Back_Ground=CYAN;
		if(auto_hand_action==1)
		{
							LCD_Clear(Back_Ground,1); 											

							Show_Str(8,7,BLUE,Back_Ground,"L",24,0,1);
							Show_Str(20,7,BLUE,Back_Ground,"1",24,0,1);
							
							if(Tvol[0][0]<Tvol[0][1] || Tvol[0][0]>Tvol[0][2] )
							{
								if(cur_dc_ac)
								{
									Show_Str(93,13,RED,Back_Ground,"VAC",20,0,1);
								}
								else
								{
									Show_Str(93,13,RED,Back_Ground,"VDC",20,0,1);
								}								
								LCD_ShowxNum(45,7,RED,Back_Ground,Tvol[0][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,RED,Back_Ground,Tvol[0][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,RED,Back_Ground,Tvol[0][0]%10,1,28,0,1);	
							}
							else
							{
								if(cur_dc_ac)
								{
									Show_Str(93,13,BLACK,Back_Ground,"VAC",20,0,1);
								}
								else
								{
									Show_Str(93,13,BLACK,Back_Ground,"VDC",20,0,1);
								}								
								LCD_ShowxNum(45,7,BLACK,Back_Ground,Tvol[0][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,BLACK,Back_Ground,Tvol[0][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,BLACK,Back_Ground,Tvol[0][0]%10,1,28,0,1);									
						 }						
						 if(Tcur[0][0]<Tcur[0][1] || Tcur[0][0]>Tcur[0][2] )
						 {
								LCD_ShowxNum(44,37,RED,Back_Ground,Tcur[0][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,RED,Back_Ground,Tcur[0][0]/10%10,1,28,0,1);								
								Show_Str(68,39,RED,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,RED,Back_Ground,Tcur[0][0]%10,1,28,0,1);
								Show_Str(93,41,RED,Back_Ground,"A",22,0,1);			
						 }
						 else
						 {
								LCD_ShowxNum(44,37,BLACK,Back_Ground,Tcur[0][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,BLACK,Back_Ground,Tcur[0][0]/10%10,1,28,0,1);								
								Show_Str(68,39,BLACK,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,BLACK,Back_Ground,Tcur[0][0]%10,1,28,0,1);
								Show_Str(93,41,BLACK,Back_Ground,"A",22,0,1);								
						 }			
						 if(Tvol[0][0]<Tvol[0][1] || Tvol[0][0]>Tvol[0][2] || Tcur[0][0]<Tcur[0][1] 
								 || Tcur[0][0]>Tcur[0][2] || tem[0]<tem[1] || tem[0]>tem[2] || hum[0]<hum[1]|| hum[0]>hum[2])
						 {
								if(ONorOFF_sound)
									Show_Str(10,75,RED,Back_Ground,"ON",16,0,1);
								else
									Show_Str(10,75,RED,Back_Ground,"OFF",16,0,1);									
						 }
														
							Show_Str(93,71,BLACK,Back_Ground,"kw",22,0,1);
							Show_Str(68,69,BLACK,Back_Ground,".",28,0,1);		
							LCD_ShowxNum(44,67,BLACK,Back_Ground,(Tvol[0][0]*Tcur[0][0])/100000%10,1,28,0,1);
							LCD_ShowxNum(58,67,BLACK,Back_Ground,(Tvol[0][0]*Tcur[0][0])/10000%10,1,28,0,1);
							LCD_ShowxNum(75,67,BLACK,Back_Ground,(Tvol[0][0]*Tcur[0][0])/1000%10,1,28,0,1);						
												
							Show_Str(93,100,BLACK,Back_Ground,"kwh",20,0,1);
							Show_Str(75,99,BLACK,Back_Ground,".",22,0,1);	
							if(cur_dc_ac)
							{
								LCD_ShowxNum(5,101,BLACK,Back_Ground,Energy8207[0]/1000000%10,1,22,0,1);
								LCD_ShowxNum(17,101,BLACK,Back_Ground,Energy8207[0]/100000%10,1,22,0,1);
								LCD_ShowxNum(29,101,BLACK,Back_Ground,Energy8207[0]/10000%10,1,22,0,1);
								LCD_ShowxNum(41,101,BLACK,Back_Ground,Energy8207[0]/1000%10,1,22,0,1);
								LCD_ShowxNum(53,101,BLACK,Back_Ground,Energy8207[0]/100%10,1,22,0,1);
								LCD_ShowxNum(65,101,BLACK,Back_Ground,Energy8207[0]/10%10,1,22,0,1);
								LCD_ShowxNum(79,101,BLACK,Back_Ground,Energy8207[0]%10,1,22,0,1);	
							}
							else
							{
								LCD_ShowxNum(5,101,BLACK,Back_Ground,Energy8207_dc/1000000%10,1,22,0,1);
								LCD_ShowxNum(17,101,BLACK,Back_Ground,Energy8207_dc/100000%10,1,22,0,1);
								LCD_ShowxNum(29,101,BLACK,Back_Ground,Energy8207_dc/10000%10,1,22,0,1);
								LCD_ShowxNum(41,101,BLACK,Back_Ground,Energy8207_dc/1000%10,1,22,0,1);
								LCD_ShowxNum(53,101,BLACK,Back_Ground,Energy8207_dc/100%10,1,22,0,1);
								LCD_ShowxNum(65,101,BLACK,Back_Ground,Energy8207_dc/10%10,1,22,0,1);
								LCD_ShowxNum(79,101,BLACK,Back_Ground,Energy8207_dc%10,1,22,0,1);		
							}																																						
							LCD_Refresh_Gram(1);
							
		}
		if(LINE_NUM==3)
		{
				if(auto_hand_action==2)
				{
							LCD_Clear(Back_Ground,1); 
												
							Show_Str(8,7,BLUE,Back_Ground,"L",24,0,1);
							Show_Str(20,7,BLUE,Back_Ground,"2",24,0,1);
							
							if(Tvol[1][0]<Tvol[1][1] || Tvol[1][0]>Tvol[1][2] )
							{
								Show_Str(93,13,RED,Back_Ground,"VAC",20,0,1);		
								LCD_ShowxNum(45,7,RED,Back_Ground,Tvol[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,RED,Back_Ground,Tvol[1][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,RED,Back_Ground,Tvol[1][0]%10,1,28,0,1);								
							}
							else
							{
								Show_Str(93,13,BLACK,Back_Ground,"VAC",20,0,1);							
								LCD_ShowxNum(45,7,BLACK,Back_Ground,Tvol[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,BLACK,Back_Ground,Tvol[1][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,BLACK,Back_Ground,Tvol[1][0]%10,1,28,0,1);									
							}						
							if(Tcur[1][0]<Tcur[1][1] || Tcur[1][0]>Tcur[1][2] )
							{
								LCD_ShowxNum(44,37,RED,Back_Ground,Tcur[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,RED,Back_Ground,Tcur[1][0]/10%10,1,28,0,1);								
								Show_Str(68,39,RED,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,RED,Back_Ground,Tcur[1][0]%10,1,28,0,1);
							  Show_Str(93,41,RED,Back_Ground,"A",22,0,1);
							}
							else
							{
								LCD_ShowxNum(44,37,BLACK,Back_Ground,Tcur[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,BLACK,Back_Ground,Tcur[1][0]/10%10,1,28,0,1);								
								Show_Str(68,39,BLACK,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,BLACK,Back_Ground,Tcur[1][0]%10,1,28,0,1);
								Show_Str(93,41,BLACK,Back_Ground,"A",22,0,1);								
							}
								
							if(Tvol_alarm[0]==1||Tvol_alarm[1]==1||Tvol_alarm[2]==1||Tcur_alarm[0]==1||Tcur_alarm[1]==1
								||Tcur_alarm[2]==1||tem[0]<tem[1] || tem[0]>tem[2]||hum[0]<hum[1]|| hum[0]>hum[2])
							{
								if(ONorOFF_sound)
									Show_Str(10,75,RED,Back_Ground,"ON",16,0,1);
								else
									Show_Str(10,75,RED,Back_Ground,"OFF",16,0,1);										
							}						
							
							Show_Str(93,71,BLACK,Back_Ground,"kw",22,0,1);
							Show_Str(68,69,BLACK,Back_Ground,".",28,0,1);								
							LCD_ShowxNum(44,67,BLACK,Back_Ground,(Tvol[1][0]*Tcur[1][0])/100000%10,1,28,0,1);
							LCD_ShowxNum(58,67,BLACK,Back_Ground,(Tvol[1][0]*Tcur[1][0])/10000%10,1,28,0,1);
							LCD_ShowxNum(75,67,BLACK,Back_Ground,(Tvol[1][0]*Tcur[1][0])/1000%10,1,28,0,1);						
												
							Show_Str(93,100,BLACK,Back_Ground,"kwh",20,0,1);
							Show_Str(75,99,BLACK,Back_Ground,".",22,0,1);							
							
							LCD_ShowxNum(5,101,BLACK,Back_Ground,Energy8207[1]/1000000%10,1,22,0,1);
							LCD_ShowxNum(17,101,BLACK,Back_Ground,Energy8207[1]/100000%10,1,22,0,1);
							LCD_ShowxNum(29,101,BLACK,Back_Ground,Energy8207[1]/10000%10,1,22,0,1);
							LCD_ShowxNum(41,101,BLACK,Back_Ground,Energy8207[1]/1000%10,1,22,0,1);
							LCD_ShowxNum(53,101,BLACK,Back_Ground,Energy8207[1]/100%10,1,22,0,1);
							LCD_ShowxNum(65,101,BLACK,Back_Ground,Energy8207[1]/10%10,1,22,0,1);
							LCD_ShowxNum(79,101,BLACK,Back_Ground,Energy8207[1]%10,1,22,0,1);	
																								
							LCD_Refresh_Gram(1);			
				}	
				if(auto_hand_action==3)
				{
							LCD_Clear(Back_Ground,1); 
												
							Show_Str(8,7,BLUE,Back_Ground,"L",24,0,1);
							Show_Str(20,7,BLUE,Back_Ground,"3",24,0,1);
							
							if(Tvol[2][0]<Tvol[2][1] || Tvol[2][0]>Tvol[2][2] )
							{
								Show_Str(93,13,RED,Back_Ground,"VAC",20,0,1);								
								LCD_ShowxNum(45,7,RED,Back_Ground,Tvol[2][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,RED,Back_Ground,Tvol[2][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,RED,Back_Ground,Tvol[2][0]%10,1,28,0,1);								
							}
							else
							{
								Show_Str(93,13,BLACK,Back_Ground,"VAC",20,0,1);									
								LCD_ShowxNum(45,7,BLACK,Back_Ground,Tvol[2][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,BLACK,Back_Ground,Tvol[2][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,BLACK,Back_Ground,Tvol[2][0]%10,1,28,0,1);									
							}						
							if(Tcur[2][0]<Tcur[2][1] || Tcur[2][0]>Tcur[2][2] )
							{
								LCD_ShowxNum(44,37,RED,Back_Ground,Tcur[2][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,RED,Back_Ground,Tcur[2][0]/10%10,1,28,0,1);								
								Show_Str(68,39,RED,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,RED,Back_Ground,Tcur[2][0]%10,1,28,0,1);
								Show_Str(93,41,RED,Back_Ground,"A",22,0,1);							
							}
							else
							{
								LCD_ShowxNum(44,37,BLACK,Back_Ground,Tcur[2][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,BLACK,Back_Ground,Tcur[2][0]/10%10,1,28,0,1);								
								Show_Str(68,39,BLACK,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,BLACK,Back_Ground,Tcur[2][0]%10,1,28,0,1);
								Show_Str(93,41,BLACK,Back_Ground,"A",22,0,1);								
							}
								
							if(Tvol_alarm[0]==1||Tvol_alarm[1]==1||Tvol_alarm[2]==1||Tcur_alarm[0]==1||Tcur_alarm[1]==1
								||Tcur_alarm[2]==1||tem[0]<tem[1] || tem[0]>tem[2]||hum[0]<hum[1]|| hum[0]>hum[2])
							{
								if(ONorOFF_sound)
									Show_Str(10,75,RED,Back_Ground,"ON",16,0,1);
								else
									Show_Str(10,75,RED,Back_Ground,"OFF",16,0,1);										
							}				
							
							Show_Str(93,71,BLACK,Back_Ground,"kw",22,0,1);
							Show_Str(68,69,BLACK,Back_Ground,".",28,0,1);
								
							LCD_ShowxNum(44,67,BLACK,Back_Ground,(Tvol[2][0]*Tcur[2][0])/100000%10,1,28,0,1);
							LCD_ShowxNum(58,67,BLACK,Back_Ground,(Tvol[2][0]*Tcur[2][0])/10000%10,1,28,0,1);
							LCD_ShowxNum(75,67,BLACK,Back_Ground,(Tvol[2][0]*Tcur[2][0])/1000%10,1,28,0,1);						
												
							Show_Str(93,100,BLACK,Back_Ground,"kwh",20,0,1);
							Show_Str(75,99,BLACK,Back_Ground,".",22,0,1);							
							
							LCD_ShowxNum(5,101,BLACK,Back_Ground,Energy8207[2]/1000000%10,1,22,0,1);
							LCD_ShowxNum(17,101,BLACK,Back_Ground,Energy8207[2]/100000%10,1,22,0,1);
							LCD_ShowxNum(29,101,BLACK,Back_Ground,Energy8207[2]/10000%10,1,22,0,1);
							LCD_ShowxNum(41,101,BLACK,Back_Ground,Energy8207[2]/1000%10,1,22,0,1);
							LCD_ShowxNum(53,101,BLACK,Back_Ground,Energy8207[2]/100%10,1,22,0,1);
							LCD_ShowxNum(65,101,BLACK,Back_Ground,Energy8207[2]/10%10,1,22,0,1);
							LCD_ShowxNum(79,101,BLACK,Back_Ground,Energy8207[2]%10,1,22,0,1);	
							LCD_Refresh_Gram(1);				
				}
		}
		if(auto_tem_dis==1)
		{
							LCD_Clear(Back_Ground,1); 
							
							Show_Str(36,15,BLACK,Back_Ground,"Tem",24,0,1);
							Show_Str(72,17,BLACK,Back_Ground,"p",24,0,1);
							Show_Str(36,67,BLACK,Back_Ground,"Hum",24,0,1);
							
							if(Tvol[0][0]<Tvol[0][1] || Tvol[0][0]>Tvol[0][2] || Tcur[0][0]<Tcur[0][1] 
								 || Tcur[0][0]>Tcur[0][2] || tem[0]<tem[1] || tem[0]>tem[2] || hum[0]<hum[1]|| hum[0]>hum[2])
							{
								if(ONorOFF_sound)
									Show_Str(8,75,RED,Back_Ground,"ON",16,0,1);
								else
									Show_Str(8,75,RED,Back_Ground,"OFF",16,0,1);									
							}							
					
							if(tem[0]<tem[1] || tem[0]>tem[2])
							{
								LCD_ShowxNum(36,39,RED,Back_Ground,tem[0]/10%10,1,28,0,1);
								LCD_ShowxNum(54,39,RED,Back_Ground,tem[0]%10,1,28,0,1);
								Show_Str(73,47,RED,Back_Ground,"℃",16,1,1);									
							}
							else
							{
								LCD_ShowxNum(36,39,BLACK,Back_Ground,tem[0]/10%10,1,28,0,1);
								LCD_ShowxNum(54,39,BLACK,Back_Ground,tem[0]%10,1,28,0,1);
								Show_Str(71,49,BLACK,Back_Ground,"℃",16,1,1);								
							}
							
							if(hum[0]<hum[1]|| hum[0]>hum[2])
							{
								LCD_ShowxNum(36,91,RED,Back_Ground,hum[0]/10%10,1,28,0,1);
								LCD_ShowxNum(54,91,RED,Back_Ground,hum[0]%10,1,28,0,1);
								Show_Str(73,99,RED,Back_Ground,"％",16,1,1);								
							}
							else
							{
								LCD_ShowxNum(36,91,BLACK,Back_Ground,hum[0]/10%10,1,28,0,1);
								LCD_ShowxNum(54,91,BLACK,Back_Ground,hum[0]%10,1,28,0,1);
								Show_Str(73,99,BLACK,Back_Ground,"％",16,1,1);								
							}
							LCD_Refresh_Gram(1);		
		}
}
//按键查看函数
void hand_action(void)
{
		Back_Ground=WHITE;
	
		if(button_menu[0]==1 || button_menu[1]==1)
		{				
					LCD_Clear(Back_Ground,2); //清屏
																		
					Show_Str(8,7,BLUE,Back_Ground,"L",24,0,2);
					Show_Str(20,7,BLUE,Back_Ground,"1",24,0,2);			
					if(Tvol_alarm[0]==1||Tvol_alarm[1]==1||Tvol_alarm[2]==1||Tcur_alarm[0]==1||Tcur_alarm[1]==1
							||Tcur_alarm[2]==1||tem[0]<tem[1] || tem[0]>tem[2]||hum[0]<hum[1]|| hum[0]>hum[2])
					{
								if(ONorOFF_sound)
									Show_Str(10,75,RED,Back_Ground,"ON",16,0,2);
								else
									Show_Str(10,75,RED,Back_Ground,"OFF",16,0,2);										
					}			
							
					if(Tvol[0][0]<Tvol[0][1] || Tvol[0][0]>Tvol[0][2] )
					{
						Show_Str(93,13,RED,Back_Ground,"VAC",20,0,2);				
						LCD_ShowxNum(45,7,RED,Back_Ground,Tvol[0][0]/100%10,1,28,0,2);
						LCD_ShowxNum(60,7,RED,Back_Ground,Tvol[0][0]/10%10,1,28,0,2);
						LCD_ShowxNum(75,7,RED,Back_Ground,Tvol[0][0]%10,1,28,0,2);						
					}
					else
					{
						Show_Str(93,13,BLACK,Back_Ground,"VAC",20,0,2);		
						LCD_ShowxNum(45,7,BLACK,Back_Ground,Tvol[0][0]/100%10,1,28,0,2);
						LCD_ShowxNum(60,7,BLACK,Back_Ground,Tvol[0][0]/10%10,1,28,0,2);
						LCD_ShowxNum(75,7,BLACK,Back_Ground,Tvol[0][0]%10,1,28,0,2);									
					}						
					if(Tcur[0][0]<Tcur[0][1] || Tcur[0][0]>Tcur[0][2] )
					{
						LCD_ShowxNum(44,37,RED,Back_Ground,Tcur[0][0]/100%10,1,28,0,2);
						LCD_ShowxNum(58,37,RED,Back_Ground,Tcur[0][0]/10%10,1,28,0,2);								
						Show_Str(68,39,RED,Back_Ground,".",28,0,2);	
						LCD_ShowxNum(75,37,RED,Back_Ground,Tcur[0][0]%10,1,28,0,2);
						Show_Str(93,41,RED,Back_Ground,"A",22,0,2);							
					}
					else
					{
						LCD_ShowxNum(44,37,BLACK,Back_Ground,Tcur[0][0]/100%10,1,28,0,2);
						LCD_ShowxNum(58,37,BLACK,Back_Ground,Tcur[0][0]/10%10,1,28,0,2);								
						Show_Str(68,39,BLACK,Back_Ground,".",28,0,2);	
						LCD_ShowxNum(75,37,BLACK,Back_Ground,Tcur[0][0]%10,1,28,0,2);
						Show_Str(93,41,BLACK,Back_Ground,"A",22,0,2);								
					}	
					
					Show_Str(93,71,BLACK,Back_Ground,"kw",22,0,2);
					Show_Str(68,69,BLACK,Back_Ground,".",28,0,2);						
					LCD_ShowxNum(44,67,BLACK,Back_Ground,(Tvol[0][0]*Tcur[0][0])/100000%10,1,28,0,2);
					LCD_ShowxNum(58,67,BLACK,Back_Ground,(Tvol[0][0]*Tcur[0][0])/10000%10,1,28,0,2);
					LCD_ShowxNum(75,67,BLACK,Back_Ground,(Tvol[0][0]*Tcur[0][0])/1000%10,1,28,0,2);						
												
					Show_Str(93,100,BLACK,Back_Ground,"kwh",20,0,2);
					Show_Str(75,99,BLACK,Back_Ground,".",22,0,2);									
					LCD_ShowxNum(5,101,BLACK,Back_Ground,Energy8207[0]/1000000%10,1,22,0,2);
					LCD_ShowxNum(17,101,BLACK,Back_Ground,Energy8207[0]/100000%10,1,22,0,2);
					LCD_ShowxNum(29,101,BLACK,Back_Ground,Energy8207[0]/10000%10,1,22,0,2);
					LCD_ShowxNum(41,101,BLACK,Back_Ground,Energy8207[0]/1000%10,1,22,0,2);
					LCD_ShowxNum(53,101,BLACK,Back_Ground,Energy8207[0]/100%10,1,22,0,2);
					LCD_ShowxNum(65,101,BLACK,Back_Ground,Energy8207[0]/10%10,1,22,0,2);
					LCD_ShowxNum(79,101,BLACK,Back_Ground,Energy8207[0]%10,1,22,0,2);		
					LCD_Refresh_Gram(2);
		}
		if(LINE_NUM==3)
		{
				if(button_menu[1]==2)
				{
							LCD_Clear(Back_Ground,1); //清屏				
							Show_Str(8,7,BLUE,Back_Ground,"L",24,0,1);
							Show_Str(20,7,BLUE,Back_Ground,"2",24,0,1);
									
							if(Tvol[1][0]<Tvol[1][1] || Tvol[1][0]>Tvol[1][2] )
							{
								Show_Str(93,13,RED,Back_Ground,"VAC",20,0,1);				
								LCD_ShowxNum(45,7,RED,Back_Ground,Tvol[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,RED,Back_Ground,Tvol[1][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,RED,Back_Ground,Tvol[1][0]%10,1,28,0,1);							
							}
							else
							{
								Show_Str(93,13,BLACK,Back_Ground,"VAC",20,0,1);		
								LCD_ShowxNum(45,7,BLACK,Back_Ground,Tvol[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(60,7,BLACK,Back_Ground,Tvol[1][0]/10%10,1,28,0,1);
								LCD_ShowxNum(75,7,BLACK,Back_Ground,Tvol[1][0]%10,1,28,0,1);									
							}						
							if(Tcur[1][0]<Tcur[1][1] || Tcur[1][0]>Tcur[1][2] )
							{
								LCD_ShowxNum(44,37,RED,Back_Ground,Tcur[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,RED,Back_Ground,Tcur[1][0]/10%10,1,28,0,1);								
								Show_Str(68,39,RED,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,RED,Back_Ground,Tcur[1][0]%10,1,28,0,1);
								Show_Str(93,41,RED,Back_Ground,"A",22,0,1);							
							}
							else
							{
								LCD_ShowxNum(44,37,BLACK,Back_Ground,Tcur[1][0]/100%10,1,28,0,1);
								LCD_ShowxNum(58,37,BLACK,Back_Ground,Tcur[1][0]/10%10,1,28,0,1);								
								Show_Str(68,39,BLACK,Back_Ground,".",28,0,1);	
								LCD_ShowxNum(75,37,BLACK,Back_Ground,Tcur[1][0]%10,1,28,0,1);
								Show_Str(93,41,BLACK,Back_Ground,"A",22,0,1);								
							}	

							if(Tvol_alarm[0]==1||Tvol_alarm[1]==1||Tvol_alarm[2]==1||Tcur_alarm[0]==1||Tcur_alarm[1]==1
									||Tcur_alarm[2]==1||tem[0]<tem[1] || tem[0]>tem[2]||hum[0]<hum[1]|| hum[0]>hum[2])
							{
										if(ONorOFF_sound)
											Show_Str(10,75,RED,Back_Ground,"ON",16,0,1);
										else
											Show_Str(10,75,RED,Back_Ground,"OFF",16,0,1);									
							}	
							
							Show_Str(93,71,BLACK,Back_Ground,"kw",22,0,1);
							Show_Str(68,69,BLACK,Back_Ground,".",28,0,1);
										
							LCD_ShowxNum(44,67,BLACK,Back_Ground,(Tvol[1][0]*Tcur[1][0])/100000%10,1,28,0,1);
							LCD_ShowxNum(58,67,BLACK,Back_Ground,(Tvol[1][0]*Tcur[1][0])/10000%10,1,28,0,1);
							LCD_ShowxNum(75,67,BLACK,Back_Ground,(Tvol[1][0]*Tcur[1][0])/1000%10,1,28,0,1);						
														
							Show_Str(93,100,BLACK,Back_Ground,"kwh",20,0,1);
							Show_Str(75,99,BLACK,Back_Ground,".",22,0,1);							
									
							LCD_ShowxNum(5,101,BLACK,Back_Ground,Energy8207[1]/1000000%10,1,22,0,1);
							LCD_ShowxNum(17,101,BLACK,Back_Ground,Energy8207[1]/100000%10,1,22,0,1);
							LCD_ShowxNum(29,101,BLACK,Back_Ground,Energy8207[1]/10000%10,1,22,0,1);
							LCD_ShowxNum(41,101,BLACK,Back_Ground,Energy8207[1]/1000%10,1,22,0,1);
							LCD_ShowxNum(53,101,BLACK,Back_Ground,Energy8207[1]/100%10,1,22,0,1);
							LCD_ShowxNum(65,101,BLACK,Back_Ground,Energy8207[1]/10%10,1,22,0,1);
							LCD_ShowxNum(79,101,BLACK,Back_Ground,Energy8207[1]%10,1,22,0,1);		
							LCD_Refresh_Gram(1);					
				}
				else if(button_menu[1]==3)
				{
							LCD_Clear(Back_Ground,2); //清屏
		//										
							Show_Str(8,7,BLUE,Back_Ground,"L",24,0,2);
							Show_Str(20,7,BLUE,Back_Ground,"3",24,0,2);
						
							if(Tvol_alarm[0]==1||Tvol_alarm[1]==1||Tvol_alarm[2]==1||Tcur_alarm[0]==1||Tcur_alarm[1]==1
									||Tcur_alarm[2]==1||tem[0]<tem[1] || tem[0]>tem[2]||hum[0]<hum[1]|| hum[0]>hum[2])
							{
										if(ONorOFF_sound)
											Show_Str(10,75,RED,Back_Ground,"ON",16,0,2);
										else
											Show_Str(10,75,RED,Back_Ground,"OFF",16,0,2);										
							}						
									
							if(Tvol[2][0]<Tvol[2][1] || Tvol[2][0]>Tvol[2][2] )
							{
								Show_Str(93,13,RED,Back_Ground,"VAC",20,0,2);				
								LCD_ShowxNum(45,7,RED,Back_Ground,Tvol[2][0]/100%10,1,28,0,2);
								LCD_ShowxNum(60,7,RED,Back_Ground,Tvol[2][0]/10%10,1,28,0,2);
								LCD_ShowxNum(75,7,RED,Back_Ground,Tvol[2][0]%10,1,28,0,2);							
							}
							else
							{
								Show_Str(93,13,BLACK,Back_Ground,"VAC",20,0,2);		
								LCD_ShowxNum(45,7,BLACK,Back_Ground,Tvol[2][0]/100%10,1,28,0,2);
								LCD_ShowxNum(60,7,BLACK,Back_Ground,Tvol[2][0]/10%10,1,28,0,2);
								LCD_ShowxNum(75,7,BLACK,Back_Ground,Tvol[2][0]%10,1,28,0,2);									
							}						
							if(Tcur[2][0]<Tcur[2][1] || Tcur[2][0]>Tcur[2][2] )
							{
								LCD_ShowxNum(44,37,RED,Back_Ground,Tcur[2][0]/100%10,1,28,0,2);
								LCD_ShowxNum(58,37,RED,Back_Ground,Tcur[2][0]/10%10,1,28,0,2);								
								Show_Str(68,39,RED,Back_Ground,".",28,0,2);	
								LCD_ShowxNum(75,37,RED,Back_Ground,Tcur[2][0]%10,1,28,0,2);
								Show_Str(93,41,RED,Back_Ground,"A",22,0,2);								
							}
							else
							{
								LCD_ShowxNum(44,37,BLACK,Back_Ground,Tcur[2][0]/100%10,1,28,0,2);
								LCD_ShowxNum(58,37,BLACK,Back_Ground,Tcur[2][0]/10%10,1,28,0,2);								
								Show_Str(68,39,BLACK,Back_Ground,".",28,0,2);	
								LCD_ShowxNum(75,37,BLACK,Back_Ground,Tcur[2][0]%10,1,28,0,2);
								Show_Str(93,41,BLACK,Back_Ground,"A",22,0,2);								
							}	
							
							Show_Str(93,71,BLACK,Back_Ground,"kw",22,0,2);
							Show_Str(68,69,BLACK,Back_Ground,".",28,0,2);
										
							LCD_ShowxNum(44,67,BLACK,Back_Ground,(Tvol[2][0]*Tcur[2][0])/100000%10,1,28,0,2);
							LCD_ShowxNum(58,67,BLACK,Back_Ground,(Tvol[2][0]*Tcur[2][0])/10000%10,1,28,0,2);
							LCD_ShowxNum(75,67,BLACK,Back_Ground,(Tvol[2][0]*Tcur[2][0])/1000%10,1,28,0,2);						
														
							Show_Str(93,100,BLACK,Back_Ground,"kwh",20,0,2);
							Show_Str(75,99,BLACK,Back_Ground,".",22,0,2);							
									
							LCD_ShowxNum(5,101,BLACK,Back_Ground,Energy8207[2]/1000000%10,1,22,0,2);
							LCD_ShowxNum(17,101,BLACK,Back_Ground,Energy8207[2]/100000%10,1,22,0,2);
							LCD_ShowxNum(29,101,BLACK,Back_Ground,Energy8207[2]/10000%10,1,22,0,2);
							LCD_ShowxNum(41,101,BLACK,Back_Ground,Energy8207[2]/1000%10,1,22,0,2);
							LCD_ShowxNum(53,101,BLACK,Back_Ground,Energy8207[2]/100%10,1,22,0,2);
							LCD_ShowxNum(65,101,BLACK,Back_Ground,Energy8207[2]/10%10,1,22,0,2);
							LCD_ShowxNum(79,101,BLACK,Back_Ground,Energy8207[2]%10,1,22,0,2);	
							LCD_Refresh_Gram(2);
				}
		}
		if(button_menu[0]==2 || button_menu[1]==4)  //温湿度
		{
						LCD_Clear(Back_Ground,2); //清屏								
						Show_Str(36,15,BLACK,Back_Ground,"Tem",24,0,2);
						Show_Str(72,17,BLACK,Back_Ground,"p",24,0,2);
						Show_Str(36,67,BLACK,Back_Ground,"Hum",24,0,2);
					
						if(tem[0]<tem[1] || tem[0]>tem[2])
						{
								LCD_ShowxNum(36,39,RED,Back_Ground,tem[0]/10%10,1,28,0,2);
								LCD_ShowxNum(54,39,RED,Back_Ground,tem[0]%10,1,28,0,2);
								Show_Str(73,47,RED,Back_Ground,"℃",16,1,2);							
						}
						else
						{
								LCD_ShowxNum(36,39,BLACK,Back_Ground,tem[0]/10%10,1,28,0,2);
								LCD_ShowxNum(54,39,BLACK,Back_Ground,tem[0]%10,1,28,0,2);
								Show_Str(73,47,BLACK,Back_Ground,"℃",16,1,2);								
						}
							
						if(hum[0]<hum[1]|| hum[0]>hum[2])
						{
								LCD_ShowxNum(36,91,RED,Back_Ground,hum[0]/10%10,1,28,0,2);
								LCD_ShowxNum(54,91,RED,Back_Ground,hum[0]%10,1,28,0,2);
								Show_Str(73,99,RED,Back_Ground,"％",16,1,2);							
						}
						else
						{
								LCD_ShowxNum(36,91,BLACK,Back_Ground,hum[0]/10%10,1,28,0,2);
								LCD_ShowxNum(54,91,BLACK,Back_Ground,hum[0]%10,1,28,0,2);
								Show_Str(73,99,BLACK,Back_Ground,"％",16,1,2);								
						}
						
						if(Tvol_alarm[0]==1||Tvol_alarm[1]==1||Tvol_alarm[2]==1||Tcur_alarm[0]==1||Tcur_alarm[1]==1
								||Tcur_alarm[2]==1||tem[0]<tem[1] || tem[0]>tem[2]||hum[0]<hum[1]|| hum[0]>hum[2])
						{
								if(ONorOFF_sound)
									Show_Str(8,75,RED,Back_Ground,"ON",16,0,2);
								else
									Show_Str(8,75,RED,Back_Ground,"OFF",16,0,2);										
						}		

						button_down=0;
						button_up=0;
						
						LCD_Refresh_Gram(2);					
		}
		else if(button_menu[0]==3 || button_menu[1]==5)  //IP地址、地址码
		{
								LCD_Clear(Back_Ground,2); //清屏
							  Show_Str(10,5,BLACK,Back_Ground,"I",24,0,2);
								Show_Str(26,5,BLACK,Back_Ground,"P",24,0,2);
	
								LCD_ShowxNum(10,30,BLACK,Back_Ground,ip1,3,28,0,2);
								Show_Str(50,33,BLACK,Back_Ground,".",28,0,2);
								LCD_ShowxNum(58,30,BLACK,Back_Ground,ip2,3,28,0,2);
								Show_Str(98,33,BLACK,Back_Ground,".",28,0,2);
								LCD_ShowxNum(10,60,BLACK,Back_Ground,ip3,3,28,0,2);
								Show_Str(50,63,BLACK,Back_Ground,".",28,0,2);
								LCD_ShowxNum(58,60,BLACK,Back_Ground,ip4,3,28,0,2);
								Show_Str(10,95,BLACK,Back_Ground,"A",24,0,2);
							  Show_Str(23,94,BLACK,Back_Ground,"ddr",24,0,2);	
								if(button_down==1)
								{
									LCD_ShowxNum(65,91,BLACK,Back_Ground,ser/10%4,1,28,0,2);
									LCD_ShowxNum(81,91,BLACK,LGRAY,(ser+button_up)%10,1,28,1,2);							
										
								}
								else if(button_down==2)
								{
									LCD_ShowxNum(65,91,BLACK,LGRAY,(ser/10%10+button_up)%4,1,28,1,2);
									LCD_ShowxNum(81,91,BLACK,Back_Ground,ser%10,1,28,0,2);
			
								}
								else
								{
									LCD_ShowxNum(65,91,BLACK,Back_Ground,ser/10%4,1,28,0,2);
									LCD_ShowxNum(81,91,BLACK,Back_Ground,ser%10,1,28,0,2);
								}			
								LCD_Refresh_Gram(2);					
		}
		else if(button_menu[0]==4 || button_menu[1]==6)   //波特率
		{													
							LCD_Clear(Back_Ground,2); //清屏
							Show_Str(40,41,BLACK,Back_Ground,"B",24,0,2);
							Show_Str(53,41,BLACK,Back_Ground,"aud",24,0,2);
							if(button_up)
							{
								baud += button_up;
								if(baud>5)
									baud=0;
								button_up = 0;
							}
							else if(button_down)
							{
								baud -= button_down;
								if(baud<0 || baud > 5)
									baud=5;	
								button_down = 0;		
							}
							
							if(baud==0)
								Show_Str(40,71,BLACK,Back_Ground,"1200  ",24,0,2);
							else if(baud==1)
								Show_Str(40,71,BLACK,Back_Ground,"2400 ",24,0,2);
							else if(baud==2)
								Show_Str(40,71,BLACK,Back_Ground,"4800 ",24,0,2);
							else if(baud==3)
								Show_Str(40,71,BLACK,Back_Ground,"9600 ",24,0,2);
							else if(baud==4)
								Show_Str(40,71,BLACK,Back_Ground,"19200",24,0,2);
							else if(baud==5)
								Show_Str(40,71,BLACK,Back_Ground,"38400",24,0,2);		
							LCD_Refresh_Gram(2);				
		}
		else if(button_menu[0]==5 || button_menu[1]==7)   //L1最大值设置
		{
							LCD_Clear(Back_Ground,2); //清屏
						
							Show_Str(50,5,BLUE,Back_Ground,"L",24,0,2);
							Show_Str(64,5,BLUE,Back_Ground,"1",24,0,2);
							Show_Str(44,33,BLACK,Back_Ground,"M",24,0,2);
							Show_Str(58,33,BLACK,Back_Ground,"ax",24,0,2);
							Show_Str(59,92,BLACK ,Back_Ground,".",28,0,2);
							Show_Str(85,65,BLACK,Back_Ground,"V",22,0,2);
							Show_Str(85,93,BLACK,Back_Ground,"A",22,0,2);
									
							if(button_down==1)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,LGRAY,(Tvol[0][2]%10+button_up)%10,1,28,1,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[0][2]%10),1,28,0,2);									 
							}
							else if(button_down==2)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,LGRAY,(Tvol[0][2]/10%10+button_up)%10,1,28,1,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[0][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[0][2]%10),1,28,0,2);									 
							}
							else if(button_down==3)
							{
									LCD_ShowxNum(34,60,BLACK ,LGRAY,((Tvol[0][2]/100%10+button_up)%4),1,28,1,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[0][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[0][2]%10),1,28,0,2);									 
							}
							else if(button_down==4)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[0][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,LGRAY,(Tcur[0][2]/10%10+button_up)%10,1,28,1,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[0][2]%10),1,28,0,2);									 
							}
							else if(button_down==5)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[0][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,LGRAY,((Tcur[0][2]/100%10+button_up)%7),1,28,1,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[0][2]%10),1,28,0,2);									 
							}
							else
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[0][2]%10),1,28,0,2);
										
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[0][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[0][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[0][2]%10),1,28,0,2);							 
							}	
							LCD_Refresh_Gram(2);					
		}			
		if(LINE_NUM==3)
		{
				if(button_menu[1]==8)  //L2最大值设置
				{
							LCD_Clear(Back_Ground,2); //清屏
						
							Show_Str(50,5,BLUE,Back_Ground,"L",24,0,2);
							Show_Str(64,5,BLUE,Back_Ground,"2",24,0,2);
							Show_Str(44,33,BLACK,Back_Ground,"M",24,0,2);
							Show_Str(58,33,BLACK,Back_Ground,"ax",24,0,2);
							Show_Str(59,92,BLACK ,Back_Ground,".",28,0,2);
							Show_Str(85,65,BLACK,Back_Ground,"V",22,0,2);
							Show_Str(85,93,BLACK,Back_Ground,"A",22,0,2);
									
							if(button_down==1)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,LGRAY,(Tvol[1][2]%10+button_up)%10,1,28,1,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[1][2]%10),1,28,0,2);									 
							}
							else if(button_down==2)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,LGRAY,(Tvol[1][2]/10%10+button_up)%10,1,28,1,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[1][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[1][2]%10),1,28,0,2);									 
							}
							else if(button_down==3)
							{
									LCD_ShowxNum(34,60,BLACK ,LGRAY,((Tvol[1][2]/100%10+button_up)%4),1,28,1,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[1][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[1][2]%10),1,28,0,2);									 
							}
							else if(button_down==4)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[1][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,LGRAY,(Tcur[1][2]/10%10+button_up)%10,1,28,1,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[1][2]%10),1,28,0,2);									 
							}
							else if(button_down==5)
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[1][2]%10),1,28,0,2);
								
									LCD_ShowxNum(34,89,BLACK ,LGRAY,((Tcur[1][2]/100%10+button_up)%7),1,28,1,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[1][2]%10),1,28,0,2);									 
							}
							else
							{
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[1][2]%10),1,28,0,2);
										
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[1][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[1][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[1][2]%10),1,28,0,2);							 
							}	
							LCD_Refresh_Gram(2);					
				}
				else if(button_menu[1]==9) //L3最大值设置
				{
							 LCD_Clear(Back_Ground,2); //清屏
												
							 Show_Str(50,5,BLUE,Back_Ground,"L",24,0,2);
							 Show_Str(64,5,BLUE,Back_Ground,"3",24,0,2);
							 Show_Str(44,33,BLACK,Back_Ground,"M",24,0,2);
							 Show_Str(58,33,BLACK,Back_Ground,"ax",24,0,2);
							 Show_Str(59,92,BLACK ,Back_Ground,".",28,0,2);
							 Show_Str(85,65,BLACK,Back_Ground,"V",22,0,2);
							 Show_Str(85,93,BLACK,Back_Ground,"A",22,0,2);
							
							 if(button_down==1)
							 {
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,LGRAY,(Tvol[2][2]%10+button_up)%10,1,28,1,2);
						
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[2][2]%10),1,28,0,2);									 
							 }
							 else if(button_down==2)
							 {
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,LGRAY,(Tvol[2][2]/10%10+button_up)%10,1,28,1,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[2][2]%10),1,28,0,2);
						
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[2][2]%10),1,28,0,2);									 
							 }
							 else if(button_down==3)
							 {
									LCD_ShowxNum(34,60,BLACK ,LGRAY,((Tvol[2][2]/100%10+button_up)%4),1,28,1,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[2][2]%10),1,28,0,2);
						
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[2][2]%10),1,28,0,2);									 
							 }
							 else if(button_down==4)
							 {
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[2][2]%10),1,28,0,2);
						
									LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(48,89,BLACK,LGRAY,(Tcur[2][2]/10%10+button_up)%10,1,28,1,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[2][2]%10),1,28,0,2);									 
							 }
							 else if(button_down==5)
							 {
									LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[2][2]/100%10),1,28,0,2);
									LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[2][2]%10),1,28,0,2);
						
									LCD_ShowxNum(34,89,BLACK ,LGRAY,((Tcur[2][2]/100%10+button_up)%7),1,28,1,2);
									LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[2][2]/10%10),1,28,0,2);
									LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[2][2]%10),1,28,0,2);									 
							 }
							 else
							 {
									 LCD_ShowxNum(34,60,BLACK ,Back_Ground,(Tvol[2][2]/100%10),1,28,0,2);
									 LCD_ShowxNum(50,60,BLACK ,Back_Ground,(Tvol[2][2]/10%10),1,28,0,2);
									 LCD_ShowxNum(66,60,BLACK ,Back_Ground,(Tvol[2][2]%10),1,28,0,2);
								
									 LCD_ShowxNum(34,89,BLACK ,Back_Ground,(Tcur[2][2]/100%10),1,28,0,2);
									 LCD_ShowxNum(48,89,BLACK,Back_Ground,(Tcur[2][2]/10%10),1,28,0,2);
									 LCD_ShowxNum(66,89,BLACK ,Back_Ground,(Tcur[2][2]%10),1,28,0,2);							 
							 }
							 LCD_Refresh_Gram(2);						
				}			
		}
		if(button_menu[0]==6 || button_menu[1]==10)
		{
				LCD_Clear(Back_Ground,2); //清屏
			
				Show_Str(44,28,BLACK,Back_Ground,"M",24,0,2);
				Show_Str(58,28,BLACK,Back_Ground,"ax",24,0,2);
				Show_Str(79,63,BLACK,Back_Ground,"℃",16,1,2);
				Show_Str(81,92,BLACK,Back_Ground,"％",16,1,2);
			
				if(button_down==1)
				{
						LCD_ShowxNum(44,55,BLACK,Back_Ground,tem[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,55,BLACK,LGRAY,(tem[2]%10+button_up)%10,1,28,1,2);
						LCD_ShowxNum(44,84,BLACK,Back_Ground,hum[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,84,BLACK,Back_Ground,hum[2]%10,1,28,0,2);								
				}
				else if(button_down==2)
				{
						LCD_ShowxNum(44,55,BLACK,LGRAY,(tem[2]/10%10+button_up)%10,1,28,1,2);
						LCD_ShowxNum(62,55,BLACK,Back_Ground,tem[2]%10,1,28,0,2);
						LCD_ShowxNum(44,84,BLACK,Back_Ground,hum[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,84,BLACK,Back_Ground,hum[2]%10,1,28,0,2);								
				}
				else if(button_down==3)
				{
						LCD_ShowxNum(44,55,BLACK,Back_Ground,tem[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,55,BLACK,Back_Ground,tem[2]%10,1,28,0,2);
						LCD_ShowxNum(44,84,BLACK,Back_Ground,hum[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,84,BLACK,LGRAY,(hum[2]%10+button_up)%10,1,28,1,2);								
				}
				else if(button_down==4)
				{
						LCD_ShowxNum(44,55,BLACK,Back_Ground,tem[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,55,BLACK,Back_Ground,tem[2]%10,1,28,0,2);
						LCD_ShowxNum(44,84,BLACK,LGRAY,(hum[2]/10%10+button_up)%10,1,28,1,2);
						LCD_ShowxNum(62,84,BLACK,Back_Ground,hum[2]%10,1,28,0,2);								
				}
				else
				{
						LCD_ShowxNum(44,55,BLACK,Back_Ground,tem[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,55,BLACK,Back_Ground,tem[2]%10,1,28,0,2);
						LCD_ShowxNum(44,84,BLACK,Back_Ground,hum[2]/10%10,1,28,0,2);
						LCD_ShowxNum(62,84,BLACK,Back_Ground,hum[2]%10,1,28,0,2);
				}				
			
				LCD_Refresh_Gram(2);	
		}			
}

void DisplayTask(void *param)
{
		static char auto_hand_delay=0;
		while(1)
		{
				if(button_menu[0]==0&&button_menu[1]==0)
				{
					auto_hand_delay++;
					if(LINE_NUM==1)        //单相
					{
						if(auto_hand_delay>=0&&auto_hand_delay<=5)
						{
								auto_tem_dis=0;
								auto_hand_action = 1;
						}
						else if(auto_hand_delay>=6&&auto_hand_delay<=9)
						{							
								auto_hand_action=0;
								auto_tem_dis = 1;
						}
						else auto_hand_delay=0;
					}
					else           //三相
					{
						if(auto_hand_delay>=0&&auto_hand_delay<=5)
						{
								auto_tem_dis=0;
								auto_hand_action = 1;
						}
						else if(auto_hand_delay>=6&&auto_hand_delay<=10)
						{
								auto_hand_action = 2;
						}
						else if(auto_hand_delay>=11&&auto_hand_delay<=15)
						{
								auto_hand_action = 3;
						}					
						else if(auto_hand_delay>=16&&auto_hand_delay<=19)
						{							
								auto_hand_action=0;
								auto_tem_dis = 1;
						}
						else auto_hand_delay=0;					
					}
					auto_action();					
				}
				else 
					hand_action();			
				osDelayTask(500);	
		}
}

void Auto_Jump_HandTask(void *param)
{
		while(1)
		{						
				if(button_menu[0]>0||button_menu[1]>0)   //按键按下
				{
						lcd_rest[0]--;
						if(lcd_rest[0]<=0)
						{  
								lcd_rest[0] = 0;
								lcd_rest[1] = 0;
								button_menu[0]=button_menu[1]=button_up=button_down=0;
						}
						if(button_menu[0]==4||button_menu[1]==6)   //在波特率码页面按下设置了
						{
								if(enter_baud[0]==1||enter_baud[1]==1)
								{
										lcd_rest[1]--;
										if(lcd_rest[1]<=0)
										{
											devicedown();
										}										
								}
						}
						else if(button_menu[0]==3||(button_menu[0]>=5&&button_menu[0]<=6) || (button_menu[1]>=7&&button_menu[1]<=10)||button_menu[1]==5)   //在阈值页面按下设置了
						{
								if(button_down>0)
								{
									lcd_rest[1]--;
									if(lcd_rest[1]<=0)
									{
										devicedown();
									}							
								}								
						}
						else lcd_rest[1] = 0;
				}		
				
				osDelayTask(500);
				if(button_iic_write==1)
				{
								button_iic_write=0;
								if(ser<=0)ser=1;				
								I2cWrite(224,ser);
								I2cWrite(225,baud);
								if(cur_dc_ac)            //ac
								{
									if(Tvol[0][2]>276)
										Tvol[0][2]=276;
									if(Tcur[0][2]>320)
										Tcur[0][2]=320;
							   }
								else
								{
									if(Tvol[0][2]>400)
										Tvol[0][2]=400;
									if(Tcur[0][2]>600)
										Tcur[0][2]=600;									
								}
								
								I2cWrite_2(11,Tvol[0][2]/256%256);
								I2cWrite_2(12,Tvol[0][2]%256);
								
								I2cWrite_2(15,Tcur[0][2]/256%256);
								I2cWrite_2(16,Tcur[0][2]%256);								
							
								I2cWrite(227,tem[2]);	
								I2cWrite(229,hum[2]);								
								
								if(LINE_NUM==3)
								{			
										if(Tvol[1][2]>276)
											Tvol[1][2]=276;
										if(Tcur[1][2]>320)
											Tcur[1][2]=320;
										
										if(Tvol[2][2]>276)
											Tvol[2][2]=276;
										if(Tcur[2][2]>320)
											Tcur[2][2]=320;
										
										I2cWrite_2(19,Tvol[1][2]/256%256);
										I2cWrite_2(20,Tvol[1][2]%256);
										I2cWrite_2(27,Tvol[2][2]/256%256);
										I2cWrite_2(28,Tvol[2][2]%256);
									
										I2cWrite_2(23,Tcur[1][2]/256%256);
										I2cWrite_2(24,Tcur[1][2]%256);
										I2cWrite_2(31,Tcur[2][2]/256%256);
										I2cWrite_2(32,Tcur[2][2]%256);									
								}															
								devicedown();					
				}			
			
			
		}
}

void display_init(void)
{
		osCreateTask("dispaly_init", DisplayTask, NULL, 1000, 1);
		osCreateTask("auto_jump_hand_init", Auto_Jump_HandTask, NULL, 500, 2);
	 
}



