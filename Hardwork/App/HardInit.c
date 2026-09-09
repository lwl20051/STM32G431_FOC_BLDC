#include "HardInit.h"

/**
 * @brief  初始化电机硬件
 * @param  无
 * @return 无
*/
void Motor_hardinit(void)
{
    BLDCDriver_Init();
    HAL_TIM_Base_Start_IT(&htim3);  
    BLDCDriver_Enable();
}

/**
 * @brief  初始化 FOC 算法
 * @param  无
 * @return 无
 */
void FocAlgorithm_Hardinit(void)
{
    FocAlgorithm_Init(&motor.foc, MOTOR_UDC, MOTOR_ARR);
}


/**
 * @brief  初始化编码器配置
 * @param  无
 * @return 无
 */
void Encoder_Init(void)
{
    AS5047P_Init();   // 无参数
}

/**
 * @brief  初始化电流传感器
 * @param  无
 * @return 无
 */
void CurrentSense_Init(void)
{
    CurrentSense_Init_ADC((uint32_t*)motor.current_sense.adc_buf);
}

void ALL_Init(void)
{
    Motor_hardinit();
    FocAlgorithm_Hardinit();
    Encoder_Init();
    CurrentSense_Init();
}