#include "telnet.h"
#include "ip_info.h"
#include <string.h>

// Telnet options 远程登陆选项
char *tel_options[] = {
		"Transmit Binary",
		"Echo",
		"",
		"Suppress Go Ahead",
		"",
		"Status",
		"Timing Mark"
};

char buf[LINELEN] = {0,};
uint8_t remote[NOPTIONS] = {0,};


uint8_t user_name[DATA_BUF_SIZE];
uint8_t user_password[DATA_BUF_SIZE];
char data_buf[DATA_BUF_SIZE];
uint8_t buffer[256];
size_t length;

uint16_t buf_index;

uint8_t ch_status[8] = { 0, };	/** 0:close, 1:ready, 2:connected */

uint8_t user_state;


void login(Socket *s,uint8_t c)
{
  if(user_state == USER_NAME)  //用户名
	{       /* input the client ID and Password 输入的客户ID和密码 */
 
    strcpy((char *)user_name, data_buf);    
    sprintf(buf, "Password: ");
		socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);	
    user_state = PASS_WORD;
    return;
  }
	else if(user_state == PASS_WORD)  //密码
	{
    strcpy((char *)user_password, data_buf); 
    
    /*Check the client ID and Password*/    
    if(!(strcmp((char const *)user_name, (char const *)user)) && !(strcmp((char const *)user_password, (char const *)psd))) 
		{

      sprintf(buf, "\r\nCommand: STATUS SENSOR QUIT REBOOT RESET HELP\r\n");                      
			socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);			
      user_state = LOGIN;
      return;
    } 
		else     //输入用户名和密码错误
		{
      sprintf(buf, "\r\nUser or Password incorrect!\r\n");  /* If the ID or Password incorrect, print error msg */
			socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);
      sprintf(buf, "User: ");
			socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);
      user_state = USER_NAME;
      return;      
    }
  } 	
}
void telnet_menu(Socket *s,char *data)
{
		char sendbuff[2024];
		int outindex=0;
		char net[32];
		memset(net,0,32);		
		memset(sendbuff,0,sizeof(char)*1024);

	  if(strcmp(data,"status")==0 || strcmp(data,"STATUS")==0)
		{	
			int j;
			if(LINE_NUM == 1)
			{
				j= sprintf(sendbuff, "\r\nTotal Voltage: %dV(%d--%d)", Tvol[0][0], Tvol[0][1], Tvol[0][2]);
				j+= sprintf(sendbuff+j, "\r\nTotal Current: %d.%dA(%d--%d)", Tcur[0][0]/10, Tcur[0][0]%10, Tcur[0][1]/10, Tcur[0][2]/10);
				j+= sprintf(sendbuff+j, "\r\nTotal Power: %d.%d KW ", active_power[0]/1000, active_power[0]%1000);
				if(cur_dc_ac==0) j+= sprintf(sendbuff+j, "\r\nTotal Energy: %d.%d Kwh\r\n", Energy8207[0]/10, Energy8207[0]%10);	                            // dc
			  else j+= sprintf(sendbuff+j, "\r\nTotal Energy: %d.%d Kwh\r\n", Energy8207_dc/10, Energy8207_dc%10);							
			}
			else if(LINE_NUM == 3)
			{
					j= sprintf(sendbuff, "\r\nName           L1            L2            L3\r\n");	
	        j+= sprintf(sendbuff+j, "Voltage:   %dV(%d--%d)     %dV(%d--%d)    %dV(%d--%d)\r\n",Tvol[0][0], Tvol[0][1], Tvol[0][2], Tvol[1][0], Tvol[1][1]
				  , Tvol[1][2], Tvol[2][0], Tvol[2][1], Tvol[2][2]);	
				
					j+= sprintf(sendbuff+j, "Current:   %d.%dA(%d--%d)    %d.%dA(%d--%d)   %d.%dA(%d--%d)\r\n", Tcur[0][0]/10, Tcur[0][0]%10, Tcur[0][1]/10, Tcur[0][2]/10
				  , Tcur[1][0]/10, Tcur[1][0]%10, Tcur[1][1]/10, Tcur[1][2]/10, Tcur[2][0]/10, Tcur[2][0]%10, Tcur[2][1]/10, Tcur[2][2]/10);	
				
					j+= sprintf(sendbuff+j, "Power:       %d.%d KW          %d.%d KW        %d.%d KW\r\n", active_power[0]/1000, active_power[0]%1000
					,active_power[1]/1000, active_power[1]%1000, active_power[2]/1000, active_power[2]%1000);		
					j+= sprintf(sendbuff+j, "Energy:      %d.%d Kwh         %d.%d Kwh       %d.%d Kwh\r\n", Energy8207[0]/10, Energy8207[0]%10, Energy8207[1]/10, Energy8207[1]%10
					, Energy8207[2]/10, Energy8207[2]%10);
			}			
		}	 
		else if(strcmp(data,"sensor")==0 || strcmp(data,"SENSOR")==0)
		{	
			  char j;			
				j=sprintf(sendbuff, "\r\nTemperature: %d C(%d--%d) Humidity:%d%%(%d--%d)\r\n", tem[0], tem[1], tem[2], hum[0], hum[1], hum[2]);	  
		}
		else if(strcmp(data,"reboot")==0 || strcmp(data,"REBOOT")==0)
		{
  			osDelayTask(300);
				devicedown();	
				return;			
			
		}
		else if(strcmp(data,"reset")==0 || strcmp(data,"RESET")==0)
		{
				osDelayTask(50);
				iicresetdata();	
				devicedown();
				return;
		}
		else if(strcmp(data,"help")==0 || strcmp(data,"HELP")==0)
		{
				sprintf(sendbuff, "\r\nCommand:STATUS SENSOR QUIT REBOOT RESET HELP ");
		}
		else if(strcmp(data,"quit")==0 || strcmp(data,"QUIT")==0)
		{
			  osDelayTask(500);
			  socketClose(s);
				ch_status[0] = close_state; 
        user_state = LOGOUT;
		}	
   	else
		{
				sprintf(sendbuff,"\r\nInvalid command!");
		//		sprintf(sendbuff,"\r\nCommand:PHASE GROUP OUTPUT SENSOR ON OFF REBOOT RESET QUIT HELP");
		}		

		socketSend(s, (uint8_t const *)sendbuff, strlen(sendbuff), NULL, 0);	

}

