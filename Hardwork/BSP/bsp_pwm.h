#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include <stdint.h>

/* 三相通道枚举，驱动层只认识这个 */
typedef enum {
    BSP_PWM_A = 0,
    BSP_PWM_B,
    BSP_PWM_C
} bsp_pwm_ch_t;

void bsp_pwm_init(void);
void bsp_pwm_set_duty(bsp_pwm_ch_t ch, float duty);  /* duty 0~1 */
void bsp_pwm_enable(void);
void bsp_pwm_disable(void);

#endif