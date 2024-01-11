/*
 * Author: Ben Westcott, Jayson De La Vega
 * Date created: 8/11/23
 */

#ifndef ML_SERCOM_H
#define ML_SERCOM_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define ML_SERCOM_PAD0    0x00
#define ML_SERCOM_PAD1    0x01
#define ML_SERCOM_PAD2    0x02
#define ML_SERCOM_PAD3    0x03


typedef enum
{
    SERCOM_PAD0 = ML_SERCOM_PAD0,
    SERCOM_PAD1 = ML_SERCOM_PAD1,
    SERCOM_PAD2 = ML_SERCOM_PAD2,
    SERCOM_PAD3 = ML_SERCOM_PAD3
} ml_sercom_pads_t;

typedef uint8_t baudrate_short_t;
typedef uint32_t packed_msg_t;

#ifdef __cplusplus
}
#endif

#endif // ML_SERCOM_H