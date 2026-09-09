#include "AS5047P.h"
#include "bsp_spi.h"    // ✅ 改动：包含 BSP 头，不再包含 spi.h / main.h


/* ============ 内部函数 ============ */
/** 
 * @brief  16 位 SPI 传输
 * @param  tx 要发送的 16 位数据
 * @return 从 AS5047P 接收的 16 位数据
 */
static uint16_t AS5047P_SPI_Transfer16(uint16_t tx)
{
  uint16_t rx = 0;
  
  bsp_spi_encoder_cs_low();
  
  bsp_spi_encoder_transmit_blocking(&tx, &rx, 1);
  
  bsp_spi_encoder_cs_high();
  return rx;
}
/**   
 * @brief  构建读取命令
 * @param  addr 要读取的寄存器地址
 * @return 读取命令
 */
static uint16_t AS5047P_BuildReadCmd(uint16_t addr)
{
  uint16_t payload = (1u << 14) | (addr & 0x3FFFu);
  uint16_t ones = 0;
  for (int i = 0; i < 15; i++) {
    if (payload & (1u << i)) ones++;
  }
  return (ones % 2 == 0) ? payload : (payload | 0x8000u);
}

/* ============ 对外接口 ============ */


/** 
 * @brief  初始化 AS5047P
 * @param  无
 * @return 无
 */
void AS5047P_Init(void)
{
  bsp_spi_encoder_init();
  AS5047P_ReadRegister(AS5047P_REG_ANGLECOM);
}

/** 
 * @brief  读取 AS5047P 寄存器
 * @param  addr 要读取的寄存器地址
 * @return 从 AS5047P 接收的 16 位数据
 */
uint16_t AS5047P_ReadRegister(uint16_t addr)
{
  AS5047P_SPI_Transfer16(AS5047P_BuildReadCmd(addr));
  return AS5047P_SPI_Transfer16(AS5047P_BuildReadCmd(addr));
}
/** 
 * @brief  读取 AS5047P 角度原始值
 * @param  无
 * @return 角度原始值
 */
uint16_t AS5047P_ReadAngleRaw(void)
{
  uint16_t reg = AS5047P_ReadRegister(AS5047P_REG_ANGLECOM);
  return reg & 0x3FFFu;
}
/** 
 * @brief  读取 AS5047P 角度（度）
 * @param  无
 * @return 角度（度）
 */
float AS5047P_ReadAngleDeg(void)
{
  uint16_t raw = AS5047P_ReadAngleRaw();
  return (float)raw * (360.0f / (float)AS5047P_ANGLE_MAX);
}
/** 
 * @brief  读取 AS5047P 角度（弧度）
 * @param  无
 * @return 角度（弧度）
 */
float AS5047P_ReadAngleRad(void)
{
  uint16_t raw = AS5047P_ReadAngleRaw();
  return (float)raw * (6.28318530718f / (float)AS5047P_ANGLE_MAX);
}

/* ============ DMA 非阻塞读取状态机 ============ */
static volatile ReadState_t s_state = STATE_IDLE;
static volatile uint16_t s_tx_buf;
static volatile uint16_t s_rx_buf;
static volatile uint16_t s_angle_result;
static volatile uint16_t s_angle_latest;


static void Start_SPI1_FirstFrame(void)
{
  s_state = STATE_FRAME1;
  s_tx_buf = AS5047P_BuildReadCmd(AS5047P_REG_ANGLECOM);
  
  bsp_spi_encoder_cs_low();

  bsp_spi_encoder_transmit_dma((uint16_t*)&s_tx_buf, (uint16_t*)&s_rx_buf, 1);
}

// ✅ 改动：加 static
static void Start_SPI1_SecondFrame(void)
{
  s_state = STATE_FRAME2;
  s_tx_buf = AS5047P_BuildReadCmd(AS5047P_REG_ANGLECOM);
  
  bsp_spi_encoder_cs_low();
  
  bsp_spi_encoder_transmit_dma((uint16_t*)&s_tx_buf, (uint16_t*)&s_rx_buf, 1);
}


void AS5047P_StartRead(void)
{
  if (s_state == STATE_READY)
  {
    s_state = STATE_IDLE;
    s_angle_latest = s_angle_result;
  }
  if (s_state == STATE_IDLE)
  {
    Start_SPI1_FirstFrame();
  }
}



void SPI1_TxRxCpltCallback(void)
{
  if (s_state == STATE_FRAME1)
  {
   
    bsp_spi_encoder_cs_high();
    Start_SPI1_SecondFrame();
  }
  else if (s_state == STATE_FRAME2)
  {
    
    bsp_spi_encoder_cs_high();
    s_angle_result = s_rx_buf & 0x3FFFu;
    s_state = STATE_READY;
  }
}

uint16_t AS5047P_GetAngleRaw(void)
{
  return s_angle_latest;
}
