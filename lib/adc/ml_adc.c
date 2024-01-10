/*
 * Author: Ben Westcott
 * Date created: 8/1/23
 */

#include <ml_adc.h>
#include <ml_adc0.h>
#include <ml_adc1.h>
#include <ml_clocks.h>

/**
 * Waits for ADC to synchronise with the main clock
 * 
 * 
 * instance: Pointer to the ADC syncronizing
 * 
 * Register bits that needs to be synced:
 *      -CTRLA.SWRST
 *      -CTRLA.ENABLE
 * Registers that need to be synced:
 *      -INPUTCTRL
 *      -CTRLB
 *      -REFCTRL
 *      -AVGCTRL
 *      -SAMPCTRL
 *      -WINLT
 *      -WINUT
 *      -GAINCORR
 *      -OFFSETCORR
 *      -SWTRIG
 * */
#define _ADC_SYNC(instance, label) while (instance->SYNCBUSY.bit.label)



/**
 * Enables the ADC for operation
 * 
 * instance: Pointer to the ADC instance to be enabled
 * 
 * 
 * Side effects: The ADC is ready to perform conversions.
 *               Must manually trigger first conversion.
 *               Some configuration cannot be edited if
 *               ADC is enabled.
*/
void ADC_enable(Adc* const instance)
{
    instance->CTRLA.bit.ENABLE = 1;
    _ADC_SYNC(instance, ENABLE);
}

/**
 * Disables the ADC from operation
 * 
 * instance: Pointer to the ADC instance to be disabled
 * 
 * Side effects: The ADC is no longer in operation.
 *               Enabled-protected register can be 
 *               configured in this state.
*/
void ADC_disable(Adc* const instance)
{
    instance->CTRLA.bit.ENABLE = 0;
    _ADC_SYNC(instance, ENABLE);
}



/**
 * Performs a software reset of the ADC.
 * 
 * IMPORTANT: This operation take precedence over all write 
 *            operations to the ADC. Any other writes to the ADC 
 *            will be discarded
 * 
 * instance: Pointer to the ADC instance to perform a 
 *           software reset
 * 
 * Side effects: The ADC will return to default configurations,
 *               and will be disabled.
*/
void ADC_swrst(Adc* const instance)
{
    ML_ADC_SWRST(instance);
    _ADC_SYNC(instance, SWRST);
}

/**
 * Enables Window Single Sample
 * 
 * instance: Pointer to the ADC instance
*/
void ADC_winss_enable(Adc* const instance) 
{
    instance->CTRLB.bit.WINSS = 1;
    _ADC_SYNC(instance, CTRLB);
}

/**
 * Disables Window Single Sample
 * 
 * instance: Pointer to the ADC instance
*/
void ADC_winss_disable(Adc* const instance)
{
    instance->CTRLB.bit.WINSS = 0;
    _ADC_SYNC(instance, CTRLB);
}

/**
 * Sets the Window Monitoring Mode
 * 
 * instance: Pointer to the ADC instance
 * winmode: The mode the ADC should use
*/
void ADC_set_winmode(Adc* const instance, const ml_adc_winmode_t winmode)
{
    instance->CTRLB.bit.WINMODE = winmode;
    _ADC_SYNC(instance, CTRLB);
}

void ADC_freerun_enable(Adc* const instance)
{
    instance->CTRLB.bit.FREERUN = 1;
    _ADC_SYNC(instance, CTRLB);
}

void ADC_freerun_disable(Adc* const instance)
{
    instance->CTRLB.bit.FREERUN = 0;
    _ADC_SYNC(instance, CTRLB);
}

void ADC_result_leftadj(Adc* const instance)
{
    instance->CTRLB.bit.LEFTADJ = 0;
    _ADC_SYNC(instance, CTRLB);
}

void ADC_result_rightadj(Adc* const instance)
{
    instance->CTRLB.bit.LEFTADJ = 1;
    _ADC_SYNC(instance, CTRLB);
}
/**
 * Sets the desired conversion resolution
 * for the ADC
 * 
 * 
 * instance:        Pointer to the ADC instance to change 
 *                  the conversion resolution
 * resolution:      The resolution the ADC should use
*/
void ADC_set_russel(Adc* const instance, const ml_adc_conv_resolution_t resolution)
{
    instance->CTRLB.bit.RESSEL = resolution;
    _ADC_SYNC(instance, CTRLB);
}