void sendIAC(Socket *s, uint8_t r1, uint8_t r2) 
{
  sprintf(buf, "%c%c%c", IAC, r1, r2);  
	
	//Initiate a conversation with the mail server
	socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);	
}

void willopt(Socket *s, uint16_t opt)
{
  int ack;
  switch(opt) 
	{
		case TN_TRANSMIT_BINARY :
		case TN_ECHO :
		case TN_SUPPRESS_GA :
    ack = DO;     /* If receive 'WILL' and it has TN_SUPPRESS_GA option, transmit 'DO' */
    break;
		default :
    ack = DONT;     /* Refuse other commands which not defined */	
  }
  sendIAC(s, ack, opt);	
}
void wontopt(Socket *s, uint16_t opt)
{
  switch(opt) 
	{
		case TN_TRANSMIT_BINARY :
		case TN_ECHO :
		case TN_SUPPRESS_GA :     /* If receive WONT command with TN_SUPPRESS_GA option */
    if(remote[opt] == 0) 
		{
      remote[opt] = 1;      /* Set the TN_SUPPRESS_GA option */
      sendIAC(s, DONT, opt);      /* Send DONT command with TN_SUPPRESS_GA */
    }
    break;
		default: break;
  }	
}
void doopt(Socket *s, uint16_t opt)
{
  switch(opt) 
	{
		case TN_SUPPRESS_GA :     /* If receive DO command with TN_SUPPRESS_GA option */
    sendIAC(s, WILL, opt);      /* Send WILL command with TN_SUPPRESS_GA */
    break;
		case TN_ECHO :      /* If receive DO command with TN_ECHO option */
//			sprintf(buf, "WELCOME to W5500 Telnet Server!\r\nUser : ");
 // 			socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);
    break;
		default :
    sendIAC(s, WONT, opt);
  } 	
}
void dontopt(uint16_t opt)
{
  switch(opt) 
	{
		case TN_TRANSMIT_BINARY :
		case TN_ECHO :
		case TN_SUPPRESS_GA :     /* If receive DONT command with TN_SUPPRESS_GA option */
    if(remote[opt] == 0) 
		{      /* Set the TN_SUPPRESS_GA option */
      remote[opt] = 1;     
    }
    break;
		default: break;
  } 	
}

