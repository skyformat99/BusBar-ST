#include "send_smtp.h"

SmtpAuthInfo *Auth_Info;
SmtpMail *Mail;
char total_a[3]={0,0,0},total_v[3]={0,0,0},Tem_hum[2]={0,0};


void Send_Mail(char *str_info)
{
		error_t error;
		char i=0;
		char cnnt=0;	
		SmtpMailAddr Reci_Pients ;	
		char ch[128];	

		Auth_Info = (SmtpAuthInfo *)pvPortMalloc(sizeof(SmtpAuthInfo)); 
		Mail = (SmtpMail *)pvPortMalloc(sizeof(SmtpMail)); 
	
		Auth_Info->interface = NULL;
		Auth_Info->userName = strDuplicate(smtpuser);
		Auth_Info->password  = strDuplicate(smtppsd);			//密码
		Auth_Info->serverName  = strDuplicate(smtpserver);			//服务器
		if(SMTPorSMTPS==1)
		{		
					Auth_Info->serverPort = smtpsport;			//端口号
					Auth_Info->useTls = TRUE;
		}
		else 	
		{
				Auth_Info->serverPort = smtpport;
				Auth_Info->useTls = FALSE;
		}
      //Set the relevant PRNG algorithm to be used
	
    Auth_Info->prngAlgo = YARROW_PRNG_ALGO;
    Auth_Info->prngContext = &yarrowContext;					
	
		Reci_Pients.name = NULL;
		Reci_Pients.addr = strDuplicate(To_Email);
		Reci_Pients.type = SMTP_RCPT_TYPE_TO;
 	
		Mail->from.name = NULL;
		Mail->from.addr = strDuplicate(smtpuser);
		Mail->from.type = SMTP_RCPT_TYPE_TO;
		Mail->recipients = &Reci_Pients;		    //收件人
		Mail->recipientCount = 1;              //多少个收件人      
		Mail->dateTime = NULL;
		memset(ch,0,sizeof(char)*128);
		sprintf(ch,"IP-PDU Alarm");
		Mail->subject = strDuplicate(ch);   //主题
		
		Mail->body = strDuplicate(str_info);      //内容			
		
		error = smtpSendMail(Auth_Info, Mail);
		if(error)
		{
				osDelayTask(500);
		}
									
		vPortFree(Auth_Info);
		vPortFree(Mail);		


///***********************************************************************/
////		Reci_Pients[0].name = NULL;
////		Reci_Pients[0].addr = strDuplicate(&To_Email[0][0]);
////		Reci_Pients[0].type = SMTP_RCPT_TYPE_TO;		
////		Mail->from.name = NULL;
////		Mail->from.addr = strDuplicate(smtpuser);
////		Mail->from.type = SMTP_RCPT_TYPE_TO;
////		Mail->recipients = &Reci_Pients[0];		    //收件人
////		Mail->recipientCount = 1;              //多少个收件人      
////		Mail->dateTime = NULL;
////		memset(ch,0,sizeof(char)*128);
////		sprintf(ch,"MPDU demo");
////		Mail->subject = strDuplicate(ch);   //主题		
////		memset(ch,0,sizeof(char)*128);
////		sprintf(ch,"Hello World!");
////		Mail->body = strDuplicate(ch);      //内容	

////		osDelayTask(2000);
////		error = smtpSendMail(Auth_Info, Mail);
////		
////								 if(error)
////								 {
////										osDelayTask(1000);
////								 }
///***********************************************************************/

//		
		
}




