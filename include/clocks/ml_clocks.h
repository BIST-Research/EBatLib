/**
 * @file
 *
 * @author Ben Westcott
 * @date 1/27/23
 * 
 * @brief This file contains macros and function declarations for GCLK, MCLK, and clock sources
 * 
 * This file defines the function declarations for 3 different systems on the microcontroller:
 * 
 * Generic Clock Controller (GCLK)
 * 
 * Main Clock Controller (MCLK)
 * 
 * Clock Sources (OSCCTRL or OSC32KCTRL)
 */

#ifndef ML_CLOCKS_H
#define ML_CLOCKS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *       MCLK definitions
 */
#define ML_MCLK_UNDIV 120000000
#define ML_MCLK_CPUDIV1 (MCLK_CPUDIV_DIV(MCLK_CPUDIV_DIV_DIV1_Val))

/**
 * @brief Initialize MCLK
 */
void MCLK_init(void);

/*
 *       GCLK definitions
 */

/**
 * @brief 
 */
#define ML_GCLK_CH 7

// 120 MHz
// Channel enable, GCLK7, WRTLCK - disable future writing to reg
/**
 * @brief Something
 */
#define ML_GCLK0_PCHCTRL (GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK0)

// 48 MHz
#define ML_GCLK1_PCHCTRL (GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK1)

// 100 MHz
#define ML_GCLK2_PCHCTRL (GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK2)

// 12 MHz
#define ML_GCLK4_PCHCTRL (GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK4)

#define ML_GCLK7_PCHCTRL (GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK7)

#define ML_SET_GCLK2_PCHCTRL(id) (GCLK->PCHCTRL[id].reg = ML_GCLK2_PCHCTRL)
#define ML_SET_GCLK7_PCHCTRL(id) (GCLK->PCHCTRL[id].reg = ML_GCLK7_PCHCTRL)
#define ML_SET_GCLK1_PCHCTRL(id) (GCLK->PCHCTRL[id].reg = ML_GCLK1_PCHCTRL)
#define ML_SET_GCLK0_PCHCTRL(id) (GCLK->PCHCTRL[id].reg = ML_GCLK0_PCHCTRL)
#define ML_SET_GCLK4_PCHCTRL(id) (GCLK->PCHCTRL[id].reg = ML_GCLK4_PCHCTRL)

/**
 * @brief Initialize GCLK
 */
void GCLK_init(void);

/**
 * @brief Initialize OSCULP32K
 */
void OSCULP32K_init(void);

#ifdef __cplusplus
}
#endif

#endif
