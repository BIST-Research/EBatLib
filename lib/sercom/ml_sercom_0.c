#include <Arduino.h>
#include <ml_port.h>
#include <ml_sercom_0.h>



void sercom0_usart_init(const ml_sercom_usart_settings* const settings)
{
    SERCOM0->USART.CTRLA.bit.FORM   = 0x00;
    SERCOM0->USART.CTRLA.bit.MODE   = settings->mode;
    SERCOM0->USART.CTRLA.bit.CMODE  = settings->cmode;
    SERCOM0->USART.CTRLB.bit.CHSIZE = settings->chsize;
    SERCOM0->USART.CTRLB.bit.SBMODE = settings->sbmode;


    if (settings->mode == USART_MODE_INTERNAL)
    {
        SERCOM0->USART.BAUD.reg     = settings->baud;
    }

    if (settings->parity != USART_PARITY_NONE)
    {
        SERCOM0->USART.CTRLA.bit.FORM |= 0x01;
        SERCOM0->USART.CTRLB.bit.PMODE = settings->parity;
    }
    
    SERCOM0->USART.CTRLB.bit.RXEN = 1;
    SERCOM0->USART.CTRLB.bit.TXEN = 1;
}