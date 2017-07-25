//#include "lcd.h"
//#include "font.h"
//#include <stdio.h>
//#include <stdlib.h>

////����LCD��Ҫ����
////Ĭ��Ϊ����
//_lcd_dev lcddev;

////������ɫ,������ɫ
//u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
//u16 DeviceCode;	 


//void DelayNop_lcd(int rm)
//{
//		int i=0;
//		for(i=0;i<rm;i++)
//		{
//		}
//}

////******************************************************************
////��������  LCD_Reset
////���ܣ�    LCD��λ������Һ����ʼ��ǰҪ���ô˺���
////�����������
////����ֵ��  ��
////�޸ļ�¼����
////******************************************************************
//void LCD_RESET(void)
//{
//	TFT_REST(1);          //  RST = 0
//	DelayNop_lcd(100);	
//	TFT_REST(0);            // RST = 1
//	DelayNop_lcd(50);
//}

////******************************************************************
////��������  LCD_WR_REG
////���ܣ�    ��Һ��������д��д16λָ��
////���������Reg:��д���ָ��ֵ
////����ֵ��  ��
////�޸ļ�¼����
////******************************************************************
//void LCD_WR_REG(u16 data)
//{ 
//   TFT_CS(1);            // CS=0
//	 TFT_RS(1);            // RS=0:	дָ��
//   TFT_SCK(1);             // SCK=0
//#if USE_HARDWARE_SPI   
//   SPI3_ReadWriteByte(data);
//#else
//   SPIv_WriteData(data);
//#endif 
//	 DelayNop_lcd(120);
//   TFT_SCK(0);               //CS=1
//}

////******************************************************************
////��������  LCD_WR_DATA
////���ܣ�    ��Һ��������д��д8λ����
////���������Data:��д�������
////����ֵ��  ��
////�޸ļ�¼����
////******************************************************************
//void LCD_WR_DATA(u8 data)
//{
//	
//   TFT_CS(1);            // CS=0
//	 TFT_RS(0);            // RS=1:	д����
//#if USE_HARDWARE_SPI   
//   SPI3_ReadWriteByte(data);
//#else
//   SPIv_WriteData(data);
//#endif 
//	 DelayNop_lcd(120);
//   TFT_SCK(0);            // CS=1
//}

////******************************************************************
////��������  LCD_WriteReg
////���ܣ�    д�Ĵ�������
////���������LCD_Reg:�Ĵ�����ַ
////			LCD_RegValue:Ҫд�������
////����ֵ��  ��
////�޸ļ�¼����
////******************************************************************
//void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
//{	
//	LCD_WR_REG(LCD_Reg);  
//	LCD_WR_DATA(LCD_RegValue);	    		 
//}

////******************************************************************
////��������  LCD_WriteRAM_Prepare
////���ߣ�    xiao��@ȫ������
////���ڣ�    2013-02-22
////���ܣ�    ��ʼдGRAM
////			�ڸ�Һ��������RGB����ǰ��Ӧ�÷���дGRAMָ��
////�����������
////����ֵ��  ��
////�޸ļ�¼����
////******************************************************************
//void LCD_WriteRAM_Prepare(void)
//{
//	LCD_WR_REG(lcddev.wramcmd);
//}	

////******************************************************************
////��������  LCD_DrawPoint_16Bit
////���ܣ�    8λ���������д��һ��16λ����
////���������(x,y):�������
////����ֵ��  ��
////�޸ļ�¼����
////******************************************************************
//void LCD_WR_DATA_16Bit(u16 data)
//{	
//   TFT_CS(1);             //  CS=0
//   TFT_RS(0);							// RS=1
//#if USE_HARDWARE_SPI   
//   SPI3_ReadWriteByte(data>>8);
//   SPI3_ReadWriteByte(data);
//#else
//   SPIv_WriteData(data>>8);
//   SPIv_WriteData(data);
//#endif 
//   TFT_CS(0);                // CS=1
//}

////����LCD����
////������к�����ģʽ�л�
//void LCD_SetParam(void)
//{ 	
//	lcddev.wramcmd=0x2C;
//#if USE_HORIZONTAL==1	//ʹ�ú���	  
//	lcddev.dir=1;//����
//	lcddev.width=128;
//	lcddev.height=128;
//	lcddev.setxcmd=0x2A;            //����x����ָ��
//	lcddev.setycmd=0x2B;			     //����Y����ָ��
//	LCD_WriteReg(0x36,0xA8);

