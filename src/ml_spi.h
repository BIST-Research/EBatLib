/*
 * Author: Ben Westcott, Jayson De La Vega
 * Date created: 8/11/23
 */

#ifndef ML_SERCOM_SPI_H
#define ML_SERCOM_SPI_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ML_SERCOM_SPI_FRAME_SPI             0x00
#define ML_SERCOM_SPI_FRAME_SPI_WITH_ADDR   0x02

// CPOL = 0, CPHA = 0
#define ML_SERCOM_SPI_MODE0                 (0x00 << SERCOM_SPI_CTRLA_CPHA_Pos)
// CPOL = 1, CPHA = 0
#define ML_SERCOM_SPI_MODE2                 (0x02 << SERCOM_SPI_CTRLA_CPHA_Pos)
// CPOL = 0, CPHA = 1
#define ML_SERCOM_SPI_MODE1                 (0x01 << SERCOM_SPI_CTRLA_CPHA_Pos)
// CPOL = 1, CPHA = 1
#define ML_SERCOM_SPI_MODE3                 (0x03 << SERCOM_SPI_CTRLA_CPHA_Pos)

#define ML_SERCOM_SPI_DIPO_PAD0             0x00
#define ML_SERCOM_SPI_DIPO_PAD1             0x01
#define ML_SERCOM_SPI_DIPO_PAD2             0x02
#define ML_SERCOM_SPI_DIPO_PAD3             0x03

#define ML_SERCOM_SPI_DOPO_DO0              0x00
#define ML_SERCOM_SPI_DOPO_DO3              0x02

#define ML_SERCOM_SPI_MODE_SLAVE            0x02
#define ML_SERCOM_SPI_MODE_MASTER           0x03

#define ML_SERCOM_SPI_ADDR_MODE_MASK        0x00
#define ML_SERCOM_SPI_ADDR_MODE_2ADDRS      0x01
#define ML_SERCOM_SPI_ADDR_MODE_RANGE       0x02

#define ML_SERCOM_SPI_CHSIZE_8BIT           0x00
#define ML_SERCOM_SPI_CHSIZE_9BIT           0x01

typedef enum {MASTER = 0x03, SLAVE = 0x00} ml_spi_opmode;

inline void spi_enable(Sercom *coms);
inline void spi_disable(Sercom *coms);
inline void spi_swrst(Sercom *coms);

void spi_init(Sercom *coms, const uint8_t gclk_id, const ml_spi_opmode opmode);
void clear_buffer(void);
uint8_t get_byte(void);

#ifdef __cplusplus
}
#endif

#endif // ML_SERCOM_SPI_H