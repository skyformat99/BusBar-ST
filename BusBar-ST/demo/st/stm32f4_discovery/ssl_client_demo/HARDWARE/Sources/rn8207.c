#include "rn8207.h"
#include <stdio.h>
#include <math.h>
#include "string.h"

double Kv;
double Ki;
double Kp=0.000157;
double Kp_dc=0.0000402;
double gpa[4],P_value[4];
static char P_test=0;
int Preg_test[5];
static int urms1[2];
char correct_flag_ac[3]={0,0,0};  //交流校准标志
char correct_flag_phase_ac[3]={0,0,0};  //交流相位校准标志
char register_offset_dc[4]={0,0,0,0};   //直流偏置校准
uint32_t register_data_a[4]={0,0,0,0};
int add_energy_ac[3]={0,0,0};
int save_energy_ac[3]={0,0,0};
int mw_led_data[4]={0,0,0,0};
char mw_led=0;
int add_energy_dc=0;
int save_energy_dc=0;
int snmp_power[4]={0,0,0,0};

void rn8207_delay(int temp)
{
		while(temp--);
}

int read_8207(uint8_t deivce_add,uint8_t read_add,uint8_t len)
{
	
		int data;
		uint8_t buf[32];
		data=0;		
		
		memset(buf,0,sizeof(char)*32);	
		buf[0]=deivce_add;
		buf[1]=read_add;
		uart6_send_data(buf,2);
		
		osDelayTask(50);
		memset(buf,0,sizeof(char)*32);
		Uart_Recive_data(COM6,buf,4);
		if(len==1)
				data=buf[0];
		else if(len==2)
				data=buf[0]*256+buf[1];
		else if(len==3)
				data=buf[0]*256*256+buf[1]*256+buf[2];
		else if(len==4)
				data=buf[0]*256*256*256+buf[1]*256*256+buf[2]*256+buf[3];
		osDelayTask(100);
		return data;
}

void write_8207(uint8_t Deivce_add,uint8_t add,uint8_t *data,uint8_t len)
{
		char i,xy;
		uint8_t buf[32];
		xy=0;

		memset(buf,0,32);
		buf[0]=Deivce_add;
		buf[1]=add;
		for(i=0;i<len;i++)
		{
				buf[i+2]=*(data+i);
		}
		for(i=0;i<len+2;i++)
		{
				xy+=buf[i];
		}
		buf[len+2]=~xy;
		uart6_send_data(buf,len+3);	
		osDelayTask(100);	
}