//#else//����
//	lcddev.dir=0;//����				 	 		
//	lcddev.width=128;
//	lcddev.height=128;
//	lcddev.setxcmd=0x2A;
//	lcddev.setycmd=0x2B;	
//	LCD_WriteReg(0x36,0xC8);
//#endif
//}


////******************************************************************
////��������  LCD_Init
////���ܣ�    LCD��ʼ��
////�����������
////����ֵ��  ��
////�޸ļ�¼����
////******************************************************************
//void LCD_Init(void)
//{  
//	
//#if USE_HARDWARE_SPI //ʹ��Ӳ��SPI
//	SPI3_Init();
//	SPI3_SetSpeed(SPI_BaudRatePrescaler_16);		//����Ϊ42Mʱ��,����ģʽ 
//#else	
//	LCD_GPIOInit();//ʹ��ģ��SPI
//#endif  

//	LCD_RESET(); //Һ������λ	

//	//************* Start Initial Sequence **********//		
//	//��ʼ��ʼ��Һ����
//	LCD_WR_REG(0x11);//Sleep exit 
////	DelayNop_lcd(120);		
//	//ST7735S Frame Rate
//	LCD_WR_REG(0xB1); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 

//	LCD_WR_REG(0xB2); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 

//	LCD_WR_REG(0xB3); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x05); 
//	LCD_WR_DATA(0x3C); 
//	LCD_WR_DATA(0x3C); 
//	
//	LCD_WR_REG(0xB4); //Column inversion 
//	LCD_WR_DATA(0x03); 
//	
//	//ST7735S Power Sequence
//	LCD_WR_REG(0xC0); 
//	LCD_WR_DATA(0x28); 
//	LCD_WR_DATA(0x08); 
//	LCD_WR_DATA(0x04); 
//	
//	LCD_WR_REG(0xC1); 
//	LCD_WR_DATA(0xC0); 

//	LCD_WR_REG(0xC2); 
//	LCD_WR_DATA(0x0D); 
//	LCD_WR_DATA(0x00); 

//	LCD_WR_REG(0xC3); 
//	LCD_WR_DATA(0x8D); 
//	LCD_WR_DATA(0x2A); 
//	
//	LCD_WR_REG(0xC4); 
//	LCD_WR_DATA(0x8D); 
//	LCD_WR_DATA(0xEE); 
//	
//	LCD_WR_REG(0xC5); //VCOM 
//	LCD_WR_DATA(0x1A); 
//	
//	LCD_WR_REG(0x36); //MX, MY, RGB mode 				 
//	LCD_WR_DATA(0x08); 
//	
//	//ST7735S Gamma Sequence
//	LCD_WR_REG(0xe0); 
//	LCD_WR_DATA(0x04); 
//	LCD_WR_DATA(0x22); 
//	LCD_WR_DATA(0x07); 
//	LCD_WR_DATA(0x0A); 
//	LCD_WR_DATA(0x2E); 
//	LCD_WR_DATA(0x30); 
//	LCD_WR_DATA(0x25); 
//	LCD_WR_DATA(0x2A); 
//	LCD_WR_DATA(0x28); 
//	LCD_WR_DATA(0x26); 
//	LCD_WR_DATA(0x2E); 
//	LCD_WR_DATA(0x3A); 
//	LCD_WR_DATA(0x00); 	
//	LCD_WR_DATA(0x01); 
//	LCD_WR_DATA(0x03); 
//	LCD_WR_DATA(0x13); 

//	LCD_WR_REG(0xe1); 
//	LCD_WR_DATA(0x04); 
//	LCD_WR_DATA(0x16); 
//	LCD_WR_DATA(0x06); 
//	LCD_WR_DATA(0x0D); 
//	LCD_WR_DATA(0x2D); 
//	LCD_WR_DATA(0x26); 
//	LCD_WR_DATA(0x23); 
//	LCD_WR_DATA(0x27); 
//	LCD_WR_DATA(0x27); 
//	LCD_WR_DATA(0x25); 
//	LCD_WR_DATA(0x2D); 
//	LCD_WR_DATA(0x3B); 
//	LCD_WR_DATA(0x00); 
//	LCD_WR_DATA(0x01); 
//	LCD_WR_DATA(0x04); 
//	LCD_WR_DATA(0x13);  
//		
//	LCD_WR_REG(0x3A); //65k mode 
//	LCD_WR_DATA(0x05); 	
//	LCD_WR_REG(0x29);//Display on	

//	LCD_SetParam();//����LCD����	 
//	TFT_LEDA(0);   //��������	  LEDA = 1
//	
//}

