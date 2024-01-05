#include <Arduino.h>
#include <ml_dmac.h>
#include <ml_usart_common.h>

#define _USART_SYNC(instance, label) while (instance->USART.SYNCBUSY.bit.label)


void usart_enable(void)
{
    SERCOM0->USART.CTRLA.bit.ENABLE = 1;
    _USART_SYNC(SERCOM0, ENABLE);
}
void usart_disable(void)
{
    SERCOM0->USART.CTRLA.bit.ENABLE = 1;
    _USART_SYNC(SERCOM0, ENABLE);
}

bool usart_can_transmit(void)
{
    return ML_SERCOM_USART_INTFLAG_DRE(SERCOM0);
}

bool usart_can_transmit(void)
{
    return ML_SERCOM_USART_INTFLAG_RXC(SERCOM0);
}

bool usart_can_receive(void);

uint32_t  usart_read(void)
{
    return (SERCOM0->USART.DATA.reg);
}

void usart_write(uint32_t data)
{
    SERCOM0->USART.DATA.reg = data;
}

uint8_t usart_transaction8(uint8_t data)
{
    while (!ML_SERCOM_USART_INTFLAG_DRE(SERCOM0));
    SERCOM0->USART.DATA.reg = data;
    while (!ML_SERCOM_USART_INTFLAG_RXC(SERCOM0));
    return (uint8_t)(SERCOM0->USART.DATA.reg);
}
uint32_t usart_transaction32(uint32_t data)
{
    while (!ML_SERCOM_USART_INTFLAG_DRE(SERCOM0));
    SERCOM0->USART.DATA.reg = data;
    while (!ML_SERCOM_USART_INTFLAG_RXC(SERCOM0));
    return (SERCOM0->USART.DATA.reg);
}

void usart_dmac_rx_init(const ml_dmac_s* const desc, DmacDescriptor* cpy)
{
    DMAC_channel_init(desc->ex_chnum, 
                      desc->chan_settings, 
                      desc->chan_prilvl);


    DMAC_descriptor_init(desc->descriptor_settings,
                         desc->ex_len,
                         (uint32_t)&SERCOM0->USART.DATA,
                         ((uint32_t)desc->ex_ptr) + (desc->ex_len * DMAC_extract_btsize(desc->descriptor_settings)),
                         (uint32_t) cpy,
                         cpy);

    DMAC_channel_intenset(desc->ex_chnum,
                          desc->irqn,
                          desc->intmsk,
                          desc->irqn_prilvl);
}


void usart_dmac_tx_init(const ml_dmac_s* const desc, DmacDescriptor* cpy)
{
    DMAC_channel_init(desc->ex_chnum, 
                      desc->chan_settings, 
                      desc->chan_prilvl);


    DMAC_descriptor_init(desc->descriptor_settings,
                         desc->ex_len,
                         ((uint32_t)desc->ex_ptr) + (desc->ex_len * DMAC_extract_btsize(desc->descriptor_settings)),
                         (uint32_t)&SERCOM0->USART.DATA,
                         (uint32_t) cpy,
                         cpy);

    DMAC_channel_intenset(desc->ex_chnum,
                          desc->irqn,
                          desc->intmsk,
                          desc->irqn_prilvl);
}