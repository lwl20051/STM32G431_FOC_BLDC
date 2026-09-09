#ifndef __HARDINIT_H__
#define __HARDINIT_H__

#include "FocAlgorithm.h"

#include "AS5047P.h"

#include "BLDCDriver.h"

#include "MotorConfig.h"

#include "MotorStat.h"

#include "CurrentSense.h"

#include "tim.h"

/**
 * @brief  初始化电机硬件
 * @param  无
 * @return 无
 */
void Motor_hardinit(void);
/**
 * @brief  初始化 FOC 算法
 * @param  无
 * @return 无
 */
void FocAlgorithm_Hardinit(void);
/**
 * @brief  初始化编码器配置
 * @param  无
 * @return 无
 */
void Encoder_Init(void );

/**
 * @brief  初始化电流传感器
 * @param  无
 * @return 无
 */
void CurrentSense_Init(void);

/**
 * @brief  初始化所有硬件
 * @param  无
 * @return 无
 */
void ALL_Init(void);
    
#endif
