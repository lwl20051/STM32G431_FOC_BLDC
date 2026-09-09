#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include <stdint.h>

/* ===== 编码器 SPI（AS5047P 专用） ===== */
void bsp_spi_encoder_init(void);
void bsp_spi_encoder_cs_low(void);
void bsp_spi_encoder_cs_high(void);
int  bsp_spi_encoder_transmit_blocking(uint16_t *tx, uint16_t *rx, uint16_t len);
int  bsp_spi_encoder_transmit_dma(uint16_t *tx, uint16_t *rx, uint16_t len);

#endif
