#include <ml_spi.h>
#include <ml_port.h>
#include <ml_clocks.h>
#include <ml_adc.h>
#include <ml_dmac.h>
#include <ml_tcc.h>
#include <ml_ac.h>

#define SPI_BUFFER_LEN 64

static DmacDescriptor base_descriptor[3] __attribute__((aligned(16)));
static volatile DmacDescriptor wb_descriptor[3] __attribute__((aligned(16)));

volatile uint8_t spi_rx_buffer[SPI_BUFFER_LEN];

const uint32_t spi_rx_dmac_channel_settings = 
(
  
);

const uint16_t spi_rx_dmac_descriptor_settings = 
(

);

volatile uint8_t spi_tx_buffer[SPI_BUFFER_LEN];

const uint32_t spi_tx_dmac_channel_settings = 
(
  
);

const uint16_t spi_tx_dmac_channel_settings = 
(

);



void setup(void)
{

  MCLK_init();
  GCLK_init();

  DMAC_init(&base_descriptor[0], &wb_descriptor[0]);

}

void loop(void)
{

}