//Dependencies
#include "ip_info.h"


/**
 * @brief LED blinking task
 **/

void ledTask(void *param)
{
	 char i;
	 char change=0;	 
	
   //Endless loop
   while(1)
   {		   		 
			 if(tem[0]<tem[1]||tem[0]>tem[2])Tem_Hum_alarm[0]=1;
			 else Tem_Hum_alarm[0]=0;
			 if(hum[0]<hum[1]||hum[0]>hum[2])Tem_Hum_alarm[1]=1;
			 else Tem_Hum_alarm[1]=0;	
		 
		   if(LINE_NUM==1)
			 {
						if(Tvol[0][0]<Tvol[0][1]||Tvol[0][0]>Tvol[0][2])Tvol_alarm[0]=1;
						else Tvol_alarm[0]=0;
						if(Tcur[0][0]<Tcur[0][1]||Tcur[0][0]>Tcur[0][2])Tcur_alarm[0]=1;
						else Tcur_alarm[0]=0;				 
		 			 
						if(change==0)
						{
								change=1;
								if(Tvol_alarm[0]==1||Tcur_alarm[0]==1||Tem_Hum_alarm[0]==1||Tem_Hum_alarm[1]==1)
								{
										run_alm(1);
										if(ONorOFF_sound)beel(0);
										else beel(1);
								}							
						}
						else
						{
								change=0;
								run_alm(0);
								beel(0);
						}					
			 }
			 else
			 {
					 for(i=0;i<3;i++)
					 {
							if(Tvol[i][0]<Tvol[i][1]||Tvol[i][0]>Tvol[i][2])Tvol_alarm[i]=1;
							else Tvol_alarm[i]=0;
							if(Tcur[i][0]<Tcur[i][1]||Tcur[i][0]>Tcur[i][2])Tcur_alarm[i]=1;
							else Tcur_alarm[i]=0;								 
					 }	
					 if(change==0)
					 {
							change=1;
							if(Tvol_alarm[0]==1||Tcur_alarm[0]==1||Tvol_alarm[1]==1||Tcur_alarm[1]==1||Tvol_alarm[2]==1||Tcur_alarm[2]==1||Tem_Hum_alarm[0]==1||Tem_Hum_alarm[1]==1)
							{
									run_alm(1);
									if(ONorOFF_sound)beel(0);
									else beel(1);
							}							
					 }
					 else
					 {
					 		change=0;
							run_alm(0);
							beel(0);
					 }	
			 }		
			 
		   LED0 = !LED0;   
			 osDelayTask(500);	
			 		 		 
					/* 发送事件标志，表示任务正常运行 */
		xEventGroupSetBits(xCreatedEventGroup, TASK_BIT_0);
			 		 
   }
}

void ReadParam(void *param)
{
	Init_8207();
	while(1)
	{	
		  RN8207Read();
		  Read_energy();
			Temperatuer();
			osDelayTask(500);

										/* 发送事件标志，表示任务正常运行 */
			xEventGroupSetBits(xCreatedEventGroup, TASK_BIT_1);			
		
	}
}
void IwdgTask(void *param)
{
		EventBits_t uxBits;
		IWDG_Init();    //独立看门狗初始化
	
		while(1)
		{
				/* 等待所有任务发来事件标志 */
				uxBits = xEventGroupWaitBits(xCreatedEventGroup, /* 事件标志组句柄 */
													 TASK_BIT_ALL,       /* 等待TASK_BIT_ALL被设置 */
													 pdTRUE,             /* 退出前TASK_BIT_ALL被清除，这里是TASK_BIT_ALL都被设置才表示“退出”*/
													 pdTRUE,             /* 设置为pdTRUE表示等待TASK_BIT_ALL都被设置*/
													 8000); 	 /* 等待延迟时间 */	

				if((uxBits & TASK_BIT_ALL) == TASK_BIT_ALL)
				{
						IWDG_ReloadCounter();  //喂狗
				}
			
			
		}
}


void application(void)
{
	 OsTask *task;                   //void类型
//	
	http_web_init();
	
   task = osCreateTask("LED", ledTask, NULL, 500, 3);
   if(task == OS_INVALID_HANDLE)
   {
      //Debug message
      TRACE_ERROR("Failed to create task!\r\n");
   }	
   
   task = osCreateTask("Read param", ReadParam, NULL, 500, 1);
   if(task == OS_INVALID_HANDLE)
   {
      //Debug message
      TRACE_ERROR("Failed to create task!\r\n");
   }
////   
	 IAP_tftpd_init();
	 Telnet_init();
//   IAP_udp_init();
//   IAP_udp_control();
//   IAP_tcp_control();	 
//   IAP_app_read();		 
	 modbus_rtu();
	 display_init();
	 SNMP_trap_init();
	 send_smtp_init();
 
   task = osCreateTask("Iwdg", IwdgTask, NULL, 800, 6);
   if(task == OS_INVALID_HANDLE)
   {
      //Debug message
      TRACE_ERROR("Failed to create task!\r\n");
   }	 

}





























