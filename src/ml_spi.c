/*
 * Author: Ben Westcott, Jayson De La Vega
 * Date created: 8/11/23
 */

#include <ml_spi.h>
#include <ml_clocks.h>

/*
 * Notes:
 * - CPOL: SCK or SCK + 180 deg
 * - transmission starts with falling edge or SS
 * 
 */


inline void spi_enable(Sercom *coms)
{
    coms->SPI.CTRLA.bit.ENABLE = 0x01;
    while(coms->SPI.SYNCBUSY.bit.ENABLE != 0U)
    {
        /* Wait for syncronization */
    }
}

inline void spi_disable(Sercom *coms)
{
    coms->SPI.CTRLA.bit.ENABLE = 0x00;
    while(coms->SPI.SYNCBUSY.bit.ENABLE != 0U)
    {
        /* Wait for syncronization */
    }
}

inline void spi_swrst(Sercom *coms)
{
    coms->SPI.CTRLA.bit.SWRST = 0x01;
    while(coms->SPI.SYNCBUSY.bit.SWRST != 0U)
    {
        /* Wait for syncronization */
    }
}

inline void spi_rxen(Sercom *coms)
{
    coms->SPI.CTRLB.bit.RXEN = 0x01;
    while(coms->SPI.SYNCBUSY.bit.CTRLB != 0U)
    {
        /* Wait for syncronization */
    }
}

inline void spi_mssen(Sercom *coms)
{
    coms->SPI.CTRLB.bit.MSSEN = 0x01;
    while(coms->SPI.SYNCBUSY.bit.CTRLB != 0U)
    {
        /* Wait for syncronization */
    }
}






void spi_init(Sercom *coms, const uint8_t gclk_id, const ml_spi_opmode opmode)
{
    ML_SET_GCLK0_PCHCTRL(gclk_id);
    spi_disable(coms);
    spi_swrst(coms);

    coms->SPI.CTRLA.reg = 
    (
        SERCOM_SPI_CTRLA_MODE(opmode ? ML_SERCOM_SPI_MODE_MASTER : ML_SERCOM_SPI_MODE_SLAVE) |
        SERCOM_SPI_CTRLA_DIPO(ML_SERCOM_SPI_DIPO_PAD3) |
        SERCOM_SPI_CTRLA_FORM(ML_SERCOM_SPI_FRAME_SPI) |
        SERCOM_SPI_CTRLA_DOPO(ML_SERCOM_SPI_DOPO_DO0) |
        ML_SERCOM_SPI_MODE0 |
        SERCOM_SPI_CTRLA_IBON
    );

    coms->SPI.CTRLA.reg &=
    ~(
        SERCOM_SPI_CTRLA_CPOL |
        SERCOM_SPI_CTRLA_CPHA |
        SERCOM_SPI_CTRLA_DORD
    );

    coms->SPI.INTENSET.reg = 
    (
        SERCOM_SPI_INTENSET_ERROR |
        SERCOM_SPI_INTENSET_SSL
    );

    NVIC_EnableIRQ(SERCOM1_0_IRQn);
    NVIC_SetPriority(SERCOM1_0_IRQn, 2);

    NVIC_EnableIRQ(SERCOM1_3_IRQn);
    NVIC_SetPriority(SERCOM1_3_IRQn, 2);
}