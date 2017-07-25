#include "web.h"

OsSemaphore connectionSemaphore;

//Credentials
char_t *dhParams = NULL;
size_t dhParamsLength = 0;
char_t *serverRsaCert = NULL;
size_t serverRsaCertLength = 0;
char_t *serverRsaPrivateKey = NULL;
size_t serverRsaPrivateKeyLength = 0;
char_t *serverDsaCert = NULL;
size_t serverDsaCertLength = 0;
char_t *serverDsaPrivateKey = NULL;
size_t serverDsaPrivateKeyLength = 0;
char_t *serverEcdsaCert = NULL;
size_t serverEcdsaCertLength = 0;
char_t *serverEcdsaPrivateKey = NULL;
size_t serverEcdsaPrivateKeyLength = 0;
char_t *trustedCaList = NULL;
size_t trustedCaListLength = 0;



//Session cache
TlsCache *tlsCache = NULL;

HttpServerSettings httpServerSettings;
HttpConnection httpConnections[APP_HTTP_MAX_CONNECTIONS];
HttpServerContext httpServerContext;


char hdrFmt[]=
"HTTP/1.0 200 OK\r\n"
"Content-Type: text/html\r\n"
"\r\n";


////Credentials
//char_t *dhParams = NULL;
//size_t dhParamsLength = 0;

//函数返回0-10
char set16_to10(char data)
{
	if(data>=0x30)        //0X30: 0   data>0
		{
			switch(data)
			{
					case 'A':
					case 'a':
						return 10;
					case 'B':
					case 'b':
						return 11;
					case 'C':
					case 'c':
						return 12;
					case 'D':
					case 'd':
						return 13;
					case 'E':
					case 'e':
						return 14;
					case 'F':
					case 'f':
						return 15;
					case '0':
						return 0;
					case '1':
						return 1;
					case '2':
						return 2;
					case '3':
						return 3;
					case '4':
						return 4;
					case '5':
						return 5;
					case '6':
						return 6;
					case '7':
						return 7;
					case '8':
						return 8;
					case '9':
						return 9;
					default:
						return 0;
			}
		}
		return data;
}

//函数返回0-F
char show_data(char data)
{
		char ret_data='0';
		if(data>0&&data<16)          // 0< data <16 
		{
				switch (data)
				{
						case 0x01:
							ret_data='1';
							return ret_data;
						case 0x02:
							ret_data='2';
							return ret_data;
						case 0x03:
							ret_data='3';
							return ret_data;
						case 0x04:
							ret_data='4';
							return ret_data;
						case 0x05:
							ret_data='5';
							return ret_data;
						case 0x06:
							ret_data='6';
							return ret_data;
						case 0x07:
							ret_data='7';
							return ret_data;
						case 0x08:
							ret_data='8';
							return ret_data;
						case 0x09:
							ret_data='9';
							return ret_data;
						case 0x0A:
							ret_data='A';
							return ret_data;
						case 0x0B:
							ret_data='B';
							return ret_data;
						case 0x0C:
							ret_data='C';
							return ret_data;
						case 0x0D:
							ret_data='D';
							return ret_data;
						case 0x0E:
							ret_data='E';
							return ret_data;
						case 0x0F:
							ret_data='F';
							return ret_data;
						default:
							break;
				}
		}
		return ret_data;
}


/**
 * @brief SSL/TLS initialization callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] tlsContext Pointer to the SSL/TLS context
 **/

error_t httpServerTlsInitCallback(HttpConnection *connection,
   TlsContext *tlsContext)
{
   error_t error;

   //Set the PRNG algorithm to be used
   error = tlsSetPrng(tlsContext, YARROW_PRNG_ALGO, &yarrowContext);
   //Any error to report?
   if(error) return error;

   //Session cache that will be used to save/resume TLS sessions
   error = tlsSetCache(tlsContext, tlsCache);
   //Any error to report?
   if(error) return error;

   //Client authentication is optional
   error = tlsSetClientAuthMode(tlsContext, TLS_CLIENT_AUTH_NONE);
   //Any error to report?
   if(error) return error;

#if (TLS_DHE_RSA_SUPPORT == ENABLED || TLS_DHE_DSS_SUPPORT == ENABLED || TLS_DH_ANON_SUPPORT)
   //Import Diffie-Hellman parameters
   error = tlsSetDhParameters(tlsContext, dhParams, dhParamsLength);
   //Any error to report?
   if(error) return error;
#endif

   //Import the server's RSA certificate
   error = tlsAddCertificate(tlsContext, serverRsaCert,
      serverRsaCertLength, serverRsaPrivateKey, serverRsaPrivateKeyLength);
   //Any error to report?
   if(error) return error;

   //Import the server's DSA certificate
   error = tlsAddCertificate(tlsContext, serverDsaCert,
      serverDsaCertLength, serverDsaPrivateKey, serverDsaPrivateKeyLength);
   //Any error to report?
   if(error) return error;

   //Import the server's ECDSA certificate
   error = tlsAddCertificate(tlsContext, serverEcdsaCert,
      serverEcdsaCertLength, serverEcdsaPrivateKey, serverEcdsaPrivateKeyLength);
   //Any error to report?
   if(error) return error;

   //Import the list of trusted CA certificates
   error = tlsSetTrustedCaList(tlsContext, trustedCaList, trustedCaListLength);
   //Any error to report?
   if(error) return error;

   //Successful processing
   return NO_ERROR;
}