///*************************************************
//��������LCD_SetWindows
//���ܣ�����lcd��ʾ���ڣ��ڴ�����д�������Զ�����
//��ڲ�����xy�����յ�
//����ֵ����
//*************************************************/
//void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
//{
//#if USE_HORIZONTAL==1	//ʹ�ú���
//	LCD_WR_REG(lcddev.setxcmd);	
//	LCD_WR_DATA(xStar>>8);
//	LCD_WR_DATA(0x00FF&xStar+3);		
//	LCD_WR_DATA(xEnd>>8);
//	LCD_WR_DATA(0x00FF&xEnd+3);

//	LCD_WR_REG(lcddev.setycmd);	
//	LCD_WR_DATA(yStar>>8);
//	LCD_WR_DATA(0x00FF&yStar+2);		
//	LCD_WR_DATA(yEnd>>8);
//	LCD_WR_DATA(0x00FF&yEnd+2);	

//#else
//	
//	LCD_WR_REG(lcddev.setxcmd);	
//	LCD_WR_DATA(xStar>>8);
//	LCD_WR_DATA(0x00FF&xStar+2);		
//	LCD_WR_DATA(xEnd>>8);
//	LCD_WR_DATA(0x00FF&xEnd+2);

//	LCD_WR_REG(lcddev.setycmd);	
//	LCD_WR_DATA(yStar>>8);
//	LCD_WR_DATA(0x00FF&yStar+3);		
//	LCD_WR_DATA(yEnd>>8);
//	LCD_WR_DATA(0x00FF&yEnd+3);	
//#endif

//	LCD_WriteRAM_Prepare();	//��ʼд��GRAM				
//} 


//void LCD_Clear(u16 Color)
//{
//	u16 i,j;      
//	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	  
//	for(i=0;i<lcddev.width;i++)
//	{
//		for(j=0;j<lcddev.height;j++)
//		LCD_WR_DATA_16Bit(Color);	//д������ 	 
//	}
//} 

/********************************************************************************************************************************************************/
/********************************************************************************************************************************************************/
#include "LCD.h" 
#include "font.h"
#include <stdio.h>
#include <stdlib.h>

/*********************************
PB3 -- SCL
PB5 -- SDA
PB6 -- RS
PB7 -- RES
PD4 -- CS
PE5 -- LEDA
**********************************/

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

lcd *_lcd_gram ;
lcd *_gram_lcd ;


//������ɫ,������ɫ
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	

//�����Դ浽LCD		 
void LCD_Refresh_Gram(u8 select)
{
	u8 i,n;	
	
	if(select==1)
	{
			for(i=0;i<128;i++)  
			{   
				for(n=0;n<128;n++)
				{
					LCD_WR_DATA_16Bit(_lcd_gram->lcd_gram[n][i]);
				}
			}	
			vPortFree(_lcd_gram);
	 }
	 else if(select==2)
	 {
			for(i=0;i<128;i++)  
			{   
				for(n=0;n<128;n++)
				{
					LCD_WR_DATA_16Bit(_gram_lcd->lcd_gram[n][i]);
				}
			}
			vPortFree(_gram_lcd);
	 }
   	
}



void DelayNop_lcd(int rm)
{
		int i=0;
		for(i=0;i<rm;i++)
		{
		}
}

//******************************************************************
//��������  LCD_Reset
//���ܣ�    LCD��λ������Һ����ʼ��ǰҪ���ô˺���
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_RESET(void)
{
	TFT_REST(1);          //  RST = 0
	DelayNop_lcd(100);	
	TFT_REST(0);            // RST = 1
	DelayNop_lcd(50);
}


//******************************************************************
//��������  LCD_WR_REG
//���ܣ�    ��Һ��������д��д16λָ��
//���������Reg:��д���ָ��ֵ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WR_REG(u16 data)
{ 
   TFT_CS(1);            // CS=0
	 TFT_RS(1);            // RS=0:	дָ��
   TFT_SCK(1);             // SCK=0
#if USE_HARDWARE_SPI   
   SPI3_ReadWriteByte(data);
#else
   SPIv_WriteData(data);
#endif 
	 DelayNop_lcd(120);
   TFT_SCK(0);               //CS=1
}

//******************************************************************
//��������  LCD_WR_DATA
//���ܣ�    ��Һ��������д��д8λ����
//���������Data:��д�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WR_DATA(u8 data)
{
	
   TFT_CS(1);            // CS=0
	 TFT_RS(0);            // RS=1:	д����
#if USE_HARDWARE_SPI   
   SPI3_ReadWriteByte(data);
#else
   SPIv_WriteData(data);
#endif 
	 DelayNop_lcd(120);
   TFT_SCK(0);            // CS=1

}

