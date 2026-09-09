#include "BLDCDriver.h"
#include "bsp_pwm.h"



void BLDCDriver_Init(void)
{
    bsp_pwm_init();                              
}

void BLDCDriver_Enable(void)
{
    bsp_pwm_enable();                            
}

void BLDCDriver_Disable(void)
{
    bsp_pwm_disable();                           
}

void BLDCDriver_SetPWM(float a, float b, float c)
{
    bsp_pwm_set_duty(BSP_PWM_A, a);               
    bsp_pwm_set_duty(BSP_PWM_B, b);               
    bsp_pwm_set_duty(BSP_PWM_C, c);               
}
