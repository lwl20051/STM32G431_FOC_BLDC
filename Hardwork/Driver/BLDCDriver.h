#ifndef __BLDCDRIVER_H
#define __BLDCDRIVER_H

#include <stdint.h>

void BLDCDriver_Init(void);
void BLDCDriver_Enable(void);
void BLDCDriver_Disable(void);
void BLDCDriver_SetPWM(float a, float b, float c);  /* 占空比 0~1 */

#endif