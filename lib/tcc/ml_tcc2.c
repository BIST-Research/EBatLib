/*
 * Author: Ben Westcott
 * Date created: 12/31/23
 */

#include <ml_tcc_common.h>
#include <ml_tcc2.h>

/*
 * Typically I use TCC2 for the DAC timing
 * so it will be on GCLK4
 */
void TCC2_init(void)
{

    TCC_disable(TCC2);
    TCC_swrst(TCC2);

    TCC0->CTRLA.reg = 
    (
        TCC_CTRLA_PRESCALER_DIV2 |
        TCC_CTRLA_PRESCSYNC_PRESC
    );

    TCC0->WAVE.reg = TCC_WAVE_WAVEGEN_NFRQ;

    // 12 MHz / (2 * 6) = 1 MHz
    TCC_set_period(TCC0, 6);

}