int correct_set()                                        
{
		uint8_t buf[32];
		memset(buf,0,sizeof(char)*32);
				
		buf[0]=read_8207(0x88,0x41,1);       
		if(buf[0]& 0x20)
			cur_dc_ac=1;            // ac
		else
			cur_dc_ac=0;            // dc
		
		if(cur_dc_ac==0)                     //dc 
		{		
				int data_value;
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0x88,0xEA,buf,1);	
		
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0x16;                          // H
				buf[1] = 0xCA;                          // L    
				write_8207(0x88,0x82,buf,2);				    //HFcont      1600 --0X2D95
			
				data_value = read_8207(0x88,0x02,2);	
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0x16;                          // H
				buf[1] = 0x00;                          // L    
				write_8207(0x88,0x80,buf,2);				    //			 一倍增益
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xB0;
				buf[1] = 0x63;            
				write_8207(0x88,0x81,buf,2);			       //关闭高通滤波

				memset(buf,0,sizeof(char)*32);
				buf[0] = register_dc_DCIH[0];
				buf[1] = register_dc_DCIH[1];
				write_8207(0x88,0x93,buf,2);	           //  DCIH

				memset(buf,0,sizeof(char)*32);
				buf[0] = 0x00;
				buf[1] = register_dc_DCL[0];
				write_8207(0x88,0x96,buf,2);	           // DCL		
				
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_dc_DCL[1];
				buf[1] = 0;
				write_8207(0x88,0x96,buf,2);	           // DCL		
				
				memset(buf,0,sizeof(char)*32);
				buf[0] = IARMSOS_reg>>8;
				buf[1] = IARMSOS_reg & 0x000000ff;
				write_8207(0x88,0x8E,buf,2);	           // IARMSOS							

				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0x88,0xEA,buf,1);										
		}
		else                                         // ac
		{
//				int data_value[5]={0,0,0,0,0}; data_value[0] = read_8207(0x88,0x02,2);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0x88,0xEA,buf,1);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0x0B;                          // H  0x0B
				buf[1] = 0xAB;                          // L    0xAB
				write_8207(0x88,0x82,buf,2);				    //HFcont			
			
				memset(buf,0,sizeof(char)*32);
				buf[0] =register_GPQ[0]>>8;                         //      0XF8
				buf[1] =register_GPQ[0] & 0x000000ff;           //   0XFB
				write_8207(0x88,0x85,buf,2);				    //GPQ			
							
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_Phs[0];        //     0XFE
				write_8207(0x88,0x87,buf,1);				    //Phs		
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xB0;               // 0xB0
				buf[1] = 0x03;            //0x03       
				write_8207(0x88,0x81,buf,2);								
									
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0x88,0xEA,buf,1);				
	
				if(LINE_NUM==3)
				{
						memset(buf,0,sizeof(char)*32);
						buf[0] = 0xE5;             
						write_8207(0x99,0xEA,buf,1);
					
						memset(buf,0,sizeof(char)*32);
						buf[0] = 0x0B;                          // H
						buf[1] = 0xAB;                          // L             
						write_8207(0x99,0x82,buf,2);				    //HFcont	

						memset(buf,0,sizeof(char)*32);
						buf[0] = register_GPQ[1]>>8;
						buf[1] = register_GPQ[1] & 0x000000ff;            
						write_8207(0x99,0x85,buf,2);				    //GPQ	
									
						memset(buf,0,sizeof(char)*32);
						buf[0] = register_Phs[1];           
						write_8207(0x99,0x87,buf,1);				    //Phs						
					
						memset(buf,0,sizeof(char)*32);
						buf[0] = 0xB0;
						buf[1] = 0x03;            
						write_8207(0x99,0x81,buf,2);							

						memset(buf,0,sizeof(char)*32);
						buf[0] = 0xDC;                
						write_8207(0x99,0xEA,buf,1);		
							
						memset(buf,0,sizeof(char)*32);
						buf[0] = 0xE5;             
						write_8207(0xAA,0xEA,buf,1);
						
						memset(buf,0,sizeof(char)*32);
						buf[0] = 0x0B;                          // H
						buf[1] = 0xAB;                          // L        
						write_8207(0xAA,0x82,buf,2);				    //HFcont	

						memset(buf,0,sizeof(char)*32);
						buf[0] = register_GPQ[2]>>8;
						buf[1] = register_GPQ[2] & 0x000000ff;            
						write_8207(0xAA,0x85,buf,2);				    //GPQ	
									
						memset(buf,0,sizeof(char)*32);
						buf[0] = register_Phs[2];           
						write_8207(0xAA,0x87,buf,1);				    //Phs	
//						
						memset(buf,0,sizeof(char)*32);
						buf[0] = 0xB0;
						buf[1] = 0x03;            
						write_8207(0xAA,0x81,buf,2);				
	
						memset(buf,0,sizeof(char)*32);
						buf[0] = 0xDC;               
						write_8207(0xAA,0xEA,buf,1);	
			  }					
		 }
		
		return cur_dc_ac;
}

void Init_8207(void)
{
		uint8_t buf[32];
		int bb , tt;
	
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xE5;
		write_8207(0x88,0xEA,buf,1);       
	
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xFA;
		write_8207(0x88,0xEA,buf,1);       
	
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xDC;
		write_8207(0x88,0xEA,buf,1);          
	
	  if(LINE_NUM==3)
		{
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;
				write_8207(0x99,0xEA,buf,1);       
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xFA;
				write_8207(0x99,0xEA,buf,1);      
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;
				write_8207(0x99,0xEA,buf,1);          

				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;
				write_8207(0xAA,0xEA,buf,1);    
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xFA;
				write_8207(0xAA,0xEA,buf,1);       
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;
				write_8207(0xAA,0xEA,buf,1); 
	  }		

		osDelayTask(300);		
    correct_set();		
		osDelayTask(1000);	
}

void rn8207_read_l1()
{
		VoltageA=read_8207(0x88,0x24,3);//V     
		CurrentA=read_8207(0x88,0x22,3);//A
	  active_power[0]=read_8207(0x88,0x26,4);
	  if(active_power[0] < 0)
			active_power[0] = ~active_power[0] + 1;	
}

