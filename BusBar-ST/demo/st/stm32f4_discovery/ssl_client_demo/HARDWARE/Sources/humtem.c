#include <humtem.h>
#include "ip_info.h"

#define Sck  GPIO_Pin_3     
#define Data GPIO_Pin_4  
#define GPIO_Sck GPIOB 
#define GPIO_Data GPIOB

#define noaCK 0             
#define aCK   1              
#define STATUS_REG_w 0x06   //000   0011    0  
#define STATUS_REG_r 0x07   //000   0011    1  
#define MEASURE_temp 0x03   //000   0001    1  
#define MEASURE_humi 0x05   //000   0010    1  
#define REset        0x1e   //000   1111    0  

typedef union   
{ 
	uint16_t i;         
	float f;  
} v_alue;

void Delay_temhum1(u32 nCount)
{
		for(; nCount > 0; nCount--)
		{
		}
}

void set_data1(char ch)
{
		if(ch)
			GPIO_SetBits(GPIO_Data, Data);
		else
			GPIO_ResetBits(GPIO_Data, Data);
}

void set_clk1(char ch)
{
	if(ch)
		GPIO_SetBits(GPIO_Sck, Sck);
	else
		GPIO_ResetBits(GPIO_Sck, Sck);
}

void temhum_init1()
{	
		
		GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
}

void s_transstart1(void)
{    
		set_data1(1);	//DATA=1,SCK=0    
		set_clk1(0);                      //Initial state     
		Delay_temhum1(100);     
		set_clk1(1);// SCK=1;     
		Delay_temhum1(100);      
		set_data1(0);// DATA=0;     
		Delay_temhum1(100);      
		set_clk1(0);//SCK=0;       
		Delay_temhum1(100); //_nop_();_nop_();_nop_();     
		set_clk1(1);//SCK=1;     
		Delay_temhum1(100);      
		set_data1(1);//DATA=1;            
		Delay_temhum1(100);     
		set_clk1(0);//SCK=0;       
		Delay_temhum1(100);
} 

void s_connectionreset1(void)
{
		unsigned char i;     
		set_data1(1);	 //DATA=1;   
		set_clk1(0); // SCK=0;                      
		for(i=0;i<9;i++)           //9 SCK cycles    
		{     
				set_clk1(1); //SCK=1;    
				Delay_temhum1(10);    
				set_clk1(0);//SCK=0;     
				Delay_temhum1(10);   
		}    
		s_transstart1();
}

char s_write_byte1(unsigned char value)
{
		unsigned char i, wrong=0;    
		set_clk1(0);                  //??????	   ?9????????????     
		Delay_temhum1(10);
		for (i=0x80;i>0;i/=2)                         //shift bit for masking    
		{       
				if (i & value) 
						set_data1(1);     //???      
				else 
						set_data1(0);  	                           
				set_clk1(1);                    //clk for SENSI-BUS     
				Delay_temhum1(10);          
				set_clk1(0);	 
				Delay_temhum1(10);
		}    
		set_data1(1);    
		Delay_temhum1(10);     
		set_clk1(1);	                    //??????	   ?9??????????????????   
		Delay_temhum1(10);    
		wrong=GPIO_ReadInputDataBit(GPIO_Data, Data);   
		Delay_temhum1(10);    
		set_clk1(0);                  //??????	   ?9????????????     
		Delay_temhum1(10);      
		set_data1(1); 				   //?????   
		return wrong;                                //error=1 in case of no acknowledge //??:0??,1?? 
}

char s_read_byte1(unsigned char ack) 
{
		unsigned char i,val=0;
  
		Delay_temhum1(10);
		set_data1(1);                                       //release DATA-line    
		Delay_temhum1(10);
		set_clk1(0); 
		Delay_temhum1(10);
		for (i=0x80;i>0;i/=2)                
		{      
				set_clk1(1);                                           
				Delay_temhum1(500);                        							  //??????????????     
				if (GPIO_ReadInputDataBit(GPIO_Data, Data)) 
						val=(val | i);        //???   	      	
				Delay_temhum1(10);                                                    //???? 3 us     
				set_clk1(0);                 
		}    
		Delay_temhum1(10);													  //?8?????????   
		if(ack==1) 
				set_data1(0);                     //in case of "ack==1" pull down DATA-Line    
		else  
				set_data1(1);                            //?????(ack==0),????????   
		Delay_temhum1(10);                                                  //pulswith approx 3 us    
		set_clk1(1);                                   //?9????   
		Delay_temhum1(10);                                                  //pulswith approx 3 us    
		set_clk1(0);                 				  //?9????   Delay(30);            
		set_data1(1);   
		Delay_temhum1(10);
		return val; 
}

