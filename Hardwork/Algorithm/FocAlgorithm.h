#ifndef __FOC_ALGORITHM_H__
#define __FOC_ALGORITHM_H__

#include <math.h>

/*FOC参数结构体定义*/
typedef struct
{

    float UDC;/*直流母线电压*/
    float ARR;/*定时器ARR值*/

    /*设置d , q 电压参数*/
    float Vd;/*电压d轴分量*/
    float Vq;/*电压q轴分量*/
    float Theta; /*电角度*/

    /* 反Park变换参数*/
    float Valpha;/*反Park变换后的alpha轴分量*/
    float Vbeta;/*反Park变换后的beta轴分量*/   

    /*反Clarke变换参数*/
    float Vu;/*反Clarke变换后的A相电压*/
    float Vv;/*反Clarke变换后的B相电压*/
    float Vw;/*反Clarke变换后的C相电压*/

    /*马鞍波电压参数*/
    float Vu_Mod;/*A相马鞍波电压*/
    float Vv_Mod;/*B相马鞍波电压*/
    float Vw_Mod;/*C相马鞍波电压*/

    /*PWM比较值参数*/
    float PWM_A;/*A相PWM比较值*/
    float PWM_B;/*B相PWM比较值*/
    float PWM_C;/*C相PWM比较值*/

} FocAlgorithm_TypeDef;


void FocAlgorithm_Init(FocAlgorithm_TypeDef *foc,float Udc,float ARR);
void FocAlgorithm_Transform_Clarke(FocAlgorithm_TypeDef *foc);
void FocAlgorithm_Transform_Park(FocAlgorithm_TypeDef *foc);
void FocAlgorithm_Calc_Mod(FocAlgorithm_TypeDef *foc);
void FOC_VoltageUpdate(FocAlgorithm_TypeDef *foc);

#endif