void rn8207_read_l2()
{
		VoltageB=read_8207(0x99,0x24,3);//V
		CurrentB=read_8207(0x99,0x22,3);//A
	  active_power[1]=read_8207(0x99,0x26,4);
	  if(active_power[1] < 0)
			active_power[1] = ~active_power[1] + 1;	
}

void rn8207_read_l3()
{
		VoltageC=read_8207(0xAA,0x24,3);//V
		CurrentC=read_8207(0xAA,0x22,3);//A
	  active_power[2]=read_8207(0xAA,0x26,4);
	  if(active_power[2] < 0)
			active_power[2] = ~active_power[2] + 1;	
}

void correct_l1()
{
		VoltageAK=read_8207(0x88,0x24,3);
		CurrentAK=read_8207(0x88,0x22,3);
}

void correct_l2()
{
		VoltageBK=read_8207(0x99,0x24,3);
		CurrentBK=read_8207(0x99,0x22,3);
}

void correct_l3()
{
		VoltageCK=read_8207(0xAA,0x24,3);
		CurrentCK=read_8207(0xAA,0x22,3);
}

void RN8207Check_A(void)
{
		uint8_t savebuff_A[128];
		memset(savebuff_A,0,128);	
	
		correct_l1();
			
		savebuff_A[0]=CurrentAK/256/256/256%256;
		savebuff_A[1]=CurrentAK/256/256%256;
		savebuff_A[2]=CurrentAK/256%256;
		savebuff_A[3]=CurrentAK%256;
	
		savebuff_A[4]=VoltageAK/256/256/256%256;
		savebuff_A[5]=VoltageAK/256/256%256;
		savebuff_A[6]=VoltageAK/256%256;
		savebuff_A[7]=VoltageAK%256;
		
		I2cWrite(230,savebuff_A[0]);
		I2cWrite(231,savebuff_A[1]);
		I2cWrite(232,savebuff_A[2]);
		I2cWrite(234,savebuff_A[3]);//CurrentAK
	
		I2cWrite(243,savebuff_A[4]);
		I2cWrite(244,savebuff_A[5]);
		I2cWrite(245,savebuff_A[6]);
		I2cWrite(246,savebuff_A[7]);//VoltageAK
		
}

void RN8207Check_B(void)
{
		uint8_t savebuff_B[128];
		memset(savebuff_B,0,128);
		
		correct_l2();
	
		savebuff_B[0]=CurrentBK/256/256/256%256;
		savebuff_B[1]=CurrentBK/256/256%256;
		savebuff_B[2]=CurrentBK/256%256;
		savebuff_B[3]=CurrentBK%256;	
	
		savebuff_B[4]=VoltageBK/256/256/256%256;
		savebuff_B[5]=VoltageBK/256/256%256;
		savebuff_B[6]=VoltageBK/256%256;
		savebuff_B[7]=VoltageBK%256;

		I2cWrite(235,savebuff_B[0]);
		I2cWrite(236,savebuff_B[1]);
		I2cWrite(237,savebuff_B[2]);
		I2cWrite(238,savebuff_B[3]);//CurrentBK

		I2cWrite(247,savebuff_B[4]);
		I2cWrite(248,savebuff_B[5]);
		I2cWrite(249,savebuff_B[6]);
		I2cWrite(250,savebuff_B[7]);//VoltageBK	
	
}
void RN8207Check_C(void)
{
		uint8_t savebuff_C[128];
		memset(savebuff_C,0,128);	

		correct_l3();

		savebuff_C[0]=CurrentCK/256/256/256%256;
		savebuff_C[1]=CurrentCK/256/256%256;
		savebuff_C[2]=CurrentCK/256%256;
		savebuff_C[3]=CurrentCK%256;	

		savebuff_C[4]=VoltageCK/256/256/256%256;
		savebuff_C[5]=VoltageCK/256/256%256;
		savebuff_C[6]=VoltageCK/256%256;
		savebuff_C[7]=VoltageCK%256;

		I2cWrite(239,savebuff_C[0]);
		I2cWrite(240,savebuff_C[1]);
		I2cWrite(241,savebuff_C[2]);
		I2cWrite(242,savebuff_C[3]);//CurrentCK
	
		I2cWrite(251,savebuff_C[4]);
		I2cWrite(252,savebuff_C[5]);
		I2cWrite(253,savebuff_C[6]);
		I2cWrite(254,savebuff_C[7]);//VoltageCK

}
void correct_dc()   
{
			
			dc_correct_v = read_8207(0x88,0x24,3);    
			dc_correct_a = read_8207(0x88,0x22,3);   
	
		
			I2cWrite_2(40,dc_correct_v/256/256%256);
			I2cWrite_2(41,dc_correct_v/256%256);
			I2cWrite_2(42,dc_correct_v%256);
		
			I2cWrite_2(43,dc_correct_a/256/256%256);
			I2cWrite_2(44,dc_correct_a/256%256);
			I2cWrite_2(45,dc_correct_a%256);
	
}

