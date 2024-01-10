#include <Arduino.h>
#include <ml_port.h>
#include <ml_sercom_0.h>



const uint32_t usart_rx_desc_settings = 
(
    DMAC_BTCTRL_STEPSEL_DST ||
    DMAC_BTCTRL_DSTINC ||
    DMAC_BTCTRL_BEATSIZE_BYTE ||
    DMAC_BTCTRL_BLOCKACT_SUSPEND ||
    DMAC_BTCTRL_VALID
);


const uint32_t usart_rx_channel_settings = 
(
    DMAC_CHCTRLA_BURSTLEN_SINGLE ||
    DMAC_CHCTRLA_TRIGACT_BLOCK ||
    DMAC_CHCTRLA_TRIGSRC(SERCOM0_DMAC_ID_RX)
);

const uint32_t usart_tx_desc_settings =
(
    DMAC_BTCTRL_STEPSEL_SRC ||
    DMAC_BTCTRL_SRCINC ||
    DMAC_BTCTRL_BEATSIZE_BYTE ||
    DMAC_BTCTRL_BLOCKACT_SUSPEND ||
    DMAC_BTCTRL_VALID
);


const uint32_t usart_tx_channel_settings =
(
    DMAC_CHCTRLA_BURSTLEN_SINGLE ||
    DMAC_CHCTRLA_TRIGACT_BLOCK ||
    DMAC_CHCTRLA_TRIGSRC(SERCOM0_DMAC_ID_TX)
);

const ml_usart_s usart_prototype = {
    .sercom_settings = {
        .mode = ML_USART_MODE_INTERNAL,
        .cmode = USART_CMODE_ASYNC,
        .chsize = USART_CHSIZE_8,
        .parity = ML_USART_PARITY_EVEN,
        .sbmode = USART_SBMODE_ONE,
        .baud = 0xCED9
    },
    .rx_dmac_s = {
        .ex_chnum = DMAC_CH0,
        .chan_settings = usart_rx_channel_settings,
        .chan_prilvl = PRILVL0,
        .descriptor_settings = usart_rx_desc_settings,
        .intmsk = (DMAC_CHINTENSET_TCMPL | DMAC_CHINTENSET_TERR),
        .nvic = true,
        .irqn = DMAC_0_IRQn,
        .irqn_prilvl = 2
    },
    .tx_dmac_s = {
        .ex_chnum = DMAC_CH1,
        .chan_settings = usart_tx_channel_settings,
        .chan_prilvl = PRILVL0,
        .descriptor_settings = usart_tx_desc_settings,
        .intmsk = (DMAC_CHINTENSET_TCMPL | DMAC_CHINTENSET_TERR),
        .nvic = true,
        .irqn = DMAC_1_IRQn,
        .irqn_prilvl = 2
    }
};



#define _USART_SYNC(instance, label) while (instance->USART.SYNCBUSY.bit.label)

void sercom0_usart_init(const ml_sercom_usart_settings_t* const settings)
{
    usart_disable(SERCOM0);
    usart_swrst(SERCOM0);
    
    SERCOM0->USART.CTRLA.bit.FORM   = 0x00;
    SERCOM0->USART.CTRLA.bit.MODE   = settings->mode;
    SERCOM0->USART.CTRLA.bit.CMODE  = settings->cmode;
    SERCOM0->USART.CTRLB.bit.CHSIZE = settings->chsize;
    SERCOM0->USART.CTRLB.bit.SBMODE = settings->sbmode;
    SERCOM0->USART.CTRLA.bit.SAMPR  = 0x00;
    SERCOM0->USART.CTRLA.bit.RXPO   = 0x01;
    SERCOM0->USART.CTRLA.bit.TXPO   = 0x00;

    if (settings->mode == ML_USART_MODE_INTERNAL)
    {
        SERCOM0->USART.BAUD.reg     = settings->baud;
    }

    if (settings->parity != ML_USART_PARITY_NONE)
    {
        SERCOM0->USART.CTRLA.bit.FORM |= 0x01;
        SERCOM0->USART.CTRLB.bit.PMODE = settings->parity;
    }
    
    SERCOM0->USART.CTRLB.bit.RXEN = 1;
    _USART_SYNC(SERCOM0, CTRLB);
    SERCOM0->USART.CTRLB.bit.TXEN = 1;
    _USART_SYNC(SERCOM0, CTRLB);


    ML_SERCOM_USART_INTSET_TXC(SERCOM0);
    ML_SERCOM_USART_INTSET_RXC(SERCOM0);
}
