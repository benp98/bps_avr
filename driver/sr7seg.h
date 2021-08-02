/**
 * sr7seg.h - Seven Segment Display Driver for 74HC595
 *
 * (c) 2021 Ben-Ove Pasinski - See the LICENSE file for more information
 */

#ifndef BPS_DRIVER_SR7SEG_H
#define BPS_DRIVER_SR7SEG_H

#include <stdint.h>

#include "sr74hc595.h"

extern void sr7seg_setn(sr74hc595 sr, uint8_t data);
extern void sr7seg_set(sr74hc595 sr, uint8_t data);

#endif