uint32_t read_code_dc(uint32_t reg,int temp)
{
	int data_dc_1=0;
	uint32_t code_dc=0;
	int dcuh_dc;
	uint8_t ch[4];
	uint8_t buf[32];
	
	code_dc = ~(reg);
	dcuh_dc = ~(temp);
	
	memset(ch,0,sizeof(char)*4);
	
	ch[0] = ((code_dc>>16)&0x00ff);
	ch[1] = ((code_dc>>8)&0x0000ff);
	ch[2] = ((code_dc>>4)&0x000000f);
		
	memset(buf,0,sizeof(char)*32);
	buf[0] = 0xE5;            
	write_8207(0x88,0xEA,buf,1);	 

  data_dc_1 = read_8207(0x88,0x13,2);	
					
	memset(buf,0,sizeof(char)*32);
	buf[0] = ch[0];
	buf[1] = ch[1];
	write_8207(0x88,0x93,buf,2);	           // DCIH
	
	data_dc_1 = read_8207(0x88,0x16,2);

	memset(buf,0,sizeof(char)*32);
	buf[0] = 0x00;
	buf[1] = ch[2];
	write_8207(0x88,0x96,buf,2);	           // DCL		
	
	data_dc_1 = read_8207(0x88,0x16,2);
	
	memset(buf,0,sizeof(char)*32);
	buf[0] = (dcuh_dc>>4 & 0x000000f);
	buf[1] = 0;
	write_8207(0x88,0x96,buf,2);	           // DCL			

	memset(buf,0,sizeof(char)*32);
	buf[0] = 0xDC;               
	write_8207(0x88,0xEA,buf,1);	

	I2cWrite_2(55,ch[0] );	
	I2cWrite_2(56,ch[1]);
	I2cWrite_2(57,ch[2]);	
//	I2cWrite_2(35,dcuh_dc>>16 &0x00ff);
//	I2cWrite_2(36,dcuh_dc>>8 &0x0000ff);
	I2cWrite_2(64,(dcuh_dc>>4 & 0x000000f));

}

uint32_t IARMSOS_offset(uint32_t reg)
{
	int data_dc_2=0;
	uint8_t buf[32];
	IARMSOS_reg = ~reg/256 & 0x0000ffff;
	
	memset(buf,0,sizeof(char)*32);
	buf[0] = 0xE5;            
	write_8207(0x88,0xEA,buf,1);	

	data_dc_2 = read_8207(0x88,0x0E,2);
					
	memset(buf,0,sizeof(char)*32);
	buf[0] = IARMSOS_reg>>8;
	buf[1] = IARMSOS_reg & 0x000000ff;
	write_8207(0x88,0x8E,buf,2);	           // IARMSOS	

	memset(buf,0,sizeof(char)*32);
	buf[0] = 0xDC;               
	write_8207(0x88,0xEA,buf,1);	

	I2cWrite_2(60,IARMSOS_reg>>8);	
	I2cWrite_2(61,IARMSOS_reg & 0x000000ff);	
}