//******************************************************************
//��������  LCD_WriteReg
//���ܣ�    д�Ĵ�������
//���������LCD_Reg:�Ĵ�����ַ
//			LCD_RegValue:Ҫд�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}

//******************************************************************
//��������  LCD_WriteRAM_Prepare
//���ܣ�    ��ʼдGRAM
//			�ڸ�Һ��������RGB����ǰ��Ӧ�÷���дGRAMָ��
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

//******************************************************************
//��������  LCD_DrawPoint_16Bit
//���ܣ�    8λ���������д��һ��16λ����
//���������(x,y):�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WR_DATA_16Bit(u16 data)
{	
   TFT_CS(1);             //  CS=0
   TFT_RS(0);							// RS=1
#if USE_HARDWARE_SPI   
   SPI3_ReadWriteByte(data>>8);
   SPI3_ReadWriteByte(data);
#else
   SPIv_WriteData(data>>8);
   SPIv_WriteData(data);
#endif 
   TFT_CS(0);                // CS=1
}

/*************************************************
��������LCD_SetCursor
���ܣ����ù��λ��
��ڲ�����xy����
����ֵ����
*************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);
} 

//����LCD����
//������к�����ģʽ�л�
void LCD_SetParam(void)
{ 	
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//ʹ�ú���	  
	lcddev.dir=1;//����
	lcddev.width=128;
	lcddev.height=128;
	lcddev.setxcmd=0x2A;            //����x����ָ��
	lcddev.setycmd=0x2B;			     //����Y����ָ��
	LCD_WriteReg(0x36,0xA8);

#else//����
	lcddev.dir=0;//����				 	 		
	lcddev.width=128;
	lcddev.height=128;
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;	
	LCD_WriteReg(0x36,0xC8);
#endif
}	


//******************************************************************
//��������  LCD_DrawPoint
//���ܣ�    ��ָ��λ��д��һ�����ص�����
//���������(x,y):�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//���ù��λ�� 
//	LCD_WR_DATA_16Bit(RED);
//	_lcd_gram->lcd_gram[x][y]=RED;
}



//******************************************************************
//��������  LCD_Init
//���ܣ�    LCD��ʼ��
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_Init(void)
{  
	
#if USE_HARDWARE_SPI //ʹ��Ӳ��SPI
	SPI3_Init();
	SPI3_SetSpeed(SPI_BaudRatePrescaler_2);		//����Ϊ42Mʱ��,����ģʽ 
#else	
	LCD_GPIOInit();//ʹ��ģ��SPI
#endif  

	LCD_RESET(); //Һ������λ	

	//************* Start Initial Sequence **********//		
	//��ʼ��ʼ��Һ����
	LCD_WR_REG(0x11);//Sleep exit 
//	DelayNop_lcd(120);		
	//ST7735S Frame Rate
	LCD_WR_REG(0xB1); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 

	LCD_WR_REG(0xB2); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 

	LCD_WR_REG(0xB3); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x3C); 
	
	LCD_WR_REG(0xB4); //Column inversion 
	LCD_WR_DATA(0x03); 
	
	//ST7735S Power Sequence
	LCD_WR_REG(0xC0); 
	LCD_WR_DATA(0x28); 
	LCD_WR_DATA(0x08); 
	LCD_WR_DATA(0x04); 
	
	LCD_WR_REG(0xC1); 
	LCD_WR_DATA(0xC0); 

	LCD_WR_REG(0xC2); 
	LCD_WR_DATA(0x0D); 
	LCD_WR_DATA(0x00); 

	LCD_WR_REG(0xC3); 
	LCD_WR_DATA(0x8D); 
	LCD_WR_DATA(0x2A); 
	
	LCD_WR_REG(0xC4); 
	LCD_WR_DATA(0x8D); 
	LCD_WR_DATA(0xEE); 
	
	LCD_WR_REG(0xC5); //VCOM 
	LCD_WR_DATA(0x1A); 
	
	LCD_WR_REG(0x36); //MX, MY, RGB mode 				 
	LCD_WR_DATA(0x08); 
	
	//ST7735S Gamma Sequence
	LCD_WR_REG(0xe0); 
	LCD_WR_DATA(0x04); 
	LCD_WR_DATA(0x22); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x0A); 
	LCD_WR_DATA(0x2E); 
	LCD_WR_DATA(0x30); 
	LCD_WR_DATA(0x25); 
	LCD_WR_DATA(0x2A); 
	LCD_WR_DATA(0x28); 
	LCD_WR_DATA(0x26); 
	LCD_WR_DATA(0x2E); 
	LCD_WR_DATA(0x3A); 
	LCD_WR_DATA(0x00); 	
	LCD_WR_DATA(0x01); 
	LCD_WR_DATA(0x03); 
	LCD_WR_DATA(0x13); 

	LCD_WR_REG(0xe1); 
	LCD_WR_DATA(0x04); 
	LCD_WR_DATA(0x16); 
	LCD_WR_DATA(0x06); 
	LCD_WR_DATA(0x0D); 
	LCD_WR_DATA(0x2D); 
	LCD_WR_DATA(0x26); 
	LCD_WR_DATA(0x23); 
	LCD_WR_DATA(0x27); 
	LCD_WR_DATA(0x27); 
	LCD_WR_DATA(0x25); 
	LCD_WR_DATA(0x2D); 
	LCD_WR_DATA(0x3B); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x01); 
	LCD_WR_DATA(0x04); 
	LCD_WR_DATA(0x13);  
		
	LCD_WR_REG(0x3A); //65k mode 
	LCD_WR_DATA(0x05); 	
	LCD_WR_REG(0x29);//Display on	

	LCD_SetParam();//����LCD����	 
	TFT_LEDA(0);   //��������	  LEDA = 1

	LCD_Clear(CYAN,1); 
	LCD_Refresh_Gram(1);
	
}

