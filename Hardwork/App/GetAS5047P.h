#ifndef _GETAS5047P_H_
#define _GETAS5047P_H_

#include <math.h>
#include "main.h"
#include "AS5047P.h"
#include "MotorConfig.h"

// 获取编码器原始值（0~16383）
uint16_t Get_Encoder_Raw(void);

// 获取编码器绝对机械角（rad，0~2π）
float Get_Encoder_Abs_Angle_Rad(void);

// 获取编码器绝对机械角（度，0~360）
float Get_Encoder_Abs_Angle_Deg(void);

float Get_Elec_Angle_Rad(float * align_offset);


#endif
