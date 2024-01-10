
#ifndef ML_SERCOM_USART_H
#define ML_SERCOM_USART_H

#include <stdint.h>
#include <Arduino.h>
#include <ml_dmac.h>

#define ML_USART_MODE_EXTERNAL 0x00
#define ML_USART_MODE_INTERNAL 0x01


#define ML_USART_CMODE_ASYNC    0x00
#define ML_USART_CMODE_SYNC     0x01

#define ML_USART_CHSIZE_5   0x05
#define ML_USART_CHSIZE_6   0x06
#define ML_USART_CHSIZE_7   0x07
#define ML_USART_CHSIZE_8   0x00
#define ML_USART_CHSIZE_9   0x01

#define ML_USART_PARITY_EVEN    0x00
#define ML_USART_PARITY_ODD     0x01
#define ML_USART_PARITY_NONE    0xFF

#define ML_USART_ONE_STOPBIT    0x00
#define ML_USART_TWO_STOPBIT    0x01


typedef enum
{
    USART_MODE_EXTERNAL = ML_USART_MODE_EXTERNAL,
    USART_MODE_INTERNAL = ML_USART_MODE_INTERNAL
} ml_sercom_usart_mode_t;

typedef enum
{
    USART_CMODE_ASYNC = ML_USART_CMODE_ASYNC,
    USART_CMODE_SYNC  = ML_USART_CMODE_SYNC
} ml_sercom_usart_cmode_t;
typedef enum
{
    USART_CHSIZE_8 = ML_USART_CHSIZE_8,
    USART_CHSIZE_9 = ML_USART_CHSIZE_9,
    USART_CHSIZE_5 = ML_USART_CHSIZE_5,
    USART_CHSIZE_6 = ML_USART_CHSIZE_6,
    USART_CHSIZE_7 = ML_USART_CHSIZE_7
} ml_sercom_usart_chsize_t;

typedef enum
{
    USART_PARITY_EVEN = ML_USART_PARITY_EVEN,
    USART_PARITY_ODD  = ML_USART_PARITY_ODD,
    USART_PARITY_NONE = ML_USART_PARITY_NONE
} ml_sercom_usart_parity_t;

typedef enum
{
    USART_SBMODE_ONE = ML_USART_ONE_STOPBIT,
    USART_SBMODE_TWO = ML_USART_TWO_STOPBIT
} ml_sercom_usart_sbmode_t;


typedef struct
{
    ml_sercom_usart_mode_t mode;
    ml_sercom_usart_cmode_t cmode;
    ml_sercom_usart_chsize_t chsize;
    ml_sercom_usart_parity_t parity;
    ml_sercom_usart_sbmode_t sbmode;
    uint16_t baud;
} ml_sercom_usart_settings_t;

typedef struct 
{
    ml_sercom_usart_settings_t sercom_settings;


    ml_dmac_s rx_dmac_s;
    ml_dmac_s tx_dmac_s;

} ml_usart_s;




void usart_dmac_rx_init(Sercom* const, const ml_dmac_s* const, DmacDescriptor*);
void usart_dmac_tx_init(Sercom* const, const ml_dmac_s* const, DmacDescriptor*);
void usart_enable(Sercom* const);
void usart_swrst(Sercom* const);
void usart_disable(Sercom* const);

bool usart_can_transmit(Sercom* const);
bool usart_has_receive(Sercom* const);


uint32_t usart_read(Sercom* const);
void usart_write(Sercom* const, uint32_t);

uint8_t usart_transaction8(Sercom* const, uint8_t);
uint32_t usart_transaction32(Sercom* const, uint32_t);


#define ML_SERCOM_USART_INTCLR_ERR(instance)    (instance->USART.INTENCLR.bit.ERROR = 0x01)
#define ML_SERCOM_USART_INTCLR_RXN(instance)    (instance->USART.INTENCLR.bit.RXBRK = 0x01)
#define ML_SERCOM_USART_INTCLR_CTS(instance)    (instance->USART.INTENCLR.bit.CTSIC = 0x01)
#define ML_SERCOM_USART_INTCLR_RXS(instance)    (instance->USART.INTENCLR.bit.RXS   = 0x01)
#define ML_SERCOM_USART_INTCLR_RXC(instance)    (instance->USART.INTENCLR.bit.RXC   = 0x01)
#define ML_SERCOM_USART_INTCLR_TXC(instance)    (instance->USART.INTENCLR.bit.TXC   = 0x01)
#define ML_SERCOM_USART_INTCLR_DRE(instance)    (instance->USART.INTENCLR.bit.DRE   = 0x01)

#define ML_SERCOM_USART_INTSET_ERR(instance)    (instance->USART.INTENSET.bit.ERROR = 0x01)
#define ML_SERCOM_USART_INTSET_RXN(instance)    (instance->USART.INTENSET.bit.RXBRK = 0x01)
#define ML_SERCOM_USART_INTSET_CTS(instance)    (instance->USART.INTENSET.bit.CTSIC = 0x01)
#define ML_SERCOM_USART_INTSET_RXS(instance)    (instance->USART.INTENSET.bit.RXS   = 0x01)
#define ML_SERCOM_USART_INTSET_RXC(instance)    (instance->USART.INTENSET.bit.RXC   = 0x01)
#define ML_SERCOM_USART_INTSET_TXC(instance)    (instance->USART.INTENSET.bit.TXC   = 0x01)
#define ML_SERCOM_USART_INTSET_DRE(instance)    (instance->USART.INTENSET.bit.DRE   = 0x01)

#define ML_SERCOM_USART_CLR_INTFLAG_ERR(instance)    (instance->USART.INTFLAG.bit.ERROR = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_RXN(instance)    (instance->USART.INTFLAG.bit.RXBRK = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_CTS(instance)    (instance->USART.INTFLAG.bit.CTSIC = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_RXS(instance)    (instance->USART.INTFLAG.bit.RXS   = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_RXC(instance)    (instance->USART.INTFLAG.bit.RXC   = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_TXC(instance)    (instance->USART.INTFLAG.bit.TXC   = 0x01)
#define ML_SERCOM_USART_CLR_INTFLAG_DRE(instance)    (instance->USART.INTFLAG.bit.DRE   = 0x01)

#define ML_SERCOM_USART_INTFLAG_ERR(instance)    (instance->USART.INTFLAG.bit.ERROR == 0x01)
#define ML_SERCOM_USART_INTFLAG_RXN(instance)    (instance->USART.INTFLAG.bit.RXBRK == 0x01)
#define ML_SERCOM_USART_INTFLAG_CTS(instance)    (instance->USART.INTFLAG.bit.CTSIC == 0x01)
#define ML_SERCOM_USART_INTFLAG_RXS(instance)    (instance->USART.INTFLAG.bit.RXS   == 0x01)
#define ML_SERCOM_USART_INTFLAG_RXC(instance)    (instance->USART.INTFLAG.bit.RXC   == 0x01)
#define ML_SERCOM_USART_INTFLAG_TXC(instance)    (instance->USART.INTFLAG.bit.TXC   == 0x01)
#define ML_SERCOM_USART_INTFLAG_DRE(instance)    (instance->USART.INTFLAG.bit.DRE   == 0x01)



#endif