/*************************************************
��������LCD_SetWindows
���ܣ�����lcd��ʾ���ڣ��ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
#if USE_HORIZONTAL==1	//ʹ�ú���
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar+3);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd+3);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar+2);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd+2);	

#else
	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar+2);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd+2);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar+3);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd+3);	
#endif

	LCD_WriteRAM_Prepare();	//��ʼд��GRAM				
}  

/******************************************* GUI  ******************************************************************/


//******************************************************************
//��������  GUI_DrawPoint
//���ܣ�    GUI���һ����
//���������x:���λ��x����
//        	y:���λ��y����
//			color:Ҫ������ɫ
//			select:ѡ����Ӧ��������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void GUI_DrawPoint(u16 x,u16 y,u16 color,u8 select)
{
	LCD_SetCursor(x,y);//���ù��λ�� 
	if(select==1)
		_lcd_gram->lcd_gram[x][y]=color;
	else if(select==2)
	  _gram_lcd->lcd_gram[x][y]=color;
}


//******************************************************************
//��������  LCD_Clear
//���ܣ�    LCDȫ�������������
//���������Color:Ҫ���������ɫ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_Clear(u16 Color,u8 select)
{
	u16 i,j; 

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
	if(select==1)
	{
		_lcd_gram=(lcd *) pvPortMalloc(sizeof(lcd));   //���붯̬�ڴ�		
		for(i=0;i<lcddev.width;i++)
		{
			for(j=0;j<lcddev.height ;j++)
				_lcd_gram->lcd_gram[i][j]=Color;
		}	
	}
	else if(select==2)
	{
		_gram_lcd=(lcd *) pvPortMalloc(sizeof(lcd));  //���붯̬�ڴ�
		for(i=0;i<lcddev.width;i++)
		{		
			for(j=0;j<lcddev.height ;j++)
				_gram_lcd->lcd_gram[i][j]=Color;
		}		
	}

}

//******************************************************************
//��������  LCD_DrawLine
//���ܣ�    ����
//���������x1,y1:�������
//        	x2,y2:�յ����� 
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color,u8 select)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)
		incx=1; //���õ������� 
	else if(delta_x==0)
		incx=0;//��ֱ�� 
	else 
	{
		incx=-1;
		delta_x=-delta_x;
	} 
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//ˮƽ�� 
	else
	{
		incy=-1;
		delta_y=-delta_y;
	} 
	if( delta_x>delta_y)
		distance=delta_x; //ѡȡ�������������� 
	else 
		distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		GUI_DrawPoint(uRow,uCol,color,select);  //���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

//******************************************************************
//��������  LCD_DrawRectangle
//���ܣ�    ������(�����)
//���������(x1,y1),(x2,y2):���εĶԽ�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color,u8 select)
{
	LCD_DrawLine(x1,y1,x2,y1,color,select);
	LCD_DrawLine(x1,y1,x1,y2,color,select);
	LCD_DrawLine(x1,y2,x2,y2,color,select);
	LCD_DrawLine(x2,y1,x2,y2,color,select);
} 

//******************************************************************
//��������  LCD_DrawFillRectangle
//���ܣ�    GUI������(���)
//���������(x1,y1),(x2,y2):���εĶԽ�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************   
void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color,u8 select)
{
//	LCD_Fill(x1,y1,x2,y2,color,select);

}