/**
 * Enables digital correction (Gain and Offset correction)
 * 
 * 
 * instance: Pointer to the ADC instance to enable 
 *           digital correction
*/
void ADC_corren_enable(Adc* const instance) 
{
    instance->CTRLB.bit.CORREN = 1;
    _ADC_SYNC(instance, CTRLB);
}

/**
 * Disables digital correction (Gain and Offset correction)
 * 
 * instance: Pointer to the ADC instance to disable
 *           digital correction
*/
void ADC_corren_disable(Adc* const instance) 
{
    instance->CTRLB.bit.CORREN = 0;
    _ADC_SYNC(instance, CTRLB);
}

/**
 * Enables the DMA sequencing to stop automatically when
 * the last sequence is completed
 * 
 * instance: Pointer to the ADC instance to enable autostop
*/
void ADC_dseqstop_enable(Adc* const instance) 
{
    instance->INPUTCTRL.bit.DSEQSTOP = 1;
    _ADC_SYNC(instance, INPUTCTRL);
}

/**
 * 
*/
void ADC_dseqstop_disable(Adc* const instance)
{
    instance->INPUTCTRL.bit.DSEQSTOP = 0;
    _ADC_SYNC(instance, INPUTCTRL);
}

/**
 * Sets the negative input for the ADC to compare
 * to subtract from the positive input (in BOTH diff mode)
 * 
 * instance: Pointer to the ADC instance
 * negIn: The negative input the ADC instance should use
*/
void ADC_set_muxneg(Adc* const instance, const ml_adc_muxneg_t negIn)
{
    instance->INPUTCTRL.bit.MUXNEG = negIn;
    _ADC_SYNC(instance, INPUTCTRL);
}

/**
 * Sets the positive input for the ADC to sample
 * 
 * instance: Pointer to the ADC instance
 * posIn: The positive input the ADC instance should use
*/
void ADC_set_muxpos(Adc* const instance, const ml_adc_muxpos_t posIn)
{
    instance->INPUTCTRL.bit.MUXPOS = posIn;
    _ADC_SYNC(instance, INPUTCTRL);
}

/**
 * Sets the input mode of the ADC
 * 
 * instance: Pointer to the ADC instance
 * mode: The mode to change the input mode
 *       for the ADC
*/
void ADC_set_diffmode(Adc* const instance, ml_adc_inputmode_t mode)
{
    instance->INPUTCTRL.bit.DIFFMODE = mode;
    _ADC_SYNC(instance, INPUTCTRL);
}

void ADC_refcomp_enable(Adc* const instance)
{
    instance->REFCTRL.bit.REFCOMP = 1;
    _ADC_SYNC(instance, REFCTRL);
}

void ADC_refcomp_disable(Adc* const instance)
{
    instance->REFCTRL.bit.REFCOMP = 0;
    _ADC_SYNC(instance, REFCTRL);
}

void ADC_set_divisioncoef(Adc* const instance, const uint8_t n)
{
    instance->AVGCTRL.bit.ADJRES = n;
    _ADC_SYNC(instance, AVGCTRL);
}

void ADC_set_avgsample(Adc* const instance, const ml_adc_samplenum_t sampleNum)
{
    instance->AVGCTRL.bit.SAMPLENUM = sampleNum;
    _ADC_SYNC(instance, AVGCTRL);
}


/* WINLT Configurations */
void ADC_set_winlt(Adc* const instance, const uint16_t threshold)
{
    instance->WINLT.reg = threshold;
    _ADC_SYNC(instance, WINLT);
}

/* WINUT Configurations */
void ADC_set_winut(Adc* const instance, const uint16_t threshold)
{
    instance->WINUT.reg = threshold;
    _ADC_SYNC(instance, WINUT);
}

/* GAINCORR Configurations */
void ADC_set_gaincorr(Adc* const instance, const uint16_t gaincorr)
{
    instance->GAINCORR.reg = gaincorr;
    _ADC_SYNC(instance, GAINCORR);
}

/* OFFSETCORR Configurations */
void ADC_set_offsetcorr(Adc* const instance, const uint16_t offsetcorr)
{
    instance->OFFSETCORR.reg = offsetcorr;
    _ADC_SYNC(instance, OFFSETCORR);
}

