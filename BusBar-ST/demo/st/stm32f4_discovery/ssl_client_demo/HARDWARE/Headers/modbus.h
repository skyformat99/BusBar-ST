#ifndef _MODBUS_H_
#define _MODBUS_H_

#include "ip_info.h"


int CRC16_2(char* pchMsg, char wDataLen);
void modbus_rtu(void);

#endif                                                  