//******************************************************************
//��������  _draw_circle_8

//���ܣ�    8�Գ��Ի�Բ�㷨(�ڲ�����)
//���������(xc,yc) :Բ��������
// 			(x,y):��������Բ�ĵ�����
//         	c:������ɫ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void _draw_circle_8(int xc, int yc, int x, int y, u16 c,u8 select)
{
	GUI_DrawPoint(xc + x, yc + y, c, select);

	GUI_DrawPoint(xc - x, yc + y, c, select);

	GUI_DrawPoint(xc + x, yc - y, c, select);

	GUI_DrawPoint(xc - x, yc - y, c, select);

	GUI_DrawPoint(xc + y, yc + x, c, select);

	GUI_DrawPoint(xc - y, yc + x, c, select);

	GUI_DrawPoint(xc + y, yc - x, c, select);

	GUI_DrawPoint(xc - y, yc - x, c, select);
}

//******************************************************************
//��������  gui_circle
//���ܣ�    ��ָ��λ�û�һ��ָ����С��Բ(���)
//���������(xc,yc) :Բ��������
//         	c:������ɫ
//		 	r:Բ�뾶
//		 	fill:����жϱ�־��1-��䣬0-�����
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void gui_circle(int xc, int yc,u16 c,int r, int fill,u8 select)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) 
	{
		// �����䣨��ʵ��Բ��
		while (x <= y) 
		{
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c,select);

			if (d < 0) 
			{
				d = d + 4 * x + 6;
			}
			else 
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
	else 
	{
		// �������䣨������Բ��
		while (x <= y) 
		{
			_draw_circle_8(xc, yc, x, y, c,select);
			if (d < 0) 
			{
				d = d + 4 * x + 6;
			} 
			else 
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode,u8 select)
{  
    u8 temp;
    u8 pos,t;
		u16 x0=x;
		u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	     
		   
		num=num-' ';//�õ�ƫ�ƺ��ֵ
		LCD_SetWindows(x,y,x+size/2-1,y+size-1);//���õ���������ʾ����
		if(!mode) //�ǵ��ӷ�ʽ
		{
			if(size==20)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2010[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }
			else if(size==22)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2211[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }			
			else if(size==24)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2412[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }
			else if(size==28)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2814[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }			
			 else
			 {
				for(pos=0;pos<csize;pos++)
				{
					if(size==12)
						temp=asc2_1206[num][pos];//����1206����		
					else
						temp=asc2_1608[num][pos];		 //����1608����
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }
			 }				
		}	
		else//���ӷ�ʽ
		{	
			if(size==20)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2010[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							else 
								GUI_DrawPoint(x,y,bc,select);//��һ����		
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }
			else if(size==22)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2211[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							else 
								GUI_DrawPoint(x,y,bc,select);//��һ����		
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }			
			else if( size==24)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2412[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							else 
								GUI_DrawPoint(x,y,bc,select);//��һ����							
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }
			else if(size==28)
			{
				for(pos=0;pos<(csize+8);pos++)
				{
					temp=asc2_2814[num][pos];//����2412����				
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							else 
								GUI_DrawPoint(x,y,bc,select);//��һ����	
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }					
			 }				
			 else
			 {
				for(pos=0;pos<csize;pos++)
				{
					if(size==12)
						temp=asc2_1206[num][pos];//����1206����		
					else
						temp=asc2_1608[num][pos];		 //����1608����
					for(t=0;t<8;t++)
					{                 
							if(temp&0x01)
								GUI_DrawPoint(x,y,fc,select);//��һ����
							else 
								GUI_DrawPoint(x,y,bc,select);//��һ����
							temp>>=1;
							x++;
							if(x>=lcddev.width)return;		//��������
							if((x-x0)==size/2)
							{
								x=x0;
								y++;
								if(y>=lcddev.height)return;	//��������
								break;
							}						
					 }	
				 }
			 }	
	  }	
		LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��    	   	 	  
} 


//******************************************************************
//��������  LCD_ShowChar
//���ܣ�    ��ʾ����Ӣ���ַ�
//���������(x,y):�ַ���ʾλ����ʼ����
//        	fc:ǰ�û�����ɫ
//			bc:������ɫ
//			num:��ֵ��0-94��
//			size:�����С
//			mode:ģʽ  0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void LCD_ShowNum2412(u16 x,u16 y,u16 fc, u16 bc,u8 *p ,u8 size,u8 mode,u8 select)
{  
    u16 temp;
    u8 pos,t;     
		u16 x0=x;
		u16 y0=y; 
		u8 num=0;
	
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {   
			if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
				return;   
			num=*p;
			if(':'==num) //�����ַ�":"
				num=10;	
			else if('.'==num)//�����ַ�"."
				num=11;	
			else  //������   	
				num=num-'0';   
			x0=x;
					
			for(pos=0;pos<48;pos++)
			{
				temp=asc2_2412[num][pos];
				for(t=0;t<8;t++)
				{               
					if(temp&0x01)
						GUI_DrawPoint(x,y,fc,select);//��һ����  
					temp>>=1; 
					x++;
					if((x-x0)==12)
					{
						x=x0;
						y++;
						break;
					}
				}
			}
			if(num<10)
				x+=16;	//��Ϊ�����־࣬ʹ���Ű���ÿ���ԭֵΪ12
			else
				x+=8; //��Ϊ�����־࣬ʹ���Ű���ÿ���ԭֵΪ12

			y=y0;
			p++;
    }  
	 	  
}

//******************************************************************
//��������  LCD_ShowString
//���ܣ�    ��ʾӢ���ַ���
//���������x,y :�������	 
//			size:�����С
//			*p:�ַ�����ʼ��ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  	  
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode,u8 select)
{         
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {   
			if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
				return;     
      LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode,select);
      x+=size/2;
      p++;
    }  
} 

