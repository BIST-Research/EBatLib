#include <ml_clocks.h>
#include <ml_sercom_0.h>
#include <ml_port.h>


const ml_pin_settings rx_pin = 
{
    PORT_GRP_A,
    0x05,
    PF_D,
    PP_ODD,
    INPUT_STANDARD,
    DRIVE_OFF
};

const ml_pin_settings tx_pin =
{
    PORT_GRP_A,
    0x04,
    PF_D,
    PP_EVEN,
    OUTPUT_PULL_DOWN,
    DRIVE_OFF
};

const ml_sercom_usart_settings_t usart_settings = 
{
    USART_MODE_INTERNAL,
    USART_CMODE_ASYNC,
    USART_CHSIZE_8,
    USART_PARITY_EVEN,
    USART_SBMODE_ONE,
    0xCED9
};
//PA04
//PA05
void setup()
{
    MCLK_init();
    GCLK_init();

    peripheral_port_init(&rx_pin);
    peripheral_port_init(&tx_pin);

    Serial.begin(9600);
    sercom0_usart_init(&usart_settings);
    usart_enable(SERCOM0);
}

void loop()
{
    if (usart_has_receive(SERCOM0))
    {
        char c = usart_read(SERCOM0);
        Serial.printf("Character received: %#x", c);
    }
}
