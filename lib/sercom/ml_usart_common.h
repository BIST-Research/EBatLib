#ifndef ML_SERCOM_USART_H
#define ML_SERCOM_USART_H

#include <stdint.h>

void usart_enable(void);
void usart_disable(void);


uint8_t  usart_read8(void);
uint32_t usart_read32(void);

uint8_t usart_write8(uint8_t);
uint32_t usart_write32(uint32_t);


#define ML_SERCOM_USART_INTCLR_ERR(instance)    (instance->INTENCLR.bit.ERROR = 0x01)
#define ML_SERCOM_USART_INTCLR_RXN(instance)    (instance->INTENCLR.bit.RXBRK = 0x01)
#define ML_SERCOM_USART_INTCLR_CTS(instance)    (instance->INTENCLR.bit.CTSIC = 0x01)
#define ML_SERCOM_USART_INTCLR_RXS(instance)    (instance->INTENCLR.bit.RXS   = 0x01)
#define ML_SERCOM_USART_INTCLR_TXC(instance)    (instance->INTENCLR.bit.TXC   = 0x01)
#define ML_SERCOM_USART_INTCLR_DRE(instance)    (instance->INTENCLR.bit.DRE   = 0x01)

#define ML_SERCOM_USART_INTSET_ERR(instance)    (instance->INTENSET.bit.ERROR = 0x01)
#define ML_SERCOM_USART_INTSET_RXN(instance)    (instance->INTENSET.bit.RXBRK = 0x01)
#define ML_SERCOM_USART_INTSET_CTS(instance)    (instance->INTENSET.bit.CTSIC = 0x01)
#define ML_SERCOM_USART_INTSET_RXS(instance)    (instance->INTENSET.bit.RXS   = 0x01)
#define ML_SERCOM_USART_INTSET_TXC(instance)    (instance->INTENSET.bit.TXC   = 0x01)
#define ML_SERCOM_USART_INTSET_DRE(instance)    (instance->INTENSET.bit.DRE   = 0x01)

#define ML_SERCOM_USART_CLR_INTFLAG_ERR(instance)    (instance->INTFLAG.bit.ERROR = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_RXN(instance)    (instance->INTFLAG.bit.RXBRK = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_CTS(instance)    (instance->INTFLAG.bit.CTSIC = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_RXS(instance)    (instance->INTFLAG.bit.RXS   = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_TXC(instance)    (instance->INTFLAG.bit.TXC   = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_DRE(instance)    (instance->INTFLAG.bit.DRE   = 0x01)

#define ML_SERCOM_USART_INTFLAG_ERR(instance)    (instance->INTFLAG.bit.ERROR == 0x01)
#define ML_SERCOM_USART_INTFLAG_RXN(instance)    (instance->INTFLAG.bit.RXBRK == 0x01)
#define ML_SERCOM_USART_INTFLAG_CTS(instance)    (instance->INTFLAG.bit.CTSIC == 0x01)
#define ML_SERCOM_USART_INTFLAG_RXS(instance)    (instance->INTFLAG.bit.RXS   == 0x01)
#define ML_SERCOM_USART_INTFLAG_TXC(instance)    (instance->INTFLAG.bit.TXC   == 0x01)
#define ML_SERCOM_USART_INTFLAG_DRE(instance)    (instance->INTFLAG.bit.DRE   == 0x01)



#endif