void tel_input(Socket *s)
{
  uint8_t c;
  uint8_t input_command[] ="\r\nCommand:";	
	
	while(1)
	{
    if(socketReceive(s, &c, sizeof(c), &length, 0)) break;      /* If there the received data is 0, break 如果接收到的数据为0 */
    if(user_state == LOGOUT) break;     /* If the user's state is LOGOUT, break */ 

		if(c != IAC)
		{
			data_buf[buf_index++] = c;      /* Save the received data to data_buf 接收到的数据保存到缓冲区*/
			
      if(user_state != PASS_WORD) 
			{  				
        sprintf(buf, "%c", c);
				socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);
      }
			else
			{			
				if((c != '\n')&&(c != '\r')) 
				{
					sprintf(buf, "*");
					socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);	
				}					
			}
					
      if(c == '\n') 
			{     /* If receive an '\n' ASCII code 如果接收到一个‘\0’*/
        if(buf_index > 1) 
				{          
          if(data_buf[buf_index-2] == '\r') 
					{
            data_buf[buf_index-2] = '\0';
          } 
					else 
					{
            data_buf[buf_index-1] = '\0';
          }
          
          if(user_state != LOGIN) 			
						login(s,c); /* Call the login() to process login 登陆函数*/									
          else 
	           telnet_menu(s,data_buf);					     /* Process the received data处理接收到的数据 */
          
          if(user_state == LOGIN) 
					{           
						socketSend(s, (uint8_t const *)input_command, 10, NULL, 0);
          }
        } 
				else 
				{ 
            socketSend(s, (uint8_t const *)input_command, 10, NULL, 0);					
//          send(s, input_command, 10); 
        }
        buf_index = 0;
      }		
		
			continue; 
		}
		if(socketReceive(s, &c, sizeof(c), &length, 0)) break;
		
		switch(c) 
		{
      case WILL :
        if(socketReceive(s, &c, sizeof(c), &length, 0)) break;
        willopt(s, c);      /* Call the willopt() to process WILL command 调用willopt()*/
        break;
      case WONT :
        if(socketReceive(s, &c, sizeof(c), &length, 0)) break;
        wontopt(s, c);      /* Call the wontopt() to process WONT command */
        break;
      case DO :
        if(socketReceive(s, &c, sizeof(c), &length, 0)) break;
        doopt(s, c);      /* Call the doopt() to process DO command */
        break;
      case DONT :
        if(socketReceive(s, &c, sizeof(c), &length, 0)) break;
        dontopt(c);     /* Call the dontopt() to process DONT command */
        break;
      case IAC :
        break;   			
		}
		break;
	}
}



void init_telopt(Socket *s)
{
//  sendIAC(s, DO, TN_ENVIRONMENT);   //发送IAC+命令码+选项码到客户端  WILL:251   TN_ECHO:1   DO:253     TN_ENVIRONMENT:0X24
//  sendIAC(s, WILL, TN_ECHO);      /* Negotiate ECHO option */
	
	sendIAC(s, WILL, TN_ECHO);             //WILL:251   TN_ECHO:1
	sendIAC(s, WILL, TN_SUPPRESS_GA);        //     TN_SUPPRESS_GA:3
	
  sprintf(buf, "Welcome To IP-PDU Telnet Server!\r\nUser: ");
	socketSend(s, (uint8_t const *)buf, strlen(buf), NULL, 0);		
}

void TELNETS(Socket *s)   //0  ， 23
{
	
	  switch(s->state) 
		{
			case TCP_STATE_ESTABLISHED:
				if(ch_status[0] == ready_state) 
				{  
					init_telopt(s);     /* Initialize and negotiate the options 发送IAC+命令码+选项码到客户端  */
					ch_status[0] = connected_state;  
				}	
				osDelayTask(50);
				if(socketReceive(s, buffer, sizeof(buffer), &length, 0) == 0)  //接收到的数据大于零
				{  				
					tel_input(s);     /* If there is any received data, process it如果收到数据处理它 */     					
				}				
				break;
			case TCP_STATE_CLOSE_WAIT:
				socketClose(s);
				break;	
				
		}

}



void TelnetTask(void *param)
{
	error_t error;
	Socket *telnet_serverSocket;
	Socket *telnet_clientSocket;
	IpAddr telnet_clientIpAddr;
	uint16_t telnet_clientPort;
	
	telnet_serverSocket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);
	
	ch_status[0] = ready_state;  
	user_state = USER_NAME;
	
	//Bind the newly created socket to port 23
	error = socketBind(telnet_serverSocket, &IP_ADDR_ANY, 23);
	//Any error to report?
	if(error) 
	{
		ch_status[0] = close_state; 
		socketClose(telnet_serverSocket);
	}	
	
	//Place socket in listening state
	error = socketListen(telnet_serverSocket, 0);	
	
	//Accept an incoming connection
	telnet_clientSocket = socketAccept(telnet_serverSocket, &telnet_clientIpAddr, &telnet_clientPort);	
	
   while(1)
   {	
		 if(ONorrOFF_telnet==1)
		 {
				TELNETS(telnet_clientSocket);
				if(telnet_clientSocket->state==TCP_STATE_CLOSED)
				{
						socketClose(telnet_serverSocket);
						socketClose(telnet_clientSocket);
						osDelayTask(200); 
						telnet_serverSocket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);
						ch_status[0] = ready_state;  
						user_state = USER_NAME;	
						//Bind the newly created socket to port 23
						error = socketBind(telnet_serverSocket, &IP_ADDR_ANY, 23);
						//Any error to report?
						if(error) 
						{
							ch_status[0] = close_state; 
							socketClose(telnet_serverSocket);
						}			
						//Place socket in listening state
						error = socketListen(telnet_serverSocket, 0);	
						//Accept an incoming connection
						telnet_clientSocket = socketAccept(telnet_serverSocket, &telnet_clientIpAddr, &telnet_clientPort);					
				}			 
		 }
		 
      osDelayTask(500); 
		  
		  
   }
}
void Telnet_init(void)
{
	
	osCreateTask("telnet init", TelnetTask, NULL, 1000, 3);
		
}