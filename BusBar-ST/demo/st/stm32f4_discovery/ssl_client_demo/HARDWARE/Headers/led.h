#ifndef __LED_H
#define __LED_H
#include "sys.h"




//LED端口定义
#define LED0 PFout(6)	// run_led
#define LED1 PFout(7)	// 	 run_alarm
#define LED2 PFout(8)	//  run_mw
#define BEEP PFin(11)	// beep 

void LED_Init(void);//初始化		 
void run_led(char ch);
void run_mw(char ch);
void run_alm(char ch);
void beel(char ch);
void devicedown(void);
void IWDG_Init(void); 				    
#endif