/**
 * @brief URI not found callback
 * @param[in] connection Handle referencing a client connection
 * @param[in] uri NULL-terminated string containing the path to the requested resource
 * @return Error code
 **/

error_t httpServerUriNotFoundCallback(HttpConnection *connection,
   const char_t *uri)
{		
   error_t error;
   size_t n;
   char_t *buffer;
	
	 if(!strcasecmp(uri, "/getlogo"))
	 {
		  buffer = connection->buffer + 384;
		 
		  n = sprintf(buffer,"%d?",language);		 
	 }	 
	 else if(!strcasecmp(uri, "/login"))
	 {
		  char a[128];
		  char b[128];
		  char i;
		 
			buffer = connection->request.queryString;
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);		
			memset(b,0,sizeof(char)*128);
			reqorder(buffer,b,1);
		 
		  if(strlen(a) > 0 && strlen(b) > 0)
			{
					if(strcmp(user,a)==0 && strcmp(psd,b)==0)
					{
							n = sprintf(buffer,"OK");
					}	
					else
					{
							n = sprintf(buffer,"ERR");
					}					
			}
			else
			{
					n = sprintf(buffer,"ERR");
			}		 
	 }
	 else if(!strcasecmp(uri, "/gethome"))
	 {
		  buffer = connection->buffer + 384;
		 
		  n = sprintf(buffer,"%d?",language);		 
	 }
	 else if(!strcasecmp(uri, "/sethome"))
	 {
			char a[128];
			buffer = connection->request.queryString;
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);	
			language = atoi(a);
			if(language==1||language==0)
			{
				 I2cWrite(31,language);          //language
				 n = sprintf(buffer,"OK");
			}
			else n = sprintf(buffer,"ERR"); 
	 }
	 else if(!strcasecmp(uri, "/getstatus"))
	 {
		  char a[128];
		  char line=0;

			buffer = connection->request.queryString;
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);				 
		  line = atoi(a); 		 
		  buffer = connection->buffer + 384;
		 
		  if(cur_dc_ac)  //ac
			{
					n = sprintf(buffer,"%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?"
														,Tcur[line][0],Tvol[line][0],Energy8207[line]
														,Tcur_alarm[line]
														,Tvol_alarm[line]
														,LINE_NUM
														,language,1,tem[0],hum[0]
														,(tem[0]<tem[1] || tem[0]>tem[2])?1:0
														,(hum[0]<hum[1] || hum[0]>hum[2])?1:0
														,cur_dc_ac);				
			}
			else           //dc
			{
					n = sprintf(buffer,"%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?"
														,Tcur[0][0],Tvol[0][0],Energy8207_dc
														,Tcur_alarm[0]
														,Tvol_alarm[0]
														,LINE_NUM
														,language,1,tem[0],hum[0]
														,(tem[0]<tem[1] || tem[0]>tem[2])?1:0
														,(hum[0]<hum[1] || hum[0]>hum[2])?1:0
														,cur_dc_ac);					
			}		
	 }


	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	  else if(!strcasecmp(uri, "/getlimit"))
	  {	 
				buffer = connection->buffer + 384;
			 
				n = sprintf(buffer,"%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?%d?"
														,Tcur[0][0],Tcur[0][1],Tcur[0][2]
														,Tcur[1][0],Tcur[1][1],Tcur[1][2]
														,Tcur[2][0],Tcur[2][1],Tcur[2][2]
														,Tvol[0][0],Tvol[0][1],Tvol[0][2]
														,Tvol[1][0],Tvol[1][1],Tvol[1][2]
														,Tvol[2][0],Tvol[2][1],Tvol[2][2]
														,LINE_NUM,language
														,tem[0],tem[1],tem[2]
														,hum[0],hum[1],hum[2]);		 
		 
	 }	 
	 else if(!strcasecmp(uri, "/setlimit"))
	 {
		  char i;
			char a[128];
			int line;
			int min;
			int max;
		 
      buffer = connection->request.queryString;
		 
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);
			line = atoi(a);
			if(line<=3 && line>=1)
			{
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,1);
					min = atoi(a);
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,2);
					max = atoi(a);
					Tcur[line -1][1]=min;
					Tcur[line -1][2]=max;
					I2cWrite_2(13+(line-1)*8,min/256%256);
					I2cWrite_2(14+(line-1)*8,min%256);
					I2cWrite_2(15+(line-1)*8,max/256%256);
					I2cWrite_2(16+(line-1)*8,max%256);
					
					n = sprintf(buffer,"OK");
			}
			else if(line<=6 && line>=4)
			{
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,1);
					min = atoi(a);
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,2);
					max = atoi(a);
					Tvol[line-4][1] = min;
					Tvol[line-4][2] = max;
					I2cWrite_2(9+(line-4)*8,min/256);
					I2cWrite_2(10+(line-4)*8,min%256);
					I2cWrite_2(11+(line-4)*8,max/256);
					I2cWrite_2(12+(line-4)*8,max%256);
					n = sprintf(buffer,"OK");
			}
			else if(line==7)
			{
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,1);
					min = atoi(a);
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,2);
					max = atoi(a);
					tem[1] = min;
					tem[2] = max;
					I2cWrite(226,min);
					I2cWrite(227,max);
				
					n = sprintf(buffer,"OK");
			}
			else if(line==8)
			{	
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,1);
					min = atoi(a);
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,2);
					max = atoi(a);
					hum[1] = min;
					hum[2] = max;
					I2cWrite(228,min);
					I2cWrite(229,max);
				
					n = sprintf(buffer,"OK");
			}
			else
			{
					n = sprintf(buffer,"ERR");
					return;
			}		 	 
	 }		 
	 else if(!strcasecmp(uri, "/getdevice"))
	 {		 
		  buffer = connection->buffer + 384;
		 
		  n = sprintf(buffer,"%d?%s?%d?%d?%d?%d?%d?",language,devicename,ser,LINE_NUM,cur_dc_ac,ONorOFF_sound,baud);

	 }	
	 else if(!strcasecmp(uri, "/setdevice"))
	 {
			char a[128];
		  char d[128];
		  char i;
      buffer = connection->request.queryString;
			
			memset(d,0,sizeof(char)*128);
			reqorder(buffer,d,0);		
		  strncpy(devicename,d,sizeof(char)*10);
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,1);
			ONorOFF_sound =  atoi(a);	
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,2);
			ser =  atoi(a);	
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,3);
			baud =  atoi(a);	

      for(i=0;i<10;i++)
			{
				I2cWrite(34+i,devicename[i]);
			}	
		 
		  I2cWrite(30,ONorOFF_sound);
			I2cWrite(224,ser);
			I2cWrite(225,baud); 
			
			if(strlen(d)>10) 
				n = sprintf(buffer,"outlong");
			else 
				n = sprintf(buffer,"OK");
	 }
		else if(strncmp(uri,"/energyzero",11)==0)
		{
			char a[128];
			char order=10;
			
			buffer = connection->request.queryString;
			
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);	
			order = atoi(a);
			if(order==0)
			{
				Energy8207[0]=0;
				I2cWrite_2(0,0);
				I2cWrite_2(1,0);
				I2cWrite_2(2,0);				
			}
			else if(order==1)
			{
				Energy8207[1]=0;
				I2cWrite_2(3,0);
				I2cWrite_2(4,0);
				I2cWrite_2(5,0);
			}
			else if(order==2)
			{
				Energy8207[2]=0;
				I2cWrite_2(6,0);
				I2cWrite_2(7,0);
				I2cWrite_2(8,0);
			}
			else if(order==3)
			{
				Energy8207_dc = 0;
				I2cWrite_2(65,0);
				I2cWrite_2(66,0);
				I2cWrite_2(67,0);								
			}	
			n = sprintf(buffer,"OK");
		} 	 
	 else if(!strcasecmp(uri, "/getuser"))
	 {
		  char i;
		 
		  buffer = connection->buffer + 384;
		 	 
		  n = sprintf(buffer,"%d?%s?%s?",language,user,psd);		  
	 }
	 else if(!strcasecmp(uri, "/setuser"))
	 {
			char a[128];
		  char b[128];
		  char i;
      buffer = connection->request.queryString;	
		 
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);
			memset(b,0,sizeof(char)*128);
			reqorder(buffer,b,1);			

			if(strlen(a)>10||strlen(b)>10)
			{
					n = sprintf(buffer,"outlong");
			}	
			else
			{
					strncpy(user,a,10);	
					strncpy(psd,b,10);
					for(i=0;i<10;i++)
					{
							I2cWrite(44+i,user[i]);
							I2cWrite(54+i,psd[i]);                
					}	
					n = sprintf(buffer,"OK");	
			}
			
	 }
	 else if(!strcasecmp(uri, "/getnetinfo"))
	 { 
		  buffer = connection->buffer + 384;
		 
      //Format XML data
		
      n = sprintf(buffer, "%d?%d?%d?%d?",language,webport[0]*256+webport[1],https_port[0]*256+https_port[1],ONorrOFF_SSL);
      n += sprintf(buffer + n,"%s?%s?%s?%s?",ip_v4,ms_v4,gw_v4,dnsinfo); 
	 }	 
	 else if(!strcasecmp(uri, "/setnetinfo"))
	 {
			char ip_set[128];
			char mask_set[128];
			char gw_set[128];
			char dns_set[128];		 
			char a[128];
		  char index;
      buffer = connection->request.queryString;	
			
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);	
		  index = atoi(a);
		  
