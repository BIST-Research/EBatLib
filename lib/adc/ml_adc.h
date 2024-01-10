/*
 * Author: Ben Westcott
 * Date created: 3/6/23
 */

#ifndef ML_ADC_H
#define ML_ADC_H

#include <Arduino.h>
#include <ml_dmac.h>

#ifdef __cplusplus
extern "C"
{
#endif


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////   MACRO DEFINITIONS   /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

#define ML_ADC_RES8_MAX         (0x00FF)
#define ML_ADC_RES10_MAX        (0x03FF)
#define ML_ADC_RES12_MAX        (0x0FFF)
#define ML_ADC_RES16_MAX        (0xFFFF)

#define ML_ADC_PRESCALER_DIV2   (0x00)
#define ML_ADC_PRESCALER_DIV4   (0x01)
#define ML_ADC_PRESCALER_DIV8   (0x02)
#define ML_ADC_PRESCALER_DIV16  (0x03)
#define ML_ADC_PRESCALER_DIV32  (0x04)
#define ML_ADC_PRESCALER_DIV64  (0x05)
#define ML_ADC_PRESCALER_DIV128 (0x06)
#define ML_ADC_PRESCALER_DIV256 (0x07)


#define ML_ADC_CONVERSION_RES12 (0x00)
#define ML_ADC_CONVERSION_RES16 (0x01)
#define ML_ADC_CONVERSION_RES10 (0x02)
#define ML_ADC_CONVERSION_RES8  (0x03)


#define ML_ADC_REFCTRL_INTREF   (0x00)
#define ML_ADC_REFCTRL_INTVCC0  (0x02)
#define ML_ADC_REFCTRL_INTVCC1  (0x03)
#define ML_ADC_REFCTRL_AREFA    (0x04)
#define ML_ADC_REFCTRL_AREFB    (0x05)
#define ML_ADC_REFCTRL_AREFC    (0x06)

/* MUX/MUXNEG input selection*/
#define ML_ADC_AIN0             (0x00)
#define ML_ADC_AIN1             (0x01)
#define ML_ADC_AIN2             (0x02)
#define ML_ADC_AIN3             (0x03)
#define ML_ADC_AIN4             (0x04)
#define ML_ADC_AIN5             (0x05)
#define ML_ADC_AIN6             (0x06)
#define ML_ADC_AIN7             (0x07)
#define ML_ADC_AIN8             (0x08)
#define ML_ADC_AIN9             (0x09)
#define ML_ADC_AIN10            (0x0A)
#define ML_ADC_AIN11            (0x0B)
#define ML_ADC_AIN12            (0x0C)
#define ML_ADC_AIN13            (0x0D)
#define ML_ADC_AIN14            (0x0E)
#define ML_ADC_AIN15            (0x0F)
#define ML_ADC_AIN16            (0x10)
#define ML_ADC_AIN17            (0x11)
#define ML_ADC_AIN18            (0x12)
#define ML_ADC_AIN19            (0x13)
#define ML_ADC_AIN20            (0x14)
#define ML_ADC_AIN21            (0x15)
#define ML_ADC_AIN22            (0x16)
#define ML_ADC_AIN23            (0x17)


#define ML_ADC_DIFFMODE_SINGLE  (0x00)
#define ML_ADC_DIFFMODE_BOTH    (0x01)

/* Special MUX/MUXNEG input selection*/
#define ML_ADC_AINSCALEDCOREVCC    (0x18)
#define ML_ADC_AINGND              (0x18)
#define ML_ADC_AINSCALEDVBAT       (0x19)
#define ML_ADC_AINSCALEDIOVCC      (0x20)
#define ML_ADC_AINBANDGAP          (0x21)
#define ML_ADC_AINPTAT             (0x22)
#define ML_ADC_AINCTAT             (0x23)
#define ML_ADC_AINDAC              (0x24)


/* AVGCTRL Sample */
#define ML_ADC_SAMPLE1      (0x00)
#define ML_ADC_SAMPLE2      (0x01)
#define ML_ADC_SAMPLE4      (0x02)
#define ML_ADC_SAMPLE8      (0x03)
#define ML_ADC_SAMPLE16     (0x04)
#define ML_ADC_SAMPLE32     (0x05)
#define ML_ADC_SAMPLE64     (0x06)
#define ML_ADC_SAMPLE128    (0x07)
#define ML_ADC_SAMPLE256    (0x08)
#define ML_ADC_SAMPLE512    (0x09)
#define ML_ADC_SAMPLE1024   (0x0A)

/* WINMODE */
#define ML_ADC_WINMODE0     (0x00)
#define ML_ADC_WINMODE1     (0x01)
#define ML_ADC_WINMODE2     (0x02)
#define ML_ADC_WINMODE3     (0x03)
#define ML_ADC_WINMODE4     (0x04)


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////  MACRO CONFIGURATIONS        //////////////////////////
///////////////////////////////////////////////////////////////////////////////////
#define ML_ADC_ENABLE(instance) (instance->CTRLA.reg |= ADC_CTRLA_ENABLE)
#define ML_ADC_DISABLE(instance) (instance->CTRLA.reg &= ~ADC_CTRLA_ENABLE)
#define ML_ADC_SWRST(instance) (instance->CTRLA.reg |= ADC_CTRLA_SWRST)
#define ML_ADC_SWTRIG_START(instance) (instance->SWTRIG.reg |= ADC_SWTRIG_START)

/* CTRLA */
#define ML_ADC_R2R_ENABLE(instance)         (instance->CTRLA.bit.R2R = 1)
#define ML_ADC_R2R_DISABLE(instance)        (instance->CTRLA.bit.R2R = 0)
#define ML_ADC_SET_PRESCALER(instance, p)   (instance->CTRLA.bit.PRESCALER = p)
#define ML_ADC_ONDEMAND_ENABLE(instance)    (instance->CTRLA.bit.ONDEMAND = 1)
#define ML_ADC_ONDEMAND_DISABLE(instance)   (instance->CTRLA.bit.ONDEMAND = 0)
#define ML_ADC_SET_DUALSEL_BOTH(instance)   (instance->CTRLA.bit.DUALSEL = 0)
#define ML_ADC_SET_DUALSEL_INTER(instance)  (instance->CTRLA.bit.DUALSEL = 1)

/* EVCTRL */
#define ML_ADC_WINMONITOREO_ENABLE(instance)    (instance->EVCTRL.bit.WINMONEO = 1)
#define ML_ADC_WINMONITOREO_DISABLE(instance)   (instance->EVCTRL.bit.WINMONEO = 0)
#define ML_ADC_RESULTEO_ENABLE(instance)        (instance->EVCTRL.bit.RESRDYEO = 1)
#define ML_ADC_RESULTEO_DISABLE(instance)       (instance->EVCTRL.bit.RESRDYEO = 0)
#define ML_ADC_START_INVEO_ENABLE(instance)     (instance->EVCTRL.bit.STARTINV = 1)
#define ML_ADC_START_INVEO_DISABLE(instance)    (instance->EVCTRL.bit.STARTINV = 0)
#define ML_ADC_FLUSH_INVEO_ENABLE(instance)     (instance->EVCTRL.bit.FLUSHINV = 1)
#define ML_ADC_FLUSH_INVEO_DISABLE(instance)    (instance->EVCTRL.bit.FLUSHINV = 0)
#define ML_ADC_START_CONVEO_ENABLE(instance)    (instance->EVCTRL.bit.STARTEI  = 1)
#define ML_ADC_START_CONVEO_DISABLE(instance)   (instance->EVCTRL.bit.STARTEI  = 0)
#define ML_ADC_FLUSHEV_ENABLE(instance)         (instance->EVCTRL.bit.FLUSHEI  = 1)
#define ML_ADC_FLUSHEV_DISABLE(instance)        (instance->EVCTRL.bit.FLUSHEI  = 1)

/* DBGCTRL */
#define ML_ADC_DBGCTRL_HALT(instance)   (instance->DBGRUN.reg = 0)
#define ML_ADC_DBGCTRL_CONT(instance)   (instance->DBGRUN.reg = 1)

/* INTENSET and INTENCLR */
#define ML_ADC_INT_WINMON_ENABLE(instance)      (instance->INTENSET.bit.WINMON = 1)
#define ML_ADC_INT_WINMON_DISABLE(instance)     (instance->INTENCLR.bit.WINMON = 0)
#define ML_ADC_INT_OVERRUN_ENABLE(instance)     (instance->INTENSET.bit.OVERRUN = 1)
#define ML_ADC_INT_OVERRUN_DISABLE(instance)    (instance->INTENCLR.bit.OVERRUN = 0)
#define ML_ADC_INT_RESRDY_ENABLE(instance)      (instance->INTENSET.bit.RESRDY = 1)
#define ML_ADC_INT_RESRDY_DISABLE(instance)     (instance->INTENCLR.bit.RESRDY = 0)

/* INTFLAG */
#define ML_ADC_INTFLAG_WINMON(instance)         (instance->INTFLAG.bit.WINMON)
#define ML_ADC_INTFLAG_WINMON_CLR(instance)     (instance->INTFLAG.bit.WINMON = 1)
#define ML_ADC_INTFLAG_OVERRUN(instance)        (instance->INTFLAG.bit.OVERRUN)
#define ML_ADC_INTFLAG_OVERRUN_CLR(instance)    (instance->INTFLAG.bit.OVERRUN = 1)
#define ML_ADC_INTFLAG_RESDY(instance)          (instance->INTFLAG.bit.RESRDY)
#define ML_ADC_INTFLAG_RESDY_CLR(instance)      (instance->INTFLAG.bit.RESRDY = 1)

/* STATUS */
#define ML_ADC_STATUS_WCC(instance)     (instance->STATUS.bit.WCC)
#define ML_ADC_STATUS_ADCBUSY(instance) (instance->STATUS.bit.ADCBUSY)

/* DSEQDATA */
#define ML_ADC_DSEQDATA(instance)   (instance->DSEQDATA.reg);

/* DSEQCTRL */
#define ML_ADC_DSEQCTRL_AUTOSTART_ENABLE(instance)      (instance->DSEQCTRL.bit.AUTOSTART = 1)
#define ML_ADC_DSEQCTRL_AUTOSTART_DISABLE(instance)     (instance->DSEQCTRL.bit.AUTOSTART = 0)
#define ML_ADC_DSEQCTRL_OFFSETCORR_ENABLE(instance)     (instance->DSEQCTRL.bit.OFFSETCORR = 1)
#define ML_ADC_DSEQCTRL_OFFSETCORR_DISABLE(instance)    (instance->DSEQCTRL.bit.OFFSETCORR = 0)
#define ML_ADC_DSEQCTRL_GAINCORR_ENABLE(instance)       (instance->DSEQCTRL.bit.GAINCORR = 1)
#define ML_ADC_DSEQCTRL_GAINCORR_DISABLE(instance)      (instance->DSEQCTRL.bit.GAINCORR = 0)
#define ML_ADC_DSEQCTRL_WINUT_ENABLE(instance)          (instance->DSEQCTRL.bit.WINUT = 1)
#define ML_ADC_DSEQCTRL_WINUT_DISABLE(instance)         (instance->DSEQCTRL.bit.WINUT = 0)
#define ML_ADC_DSEQCTRL_WINLT_ENABLE(instance)          (instance->DSEQCTRL.bit.WINLT = 1)
#define ML_ADC_DSEQCTRL_WINLT_DISABLE(instance)         (instance->DSEQCTRL.bit.WINLT = 0)
#define ML_ADC_DSEQCTRL_SAMPCTRL_ENABLE(instance)       (instance->DSEQCTRL.bit.SAMPCTRL = 1)
#define ML_ADC_DSEQCTRL_SAMPCTRL_DISABLE(instance)      (instance->DSEQCTRL.bit.SAMPCTRL = 0)
#define ML_ADC_DSEQCTRL_REFCTRL_ENABLE(instance)        (instance->DSEQCTRL.bit.REFCTRL = 1)
#define ML_ADC_DSEQCTRL_REFCTRL_DISABLE(instance)       (instance->DSEQCTRL.bit.REFCTRL = 0)
#define ML_ADC_DSEQCTRL_CTRLB_ENABLE(instance)          (instance->DSEQCTRL.bit.CTRLB = 1)
#define ML_ADC_DSEQCTRL_CTRLB_DISABLE(instance)         (instance->DSEQCTRL.bit.CTRLB = 0)
#define ML_ADC_DSEQCTRL_INPUTCTRL_ENABLE(instance)      (instance->DSEQCTRL.bit.INPUTCTRL = 1)
#define ML_ADC_DSEQCTRL_INPUTCTRL_DISABLE(instance)     (instance->DSEQCTRL.bit.INPUTCTRL = 0)

/* DSEQSTAT */
#define ML_ADC_DSEQSTAT_BUSY(instance)          (instance->DSEQSTAT.bit.BUSY)
#define ML_ADC_DSEQSTAT_OFFSETCORR(instance)    (instance->DSEQSTAT.bit.OFSSETCORR)
#define ML_ADC_DSEQSTAT_GAINCORR(instance)      (instance->DSEQSTAT.bit.GAINCORR)
#define ML_ADC_DSEQSTAT_WINUT(instance)         (instance->DSEQSTAT.bit.WINUT)
#define ML_ADC_DSEQSTAT_WINLT(instance)         (instance->DSEQSTAT.bit.WINLT)
#define ML_ADC_DSEQSTAT_SAMPCTRL(instance)      (instance->DSEQSTAT.bit.SAMPCTRL)
#define ML_ADC_DSEQSTAT_AVGCTRL(instance)       (instance->DSEQSTAT.bit.AVGCTRL)
#define ML_ADC_DSEQSTAT_REFCTRL(instance)       (instance->DSEQSTAT.bit.REFCTRL)
#define ML_ADC_DSEQSTAT_CTRLB(instance)         (instance->DSEQSTAT.bit.CTRLB)
#define ML_ADC_DSEQSTAT_INPUTCTRL(instance)     (instance->DSEQSTAT.bit.INPUTCTRL)


/* RESULT and RESS */
#define ML_ADC_RESULT(instance)     (instance->RESULT.reg)
#define ML_ADC_RESS(instance)       (instance->RESS.reg)

///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Structures  ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/* ADC structures */
typedef enum {
    ADC_PRESCALER_DIV2   = ML_ADC_PRESCALER_DIV2,
    ADC_PRESCALER_DIV4   = ML_ADC_PRESCALER_DIV4,
    ADC_PRESCALER_DIV8   = ML_ADC_PRESCALER_DIV8,
    ADC_PRESCALER_DIV16  = ML_ADC_PRESCALER_DIV16,
    ADC_PRESCALER_DIV32  = ML_ADC_PRESCALER_DIV32,
    ADC_PRESCALER_DIV64  = ML_ADC_PRESCALER_DIV64,
    ADC_PRESCALER_DIV128 = ML_ADC_PRESCALER_DIV128,
    ADC_PRESCALER_DIV256 = ML_ADC_PRESCALER_DIV256
} ml_adc_prescaler_t;

typedef enum {
    ADC_CONV_RESOLUTION12     = ML_ADC_CONVERSION_RES12,
    ADC_CONV_RESOLUTION16     = ML_ADC_CONVERSION_RES16,
    ADC_CONV_RESOLUTION10     = ML_ADC_CONVERSION_RES10,
    ADC_CONV_RESOLUTION8      = ML_ADC_CONVERSION_RES8
} ml_adc_conv_resolution_t;


typedef enum {
    ADC_VREF_VINTREF           = ML_ADC_REFCTRL_INTREF,
    ADC_VREF_HALF_VDDANA       = ML_ADC_REFCTRL_INTVCC0,
    ADC_VREF_VDDANA            = ML_ADC_REFCTRL_INTVCC1,
    ADC_VREF_VREFA             = ML_ADC_REFCTRL_AREFA,
    ADC_VREF_VREFB             = ML_ADC_REFCTRL_AREFB,
    ADC_VREF_VREFC             = ML_ADC_REFCTRL_AREFC
} ml_adc_refsel_t;


typedef enum {
    ADC_MUXNEG_AIN0 = ML_ADC_AIN0,
    ADC_MUXNEG_AIN1 = ML_ADC_AIN1,
    ADC_MUXNEG_AIN2 = ML_ADC_AIN2,
    ADC_MUXNEG_AIN3 = ML_ADC_AIN3,
    ADC_MUXNEG_AIN4 = ML_ADC_AIN4,
    ADC_MUXNEG_AIN5 = ML_ADC_AIN5,
    ADC_MUXNEG_AIN6 = ML_ADC_AIN6,
    ADC_MUXNEG_AIN7 = ML_ADC_AIN7,
    ADC_MUXNEG_AGND = ML_ADC_AINGND,
} ml_adc_muxneg_t;

typedef enum {
    ADC_MUXPOS_AIN0 = ML_ADC_AIN0,
    ADC_MUXPOS_AIN1 = ML_ADC_AIN1,
    ADC_MUXPOS_AIN2 = ML_ADC_AIN2,
    ADC_MUXPOS_AIN3 = ML_ADC_AIN3,
    ADC_MUXPOS_AIN4 = ML_ADC_AIN4,
    ADC_MUXPOS_AIN5 = ML_ADC_AIN5,
    ADC_MUXPOS_AIN6 = ML_ADC_AIN6,
    ADC_MUXPOS_AIN7 = ML_ADC_AIN7,
    ADC_MUXPOS_AIN8 = ML_ADC_AIN8,
    ADC_MUXPOS_AIN9 = ML_ADC_AIN9,
    ADC_MUXPOS_AIN10 = ML_ADC_AIN10,
    ADC_MUXPOS_AIN11 = ML_ADC_AIN11,
    ADC_MUXPOS_AIN12 = ML_ADC_AIN12,
    ADC_MUXPOS_AIN13 = ML_ADC_AIN13,
    ADC_MUXPOS_AIN14 = ML_ADC_AIN14,
    ADC_MUXPOS_AIN15 = ML_ADC_AIN15,
    ADC_MUXPOS_AIN16 = ML_ADC_AIN16,
    ADC_MUXPOS_AIN17 = ML_ADC_AIN17,
    ADC_MUXPOS_AIN18 = ML_ADC_AIN18,
    ADC_MUXPOS_AIN19 = ML_ADC_AIN19,
    ADC_MUXPOS_AIN20 = ML_ADC_AIN20,
    ADC_MUXPOS_AIN21 = ML_ADC_AIN21,
    ADC_MUXPOS_AIN22 = ML_ADC_AIN22,
    ADC_MUXPOS_AIN23 = ML_ADC_AIN23,
    ADC_MUXPOS_AINSCALEDVCC     = ML_ADC_AINSCALEDCOREVCC, /* 1/4 Scaled Core Supply */
    ADC_MUXPOS_AINSCALEDVBAT    = ML_ADC_AINSCALEDVBAT, /* 1/4 Scaled VBAT Supply */
    ADC_MUXPOS_AINIOVCC         = ML_ADC_AINSCALEDIOVCC, /* 1/4 Scaled I/O Supply */
    ADC_MUXPOS_AINBANDGAP       = ML_ADC_AINBANDGAP,
    ADC_MUXPOS_AINPTAT          = ML_ADC_AINPTAT, /* Temperature Sensor */
    ADC_MUXPOS_AINCTAT          = ML_ADC_AINCTAT, /* Temperature Sensor */
    ADC_MUXPOS_AINDAC           = ML_ADC_AINDAC /* DAC Output */
} ml_adc_muxpos_t;



typedef enum {
    ADC_DIFFMODE_SINGLE = ML_ADC_DIFFMODE_SINGLE,
    ADC_DIFFMODE_BOTH = ML_ADC_DIFFMODE_BOTH
} ml_adc_inputmode_t;

typedef enum {
    ADC_SAMPLE1     = ML_ADC_SAMPLE1,
    ADC_SAMPLE2     = ML_ADC_SAMPLE2,
    ADC_SAMPLE4     = ML_ADC_SAMPLE4,
    ADC_SAMPLE8     = ML_ADC_SAMPLE8,
    ADC_SAMPLE16    = ML_ADC_SAMPLE16,
    ADC_SAMPLE32    = ML_ADC_SAMPLE32,
    ADC_SAMPLE64    = ML_ADC_SAMPLE64,
    ADC_SAMPLE128   = ML_ADC_SAMPLE128,
    ADC_SAMPLE256   = ML_ADC_SAMPLE256,
    ADC_SAMPLE512   = ML_ADC_SAMPLE512,
    ADC_SAMPLE1024  = ML_ADC_SAMPLE1024
} ml_adc_samplenum_t;

typedef enum {
    ADC_WINMODE_DISABLE = ML_ADC_WINMODE0,
    ADC_WINMODE_GT      = ML_ADC_WINMODE1,  //RESULT > WINLT
    ADC_WINMODE_LT      = ML_ADC_WINMODE2,  //RESULT < WINUT
    ADC_WINMODE_BOUND   = ML_ADC_WINMODE3,  //WINLT < RESULT < WINUT
    ADC_WINMODE_NBOUND  = ML_ADC_WINMODE4   //!(WINLT < RESULT < WINUT)
} ml_adc_winmode_t;


///////////////////////////////////////////////////////////////////////////////////
/////////////////////////  Function Configurations ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

/* CTRLA Configurations */
void ADC_enable(Adc* const);
void ADC_disable(Adc* const);
void ADC_swrst(Adc* const);

/* CTRLB Configurations */
void ADC_winss_enable(Adc* const);
void ADC_winss_disable(Adc* const);
void ADC_set_winmode(Adc* const, const ml_adc_winmode_t);
void ADC_set_russel(Adc* const, const ml_adc_conv_resolution_t);
void ADC_corren_enable(Adc* const);
void ADC_corren_disable(Adc* const);
void ADC_freerun_enable(Adc* const);
void ADC_freerun_disable(Adc* const);
void ADC_result_leftadj(Adc* const);
void ADC_result_rightadj(Adc* const);

/* INPUTCTRL Configurations */
void ADC_dseqstop_enable(Adc* const);
void ADC_dseqstop_disable(Adc* const);
void ADC_set_muxneg(Adc* const, const ml_adc_muxneg_t);
void ADC_set_muxpos(Adc* const, const ml_adc_muxpos_t);
void ADC_set_diffmode(Adc* const, const ml_adc_inputmode_t);

/* REFCTRL Configurations */
void ADC_refcomp_enable(Adc* const);
void ADC_refcomp_disable(Adc* const);
void ADC_reference_select(Adc* const, const ml_adc_refsel_t);

/* AVGCTRL Configurations */
void ADC_set_divisioncoef(Adc* const, const uint8_t);
void ADC_set_avgsample(Adc* const, const ml_adc_samplenum_t);

/* WINLT Configurations */
void ADC_set_winlt(Adc* const, const uint16_t);

/* WINUT Configurations */
void ADC_set_winut(Adc* const, const uint16_t);

/* GAINCORR Configurations */
void ADC_set_gaincorr(Adc* const, const uint16_t);

/* OFFSETCORR Configurations */
void ADC_set_offsetcorr(Adc* const, const uint16_t);

/* SAMPCTRL Configurations*/
void ADC_offcomp_enable(Adc* const);
void ADC_offcomp_disable(Adc* const);
void ADC_set_samplingLength(Adc* const, const uint8_t);

/* SWTRIG Configurations */
void ADC_flush_conversion(Adc* const);
void ADC_start_conversion(Adc* const);


uint16_t ADC_read_result(Adc* const);
uint16_t ADC_read_ress(Adc* const);


void ADC_initDMA(Adc* const, ml_dmac_chnum_t, uint32_t*, uint16_t, ml_dmac_chprilvl_t, uint32_t, uint32_t, uint32_t, DmacDescriptor*);

uint8_t ADC_init(Adc* const);
//////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#endif // ML_ADC_H