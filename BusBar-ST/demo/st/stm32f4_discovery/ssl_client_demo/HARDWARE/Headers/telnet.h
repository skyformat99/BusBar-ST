#ifndef _TELNET_H_
#define _TELNET_H_
#include "ip_info.h"

#define close_state 0
#define ready_state 1
#define connected_state 2

#define IPPORT_TELNET 23            // Telnet port
#define LINELEN 400
#define DATA_BUF_SIZE 100

#define USER_NAME 1
#define	PASS_WORD 2
#define	LOGIN 3
#define	LOGOUT 4

/* Telnet Commands */
#define	IAC 0xFF                    // Interpret as command
#define WILL 251
#define WONT 252
#define DO 253
#define DONT 254 
#define CMD_IAC		 255
/* Telnet Commands end */

/* Telnet options */
#define NOPTIONS 6

#define TN_TRANSMIT_BINARY 0	    // TelNet transmit binary
#define TN_ECHO 1
#define TN_SUPPRESS_GA 3            // Supress Go Ahead
#define TN_STATUS 5
#define TN_TIMING_MARK 6
#define EXOPL 0xff	            // EXtended OPtion List
#define TN_TERMINAL_TYPE 0x18
#define TN_NE_WIN_SIZE 0x1f         // TelNet Negotiate Window SIZE
#define TN_ENVIRONMENT 0x24
#define TN_NEW_ENVIRONMENT 0x27
/* Telnet options end */

void Telnet_init(void);

#endif