char s_measure1(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode)
{
		unsigned char wrong=0;    
		unsigned int i;       
		s_transstart1();                                                  //transmission start    
		Delay_temhum1(10);   
		switch(mode)    
		{                                                              //send command to sensor     
				case 0  : 
						wrong+=s_write_byte1(MEASURE_temp); 
						break;     
				case 1  : 
						wrong+=s_write_byte1(MEASURE_humi); 
						break;     
				default : 
						break;        
		}    
		for (i=0;i<500;i++)     
		{
				Delay_temhum1(10);     
				if(GPIO_ReadInputDataBit(GPIO_Data, Data)==0) 
					break;		          // ???????    
		}    
		Delay_temhum(0x8fffff);   
		if(GPIO_ReadInputDataBit(GPIO_Data, Data)) 
			wrong+=1;                // or timeout (~2 sec.) is reached       
		*(p_value+1)=s_read_byte1(aCK);	//????    
		*(p_value)  =s_read_byte1(aCK);    //????                                     
		*p_checksum =s_read_byte1(noaCK);  //read checksum    
		return wrong;  
}
void calc_sht101(float *p_humidity ,float *p_temperature)
{
	const float C1=-4.0;              // for 12 Bit   //	const float C1=-2.0468;             // for 12 Bit //
	const float C2=+0.0405;           // for 12 Bit   //	const float C2=+0.0367;             // for 12 Bit //
	const float C3=-0.0000028;        // for 12 Bit  //	const float C3=-0.0000015955;       // for 12 Bit     
	const float T1=+0.01;             // for 14 Bit @ 5V   
	const float T2=+0.00008;          // for 14 Bit @ 5V     
	float rh=*p_humidity;             // rh:      Humidity [Ticks] 12 Bit    
	float t=*p_temperature;           // t:       Temperature [Ticks] 14 Bit   
	float rh_lin;                     // rh_lin:  Humidity linear   
	float rh_true;                    // rh_true: Temperature compensated humidity   
	float t_C;                        // t_C   :  Temperature [C]    
	t_C=(t/10 - 396)/10;                  //calc. temperature from ticks to [C]   
	rh_lin=C3*rh*rh + C2*rh + C1;     //calc. humidity from ticks to [%RH]   
	rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;   //calc. temperature compensated humidity [%RH]   //if(rh_true>100)rh_true=100;       //cut if the value is outside of   //if(rh_true<0.1)rh_true=0.1;       //the physical possible range    
	*p_temperature=t_C;               //return temperature [C]   
	*p_humidity=rh_true;          
	//return humidity[%RH] 
}

void  Temperatuer1()
{
		unsigned char w = 0; 	
		v_alue humi_val,temp_val;     
		unsigned char checksum; 
		temhum_init1();
		s_connectionreset1();               
		Delay_temhum1(0x3ff);     //??0.2s      
		w += s_measure1((unsigned char*) &humi_val.i,&checksum,1);  //measure humidity      
		w += s_measure1((unsigned char*) &temp_val.i,&checksum,0);  //measure temperature      
		if( w != 0 )   	 
		{ 	 
			s_connectionreset1();                        //in case of an error: connection reset       
		} 	
		else       
		{ 	 
			humi_val.f=(float)humi_val.i;                   //converts integer to float      
			temp_val.f=(float)temp_val.i;                   //converts integer to float      
			calc_sht101(&humi_val.f,&temp_val.f);            //calculate humidity, temperature      
		}  
		if(GPIO_ReadInputDataBit(GPIO_Data, Data)) 
		{	
//				tem[1][0]=temp_val.f; 	
//				hum[1][0]=humi_val.f;
		}
		else
		{
//				tem[1][0]=0; 	
//				hum[1][0]=0;
		}	
}
