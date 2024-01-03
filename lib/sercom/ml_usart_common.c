#include <Arduino.h>
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


uint8_t  usart_read8(void)
{
}
uint32_t usart_read32(void)
{

}

uint8_t usart_write8(uint8_t data)
{

}
uint32_t usart_write32(uint32_t data)
{

}