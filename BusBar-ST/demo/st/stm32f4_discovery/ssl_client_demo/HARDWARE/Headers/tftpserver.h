
#ifndef __TFTPSERVER_H_
#define __TFTPSERVER_H_

#include "core/net.h"
#include "core/ip.h"
#include "core/udp.h"
#include "core/socket.h"
#include "ipv4/ipv4.h"
#include "ip_info.h"
#define USER_FLASH_FIRST_PAGE_ADDRESS 0x8090000
#define  USE_IAP_TFTP

#define TFTP_OPCODE_LEN         2
#define TFTP_BLKNUM_LEN         2
#define TFTP_DATA_LEN_MAX       512
#define TFTP_DATA_PKT_HDR_LEN   (TFTP_OPCODE_LEN + TFTP_BLKNUM_LEN)        // 4  数据包头
#define TFTP_ERR_PKT_HDR_LEN    (TFTP_OPCODE_LEN + TFTP_ERRCODE_LEN)
#define TFTP_ACK_PKT_LEN        (TFTP_OPCODE_LEN + TFTP_BLKNUM_LEN)       //4 回应包头
#define TFTP_DATA_PKT_LEN_MAX   (TFTP_DATA_PKT_HDR_LEN + TFTP_DATA_LEN_MAX)  //数据包长度
#define TFTP_MAX_RETRIES        3
#define TFTP_TIMEOUT_INTERVAL   5



typedef struct
{
  int op;    /*WRQ */
  /* last block read */
  char data[TFTP_DATA_PKT_LEN_MAX];
  int  data_len;
  /* destination ip:port */
  Ipv4Addr to_ip;
  int to_port;
  /* next block number */
  int block;
  /* total number of bytes transferred */
  int tot_bytes;
  /* timer interrupt count when last packet was sent */
  /* this should be used to resend packets on timeout */
  unsigned long long last_time;
 
}tftp_connection_args;


/* TFTP opcodes as specified in RFC1350   */
typedef enum {
  TFTP_RRQ = 1,
  TFTP_WRQ = 2,
  TFTP_DATA = 3,
  TFTP_ACK = 4,
  TFTP_ERROR = 5
} tftp_opcode;


/* TFTP error codes as specified in RFC1350  */
typedef enum {
  TFTP_ERR_NOTDEFINED,
  TFTP_ERR_FILE_NOT_FOUND,
  TFTP_ERR_ACCESS_VIOLATION,
  TFTP_ERR_DISKFULL,
  TFTP_ERR_ILLEGALOP,
  TFTP_ERR_UKNOWN_TRANSFER_ID,
  TFTP_ERR_FILE_ALREADY_EXISTS,
  TFTP_ERR_NO_SUCH_USER,
} tftp_errorcode;

extern u8 *Ex_board_data;

void IAP_tftpd_init(void);


#endif

