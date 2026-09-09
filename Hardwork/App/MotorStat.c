#include "MotorStat.h"


MotorStat_TypeDef motor = {0};  /* 上电进待机，先校准电流零偏 */
MotorSpace_TypeDef motor_space = {0};

/**
 * @brief  设置目标角度
 * @param  angle 目标角度，单位弧度
 * @return 无
 */
void Set_Target_Angle(float angle)
{
    motor_space.target_angle = angle/180.0f*3.14159265f;
}
/**
 * @brief  FOC 控制任务
 * @param  无
 * @return 无
 */ 
void FOC_Control_Task(void)
{
    switch (motor.state)
    {
    case STATE_ALIGN:
        /* 1. 输出固定角度，把转子吸到0° */
        motor.foc.Theta = 0;
        motor.foc.Vd = MOTOR_ALIGN_VD;   /* 对齐电压，比如3V */
        motor.foc.Vq = 0;
        FOC_VoltageUpdate(&motor.foc);
        BLDCDriver_SetPWM(motor.foc.PWM_A, motor.foc.PWM_B, motor.foc.PWM_C);

        /* 2. 计数，持续对齐 */
        motor.align_counter++;
        if (motor.align_counter > MOTOR_ALIGN_TIME)  /* 比如20000次=1秒 */
        {
            /* 3. 时间到，记录此时编码器值作为零点偏移 */
            motor.align_offset = Get_Encoder_Raw();
            motor_space.pos_kp = 4.0f;
            motor_space.pos_ki = 4.0f;
            motor_space.pos_integral = 0;
            motor.state = STATE_CLOSEDLOOP;
        }
        break;
    case STATE_CLOSEDLOOP:
        Set_OpenLoop_Vq(2.0f);
        break;
    case STATE_FAULT:
        break;
    
    }

}


//电机开环控制
void Set_OpenLoop_Vq(float vq)
{
    motor.foc.Theta = Get_Elec_Angle_Rad(&motor.align_offset);   
    motor.foc.Vd = 0.0f;
    motor.foc.Vq = vq;
    FOC_VoltageUpdate(&motor.foc);            /* 总是更新，不要 if(Vq!=0) */
    BLDCDriver_SetPWM(motor.foc.PWM_A, motor.foc.PWM_B, motor.foc.PWM_C);
}
/* 位置环 PI，主循环 1kHz 调用 */
void Position_Control(void)
{
    if (motor.state != STATE_CLOSEDLOOP) return;

    float current_angle = Get_Encoder_Abs_Angle_Rad();
    float error = motor_space.target_angle - current_angle;
    // float error = current_angle - motor_space.target_angle;
    
    if (error > 3.14159265f)  error -= 6.2831853f;
    if (error < -3.14159265f) error += 6.2831853f;

    /* 死区：误差足够小 → 当作到位，停止出力 */
    if (fabsf(error) < 0.02f)        /* 0.02 rad ≈ 1.15° */
    {
        error = 0.0f;
        motor_space.pos_integral = 0.0f;   /* 同时清积分，防止偏置残留 */
    }
    else
    {
        /* 条件积分：误差小才积分（防积分偏置） */
        motor_space.pos_integral += error * 0.001f;
        if (motor_space.pos_integral > 2.0f)  motor_space.pos_integral = 2.0f;
        if (motor_space.pos_integral < -2.0f) motor_space.pos_integral = -2.0f;
    }

    float vq = motor_space.pos_kp * error + motor_space.pos_ki * motor_space.pos_integral;
    if (vq > 5.0f)  vq = 5.0f;
    if (vq < -5.0f) vq = -5.0f;

    motor.foc.Vq = vq;
}