//******************************************************************
//��������  mypow
//���ܣ�    ��m��n�η�(gui�ڲ�����)
//���������m:����
//	        n:��
//����ֵ��  m��n�η�
//�޸ļ�¼����
//******************************************************************  
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
		result*=m;    
	return result;
}

//******************************************************************
//��������  LCD_ShowNum
//���ܣ�    ��ʾ�������ֱ���ֵ
//���������x,y :�������	 
//			len :ָ����ʾ���ֵ�λ��
//			size:�����С(12,16)
//			color:��ɫ
//			num:��ֵ(0~4294967295)
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  			 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 select)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0,select);
				continue;
			}
			else 
				enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0,select); 
	}
} 

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
// fc:ǰ�û�����ɫ��bc:������ɫ
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u16 fc, u16 bc,u32 num,u8 len,u8 size,u8 mode,u8 select)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X01)
					LCD_ShowChar(x+(size/2)*t,y,fc,bc,'0',size,(mode),select);  
				else 
					LCD_ShowChar(x+(size/2)*t,y,fc,bc,' ',size,mode,select);  
 				continue;
			}
			else 
				enshow=1;  
		}
	 	LCD_ShowChar(x+(size/2)*t,y,fc,bc,temp+'0',size,mode,select);
	}
} 

//******************************************************************
//��������  GUI_DrawFont16
//���ܣ�    ��ʾ����16X16��������
//���������x,y :�������
//			fc:ǰ�û�����ɫ
//			bc:������ɫ	 
//			s:�ַ�����ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode,u8 select)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//�Զ�ͳ�ƺ�����Ŀ		
	for (k=0;k<HZnum;k++) 
	{
	  if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
	  { 
				LCD_SetWindows(x,y,x+16-1,y+16-1);
		    for(i=0;i<16*2;i++)
		    {
					for(j=0;j<8;j++)
					{	
						if(!mode) //�ǵ��ӷ�ʽ
						{
							if(tfont16[k].Msk[i]&(0x80>>j))
								GUI_DrawPoint(x,y,fc,select);//��һ����
							else
								GUI_DrawPoint(x,y,bc,select);//��һ����		
						}
						else
						{
							if(tfont16[k].Msk[i]&(0x80>>j))
								GUI_DrawPoint(x,y,fc,select);//��һ����
						}
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							break;
						}
					}			
				}		
		}				  	
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��  
} 

