#ifndef _RN_8207_H_
#define _RN_8207_H_

extern char correct_flag_ac[3];  //交流校准标志
extern char correct_flag_phase_ac[3];  //交流相位校准标志
extern char register_offset_dc[4];   //直流偏置校准
extern char mw_led;

void RN8207Read(void);
void Read_energy();
void Init_8207(void);

#include "ip_info.h"

#endif                                                  