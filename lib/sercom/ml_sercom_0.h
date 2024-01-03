#ifndef ML_SERCOM_0
#define ML_SERCOM_0


typedef enum
{
    USART_MODE_EXTERNAL = 0x00,
    USART_MODE_INTERNAL = 0x01
} ml_sercom_usart_mode;

typedef enum
{
    USART_CMODE_ASYNC = 0x00,
    USART_CMODE_SYNC  = 0x01
} ml_sercom_usart_cmode;
typedef enum
{
    USART_CHSIZE_8 = 0x00,
    USART_CHSIZE_9 = 0x01,
    USART_CHSIZE_5 = 0x05,
    USART_CHSIZE_6 = 0x06,
    USART_CHSIZE_7 = 0x07
} ml_sercom_usart_chsize;

typedef enum
{
    USART_PARITY_EVEN = 0x00,
    USART_PARITY_ODD  = 0x01,
    USART_PARITY_NONE = 0xFF
} ml_sercom_usart_parity;

typedef enum
{
    USART_SBMODE_ONE = 0x00,
    USART_SBMODE_TWO = 0x01
} ml_sercom_usart_sbmode;

typedef struct
{
    ml_sercom_usart_mode mode;
    ml_sercom_usart_cmode cmode;
    ml_sercom_usart_chsize chsize;
    ml_sercom_usart_parity parity;
    ml_sercom_usart_sbmode sbmode;
    uint16_t baud;
} ml_sercom_usart_settings;

void sercom0_usart_init(const ml_sercom_usart_settings* const);

#endif