//******************************************************************
//��������  GUI_DrawFont24
//���ܣ�    ��ʾ����24X24��������
//���������x,y :�������
//			fc:ǰ�û�����ɫ
//			bc:������ɫ	 
//			s:�ַ�����ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode,u8 select)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//�Զ�ͳ�ƺ�����Ŀ
		
			for (k=0;k<HZnum;k++) 
			{
			  if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
			  { 	
						LCD_SetWindows(x,y,x+24-1,y+24-1);
				    for(i=0;i<24*3;i++)
				    {
							for(j=0;j<8;j++)
							{
								if(!mode) //�ǵ��ӷ�ʽ
								{
									if(tfont24[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//��һ����
									else 
										GUI_DrawPoint(x,y,bc,select);//��һ����
								}
								else
								{
									if(tfont24[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//��һ����
								}
								x++;
								if((x-x0)==24)
								{
										x=x0;
										y++;
										break;
								}
								
							}
						}			
					}				  	
					continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
			}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��  
}

//******************************************************************
//��������  GUI_DrawFont32
//���ܣ�    ��ʾ����32X32��������
//���������x,y :�������
//			fc:ǰ�û�����ɫ
//			bc:������ɫ	 
//			s:�ַ�����ַ
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//****************************************************************** 
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode,u8 select)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//�Զ�ͳ�ƺ�����Ŀ
	for (k=0;k<HZnum;k++) 
	{
			  if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
			  { 	
						LCD_SetWindows(x,y,x+32-1,y+32-1);
				    for(i=0;i<32*4;i++)
				    {
							for(j=0;j<8;j++)
							{
								if(!mode) //�ǵ��ӷ�ʽ
								{
									if(tfont32[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//��һ����
									
									else 
										GUI_DrawPoint(x,y,bc,select);//��һ����
									
								}
								else
								{
									if(tfont32[k].Msk[i]&(0x80>>j))	
										GUI_DrawPoint(x,y,fc,select);//��һ����
								}
								x++;
								if((x-x0)==32)
								{
									x=x0;
									y++;
									break;
								}
							}
						}				
				}				  	
				continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
			}
	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ�����Ϊȫ��  
} 

//******************************************************************
//��������  Show_Str
//���ܣ�    ��ʾһ���ַ���,������Ӣ����ʾ
//���������x,y :�������
// 			fc:ǰ�û�����ɫ
//			bc:������ɫ
//			str :�ַ���	 
//			size:�����С
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************    	   		   
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode,u8 select)
{					
		u16 x0=x;							  	  
  	u8 bHz=0;     //�ַ��������� 
    while(*str!=0)//����δ����
    { 
        if(!bHz)
        {
					if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) 
					return; 
	        if(*str>0x80)
						bHz=1;//���� 
	        else              //�ַ�
	        {          
		        if(*str==0x0D)//���з���
		        {         
		            y+=size;
								x=x0;
		            str++; 
		        }  
		        else
						{
							if(size==12||size==16||size==20||size==22)
							{  
								LCD_ShowChar(x,y,fc,bc,*str,size,mode,select);
								x+=size/2; //�ַ�,Ϊȫ�ֵ�һ�� 
							}
							else//�ֿ���û�м���16X32��Ӣ������,��8X16����
							{
								LCD_ShowChar(x,y,fc,bc,*str,24,mode,select);
//								x+=12; //�ַ�,Ϊȫ�ֵ�һ�� 
								x+=size/2; //�ַ�,Ϊȫ�ֵ�һ�� 
							}
						} 
						str++; 
		        
						}
        }
				else//���� 
        {   
					if(x>(lcddev.width-size)||y>(lcddev.height-size)) 
					return;  
            bHz=0;//�к��ֿ�    
					if(size==32)
						GUI_DrawFont32(x,y,fc,bc,str,mode,select);	 	
					else if(size==24)
						GUI_DrawFont24(x,y,fc,bc,str,mode,select);	
					else
						GUI_DrawFont16(x,y,fc,bc,str,mode,select);
				
	        str+=2; 
	        x+=size;//��һ������ƫ��	    
        }						 
    }   
}


//******************************************************************
//��������  Gui_StrCenter

//���ܣ�    ������ʾһ���ַ���,������Ӣ����ʾ
//���������x,y :�������
// 			fc:ǰ�û�����ɫ
//			bc:������ɫ
//			str :�ַ���	 
//			size:�����С
//			mode:ģʽ	0,���ģʽ;1,����ģʽ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************   
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode,u8 select)
{
	u16 len=strlen((const char *)str);
	u16 x1=(lcddev.width-len*8)/2;
	Show_Str(x+x1,y,fc,bc,str,size,mode,select);
} 






//******************************************************************
//��������  Gui_Drawbmp16
//���ܣ�    ��ʾһ��16λBMPͼ��
//���������x,y :�������
// 			*p :ͼ��������ʼ��ַ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************  
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p) //��ʾ40*40 QQͼƬ
{
  	int i; 
	unsigned char picH,picL; 
	LCD_SetWindows(x,y,x+40-1,y+40-1);//��������
    for(i=0;i<40*40;i++)
	{	
	 	picL=*(p+i*2);	//���ݵ�λ��ǰ
		picH=*(p+i*2+1);				
		LCD_WR_DATA_16Bit(picH<<8|picL);  						
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//�ָ���ʾ����Ϊȫ��	

}






/********************************************************************************************************************************************************/
/********************************************************************************************************************************************************/


