//			if(index==1)
//			{
//				int port_ht;
//				int port_hts;
//				memset(a,0,sizeof(char)*128);
//				reqorder(buffer,a,1);	
//				ONorrOFF_SSL = atoi(a);
//				memset(a,0,sizeof(char)*128);
//				reqorder(buffer,a,2);	
//				port_ht = atoi(a);	
//				webport[0]=port_ht>>8;
//				webport[1]=port_ht;
//				memset(a,0,sizeof(char)*128);
//				reqorder(buffer,a,3);	
//				port_hts = atoi(a);
//				https_port[0]=port_hts>>8;
//				https_port[1]=port_hts;	
//				I2cWrite(22,webport[0]);
//				I2cWrite(23,webport[1]);        //HTTP
//				I2cWrite(24,https_port[0]);
//				I2cWrite(25,https_port[1]);		   //HTTPS				
//				I2cWrite(27,ONorrOFF_SSL);		
//				n = sprintf(buffer,"OK");
//			}
			if(index==2)
			{
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,1);		 
				strncpy(ip_set,a,sizeof(char)*128);	
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,2);		 
				strncpy(mask_set,a,sizeof(char)*128);
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,3);		 
				strncpy(gw_set,a,sizeof(char)*128);	
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,4);		 
				strncpy(dns_set,a,sizeof(char)*128);				
				ip1 =mytok(ip_set,0);
				ip2 =mytok(ip_set,1);
				ip3 =mytok(ip_set,2);
				ip4 =mytok(ip_set,3);		
				sprintf(ip_v4,"%d.%d.%d.%d",ip1,ip2,ip3,ip4);
				I2cWrite(0,ip1);
				I2cWrite(1,ip2);
				I2cWrite(2,ip3);
				I2cWrite(3,ip4);			
				ms1 =mytok(mask_set,0);
				ms2 =mytok(mask_set,1);
				ms3 =mytok(mask_set,2);
				ms4 =mytok(mask_set,3);
				sprintf(ms_v4,"%d.%d.%d.%d",ms1,ms2,ms3,ms4);	
				I2cWrite(4,ms1);
				I2cWrite(5,ms2);
				I2cWrite(6,ms3);
				I2cWrite(7,ms4);
				gw1 =mytok(gw_set,0);
				gw2 =mytok(gw_set,1);
				gw3 =mytok(gw_set,2);
				gw4 =mytok(gw_set,3);
				sprintf(gw_v4,"%d.%d.%d.%d",gw1,gw2,gw3,gw4);	
				I2cWrite(8,gw1);
				I2cWrite(9,gw2);
				I2cWrite(10,gw3);
				I2cWrite(11,gw4);
				memset(dnsinfo,0,sizeof(char)*20);
				sprintf(dnsinfo,"%d.%d.%d.%d"
				, mytok(dns_set,0)
				, mytok(dns_set,1)
				, mytok(dns_set,2)
				, mytok(dns_set,3));
				I2cWrite(12,mytok(dns_set,0));
				I2cWrite(13,mytok(dns_set,1));
				I2cWrite(14,mytok(dns_set,2));
				I2cWrite(15,mytok(dns_set,3));	
				n = sprintf(buffer,"OK");
			}
			else
			{
				n = sprintf(buffer,"ERR");
			}	
	 }	
	 else if(!strcasecmp(uri, "/getsnmp"))
	 { 
		  buffer = connection->buffer + 384;
	
      n = sprintf(buffer,"%d.%d.%d.%d?%d.%d.%d.%d?%d?%d?",trapip1[0],trapip1[1],trapip1[2],trapip1[3],trapip2[0],trapip2[1],trapip2[2],trapip2[3],ONorrOFF_telnet,language);
      n += sprintf(buffer + n,"%d?%s?%s?%s?",ONorrOFF_SNMPv3,snmpsysuser,snmp_authkey,snmp_privkey);
		 
	 }	
	 else if(!strcasecmp(uri, "/setsnmp"))
	 {
			char a[128];
		  char i;
		  char index;
      buffer = connection->request.queryString;	
			
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);	
		  index = atoi(a);
      
			if(index==1)
			{
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,1);	
				trapip1[0] =mytok(a,0);
				trapip1[1] =mytok(a,1);
				trapip1[2] =mytok(a,2);
				trapip1[3] =mytok(a,3);	
				sprintf(&trap_ip[0][0],"%d.%d.%d.%d",trapip1[0],trapip1[1],trapip1[2],trapip1[3]);
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,2);	
				trapip2[0] =mytok(a,0);
				trapip2[1] =mytok(a,1);
				trapip2[2] =mytok(a,2);
				trapip2[3] =mytok(a,3);	
				sprintf(&trap_ip[1][0],"%d.%d.%d.%d",trapip2[0],trapip2[1],trapip2[2],trapip2[3]);

				I2cWrite(112,trapip1[0]);	//trap1
				I2cWrite(113,trapip1[1]);
				I2cWrite(114,trapip1[2]);
				I2cWrite(115,trapip1[3]);
				
				I2cWrite(116,trapip2[0]);	//trap2
				I2cWrite(117,trapip2[1]);
				I2cWrite(118,trapip2[2]);
				I2cWrite(119,trapip2[3]);	
				n = sprintf(buffer,"OK");
			}
			else if(index==2)
			{
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,1);	
				ONorrOFF_SNMPv3 = atoi(a);
				I2cWrite(28,ONorrOFF_SNMPv3);
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,2);		
				strncpy(snmpsysuser,a,16);
				memset(a,0,sizeof(char)*128);				
				reqorder(buffer,a,3);		
				
				if(strlen(a)<8) 
					n = sprintf(buffer,"lesslong");	
				else
				{
					if(strlen(a)>16) 
						n = sprintf(buffer,"outlong");	
					else
					{
							DISABLE_INT();
							strncpy(snmp_authkey,a,16);	
							memset(a,0,sizeof(char)*128);
							reqorder(buffer,a,4);		
							strncpy(snmp_privkey,a,16);		

							for(i=0;i<16;i++)
							{
									I2cWrite(74+i,snmpsysuser[i]);
									I2cWrite(90+i,snmp_authkey[i]);
									I2cWrite_2(68+i,snmp_privkey[i]);
							}			
							n = sprintf(buffer,"OK");
							ENABLE_INT();
					}
				}							
			}
			else if(index==3)
			{
				memset(a,0,sizeof(char)*128);
				reqorder(buffer,a,1);	
				ONorrOFF_telnet = atoi(a);
				I2cWrite(29,ONorrOFF_telnet);		
				n = sprintf(buffer,"OK");
			}
			else
			{
				n = sprintf(buffer,"ERR");
			}		
	 }		 
	 else if(!strcasecmp(uri, "/getsmtp"))
	 {	 
				buffer = connection->buffer + 384;
			 
				n = sprintf(buffer,"%s?%s?%s?%d?%s?%d?",smtpuser,smtppsd,smtpserver,smtpport,To_Email,language);		 
		 
	 }	
	 else if(!strcasecmp(uri, "/setsmtp"))
	 {
		  char aa_ch;
			char c[128];
		  char deluser[25];			
		  char i,j;
			int input_port;
			buffer = connection->request.queryString;	
		 			
			memset(c,0,sizeof(char)*128);
			reqorder(buffer,c,0);
			strncpy(smtpuser,c,25);	
			if(strlen(c)>25)
			{
					n = sprintf(buffer,"outlong");
			}
			else
			{
					memset(c,0,sizeof(char)*128);
					reqorder(buffer,c,1);	
					strncpy(smtppsd,c,25);
					memset(c,0,sizeof(char)*128);
					reqorder(buffer,c,2);	
					strncpy(smtpserver,c,25);
					memset(c,0,sizeof(char)*128);
					reqorder(buffer,c,3);	
					smtpport = atoi(c);	
					memset(c,0,sizeof(char)*128);
					reqorder(buffer,c,4);	
					strncpy(To_Email,c,25);	
					for(i=0;i<25;i++)
					{
							I2cWrite(124+i,smtpuser[i]);
							I2cWrite(149+i,smtppsd[i]);
							I2cWrite(174+i,smtpserver[i]);
							I2cWrite(199+i,To_Email[i]);							
					}	
					n = sprintf(buffer,"OK");
			}	 
	 }
	 else if(!strcasecmp(uri, "/smtptest"))
	 {
		  error_t error;
		  char list[2];
			char a[128];
		  char b[128];
      SmtpAuthInfo authInfo;
      SmtpMail mail;
      SmtpMailAddr recipients[5];	
			SmtpMailAddr to_pients;	

			authInfo.interface = NULL;
		 
		  buffer = connection->request.queryString;	
		 
      //Initialize structures to zero
      memset(&authInfo, 0, sizeof(authInfo));
      memset(&mail, 0, sizeof(mail));
      memset(recipients, 0, sizeof(recipients));
		  memset(&to_pients, 0, sizeof(to_pients));

      //Set the relevant PRNG algorithm to be used
      authInfo.prngAlgo = YARROW_PRNG_ALGO;
      authInfo.prngContext = &yarrowContext;	
		 
			memset(a,0,sizeof(char)*128);             
			reqorder(buffer,a,0);			          //发件用户
		  strncpy(smtpuser,a,25);	
		  authInfo.userName = strDuplicate(smtpuser);
			
			memset(a,0,sizeof(char)*128);             
			reqorder(buffer,a,1);			          
		  strncpy(smtppsd,a,25);	
		  authInfo.password  = strDuplicate(smtppsd);			//密码
			
			memset(a,0,sizeof(char)*128);             
			reqorder(buffer,a,2);			         
		  strncpy(smtpserver,a,25);	
		  authInfo.serverName  = strDuplicate(smtpserver);			//服务器

			memset(a,0,sizeof(char)*128);             
			reqorder(buffer,a,3);			         
		  authInfo.serverPort = atoi(a);			//端口号
			
			authInfo.useTls = FALSE;				

			memset(a,0,sizeof(char)*128);             
			reqorder(buffer,a,4);			         		
      recipients[0].name = NULL;
      recipients[0].addr = strDuplicate(a);
      recipients[0].type = SMTP_RCPT_TYPE_TO;	
      to_pients.name = NULL;
      to_pients.addr = strDuplicate(smtpuser);	
			to_pients.type = NULL;			
			
			mail.recipients = &recipients[0];
			mail.from = to_pients;
		  mail.dateTime = NULL;
			mail.recipientCount = 5;
			memset(a,0,sizeof(char)*128);
			sprintf(a,"SMTP Test");
			mail.subject = strDuplicate(a);   //主题
			memset(a,0,sizeof(char)*128);
			sprintf(a,"Hello World!");
			mail.body = strDuplicate(a);      //内容
			
			error = smtpSendMail(&authInfo, &mail);
			
//		 error =	smtpClientTest();
			
			if(error)
			{
				n = sprintf(buffer,"ERR");
			}
			else
			{
				n = sprintf(buffer,"OK");
			}		
			
	 }	
	 else if(!strcasecmp(uri, "/getsys"))
	 {
		  buffer = connection->buffer + 384;
		 
		  n = sprintf(buffer,"%d?",language);		 
	 }		 
	 else if(!strcasecmp(uri, "/setsys"))
	 {
			char a[128];
		  char i;
		  char index;
      buffer = connection->request.queryString;	
			
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);	
		  index = atoi(a);
			if(index==0)
			{
					devicedown();	
			}
			else if(index==1)
			{	
					iicresetdata();    //恢复出厂设置
					devicedown();								
			}	
			else
			{
				n = sprintf(buffer,"ERR");
			}
			n = sprintf(buffer,"OK");
	 }
	 else if(!strcasecmp(uri, "/getmac"))
	 { 
		  buffer = connection->buffer + 384;
	
      n = sprintf(buffer ,"%c%c:%c%c:%c%c:%c%c:%c%c:%c%c?%d?0x%x?0x%x?0x%x?",show_data(mac1/16),show_data(mac1%16),show_data(mac2/16),show_data(mac2%16),
																											show_data(mac3/16),show_data(mac3%16),show_data(mac4/16),show_data(mac4%16),
																											show_data(mac5/16),show_data(mac5%16),show_data(mac6/16),show_data(mac6%16),
																											language,correct_flag_phase_ac[0],correct_flag_phase_ac[1],correct_flag_phase_ac[2]);
		 
	 }	 
	 else if(!strcasecmp(uri, "/correct"))
	 {
			char a[128];
		  char i;
		  char order=10;
      buffer = connection->request.queryString;	
			
			memset(a,0,sizeof(char)*128);
			reqorder(buffer,a,0);	
			order = atoi(a);
		 
			if(order==3) 
			{
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,1);	

					mac1 =set16_to10(a[0])*16+set16_to10(a[1]);
					mac2 =set16_to10(a[3])*16+set16_to10(a[4]);
					mac3 =set16_to10(a[6])*16+set16_to10(a[7]);
					mac4 =set16_to10(a[9])*16+set16_to10(a[10]);
					mac5 =set16_to10(a[12])*16+set16_to10(a[13]);
					mac6 =set16_to10(a[15])*16+set16_to10(a[16]);
					
					memset(a,0,sizeof(char)*128);
					reqorder(buffer,a,2);	
					language = atoi(a);
												
					I2cWrite(16,mac1);
					I2cWrite(17,mac2);
					I2cWrite(18,mac3);
					I2cWrite(19,mac4);
					I2cWrite(20,mac5);
					I2cWrite(21,mac6);
					I2cWrite(31,language);
					n = sprintf(buffer,"OK");					
			}		 
		  else if(order==0)
			{
					correct_flag_ac[0]=1;
					n = sprintf(buffer,"OK");				
			}
		  else if(order==1)
			{
					correct_flag_ac[1]=1;
					n = sprintf(buffer,"OK");					
			}		
		  else if(order==2)
			{
					correct_flag_ac[2]=1;
					n = sprintf(buffer,"OK");				
			}		
			else if(order==11)                 
			{
					clear_zero_register_dc();
					n = sprintf(buffer,"OK");
			}				
			else if(order==12)
			{
					register_offset_dc[0]=1;               //直流offset
					n = sprintf(buffer,"OK");
			}
			else if(order==13)
			{
					register_offset_dc[2]=1;               //直流 IARMSOS offset
					n = sprintf(buffer,"OK");
			}				
			else if(order==4)
			{
					register_offset_dc[1]=1;               //直流校准
					n = sprintf(buffer,"OK");
			}	
			else if(order==14)
			{
					register_offset_dc[3]=1;               //直流功率增益
					n = sprintf(buffer,"OK");
			}					
			else if(order==5)                 
			{
					clear_zero_register_A();
					n = sprintf(buffer,"OK");
			}
			else if(order==9)                 
			{
					clear_zero_register_B();
					n = sprintf(buffer,"OK");
			}
			else if(order==10)                 
			{
					clear_zero_register_C();
					n = sprintf(buffer,"OK");
			}				
			else if(order==6)              
			{
					correct_flag_phase_ac[0]=1;
					n = sprintf(buffer,"OK");
			}
			else if(order==7)
			{
					correct_flag_phase_ac[1]=1;
					n = sprintf(buffer,"OK");
			}	
			else if(order==8)
			{
					correct_flag_phase_ac[2]=1;
					n = sprintf(buffer,"OK");
			}			 
			n = sprintf(buffer,"OK");
	 } 
   else
   {
      return ERROR_NOT_FOUND;
   }	 
      //Format HTTP response header
      connection->response.version = connection->request.version;
      connection->response.statusCode = 200;
      connection->response.keepAlive = connection->request.keepAlive;
      connection->response.noCache = TRUE;
      connection->response.contentType = mimeGetType(".xml");
      connection->response.chunkedEncoding = FALSE;
      connection->response.contentLength = n;
      //Send the header to the client  HTTP响应首部发送给客户端
   error = httpWriteHeader(connection);
      //Any error to report?
   if(error) return error;

      //Send response body 发送响应的内容
   error = httpWriteStream(connection, buffer, n);
      //Any error to report?
   if(error) return error;

      //Properly close output stream 适当关闭输出流
   error = httpCloseStream(connection);
      //Return status code
   return error;				 
	 
	 

}


