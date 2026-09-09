#ifndef __CURRENT_SENSE_H__
#define __CURRENT_SENSE_H__

#include "main.h"
#include "bsp_adc.h"



typedef struct {
    uint16_t adc_buf;   /* DMA直接填充：adc_buf=A相, adc_buf=B相 */
    float    zero_offset;  /* 零偏（上电校准） */
    float    ia;           /* A相电流 (A) */
    float    ib;           /* B相电流 (A) */
    float    ic;           /* C相电流 (A)，星形合成 */
} CurrentSense_TypeDef;

void CurrentSense_Init_ADC(uint32_t* adc_buf);

#endif