void clear_zero_register_dc(void)
{
		uint8_t buf[32];
			
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xE5;            
		write_8207(0x88,0xEA,buf,1);	
				
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;
		buf[1] = 0;
		write_8207(0x88,0x93,buf,2);	           // DCIH

		memset(buf,0,sizeof(char)*32);
		buf[0] = 0x00;
		buf[1] = 0;
		write_8207(0x88,0x96,buf,2);	           // DCL
	
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;
		buf[1] = 0;
		write_8207(0x88,0x8E,buf,2);	           // IARMSOS		

		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;
		buf[1] = 0;            
		write_8207(0x88,0x85,buf,2);				    //GPQ		

		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xDC;               
		write_8207(0x88,0xEA,buf,1);										
}
void clear_zero_register_A(void)
{
		uint8_t buf[32];
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xE5;            
		write_8207(0x88,0xEA,buf,1);
						
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;
		buf[1] = 0;            
		write_8207(0x88,0x85,buf,2);				    //GPQ	
								
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;           
		write_8207(0x88,0x87,buf,1);				    //Phs				
														
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xDC;               
		write_8207(0x88,0xEA,buf,1);			
}
void clear_zero_register_B(void)
{
		uint8_t buf[32];
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xE5;            
		write_8207(0x99,0xEA,buf,1);
						
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;
		buf[1] = 0;            
		write_8207(0x99,0x85,buf,2);				    //GPQ	
								
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;           
		write_8207(0x99,0x87,buf,1);				    //Phs				
														
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xDC;               
		write_8207(0x99,0xEA,buf,1);		
}
void clear_zero_register_C(void)
{
		uint8_t buf[32];
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xE5;            
		write_8207(0xAA,0xEA,buf,1);
						
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;
		buf[1] = 0;            
		write_8207(0xAA,0x85,buf,2);				    //GPQ	
								
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0;           
		write_8207(0xAA,0x87,buf,1);				    //Phs				
														
		memset(buf,0,sizeof(char)*32);
		buf[0] = 0xDC;               
		write_8207(0xAA,0xEA,buf,1);		
}

void read_correctPF_dc(uint32_t temp)
{
		int data_dc_3=0;
		uint8_t buf[32];	
		gpa[3] = -((temp*Kp_dc-1320)/1320)/(1+(temp*Kp_dc-1320)/1320);           //功率增益
		if(gpa[3]<0)
			register_GPQ[3] = gpa[3]*32768+65536;
		else
			register_GPQ[3] = gpa[3]*32768;	
		I2cWrite_2(58,register_GPQ[3]>>8);
		I2cWrite_2(59,register_GPQ[3] & 0x000000ff);	
		
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0x88,0xEA,buf,1);
		
				data_dc_3 = read_8207(0x88,0x05,2);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_GPQ[3]>>8;
				buf[1] = register_GPQ[3] & 0x000000ff;            
				write_8207(0x88,0x85,buf,2);				    //GPQ	
														
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0x88,0xEA,buf,1);			
		
}

void read_correctPF_A()
{
	  int data_aa=0; 
	
		uint8_t buf[32];
	  active_power[0]=read_8207(0x88,0x26,4);
	  if(active_power[0] < 0)
			active_power[0] = ~active_power[0] + 1;	                     //有功功率值
			
		gpa[0] = -((active_power[0]*Kp-1320)/1320)/(1+(active_power[0]*Kp-1320)/1320);           //功率增益
		if(gpa[0]<0)
			register_GPQ[0] = gpa[0]*32768+65536;
		else
			register_GPQ[0] = gpa[0]*32768;	
		I2cWrite_2(46,register_GPQ[0]>>8);
		I2cWrite_2(47,register_GPQ[0] & 0x000000ff);	
		
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0x88,0xEA,buf,1);
		
		    data_aa = read_8207(0x88,0x05,2);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_GPQ[0]>>8;
				buf[1] = register_GPQ[0] & 0x000000ff;            
				write_8207(0x88,0x85,buf,2);				    //GPQ	
														
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0x88,0xEA,buf,1);			
		
}
void read_correctPF_B()
{
			int data_bb=0;
			uint8_t buf[32];
			active_power[1]=read_8207(0x99,0x26,4);
			if(active_power[1] < 0)
				active_power[1] = ~active_power[1] + 1;	                     //有功功率值
				
			gpa[1] = -((active_power[1]*Kp-1320)/1320)/(1+(active_power[1]*Kp-1320)/1320);           //功率增益
			if(gpa[1]<0)
				register_GPQ[1] = gpa[1]*32768+65536;
			else
				register_GPQ[1] = gpa[1]*32768;	
			I2cWrite_2(48,register_GPQ[1]>>8);
			I2cWrite_2(49,register_GPQ[1] & 0x000000ff);	

				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0x99,0xEA,buf,1);
			
				data_bb = read_8207(0x99,0x05,2);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_GPQ[1]>>8;
				buf[1] = register_GPQ[1] & 0x000000ff;            
				write_8207(0x99,0x85,buf,2);				    //GPQ	
														
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0x99,0xEA,buf,1);	
			
}
void read_correctPF_C()
{
			int data_cc=0;
			uint8_t buf[32];
			active_power[2]=read_8207(0xAA,0x26,4);
			if(active_power[2] < 0)
				active_power[2] = ~active_power[2] + 1;	                     //有功功率值
				
			gpa[2] = -((active_power[2]*Kp-1320)/1320)/(1+(active_power[2]*Kp-1320)/1320);           //功率增益
			if(gpa[2]<0)
				register_GPQ[2] = gpa[2]*32768+65536;
			else
				register_GPQ[2] = gpa[2]*32768;	
			I2cWrite_2(50,register_GPQ[2]>>8);
			I2cWrite_2(51,register_GPQ[2] & 0x000000ff);		
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0xAA,0xEA,buf,1);
				
				data_cc = read_8207(0xAA,0x05,2);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_GPQ[2]>>8;
				buf[1] = register_GPQ[2] & 0x000000ff;            
				write_8207(0xAA,0x85,buf,2);				    //GPQ	
														
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0xAA,0xEA,buf,1);				
}

