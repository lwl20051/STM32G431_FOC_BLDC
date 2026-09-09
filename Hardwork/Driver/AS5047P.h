#ifndef __AS5047P_H
#define __AS5047P_H

#include <stdint.h>   // ✅ 改动：只需要 stdint，不再包含 spi.h / main.h

/* ================= 寄存器定义 ================= */
#define AS5047P_REG_ANGLECOM   0x3FFF   /* 角度寄存器 */
#define AS5047P_REG_ERRFL      0x0001   /* 错误标志寄存器 */
#define AS5047P_REG_PROG       0x0003   /* 编程寄存器 */
#define AS5047P_REG_DIAAGC     0x3FFC   /* 诊断/AGC 寄存器 */

/* ================= DMA 非阻塞读取状态机 ================= */
typedef enum {
  STATE_IDLE = 0,    /* 空闲，可以启动新读取 */
  STATE_FRAME1,      /* 第一帧 DMA 传输中 */
  STATE_FRAME2,      /* 第二帧 DMA 传输中 */
  STATE_READY        /* 数据就绪，等待中断消费 */
} ReadState_t;

// ✅ 改动：删除了 AS5047P_Hardware_t 结构体（硬件信息藏在 BSP 里）
// ✅ 改动：删除了 extern AS5047P_Hardware_t s_hw

/* 角度分辨率 */
#define AS5047P_ANGLE_MAX      16383    /* 14 位 */

/* ================= 接口函数 ================= */
// ✅ 改动：Init 改成无参数
void     AS5047P_Init(void);
uint16_t AS5047P_ReadAngleRaw(void);
float    AS5047P_ReadAngleDeg(void);
float    AS5047P_ReadAngleRad(void);
uint16_t AS5047P_ReadRegister(uint16_t addr);

void     AS5047P_StartRead(void);
uint16_t AS5047P_GetAngleRaw(void);

// ✅ 改动：删除了 Start_SPI1_FirstFrame / Start_SPI1_SecondFrame（已加 static，不对外暴露）
void SPI1_TxRxCpltCallback(void);   /* 中断回调，暂时保留 */

#endif
