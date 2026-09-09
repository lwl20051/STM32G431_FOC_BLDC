#ifndef __MOTOR_CONFIG_H__
#define __MOTOR_CONFIG_H__

/* ===== 三相 PWM 硬件配置 ===== */
#define MOTOR_A_TIM_HANDLE   &htim3       /* A 相定时器句柄 */
#define MOTOR_A_CH           TIM_CHANNEL_2
#define MOTOR_B_TIM_HANDLE   &htim3       /* B 相定时器句柄 */
#define MOTOR_B_CH           TIM_CHANNEL_1
#define MOTOR_C_TIM_HANDLE   &htim2       /* C 相定时器句柄 */
#define MOTOR_C_CH           TIM_CHANNEL_3
#define MOTOR_ARR            4249.0f      /* ARR 值 */

/* ===== 使能引脚 ===== */
#define MOTOR_EN_PORT        GPIOA
#define MOTOR_EN_PIN         GPIO_PIN_9
#define MOTOR_EN_ACTIVE_HIGH 1


/* ===== FOC 算法配置 ===== */
#define MOTOR_UDC            12.0f    /* 直流母线电压 */
//#define MOTOR_ARR            4299.0f  /* 定时器 ARR 值*/
/* 加这些 */
#define MOTOR_POLE_PAIRS     7        /* 极对数 */
#define MOTOR_ALIGN_TIME     20000    /* 对齐计数（20kHz × 1秒） */
#define MOTOR_ALIGN_VD       3.0f     /* 对齐电压 */


/* ===== 编码器配置（AS5047P） ===== */
#define ENCODER_SPI_HANDLE    &hspi1         /* SPI 句柄指针 */
#define ENCODER_CS_PORT       GPIOB          /* CS 端口 */
#define ENCODER_CS_PIN        GPIO_PIN_6     /* CS 引脚 */
#define ENCODER_SPI_MODE      1              /* SPI Mode1（CPOL=0, CPHA=1） */

/**
 * @brief ===== 电流传感器配置 =====
 */
#define CURRENT_SENSE_ADC_HANDLE &hadc2
#define CURRENT_SENSE_ADC_CH ADC_CHANNEL_1
#define CURRENT_SENSE_ADC_RES ADC_RESOLUTION_12B
#define CURRENT_SENSE_ADC_DMA_SIZE 2


/*常数*/

#define _2_PI                 6.28318530717f 
#define _1_PI                 3.14159265358f


#endif
