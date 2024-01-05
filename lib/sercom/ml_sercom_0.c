#include <Arduino.h>
#include <ml_port.h>
#include <ml_sercom_0.h>


static Sercom* coms[SERCOM_INST_NUM] = SERCOM_INSTS;

#define _USART_SYNC(instance, label) while (instance->USART.SYNCBUSY.bit.label)

void sercom0_usart_init(const ml_sercom_usart_settings_t* const settings)
{
    SERCOM0->USART.CTRLA.bit.FORM   = 0x00;
    SERCOM0->USART.CTRLA.bit.MODE   = settings->mode;
    SERCOM0->USART.CTRLA.bit.CMODE  = settings->cmode;
    SERCOM0->USART.CTRLB.bit.CHSIZE = settings->chsize;
    SERCOM0->USART.CTRLB.bit.SBMODE = settings->sbmode;
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