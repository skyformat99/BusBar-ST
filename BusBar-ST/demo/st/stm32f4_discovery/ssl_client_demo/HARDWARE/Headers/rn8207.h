#ifndef _RN_8207_H_
#define _RN_8207_H_

extern char correct_flag_ac[3];  //����У׼��־
extern char correct_flag_phase_ac[3];  //������λУ׼��־
extern char register_offset_dc[4];   //ֱ��ƫ��У׼
extern char mw_led;

void RN8207Read(void);
void Read_energy();
void Init_8207(void);

#include "ip_info.h"

#endif                                                  