/**
 * @brief HTTPS server initialization
 **/

error_t httpsServerInit(void)
{
   error_t error;
   uint_t i;
   uint32_t value;
   uint8_t seed[32];

	

		 //Generate a random seed
		 for(i = 0; i < 32; i += 4)
		 {
				//Wait for the RNG to contain a valid data
				while(RNG_GetFlagStatus(RNG_FLAG_DRDY) == RESET);

				//Get 32-bit random value
				value = RNG_GetRandomNumber();

				//Copy random value
				seed[i] = value & 0xFF;
				seed[i + 1] = (value >> 8) & 0xFF;
				seed[i + 2] = (value >> 16) & 0xFF;
				seed[i + 3] = (value >> 24) & 0xFF;
		 }

		 //PRNG initialization
		 error = yarrowInit(&yarrowContext);
		 //Any error to report?
		 if(error) return error;

		 //Properly seed the PRNG
		 error = yarrowSeed(&yarrowContext, seed, sizeof(seed));
		 //Any error to report?
		 if(error) return error;

//		 //Load Diffie-Hellman parameters
//		 error = resGetData(APP_SERVER_DH_PARAMS,  (uint8_t **) &dhParams, &dhParamsLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //Load server's RSA certificate
//		 error = resGetData(APP_SERVER_RSA_CERT, (uint8_t **) &serverRsaCert, &serverRsaCertLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //Load server's RSA private key
//		 error = resGetData(APP_SERVER_RSA_PRIVATE_KEY, (uint8_t **) &serverRsaPrivateKey, &serverRsaPrivateKeyLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //Load server's DSA certificate
//		 error = resGetData(APP_SERVER_DSA_CERT, (uint8_t **) &serverDsaCert, &serverDsaCertLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //Load server's DSA private key
//		 error = resGetData(APP_SERVER_DSA_PRIVATE_KEY, (uint8_t **) &serverDsaPrivateKey, &serverDsaPrivateKeyLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //Load server's ECDSA certificate
//		 error = resGetData(APP_SERVER_ECDSA_CERT, (uint8_t **) &serverEcdsaCert, &serverEcdsaCertLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //Load server's ECDSA private key
//		 error = resGetData(APP_SERVER_ECDSA_PRIVATE_KEY, (uint8_t **) &serverEcdsaPrivateKey, &serverEcdsaPrivateKeyLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //Load trusted CA certificates
//		 error = resGetData(APP_CA_CERT_BUNDLE, (uint8_t **) &trustedCaList, &trustedCaListLength);
//		 //Any error to report?
//		 if(error) return error;

//		 //TLS session cache initialization
//		 tlsCache = tlsInitCache(16);
//		 //Any error to report?
//		 if(!tlsCache) return ERROR_OUT_OF_MEMORY;

   //Get default settings
   httpServerGetDefaultSettings(&httpServerSettings);
   //Bind HTTP server to the desired interface
   httpServerSettings.interface = &netInterface[0];
//	 if(ONorrOFF_SSL)                                   //ssl--on
//	 {
//		 //HTTP over SSL/TLS
//		 httpServerSettings.useTls = TRUE;
//		 //Listen to port 443
//		 httpServerSettings.port =  https_port[0]*256+https_port[1];                            
//				//Callback functions
//		 httpServerSettings.tlsInitCallback = httpServerTlsInitCallback;
//	 }
//	 else
		 httpServerSettings.port =  webport[0]*256+webport[1];
   //Client connections
   httpServerSettings.maxConnections = APP_HTTP_MAX_CONNECTIONS;
   httpServerSettings.connections = httpConnections;
   //Specify the server's root directory
   strcpy(httpServerSettings.rootDirectory, "/www/");
   //Set default home page
	 strcpy(httpServerSettings.defaultDocument, "index.html");
   //Callback functions
//	 httpServerSettings.authCallback = httpServerAuthCallback;
//	 httpServerSettings.cgiCallback = httpServerCgiCallback;
   httpServerSettings.uriNotFoundCallback = httpServerUriNotFoundCallback;

   //HTTP server initialization
   error = httpServerInit(&httpServerContext, &httpServerSettings);
   //Failed to initialize HTTP server?
   if(error) return error;

   //Start HTTP server
   error = httpServerStart(&httpServerContext);
   //Failed to start server?
   if(error) return error;
	 

   //Successful processing
   return NO_ERROR;
}

void http_web_init(void)
{
		//   //HTTPS server initialization
    httpsServerInit();
}