void read_correctPHxA()
{
		int data_aax=0;
	  uint8_t buf[32];
	  active_power[0]=read_8207(0x88,0x26,4);
	  if(active_power[0] < 0)
			active_power[0] = ~active_power[0] + 1;	                     //有功功率值	
		
		if(register_GPQ[0]>32768)
			P_value[0] = (float)(register_GPQ[0]-65536)/32768;             //归一化值
		else
			P_value[0] =(float)register_GPQ[0]/32768;	
			
		if((asin(-(active_power[0]*Kp*(1+P_value[0])-660)/660/1.732)/0.02)>0)                    //相位寄存器值
			register_Phs[0] = (asin(-(active_power[0]*Kp*(1+P_value[0])-660)/660/1.732)/0.02);
		else
			register_Phs[0] = (asin(-(active_power[0]*Kp*(1+P_value[0])-660)/660/1.732)/0.02) + 256;
		I2cWrite_2(52,register_Phs[0]);

				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0x88,0xEA,buf,1);
		
				data_aax = read_8207(0x88,0x07,1);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_Phs[0];           
				write_8207(0x88,0x87,buf,1);				    //Phs				
																
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0x88,0xEA,buf,1);		
		
}
void read_correctPHxB()
{
			int data_bbx=0;
	    uint8_t buf[32];
			active_power[1]=read_8207(0x99,0x26,4);
			if(active_power[1] < 0)
				active_power[1] = ~active_power[1] + 1;	                     //有功功率值	

			if(register_GPQ[1]>32768)
				P_value[1] = (float)(register_GPQ[1]-65536)/32768;             //归一化值
			else
				P_value[1] =(float)register_GPQ[1]/32768;	
				
			if((asin(-(active_power[1]*Kp*(1+P_value[1])-660)/660/1.732)/0.02)>0)                           //相位寄存器值
				register_Phs[1] = (asin(-(active_power[1]*Kp*(1+P_value[1])-660)/660/1.732)/0.02);
			else
				register_Phs[1] = (asin(-(active_power[1]*Kp*(1+P_value[1])-660)/660/1.732)/0.02) + 256;	
			I2cWrite_2(53,register_Phs[1]);	
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0x99,0xEA,buf,1);
			
				data_bbx = read_8207(0x99,0x07,1);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_Phs[1];           
				write_8207(0x99,0x87,buf,1);				    //Phs				
																
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0x99,0xEA,buf,1);				
}
void read_correctPHxC()
{
			int data_ccx=0;
			uint8_t buf[32];
			active_power[2]=read_8207(0xAA,0x26,4);
			if(active_power[2] < 0)
				active_power[2] = ~active_power[2] + 1;	                     //有功功率值	

			if(register_GPQ[2]>32768)
				P_value[2] = (float)(register_GPQ[2]-65536)/32768;             //归一化值
			else
				P_value[2] =(float)register_GPQ[2]/32768;	
				
			if((asin(-(active_power[2]*Kp*(1+P_value[2])-660)/660/1.732)/0.02)>0)                           //相位寄存器值
				register_Phs[2] = (asin(-(active_power[2]*Kp*(1+P_value[2])-660)/660/1.732)/0.02);
			else
				register_Phs[2] = (asin(-(active_power[2]*Kp*(1+P_value[2])-660)/660/1.732)/0.02) + 256;
			I2cWrite_2(54,register_Phs[1]);	
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xE5;            
				write_8207(0xAA,0xEA,buf,1);
			
				data_ccx = read_8207(0xAA,0x07,1);
			
				memset(buf,0,sizeof(char)*32);
				buf[0] = register_Phs[2];           
				write_8207(0xAA,0x87,buf,1);				    //Phs				
																
				memset(buf,0,sizeof(char)*32);
				buf[0] = 0xDC;               
				write_8207(0xAA,0xEA,buf,1);				
}
//交流校准  
void correct_ac_parameter(void)
{
			if(correct_flag_ac[0]==1)             //              校准
			{
					correct_flag_ac[0]=0;
					RN8207Check_A();
				  read_correctPF_A();
			}
			else if(correct_flag_phase_ac[0]==1)                  //PHxA                
			{
				read_correctPHxA();
				correct_flag_phase_ac[0] = 2;
										
			}
			if(LINE_NUM==3)
			{
						if(correct_flag_ac[1]==1)             //           校准
						{
								correct_flag_ac[1]=0;
								RN8207Check_B();
								read_correctPF_B();
						}
						else if(correct_flag_phase_ac[1]==1)               //PHxB                
						{		
							read_correctPHxB();
							correct_flag_phase_ac[1] = 2;
											
						}			
						if(correct_flag_ac[2]==1)             //                  校准
						{
								correct_flag_ac[2]=0;
								RN8207Check_C();
								read_correctPF_C();
						}			
						else if(correct_flag_phase_ac[2]==1)              //PHxC                  
						{	
							read_correctPHxC();
							correct_flag_phase_ac[2] = 2;					
						}						
			}
}
//直流校准
void correct_dc_parameter(void)
{
			if(register_offset_dc[0]==1)
			{			
					register_data_a[0] = read_8207(0x88,0x22,3);
					urms1[0] = read_8207(0x88,0x24,3);
					read_code_dc(register_data_a[0],urms1[0]);				
					register_offset_dc[0] = 2;
					beel(1);
			}
			else if(register_offset_dc[2]==1)
			{
					register_data_a[2] = read_8207(0x88,0x22,3);
					register_data_a[2] *= register_data_a[2];
					IARMSOS_offset(register_data_a[2]);
					register_offset_dc[2] = 2;
					beel(1);
			}
			else if(register_offset_dc[1]==1)
			{
					correct_dc();	
					register_offset_dc[1] = 2;				
			}
			else if(register_offset_dc[3]==1)
			{
					Preg_test[P_test] = read_8207(0x88,0x26,4);
					if(Preg_test[P_test] < 0)
						Preg_test[P_test] = ~Preg_test[P_test] + 1;	                     //有功功率值				
					if(P_test==4)
					{
						P_test=0;
						register_offset_dc[3]=2;
						register_data_a[3] = (Preg_test[0]+Preg_test[1]+Preg_test[2]+Preg_test[3]+Preg_test[4])/5;
						read_correctPF_dc(register_data_a[3]);
						beel(1);
					}
					P_test++;
			}	
}

