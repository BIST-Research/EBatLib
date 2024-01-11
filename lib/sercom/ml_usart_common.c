#include <Arduino.h>
#include <ml_dmac.h>
#include <ml_usart_common.h>

#define _USART_SYNC(instance, label) while (instance->USART.SYNCBUSY.bit.label)


void usart_enable(Sercom* const sercom)
{
    sercom->USART.CTRLA.bit.ENABLE = 1;
    _USART_SYNC(SERCOM0, ENABLE);
}

void usart_swrst(Sercom* const sercom)
{
    sercom->USART.CTRLA.bit.SWRST = 1;
    _USART_SYNC(SERCOM0, SWRST);
}

void usart_disable(Sercom* const sercom)
{
    sercom->USART.CTRLA.bit.ENABLE = 0;
    _USART_SYNC(SERCOM0, ENABLE);
}

void usart_transmitter_enable(Sercom* const sercom)
{
    sercom->USART.CTRLB.bit.TXEN = 1;
    _USART_SYNC(SERCOM0, CTRLB);
}

void usart_transmitter_disable(Sercom* const sercom)
{
    sercom->USART.CTRLB.bit.TXEN = 0;
    _USART_SYNC(SERCOM0, CTRLB);
}

void usart_receiver_enable(Sercom* const sercom)
{
    sercom->USART.CTRLB.bit.RXEN = 1;
    _USART_SYNC(SERCOM0, CTRLB);
}

void usart_receiver_disable(Sercom* const sercom)
{
    sercom->USART.CTRLB.bit.RXEN = 0;
    _USART_SYNC(SERCOM0, CTRLB);
}

bool usart_can_transmit(Sercom* const sercom)
{
    return ML_SERCOM_USART_INTFLAG_DRE(sercom);
}

bool usart_has_receive(Sercom* const sercom)
{
    return ML_SERCOM_USART_INTFLAG_RXC(sercom);
}

uint32_t  usart_read(Sercom* const sercom)
{
    return (sercom->USART.DATA.reg);
}

void usart_write(Sercom* const sercom, uint32_t data)
{
    sercom->USART.DATA.reg = data;
}

uint8_t usart_transaction8(Sercom* const sercom, uint8_t data)
{
    while (!ML_SERCOM_USART_INTFLAG_DRE(sercom));
    sercom->USART.DATA.reg = data;
    while (!ML_SERCOM_USART_INTFLAG_RXC(sercom));
    return (uint8_t)(sercom->USART.DATA.reg);
}
uint32_t usart_transaction32(Sercom* const sercom, uint32_t data)
{
    while (!ML_SERCOM_USART_INTFLAG_DRE(sercom));
    sercom->USART.DATA.reg = data;
    while (!ML_SERCOM_USART_INTFLAG_RXC(sercom));
    return (sercom->USART.DATA.reg);
}

void usart_dmac_rx_init(Sercom* const sercom, const ml_dmac_s* const desc, DmacDescriptor* cpy)
{
    DMAC_channel_init(desc->ex_chnum, 
                      desc->chan_settings, 
                      desc->chan_prilvl);


    DMAC_descriptor_init(desc->descriptor_settings,
                         desc->ex_len,
                         (uint32_t)&sercom->USART.DATA,
                         ((uint32_t)desc->ex_ptr) + (desc->ex_len * DMAC_extract_btsize(desc->descriptor_settings)),
                         (uint32_t) cpy,
                         cpy);

    DMAC_channel_intenset(desc->ex_chnum,
                          desc->irqn,
                          desc->intmsk,
                          desc->irqn_prilvl);
}


void usart_dmac_tx_init(Sercom* const sercom, const ml_dmac_s* const desc, DmacDescriptor* cpy)
{
    DMAC_channel_init(desc->ex_chnum, 
                      desc->chan_settings, 
                      desc->chan_prilvl);


    DMAC_descriptor_init(desc->descriptor_settings,
                         desc->ex_len,
                         ((uint32_t)desc->ex_ptr) + (desc->ex_len * DMAC_extract_btsize(desc->descriptor_settings)),
                         (uint32_t)&sercom->USART.DATA,
                         (uint32_t) cpy,
                         cpy);

    DMAC_channel_intenset(desc->ex_chnum,
                          desc->irqn,
                          desc->intmsk,
                          desc->irqn_prilvl);
}