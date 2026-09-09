#include "bsp_pwm.h"
#include "tim.h"
#include "gpio.h"
#include "MotorConfig.h"

/* 全部从 Config 读取，BSP 里不写死任何硬件常量 */
static TIM_HandleTypeDef *s_tim_a  = MOTOR_A_TIM_HANDLE;
static uint32_t           s_ch_a   = MOTOR_A_CH;
static TIM_HandleTypeDef *s_tim_b  = MOTOR_B_TIM_HANDLE;
static uint32_t           s_ch_b   = MOTOR_B_CH;
static TIM_HandleTypeDef *s_tim_c  = MOTOR_C_TIM_HANDLE;
static uint32_t           s_ch_c   = MOTOR_C_CH;
static uint32_t           s_arr    = MOTOR_ARR;
static GPIO_TypeDef      *s_en_port = MOTOR_EN_PORT;
static uint16_t           s_en_pin  = MOTOR_EN_PIN;
static uint8_t            s_en_active_high = MOTOR_EN_ACTIVE_HIGH;

void bsp_pwm_init(void)
{
    HAL_TIM_PWM_Start(s_tim_a, s_ch_a);
    HAL_TIM_PWM_Start(s_tim_b, s_ch_b);
    HAL_TIM_PWM_Start(s_tim_c, s_ch_c);
}

void bsp_pwm_set_duty(bsp_pwm_ch_t ch, float duty)
{
    uint32_t ccr = (uint32_t)(duty * s_arr);
    switch (ch) {
        case BSP_PWM_A: __HAL_TIM_SET_COMPARE(s_tim_a, s_ch_a, ccr); break;
        case BSP_PWM_B: __HAL_TIM_SET_COMPARE(s_tim_b, s_ch_b, ccr); break;
        case BSP_PWM_C: __HAL_TIM_SET_COMPARE(s_tim_c, s_ch_c, ccr); break;
    }
}

void bsp_pwm_enable(void)
{
    HAL_GPIO_WritePin(s_en_port, s_en_pin,
                      s_en_active_high ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void bsp_pwm_disable(void)
{
    HAL_GPIO_WritePin(s_en_port, s_en_pin,
                      s_en_active_high ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
