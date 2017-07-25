#include <temhum.h>
#include "ip_info.h"
#define SCK  GPIO_Pin_8     
#define DATA GPIO_Pin_9  
#define GPIO_SCK GPIOC 
#define GPIO_DATA GPIOC

//#define SCK  GPIO_Pin_3     
//#define DATA GPIO_Pin_4  
//#define GPIO_SCK GPIOB 
//#define GPIO_DATA GPIOB


#define noACK 0             
#define ACK   1              
#define STATUS_REG_W 0x06   //000   0011    0  
#define STATUS_REG_R 0x07   //000   0011    1  
#define MEASURE_TEMP 0x03   //000   0001    1  
#define MEASURE_HUMI 0x05   //000   0010    1  
#define RESET        0x1e   //000   1111    0  

typedef union   
{ 
	uint16_t i;         
	float f;  
} value;

void Delay_temhum(u32 nCount)
{
		for(; nCount > 0; nCount--)
		{
		}
}

void set_data(char ch)
{
		if(ch)
			GPIO_SetBits(GPIO_DATA, DATA);
		else
			GPIO_ResetBits(GPIO_DATA, DATA);
}

void set_clk(char ch)
{
	if(ch)
		GPIO_SetBits(GPIO_SCK, SCK);
	else
		GPIO_ResetBits(GPIO_SCK, SCK);
}

void temhum_init()
{
		GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		
	
}

void s_transstart(void)
{    
		set_data(1);	//DATA=1,SCK=0    
		set_clk(0);                      //Initial state     
		Delay_temhum(100);     
		set_clk(1);// SCK=1;     
		Delay_temhum(100);      
		set_data(0);// DATA=0;     
		Delay_temhum(100);      
		set_clk(0);//SCK=0;       
		Delay_temhum(100); //_nop_();_nop_();_nop_();     
		set_clk(1);//SCK=1;     
		Delay_temhum(100);      
		set_data(1);//DATA=1;            
		Delay_temhum(100);     
		set_clk(0);//SCK=0;       
		Delay_temhum(100);
} 

void s_connectionreset(void)
{
		unsigned char i;     
		set_data(1);	 //DATA=1;   
		set_clk(0); // SCK=0;                      
		for(i=0;i<9;i++)           //9 SCK cycles    
		{     
				set_clk(1); //SCK=1;    
				Delay_temhum(10);    
				set_clk(0);//SCK=0;     
				Delay_temhum(10);   
		}    
		s_transstart();
}

char s_write_byte(unsigned char value)
{
		unsigned char i, wrong=0;    
		set_clk(0);                  //??????	   ?9????????????     
		Delay_temhum(10);
		for (i=0x80;i>0;i/=2)                         //shift bit for masking    
		{       
				if (i & value) 
						set_data(1);     //???      
				else 
						set_data(0);  	                           
				set_clk(1);                    //clk for SENSI-BUS     
				Delay_temhum(10);          
				set_clk(0);	 
				Delay_temhum(10);
		}    
		set_data(1);    
		Delay_temhum(10);     
		set_clk(1);	                    //??????	   ?9??????????????????   
		Delay_temhum(10);    
		wrong=GPIO_ReadInputDataBit(GPIO_DATA, DATA);   
		Delay_temhum(10);    
		set_clk(0);                  //??????	   ?9????????????     
		Delay_temhum(10);      
		set_data(1); 				   //?????   
		return wrong;                                //error=1 in case of no acknowledge //??:0??,1?? 
}

char s_read_byte(unsigned char ack) 
{
		unsigned char i,val=0;
  
		Delay_temhum(10);
		set_data(1);                                       //release DATA-line    
		Delay_temhum(10);
		set_clk(0); 
		Delay_temhum(10);
		for (i=0x80;i>0;i/=2)                
		{      
				set_clk(1);                                           
				Delay_temhum(500);                        							  //??????????????     
				if (GPIO_ReadInputDataBit(GPIO_DATA, DATA)) 
						val=(val | i);        //???   	      	
				Delay_temhum(10);                                                    //???? 3 us     
				set_clk(0);                 
		}    
		Delay_temhum(10);													  //?8?????????   
		if(ack==1) 
				set_data(0);                     //in case of "ack==1" pull down DATA-Line    
		else  
				set_data(1);                            //?????(ack==0),????????   
		Delay_temhum(10);                                                  //pulswith approx 3 us    
		set_clk(1);                                   //?9????   
		Delay_temhum(10);                                                  //pulswith approx 3 us    
		set_clk(0);                 				  //?9????   Delay(30);            
		set_data(1);   
		Delay_temhum(10);
		return val; 
}

char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode)
{
		unsigned char wrong=0;    
		unsigned int i;       
		s_transstart();                                                  //transmission start    
		Delay_temhum(10);   
		switch(mode)    
		{                                                              //send command to sensor     
				case 0  : 
						wrong+=s_write_byte(MEASURE_TEMP); 
						break;     
				case 1  : 
						wrong+=s_write_byte(MEASURE_HUMI); 
						break;     
				default : 
						break;        
		}    
		for (i=0;i<500;i++)     
		{
				Delay_temhum(10);     
				if(GPIO_ReadInputDataBit(GPIO_DATA, DATA)==0) 
					break;		          // ???????    
		}    
		Delay_temhum(0x8fffff);   
		if(GPIO_ReadInputDataBit(GPIO_DATA, DATA)) 
			wrong+=1;                // or timeout (~2 sec.) is reached       
		*(p_value+1)=s_read_byte(ACK);	//????    
		*(p_value)  =s_read_byte(ACK);    //????                                     
		*p_checksum =s_read_byte(noACK);  //read checksum    
		return wrong;  
}
void calc_sht10(float *p_humidity ,float *p_temperature)
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

void  Temperatuer()
{
		unsigned char w = 0; 	
		value humi_val,temp_val;     
		unsigned char checksum; 
		temhum_init();
		s_connectionreset();               
		Delay_temhum(0x3ff);     //??0.2s      
		w += s_measure((unsigned char*) &humi_val.i,&checksum,1);  //measure humidity      
		w += s_measure((unsigned char*) &temp_val.i,&checksum,0);  //measure temperature      
		if( w != 0 )   	 
		{ 	 
			s_connectionreset();                        //in case of an error: connection reset       
		} 	
		else       
		{ 	 
			humi_val.f=(float)humi_val.i;                   //converts integer to float      
			temp_val.f=(float)temp_val.i;                   //converts integer to float      
			calc_sht10(&humi_val.f,&temp_val.f);            //calculate humidity, temperature      
		}  
		if(GPIO_ReadInputDataBit(GPIO_DATA, DATA)) 
		{	
				tem[0]=temp_val.f; 	
				hum[0]=humi_val.f;
		}
		else
		{
				tem[0]=0; 	
				hum[0]=0;
		}	
}
