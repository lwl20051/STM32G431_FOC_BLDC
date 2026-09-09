#ifndef __MOTOR_STAT_H__
#define __MOTOR_STAT_H__

#include "FocAlgorithm.h"
#include "BLDCDriver.h"
#include "MotorConfig.h"
#include "AS5047P.h"
#include "GetAS5047P.h"
#include "CurrentSense.h"
/* FOC 运行状态 */
typedef enum {
    STATE_ALIGN=0,          /* 转子对齐中 */
    STATE_CLOSEDLOOP,     /* 角度闭环运行 */
    STATE_FAULT           /* 故障 */
} FOC_State_t;

/* 电机控制状态机 */
typedef struct {
    FocAlgorithm_TypeDef foc;      /* FOC 算法状态（Vd/Vq/Theta/中间变量） */
    CurrentSense_TypeDef current_sense;  /* 电流传感器状态（A相/ B相/星形合成） */
    FOC_State_t          state;    /* 当前运行状态 */
    float                align_counter;  /* 对齐计数器 */
    float                align_offset;   /* 对齐偏移量 */
    float                target_speed;   /* 目标速度（后面速度环用） */
} MotorStat_TypeDef;

typedef struct {
    /* ... 已有变量 ... */
    float target_angle;     /* 目标机械角度（rad） */
    float pos_integral;     /* 位置积分项 */
    float pos_kp;           /* 位置环 Kp */
    float pos_ki;           /* 位置环 Ki */
} MotorSpace_TypeDef;

extern MotorStat_TypeDef motor;


void FOC_Control_Task(void);
void Set_Target_Angle(float angle);
void Position_Control(void);
void Set_OpenLoop_Vq(float vq);


#endif
