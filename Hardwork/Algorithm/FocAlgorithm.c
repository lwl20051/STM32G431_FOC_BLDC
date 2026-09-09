#include "FocAlgorithm.h"


/*步骤一初始化*/
void FocAlgorithm_Init(FocAlgorithm_TypeDef *foc,float Udc,float ARR)
{
    foc->UDC=Udc;
    foc->ARR=ARR;
}


/*步骤二反Park变换*/
void FocAlgorithm_Transform_Park(FocAlgorithm_TypeDef *foc)
{
    foc->Valpha=foc->Vd*cosf(foc->Theta)-foc->Vq*sinf(foc->Theta);
    foc->Vbeta=foc->Vd*sinf(foc->Theta)+foc->Vq*cosf(foc->Theta);
}

/*步骤三反Clarke变换*/
void FocAlgorithm_Transform_Clarke(FocAlgorithm_TypeDef *foc)
{
    foc->Vu=foc->Valpha;
    foc->Vv=-0.5*foc->Valpha+0.86602540378f*foc->Vbeta;
    foc->Vw=-0.5*foc->Valpha-0.86602540378f*foc->Vbeta;
}

/*步骤四端电压计算*/
void FocAlgorithm_Calc_Mod(FocAlgorithm_TypeDef *foc)
{
    //寻找最大电压、最小电压、偏移电压
    float Vmax=fmaxf(foc->Vu,fmaxf(foc->Vv,foc->Vw));
    float Vmin=fminf(foc->Vu,fminf(foc->Vv,foc->Vw));

    //计算电压的偏移量
    float Voffset=-(Vmax+Vmin)/2.0f;

    //计算三相马鞍波电压
    foc->Vu_Mod=foc->Vu+Voffset; 
    foc->Vv_Mod=foc->Vv+Voffset;
    foc->Vw_Mod=foc->Vw+Voffset;

    //计算三相马鞍波电压转向PWM占空比
    foc->PWM_A=((foc->Vu_Mod)/foc->UDC+0.5f);
    foc->PWM_B=((foc->Vv_Mod)/foc->UDC+0.5f);
    foc->PWM_C=((foc->Vw_Mod)/foc->UDC+0.5f);

    //限幅 [0, 1]
    foc->PWM_A=fmaxf(0.0f,fminf(1.0f,foc->PWM_A));
    foc->PWM_B=fmaxf(0.0f,fminf(1.0f,foc->PWM_B));
    foc->PWM_C=fmaxf(0.0f,fminf(1.0f,foc->PWM_C));
}

void FOC_VoltageUpdate(FocAlgorithm_TypeDef *foc)
{
    FocAlgorithm_Transform_Park(foc);
    FocAlgorithm_Transform_Clarke(foc);
    FocAlgorithm_Calc_Mod(foc);
}
