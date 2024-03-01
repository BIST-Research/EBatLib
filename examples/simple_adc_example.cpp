/*
 * Author: Ben Westcott
 * Date created: 3/1/24
 */

#include <Arduino.h>
#include <ml_clocks.h>
#include <ml_adc_common.h>
#include <ml_adc0.h>
#include <ml_port.h>

// A2 on ItsyBitsy
// A11 on GrandCentral
const ml_pin_settings adc_pin = {PORT_GRP_B, 8, PF_B, PP_EVEN, ANALOG, DRIVE_OFF};

void setup(void)
{
  MCLK_init();
  GCLK_init();

  Serial.begin(115200);
  while(!Serial);
  
  ADC0_init();
  peripheral_port_init(&adc_pin);

  ADC_enable(ADC0);
  ADC_swtrig_start(ADC0);

  // RESRDY: result ready
  ADC0->INTENSET.bit.RESRDY = true;

}

uint16_t result = 0;

void loop(void)
{
  if(ADC0->INTFLAG.bit.RESRDY == true)
  {
    // reading RESULT clears RESRDY flag (pp. 1630)
    result = (uint16_t)ADC0->RESULT.reg;
    Serial.println(result);
  }  
}