/**
 * Selects the reference voltage of the ADC
 * 
 * instance: Pointer to the ADC instance
 * refsel: The reference voltage to use for the ADC
*/
void ADC_reference_select(Adc* const instance, const ml_adc_refsel_t refsel)
{
    instance->REFCTRL.bit.REFSEL = refsel;
    _ADC_SYNC(instance, REFCTRL);
}
/**
 * Enables offset compenstation
 * 
 * instance: Pointer to the ADC instance to 
 *           enable offset compensation
 * 
 * side effects: Sets the sample time length to 1
*/
void ADC_offcomp_enable(Adc* const instance)
{
    ADC_set_samplingLength(instance, 0);
    instance->SAMPCTRL.bit.OFFCOMP = 1;
    _ADC_SYNC(instance, SAMPCTRL);
}

/**
 * Disables offset compensation
 * 
 * instance: Pointer to the ADC instance to
 *           disable offset compensation
 * 
*/
void ADC_offcomp_disable(Adc* const instance)
{
    instance->SAMPCTRL.bit.OFFCOMP = 0;
    _ADC_SYNC(instance, SAMPCTRL);
}

/**
 * Sets the sample length time (in cycles) of the
 * ADC
 * 
 * instance: Pointer to the ADC instance
 * sampling: The number of cycles for sampling
 * 
 * NOTE: The true cycle sampling would be sampling + 1
*/
void ADC_set_samplingLength(Adc* const instance, const uint8_t sampling)
{
    instance->SAMPCTRL.bit.SAMPLEN = sampling;
    _ADC_SYNC(instance, SAMPCTRL);
}

/**
 * Manually triggers the ADC to start a conversion
 * 
 * instance: Pointer to the ADC instance to
 *           trigger conversion
*/
void ADC_start_conversion(Adc* const instance)
{
    instance->SWTRIG.bit.START = 1;
    _ADC_SYNC(instance, SWTRIG);
}

/**
 * Reads the current sampled analog voltage that
 * was converted
 * 
 * instance: Pointer to the ADC instance to read
 *           the sampled analog voltage from  
*/
uint16_t ADC_read_result(Adc* const instance)
{
    return instance->RESULT.reg;
}

/**
 * General default initialization for any ADC instances
 * 
 * instance: The ADC to initialize
*/
uint8_t ADC_init(Adc* const instance)
{
    ADC_swrst(instance);
    
    ML_ADC_SET_PRESCALER(instance, ML_ADC_PRESCALER_DIV8);
    ML_ADC_SET_DUALSEL_BOTH(instance);
    
    ADC_reference_select(instance, ADC_VREF_VDDANA);
    ADC_freerun_enable(instance);
    ADC_set_diffmode(instance, ADC_DIFFMODE_SINGLE);

    return 1;
}


/**
 * Initializes the necessary clocks for ADC0
*/
void ADC0_init(void)
{
    MCLK->APBDMASK.bit.ADC0_ = 1;
    ML_SET_GCLK7_PCHCTRL(ADC0_GCLK_ID);
}

/**
 * Initializes the necessary clocks for ADC1
*/
void ADC1_init(void)
{
    MCLK->APBDMASK.bit.ADC1_ = 1;
    ML_SET_GCLK7_PCHCTRL(ADC1_GCLK_ID);
}

void ADC_initDMA(Adc* const instance, ml_dmac_chnum_t chnum, uint32_t* destination, uint16_t length, ml_dmac_chprilvl_t priv, uint32_t channel_settings, uint32_t desc_settings, uint32_t descaddr, DmacDescriptor* cpy)
{
    DMAC_channel_init(chnum, channel_settings, priv);
    DMAC_descriptor_init(desc_settings, length, (uint32_t) &instance->RESULT.reg, (uint32_t) destination, descaddr, cpy);
}
 


/*
const ml_dmac_s ml_adc0_dmac_prototype = {
    .chan_prilvl = PRILVL0,
    .chan_settings = ml_adc0_dmac_channel_settings,
    .descriptor_settings = ml_adc0_dmac_desc_settings,
    .ex_chnum = DMAC_CH0,//temp
    .intmsk = DMAC_CHINTENSET_SUSP,
    .irqn = DMAC_0_IRQn,
    .irqn_prilvl = 0,
    .nvic = true
};

*/