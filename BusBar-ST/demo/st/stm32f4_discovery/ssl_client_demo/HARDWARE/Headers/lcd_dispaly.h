#ifndef _LCD_DISPALY_H_
#define _LCD_DISPALY_H_

#include "ip_info.h"

extern u8 auto_hand_action;
extern u8 auto_tem_dis;
extern char button_iic_write;
extern char lcd_rest[2];

void display_init(void);

#endif