/**
 * sr74hc595.h - Driver for 74HC595
 *
 * (c) 2021 Ben-Ove Pasinski - See the LICENSE file for more information
 */

#ifndef BPS_DRIVER_SR74HC595
#define BPS_DRIVER_SR74HC595

#include <stdint.h>

#include "../util/bits.h"

typedef enum {
    SR74HC595_PORTB,
    SR74HC595_PORTC,
    SR74HC595_PORTD
} sr74hc595_port;

typedef struct {
    sr74hc595_port port : 2;
    uint8_t        pin_ser;
    uint8_t        pin_srclk;
    uint8_t        pin_rclk;
} sr74hc595;

extern sr74hc595 sr74hc595_init(sr74hc595_port port,
                                uint8_t        pin_ser,
                                uint8_t        pin_srclk,
                                uint8_t        pin_rclk);
extern void      sr74hc595_write(sr74hc595 sr, bool data);
extern void      sr74hc595_apply(sr74hc595 sr);

#endif
