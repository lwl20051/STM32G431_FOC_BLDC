#include "GetAS5047P.h"

/**
 * @brief 获取编码器原始值（0~16383）
 * @return uint16_t 编码器原始值
 */
uint16_t Get_Encoder_Raw(void)
{
    return AS5047P_GetAngleRaw();
}


/**
 * @brief 获取编码器绝对机械角（rad，0~2π）
 * @return float 编码器绝对机械角（rad，0~2π）
 */
float Get_Encoder_Abs_Angle_Rad(void)
{
    return (float)Get_Encoder_Raw() * 6.2831853f / 16384.0f;
}

/**
 * @brief 获取编码器绝对机械角（度，0~360）
 * @return float 编码器绝对机械角（度，0~360）
 */
float Get_Encoder_Abs_Angle_Deg(void)
{
    return (float)Get_Encoder_Raw() * 360.0f / 16384.0f;
}

/**
 * @brief 获取电角度（rad，0~2π）
 * @param align_offset 对齐偏移量指针（rad，0~2π）
 * @return float 电角度（rad，0~2π）
 */
float Get_Elec_Angle_Rad(float * align_offset)
{
    /* ① 计数域：当前位置 − 零点（单位都是计数，一致） */
    int32_t delta = (int32_t)Get_Encoder_Raw() - (int32_t)(*align_offset);
    if (delta >  8192) delta -= 16384;   /* 跨零点回绕 */
    if (delta < -8192) delta += 16384;

    /* ② 计数 → 机械角(rad) → ×7 极对数 → 电角度(rad) */
    float elec = (float)delta * 6.2831853f / 16384.0f * MOTOR_POLE_PAIRS;

    /* ③ 归一化 [0, 2π) */
    elec = fmodf(elec, _2_PI);
    if (elec < 0) elec += _2_PI;
    return elec;

}
