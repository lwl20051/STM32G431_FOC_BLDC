# STM32G431_FOC_BLDC
基于STM32G431的无刷电机FOC矢量控制（迷你伺服驱动器）

## 功能说明

当前版本实现电机**开环旋转**：

- 上电后由 TIM3 产生 20kHz 周期中断，在中断中周期调用 `FOC_Control_Task()` 执行 FOC 控制。
- 启动流程：先进入对齐状态（STATE_ALIGN），以 3V 对齐电压（`MOTOR_ALIGN_VD`）保持 1 秒完成转子电角度对齐；随后进入闭环状态机（STATE_CLOSEDLOOP），调用 `Set_OpenLoop_Vq(2.0f)`，以 Vd=0、Vq=2.0V 的定子电压矢量驱动电机，电角度取自 AS5047P 编码器，外部表现为电机**开环旋转**。

## 硬件资源

- MCU：STM32G431RBT6（LQFP64，128KB Flash / 32KB RAM），HSE 24MHz，PLL 170MHz
- 三相 PWM：TIM3_CH1=PB4、TIM3_CH2=PC7、TIM2_CH3=PB10，中心对齐 20kHz，使能脚 PA9（高有效）
- 编码器：AS5047P，SPI1（PA5/6/7，CS=PB6），SPI Mode1 16bit，DMA 双帧读取
- 电流采样：ADC2（PA0=IN1、PA4=IN17），DMA1_CH4 循环，TIM3 TRGO 触发
- 调试串口：USART2（PA2/3）115200，DMA 发送

## 目录结构

```
Core/                 HAL 初始化代码（main/gpio/adc/dma/spi/tim/usart 等）
Hardwork/
  ├── Algorithm/      FOC 控制算法
  ├── App/            应用层（初始化、电机状态机、编码器读取）
  ├── BSP/            板级外设驱动（PWM/SPI/ADC）
  ├── Config/         电机参数配置
  └── Driver/         AS5047P 编码器、BLDC 驱动
MDK-ARM/              Keil MDK 工程
STM32CubeIDE/         STM32CubeIDE 工程
```

## 工具链

- Keil MDK-ARM（ARMCC V5.06）
- STM32CubeIDE（GCC）