void RN8207Read(void)
{
		uint8_t buf[32];
	
		if(cur_dc_ac==0)                        //dc
		{
				correct_dc_parameter(); //直流校准
			
				rn8207_read_l1();
				Kv = (double)220/dc_correct_v;
				Ki = (double)6/dc_correct_a;			
				Tvol[0][0] = VoltageA * Kv;                              //电压
				Tcur[0][0] = CurrentA * Ki*10;                           //电流
				active_power[3] = active_power[0] * Kp_dc;                  //有功功率		
				snmp_power[3] = active_power[3];
		}
		else                   //ac
		{	
				int test_hz=0;
				correct_ac_parameter();         //交流校准  			
			
				rn8207_read_l1();		
				Kv = (double)220/VoltageAK;
				Ki = (double)6/CurrentAK;
			  test_hz = read_8207(0x88,0x25,3);
				hzperHz[0] = (float)(3579545/8/(float)(read_8207(0x88,0x25,3)>>8))*10;       //频率
			  if(hzperHz[0]%10>5)hzperHz[0] = hzperHz[0]/10 + 1;
			  else hzperHz[0] = hzperHz[0]/10;
				Tvol[0][0] = VoltageA * Kv;                              //电压
				Tcur[0][0] = CurrentA * Ki*10;                           //电流
				active_power[0] = active_power[0] * Kp;                  //有功功率	
				snmp_power[0] = active_power[0];
			
				if(LINE_NUM==3)
				{
						rn8207_read_l2();
						Kv = (double)220/VoltageBK;
						Ki = (double)6/CurrentBK;
            test_hz = 0;					
						test_hz = read_8207(0x99,0x25,3);		
						hzperHz[1] = (float)(3579545/8/(float)(read_8207(0x99,0x25,3)>>8))*10;
						if(hzperHz[1]%10>5)hzperHz[1] = hzperHz[1]/10 + 1;
						else hzperHz[1] = hzperHz[1]/10;					
						Tvol[1][0] = VoltageB * Kv;
						Tcur[1][0] = CurrentB * Ki*10;
						active_power[1] = active_power[1] * Kp;	
						snmp_power[1] = active_power[1];
						
						rn8207_read_l3();
						Kv = (double)220/VoltageCK;
						Ki = (double)6/CurrentCK;		
            test_hz = 0;					
						test_hz = read_8207(0xAA,0x25,3);						
						hzperHz[2] = (float)(3579545/8/(float)(read_8207(0xAA,0x25,3)>>8))*10;
						if(hzperHz[2]%10>5)hzperHz[2] = hzperHz[2]/10 + 1;
						else hzperHz[2] = hzperHz[2]/10;						
						Tvol[2][0] = VoltageC * Kv;
						Tcur[2][0] = CurrentC * Ki*10;	
						active_power[2] = active_power[2] * Kp;
						snmp_power[2] = active_power[2];
				}				
		}
}