void SendSMTPTask(void *param)
{
	error_t error;
	char i=0;	
	
	while(1)
	{
		
		osDelayTask(500);
		
		if(LINE_NUM==1)      //单相
		{
									if(Tcur_alarm[0]==1&&total_a[0]==0)
									{
										 char info[128];
										 memset(info,0,sizeof(char)*128);
										 sprintf(info,"DEVICE IP:%d.%d.%d.%d Line %d total current is alarming,the value is %.1fA(%.1f-%.1f).",ip1,ip2,ip3,ip4,1
										 ,((float)Tcur[0][0])/10
										 ,((float)Tcur[0][1])/10
										 ,((float)Tcur[0][2])/10);
										 Send_Mail(info);
										 total_a[0]=1;																			 
									}	
									if(Tcur_alarm[0]==0&&total_a[0]==1)
									{
										 char info[128];									
										 memset(info,0,sizeof(char)*128);
										 sprintf(info,"DEVICE IP:%d.%d.%d.%d Line %d total current relieve the alarm,the value is %.1fA(%.1f-%.1f).",ip1,ip2,ip3,ip4,1
										 ,((float)Tcur[0][0])/10
										 ,((float)Tcur[0][1])/10
										 ,((float)Tcur[0][2])/10);
										 Send_Mail(info);
										 total_a[0]=0;																					 
									}								
									if(Tvol_alarm[0]==1&&total_v[0]==0)
									{
												char info[128];
												memset(info,0,sizeof(char)*128);
												sprintf(info,"DEVICE IP:%d.%d.%d.%d  Line %d voltage is alarm,the value is %dV(%dV-%dV).",ip1,ip2,ip3,ip4,1
												,Tvol[0][0]
												,Tvol[0][1]
												,Tvol[0][2]);
												Send_Mail(info);
												total_v[0]=1;																								
													
									}
									if(Tvol_alarm[0]==0&&total_v[0]==1)
									{
												char info[128];
												memset(info,0,sizeof(char)*128);
												sprintf(info,"DEVICE IP:%d.%d.%d.%d  Line %d voltage relieve the alarm,the value is %dV(%dV-%dV).",ip1,ip2,ip3,ip4,1
												,Tvol[0][0]
												,Tvol[0][1]
												,Tvol[0][2]);
												Send_Mail(info);
												total_v[0]=0;														
									}							
		}
		else               //三相
		{
					for(i=0;i<3;i++)             
					{
									if(Tcur_alarm[i]==1&&total_a[i]==0)
									{
										 char info[128];
										 memset(info,0,sizeof(char)*128);
										 sprintf(info,"DEVICE IP:%d.%d.%d.%d Line %d total current is alarming,the value is %.1fA(%.1f-%.1f).",ip1,ip2,ip3,ip4,i+1
										 ,((float)Tcur[i][0])/10
										 ,((float)Tcur[i][1])/10
										 ,((float)Tcur[i][2])/10);
										 Send_Mail(info);
										 total_a[i]=1;																			 
									}	
									if(Tcur_alarm[i]==0&&total_a[i]==1)
									{
										 char info[128];									
										 memset(info,0,sizeof(char)*128);
										 sprintf(info,"DEVICE IP:%d.%d.%d.%d Line %d total current relieve the alarm,the value is %.1fA(%.1f-%.1f).",ip1,ip2,ip3,ip4,i+1
										 ,((float)Tcur[i][0])/10
										 ,((float)Tcur[i][1])/10
										 ,((float)Tcur[i][2])/10);
										 Send_Mail(info);
										 total_a[i]=0;																					 
									}								
									if(Tvol_alarm[i]==1&&total_v[i]==0)
									{
												char info[128];
												memset(info,0,sizeof(char)*128);
												sprintf(info,"DEVICE IP:%d.%d.%d.%d  Line %d voltage is alarm,the value is %dV(%dV-%dV).",ip1,ip2,ip3,ip4,i+1
												,Tvol[i][0]
												,Tvol[i][1]
												,Tvol[i][2]);
												Send_Mail(info);
												total_v[i]=1;																								
													
									}
									if(Tvol_alarm[i]==0&&total_v[i]==1)
									{
												char info[128];
												memset(info,0,sizeof(char)*128);
												sprintf(info,"DEVICE IP:%d.%d.%d.%d  Line %d voltage relieve the alarm,the value is %dV(%dV-%dV).",ip1,ip2,ip3,ip4,i+1
												,Tvol[i][0]
												,Tvol[i][1]
												,Tvol[i][2]);
												Send_Mail(info);
												total_v[i]=0;														
									}						 
					 }					
		}
		if(Tem_Hum_alarm[0]==1&&Tem_hum[0]==0)
		{
						char info[128];										
						memset(info,0,sizeof(char)*128);
						sprintf(info,"DEVICE IP:%d.%d.%d.%d  temperature is alarming,the value is %dC(%dC-%dC).",ip1,ip2,ip3,ip4
						,tem[0]
						,tem[1]
						,tem[2]);
						Send_Mail(info);
						Tem_hum[0]=1;
		}
		if(Tem_Hum_alarm[0]==0&&Tem_hum[0]==1)
		{
						char info[128];						
						memset(info,0,sizeof(char)*128);
						sprintf(info,"DEVICE IP:%d.%d.%d.%d  temperature relieve the alarm,the value is %dC(%dC-%dC).",ip1,ip2,ip3,ip4
						,tem[0]
						,tem[1]
						,tem[2]);
						Send_Mail(info);
						Tem_hum[0]=0;												
		}								 
		if(Tem_Hum_alarm[1]==1&&Tem_hum[1]==0)
		{
						char info[128];
						memset(info,0,sizeof(char)*128);
						sprintf(info,"DEVICE IP:%d.%d.%d.%d  humidity is alarming,the value is %d%% (%d%% - %d%%).",ip1,ip2,ip3,ip4
						,hum[0]
						,hum[1]
						,hum[2]);
						Send_Mail(info);
						Tem_hum[1]=1;												
		}
		if(Tem_Hum_alarm[1]==0&&Tem_hum[1]==1)
		{
						char info[128];
						memset(info,0,sizeof(char)*128);
						sprintf(info,"DEVICE IP:%d.%d.%d.%d  humidity relieve the alarm,the value is %d%% (%d%% - %d%%).",ip1,ip2,ip3,ip4
						,hum[0]
						,hum[1]
						,hum[2]);
						Send_Mail(info);
						Tem_hum[1]=0;											
		}								 			 	
	}        //while
}


void send_smtp_init(void)
{
	osCreateTask("send smtp", SendSMTPTask, NULL, 600, 1);
}