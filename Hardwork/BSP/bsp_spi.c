#include "bsp_spi.h"
#include "spi.h"
#include "gpio.h"
#include "MotorConfig.h"   /* 从 Config 层读硬件配置 */

/* 全部从 Config 读取，BSP 里没有任何写死的硬件常量 */
static SPI_HandleTypeDef *s_hspi    = ENCODER_SPI_HANDLE;
static GPIO_TypeDef      *s_cs_port = ENCODER_CS_PORT;
static uint16_t           s_cs_pin  = ENCODER_CS_PIN;

void bsp_spi_encoder_init(void)
{
    /* CubeMX 已经初始化好了 SPI 和 GPIO，这里预留扩展 */
}

void bsp_spi_encoder_cs_low(void)
{
    HAL_GPIO_WritePin(s_cs_port, s_cs_pin, GPIO_PIN_RESET);
}

void bsp_spi_encoder_cs_high(void)
{
    HAL_GPIO_WritePin(s_cs_port, s_cs_pin, GPIO_PIN_SET);
}

int bsp_spi_encoder_transmit_blocking(uint16_t *tx, uint16_t *rx, uint16_t len)
{
    return HAL_SPI_TransmitReceive(s_hspi, (uint8_t*)tx, (uint8_t*)rx, len, HAL_MAX_DELAY);
}

int bsp_spi_encoder_transmit_dma(uint16_t *tx, uint16_t *rx, uint16_t len)
{
    return HAL_SPI_TransmitReceive_DMA(s_hspi, (uint8_t*)tx, (uint8_t*)rx, len);
}