void Read_energy()
{
	
  if(cur_dc_ac==0)                             // dc
	{
			add_energy_dc = read_8207(0x88,0x29,3);
			mw_led_data[0] +=  add_energy_dc;
			save_energy_dc +=  add_energy_dc;
		  if(mw_led_data[0] >=1 )
			{
				mw_led_data[0] -= 1;
				mw_led = 1;
			}
			if(save_energy_dc >=5 )
			{
					save_energy_dc -= 5;			
					Energy8207_dc+=1;
					I2cWrite_2(65,Energy8207_dc/256/256%256);
					I2cWrite_2(66,Energy8207_dc/256%256);
					I2cWrite_2(67,Energy8207_dc%256);					
			}
		
	}
	else                                           //ac
	{
				add_energy_ac[0] = read_8207(0x88,0x29,3);
				mw_led_data[1] += add_energy_ac[0];
				save_energy_ac[0] +=  add_energy_ac[0] ;
				if(mw_led_data[1] >= 8)
				{
					mw_led_data[1] -= 8;
					mw_led = 1;
				}
				if(save_energy_ac[0] >= 160)
				{
						save_energy_ac[0] -= 160;			
						Energy8207[0]+=1;
						I2cWrite_2(0,Energy8207[0]/256/256%256);
						I2cWrite_2(1,Energy8207[0]/256%256);
						I2cWrite_2(2,Energy8207[0]%256);					
				}
	
					
///////////////////////////////////////////////////////////////////	
				if(LINE_NUM==3)
				{
				
						add_energy_ac[1] = read_8207(0x99,0x29,3);
						mw_led_data[2] += add_energy_ac[1];
						save_energy_ac[1] +=  add_energy_ac[1];
						if(mw_led_data[2] >= 8)
						{
							mw_led_data[2] -= 8;
							mw_led = 1;
						}

						if(save_energy_ac[1] >= 160)
						{
							save_energy_ac[1] -= 160;
							Energy8207[1]+=1;
							I2cWrite_2(3,Energy8207[1]/256/256%256);
							I2cWrite_2(4,Energy8207[1]/256%256);
							I2cWrite_2(5,Energy8207[1]%256);				
						}
										
						
/////////////////////////////////////////////////////////////////////	
						
						add_energy_ac[2] = read_8207(0xAA,0x29,3);
						mw_led_data[3] += add_energy_ac[2];
						save_energy_ac[2] += add_energy_ac[2];
						if(mw_led_data[3] >= 8)
						{
							mw_led_data[3] -= 8;
							mw_led = 1;
						}
						if(save_energy_ac[2] >= 160)
						{
							save_energy_ac[2] -= 160;
							Energy8207[2]+=1;
							I2cWrite_2(6,Energy8207[2]/256/256%256);
							I2cWrite_2(7,Energy8207[2]/256%256);
							I2cWrite_2(8,Energy8207[2]%256);				
						}						
					
			  }
	}
		
	if(mw_led==1)
	{
			mw_led=0;
			run_mw(1);   //mw
		  osDelayTask(200);	
	}		
	run_mw(0);
}












