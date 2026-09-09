#include "bsp_adc.h"



void BSP_ADC_Init(uint32_t* adc_buf)
{
    HAL_ADC_Start_DMA(CURRENT_SENSE_ADC_HANDLE, adc_buf, CURRENT_SENSE_ADC_DMA_SIZE);
}
