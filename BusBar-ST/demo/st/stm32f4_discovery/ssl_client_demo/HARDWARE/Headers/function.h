#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include "ip_info.h"



char xor(char *buf,char len);             //“ÏªÚ–£—È

void reqorder(char *request,char *orderline,int counter);
error_t snmpAgentRandCallback(uint8_t *data, size_t length);
HttpAccessStatus httpServerAuthCallback(HttpConnection *connection,
   const char_t *user, const char_t *uri);
char mytok(char *src,int counter);


error_t sntpClientTest(void);

#endif