#include "modbus.h"

char ch_cpy[100];

const unsigned short wCRCTalbeAbs[] =
{
0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401, 0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400, 
};
int CRC16_2(char* pchMsg, char wDataLen)
{
        unsigned short wCRC = 0xFFFF;
        char i;
        char chChar;

        for (i = 0; i < wDataLen; i++)
        {
                chChar = *pchMsg++;
                wCRC = wCRCTalbeAbs[(chChar ^ wCRC) & 15] ^ (wCRC >> 4);
                wCRC = wCRCTalbeAbs[((chChar >> 4) ^ wCRC) & 15] ^ (wCRC >> 4);
        }

        return wCRC;
}

void read_modbus_data(u8 *rx_usart3)
{
			char i;
			static char first_rece_flag=0;
			static char sen_data_len=0;
	
			if(rx_usart3[0]==ser)
			{
					char index=0;  
					char buf[128];
					int crc = CRC16_2(rx_usart3,6);
					char H =  crc/256%256;
					char L =  crc%256;
					if(L==rx_usart3[6] && H==rx_usart3[7])
					{
							if(rx_usart3[1]==0x03)
							{
									char data[128];
									int reglen=0;
									int regaddr=0;
									int datacrc = 0;
									memset(data,0,sizeof(char)*128);
									data[0] = Tvol[0][0]/256;
									data[1] = Tvol[0][0]%256;           //0
									data[2] = Tvol[1][0]/256;
									data[3] = Tvol[1][0]%256;        //1
									data[4] = Tvol[2][0]/256;
									data[5] = Tvol[2][0]%256;          //2

									data[6] = Tcur[0][0]/256;
									data[7] = Tcur[0][0]%256;         //3
									data[8] = Tcur[1][0]/256;
									data[9] = Tcur[1][0]%256;         //4
									data[10] = Tcur[2][0]/256;
									data[11] = Tcur[2][0]%256;            //5

									data[12] = Tcur[0][0]*Tvol[0][0]/2560;
									data[13] = (Tcur[0][0]*Tvol[0][0]/10)%256;       //6
									data[14] = Tcur[1][0]*Tvol[1][0]/2560;
									data[15] = (Tcur[1][0]*Tvol[1][0]/10)%256;        //7
									data[16] = Tcur[2][0]*Tvol[2][0]/2560;
									data[17] = (Tcur[2][0]*Tvol[2][0]/10)%256;       //8

									data[18] = hzperHz[0]/256;
									data[19] = hzperHz[0]%256;               //9
									data[20] = hzperHz[1]/256;
									data[21] = hzperHz[1]%256;             //10
									data[22] = hzperHz[2]/256;
									data[23] = hzperHz[2]%256;           //11
									
									Energy8207_dc=Energy8207[0]=1048575;
									
									if(cur_dc_ac==0)                        //dc
									{
											data[24] = Energy8207_dc/256/256/256%256;
											data[25] = Energy8207_dc/256/256%256;              //12
											data[26] = Energy8207_dc/256%256;
											data[27] = Energy8207_dc%256;					            //13																						
									}
									else
									{
											data[24] = Energy8207[0]/256/256/256%256;
											data[25] = Energy8207[0]/256/256%256;            //12
											data[26] = Energy8207[0]/256%256;
											data[27] = Energy8207[0]%256;				            //13							
									}
									data[28] = Energy8207[1]/256/256/256%256;
									data[29] = Energy8207[1]/256/256%256;            //14
									data[30] = Energy8207[1]/256%256;
									data[31] = Energy8207[1]%256;                   //15
									data[32] = Energy8207[2]/256/256/256%256;
									data[33] = Energy8207[2]/256/256%256;            //16
									data[34] = Energy8207[2]/256%256;
									data[35] = Energy8207[2]%256;			            //17												

									data[36] = tem[0]/256%256;
									data[37] = tem[0]%256;                     //18
									data[38] = hum[0]/256%256;
									data[39] = hum[0]%256;              //19
									//////////////////设定值//////////////////////
									data[40] = Tvol[0][1]/256;
									data[41] = Tvol[0][1]%256;               //20
									data[42] = Tvol[0][2]/256;
									data[43] = Tvol[0][2]%256;             //21

									data[44] = Tvol[1][1]/256;
									data[45] = Tvol[1][1]%256;          //22
									data[46] = Tvol[1][2]/256;
									data[47] = Tvol[1][2]%256;          //23

									data[48] = Tvol[2][1]/256;
									data[49] = Tvol[2][1]%256;          //24
									data[50] = Tvol[2][2]/256;
									data[51] = Tvol[2][2]%256;         //25

									data[52] = Tcur[0][1]/256;
									data[53] = Tcur[0][1]%256;        //26
									data[54] = Tcur[0][2]/256;
									data[55] = Tcur[0][2]%256;         //27

									data[56] = Tcur[1][1]/256;
									data[57] = Tcur[1][1]%256;       //28
									data[58] = Tcur[1][2]/256;
									data[59] = Tcur[1][2]%256;      //29

									data[60] = Tcur[2][1]/256;
									data[61] = Tcur[2][1]%256;       //30
									data[62] = Tcur[2][2]/256;
									data[63] = Tcur[2][2]%256;        //31
									
									data[64] = tem[1]/256%256;
									data[65] = tem[1]%256;       //32
									data[66] = tem[2]/256%256;
									data[67] = tem[2]%256;        //33
									data[68] = hum[1]/256%256;
									data[69] = hum[1]%256;         //34
									data[70] = hum[2]/256%256;
									data[71] = hum[2]%256;          //35
									
									//电压告警 00 正常 01 低压 10 高压
									data[72] = 0;
									if(Tvol[0][0]<Tvol[0][1])
									{
											data[73] = 1;             
									}
									else if(Tvol[0][0]>Tvol[0][2])
									{
											data[73] = 2;
									}
									else
									{
											data[73] = 0;               //36
									}
									data[74] = 0;
									if(Tvol[1][0]<Tvol[1][1])
									{
											data[75] = 1;
									}
									else if(Tvol[1][0]>Tvol[1][2])
									{
											data[75] = 2;
									}
									else
									{
											data[75] = 0;               //37
									}
									data[76] = 0;
									if(Tvol[2][0]<Tvol[2][1])
									{
											data[77] = 1;
									}
									else if(Tvol[2][0]>Tvol[2][2])
									{
											data[77] = 2;
									}
									else
									{
											data[77] = 0;                //38
									}
									///////////////电流报警///////////////////
									data[78] = 0;
									if(Tcur[0][0]<Tcur[0][1])
									{
											data[79] = 1;
									}
									else if(Tcur[0][0]>Tcur[0][2])
									{
											data[79] = 2;
									}
									else
									{
											data[79] = 0;               //39
									}
									data[80] = 0;
									if(Tcur[1][0]<Tcur[1][1])
									{
											data[81] = 1;
									}
									else if(Tcur[1][0]>Tcur[1][2])
									{
											data[81] = 2;
									}
									else
									{
											data[81] = 0;                 //40
									}
									data[82] = 0;
									if(Tcur[2][0]<Tcur[2][1])
									{
											data[83] = 1;
									}
									else if(Tcur[2][0]>Tcur[2][2])
									{
											data[83] = 2;
									}
									else
									{
											data[83] = 0;            //41
									}
									data[84] = 0;
									if(tem[0]<tem[1])
									{
											data[85] = 1;
									}
									else if(tem[0]>tem[2])
									{
											data[85] = 2;
									}
									else
									{
											data[85] = 0;             //42
									}
									data[86] = 0;
									if(hum[0]<hum[1])
									{
											data[87] = 1;
									}
									else if(hum[0]>hum[2])
									{
											data[87] = 2;
									}
									else
									{
											data[87] = 0;             //43
									}
									////////////////单项或3相标志//////////////////
									data[88] = 0;
									data[89] = LINE_NUM;           //44
									data[90] = 0;
									data[91] = 150;            //45
									data[92] = 0;
									data[93] = baud;                //46
									data[94] = 0;			//波特率
									data[95] = 0;			//预留        //47

									regaddr = rx_usart3[2]*256+rx_usart3[3];
									reglen = rx_usart3[4]*256+rx_usart3[5];
									if(reglen<=50 && regaddr>=0 && regaddr<=49 && regaddr+reglen<=50) //读操作
									{
											memset(buf,0,sizeof(char)*128);
											buf[0] = ser;
											buf[1] = rx_usart3[1];//功能吗
											buf[2] = reglen*2;//长度
											for(index=0;index<reglen*2;index++)
											{
													buf[3+index] = data[regaddr*2+index];
											}
											datacrc = CRC16_2(buf,reglen*2+3);
											buf[3+reglen*2] = datacrc%256;
											buf[4+reglen*2] = datacrc/256%256;
																						
											sen_data_len = 5+reglen*2;									
											uart3_send_data(buf,sen_data_len);
											osDelayTask(10);
											
											first_rece_flag = 1;
											memset(ch_cpy,0,sizeof(char)*100);
											for(i=0;i<sen_data_len;i++)
											{
													ch_cpy[i] = buf[i];
											}
											comClearRxFifo(COM3);											
											
									}
							}
							else if(rx_usart3[1]==0x06)
							{
									int regaddr = rx_usart3[2]*256+rx_usart3[3];
									int order = rx_usart3[4]*256+rx_usart3[5];
									if(regaddr==1000 && order>0 && order<=99)
									{
											I2cWrite(224,order);
											ser = order;
											devicedown();
									}
									else if(regaddr==1001 && order>=0&&order<4)
									{
											baud=order;
											I2cWrite(225,baud);//baud
											devicedown();
									}
									/////////////过压、欠压//////////////
									//设定阀值 电压

									else if(regaddr==1002 && order>0&&order<300&&order<Tvol[0][2]) //L1 VOL  min
									{
											Tvol[0][1]=order;
											I2cWrite_2(9,rx_usart3[4]);
											I2cWrite_2(10,rx_usart3[5]);
									}
									else if(regaddr==1003 && order>0&&order<300&&order>Tvol[0][1]) //L1 VOL  max
									{
											Tvol[0][2]=order;
											I2cWrite_2(11,rx_usart3[4]);
											I2cWrite_2(12,rx_usart3[5]);		
									}
									else if(regaddr==1004 && order>0&&order<300&&order<Tvol[1][2]) //L2 VOL  min
									{
											Tvol[1][1]=order;
											I2cWrite_2(17,rx_usart3[4]);
											I2cWrite_2(18,rx_usart3[5]);
									}
									else if(regaddr==1005 && order>0&&order<300&&order>Tvol[1][1]) //L2 VOL  max
									{
											Tvol[1][2]=order;
											I2cWrite_2(19,rx_usart3[4]);
											I2cWrite_2(20,rx_usart3[5]);		
									}
									else if(regaddr==1006 && order>0&&order<300&&order<Tvol[2][2]) //L3 VOL  min
									{
											Tvol[2][1]=order;
											I2cWrite_2(25,rx_usart3[4]);
											I2cWrite_2(26,rx_usart3[5]);
									}
									else if(regaddr==1007 && order>0&&order<300&&order>Tvol[2][1]) //L3 VOL  max
									{
											Tvol[2][2]=order;
											I2cWrite_2(27,rx_usart3[4]);
											I2cWrite_2(28,rx_usart3[5]);		
									}
									//电流设定
									else if(regaddr==1008 && order>=0&&order<330&&order<Tcur[0][2]) //L1 cur  min
									{
											Tcur[0][1]=order;
											I2cWrite_2(13,rx_usart3[4]);
											I2cWrite_2(14,rx_usart3[5]);
									}
									else if(regaddr==1009 && order>=0&&order<330&&order>Tcur[0][1]) //L1 cur  max
									{
											Tcur[0][2]=order;
											I2cWrite_2(15,rx_usart3[4]);
											I2cWrite_2(16,rx_usart3[5]);		
									}
									else if(regaddr==1010 && order>=0&&order<330&&order<Tcur[1][2]) //L2 cur  min
									{
											Tcur[1][1]=order;
											I2cWrite_2(21,rx_usart3[4]);
											I2cWrite_2(22,rx_usart3[5]);
									}
									else if(regaddr==1011 && order>=0&&order<330&&order>Tcur[1][1]) //L2 cur  max
									{
											Tcur[1][2]=order;
											I2cWrite_2(23,rx_usart3[4]);
											I2cWrite_2(24,rx_usart3[5]);		
									}
									else if(regaddr==1012 && order>=0&&order<330&&order<Tcur[2][2]) //L3 cur  min
									{
											Tcur[2][1]=order;
											I2cWrite_2(29,rx_usart3[4]);
											I2cWrite_2(30,rx_usart3[5]);
									}
									else if(regaddr==1013 && order>=0&&order<330&&order>Tcur[2][1]) //L3 cur  max
									{
											Tcur[2][2]=order;
											I2cWrite_2(31,rx_usart3[4]);
											I2cWrite_2(32,rx_usart3[5]);		
									}
									/////////////////tem_hum///////////////////////////
									else if(regaddr==1014 && order>=0&&order<100&&order<tem[2]) //tem min
									{
											tem[1]=rx_usart3[5];
											I2cWrite(226,rx_usart3[5]);		
									}
									else if(regaddr==1015 && order>=0&&order<100&&order>tem[1]) //tem max
									{
											tem[2]=rx_usart3[5];
											I2cWrite(227,rx_usart3[5]);		
									}
									else if(regaddr==1016 && order>=0&&order<100&&order<hum[2]) //hum min
									{
											hum[1]=rx_usart3[5];
											I2cWrite(228,rx_usart3[5]);	
									}
									else if(regaddr==1017 && order>=0&&order<100&&order>hum[1]) //hum max
									{
											hum[2]=rx_usart3[5];
											I2cWrite(229,rx_usart3[5]);		
									}
									comClearRxFifo(COM3);
							}
					}    //CRC
					else
					{
							if(first_rece_flag==1)
							{
									first_rece_flag = 0;
									uart3_send_data(ch_cpy,sen_data_len);
									osDelayTask(10);
							}
							comClearRxFifo(COM3);
					}						
			}     //地址码
			else
			{
					comClearRxFifo(COM3);
			}			
}

void ModbusRTU(void *param)
{
	uint8_t lent=8;
	uint8_t rx_usart3_data[8]=NULL;
//	uint8_t ch_1[8]={0x11,0x03,0xff,0x01,0x11,0x03,0xff,0x01};
	
	while(1)
	{
		osDelayTask(500);
		memset(rx_usart3_data,0,sizeof(char)*8);
		Uart_Recive_data(COM3,rx_usart3_data,lent);
		
		if(strlen(rx_usart3_data)>0)		
		{				 			
				read_modbus_data(rx_usart3_data);
//				uart3_send_data(rx_usart3_data,8);
				comClearRxFifo(COM3);
		}
		else
		{
				comClearRxFifo(COM3);			
		}
			
		
		/* 发送事件标志，表示任务正常运行 */
		xEventGroupSetBits(xCreatedEventGroup, TASK_BIT_2);
		
	}
}



void modbus_rtu(void)
{
	
	osCreateTask("modbus rtu", ModbusRTU, NULL, 1000, 7);
		
}





