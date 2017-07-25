#include "snmp_trap.h"

//#define APP_SNMP_TRAP_DEST_IP_ADDR "192.168.1.196"
//      ipStringToAddr(APP_SNMP_TRAP_DEST_IP_ADDR, &destIpAddr);

void SNMPtrapTask(void *param)
{
	 char i;
   error_t error;
   IpAddr destIpAddr[2];
   SnmpTrapObject trapObjects;
	
		while(1)
	 { 
			osDelayTask(5000);
		 
      //Destination IP address
		  ipStringToAddr(&trap_ip[0][0], &destIpAddr[0]);
			ipStringToAddr(&trap_ip[1][0], &destIpAddr[1]);		 
		 
		  if(LINE_NUM==1)
		  {
								if(Tvol_alarm[0]==1)
								{
											trapObjects.oidLen = (size_t)privateMibObjects[4].oidLen+1;                       
											memcpy(trapObjects.oid,privateMibObjects[4].oid,trapObjects.oidLen-1);
											trapObjects.oid[trapObjects.oidLen-1] = 0;	
											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[0], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}		

											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[1], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}								
								}		
								if(Tcur_alarm[0]==1)
								{
											trapObjects.oidLen = (size_t)privateMibObjects[7].oidLen+1;                       
											memcpy(trapObjects.oid,privateMibObjects[7].oid,trapObjects.oidLen-1);
											trapObjects.oid[trapObjects.oidLen-1] = 0;	
											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[0], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}		

											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[1], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}								
								}						
		  }
		  else
		  {
					for(i=0;i<3;i++)                  //总电压电流报警
					{
								if(Tvol_alarm[i]==1)
								{
											trapObjects.oidLen = (size_t)privateMibObjects[4+i].oidLen+1;                       
											memcpy(trapObjects.oid,privateMibObjects[4+i].oid,trapObjects.oidLen-1);
											trapObjects.oid[trapObjects.oidLen-1] = 0;	
											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[0], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}		

											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[1], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}								
								}		
								if(Tcur_alarm[i]==1)
								{
											trapObjects.oidLen = (size_t)privateMibObjects[7+i].oidLen+1;                       
											memcpy(trapObjects.oid,privateMibObjects[7+i].oid,trapObjects.oidLen-1);
											trapObjects.oid[trapObjects.oidLen-1] = 0;	
											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[0], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}		

											//Send a SNMP trap 发送SNMP trap
											error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[1], SNMP_VERSION_2C,
												 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

											//Failed to send trap message?
											if(error)
											{
												 //Debug message
												 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
											}								
								}							
					 }					 
		  }		 
			for(i=0;i<2;i++)
			{
					if(Tem_Hum_alarm[i]==1)
					{
									trapObjects.oidLen = (size_t)privateMibObjects[16+i].oidLen+1;                       
									memcpy(trapObjects.oid,privateMibObjects[16+i].oid,trapObjects.oidLen-1);
									trapObjects.oid[trapObjects.oidLen-1] = 0;	
									//Send a SNMP trap 发送SNMP trap
									error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[0], SNMP_VERSION_2C,
										 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

									//Failed to send trap message?
									if(error)
									{
										 //Debug message
										 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
									}		

									//Send a SNMP trap 发送SNMP trap
									error = snmpAgentSendTrap(&snmpAgentContext, &destIpAddr[1], SNMP_VERSION_2C,
										 "public", SNMP_TRAP_LINK_UP, 0, &trapObjects, 1);

									//Failed to send trap message?
									if(error)
									{
										 //Debug message
										 TRACE_ERROR("Failed to send SNMP trap message!\r\n");
									}							
					}
			}

//								/* 发送事件标志，表示任务正常运行 */
		xEventGroupSetBits(xCreatedEventGroup, TASK_BIT_3);			
			
	 }
}


void SNMP_trap_init(void)
{
	osCreateTask("SNMP trap", SNMPtrapTask, NULL, 600, 1);
}
