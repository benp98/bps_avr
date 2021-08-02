/**
 * sr7seg.c - Seven Segment Display Driver for 74HC595
 *
 * (c) 2021 Ben-Ove Pasinski - See the LICENSE file for more information
 */

#include <stdbool.h>

#include "sr7seg.h"

typedef struct {
    uint8_t a : 1;
    uint8_t b : 1;
    uint8_t c : 1;
    uint8_t d : 1;
    uint8_t e : 1;
    uint8_t f : 1;
    uint8_t g : 1;
    uint8_t dp : 1;
} sr7seg_state;

/**
 * sr7seg_setn writes the data for the lower nibble of the given byte to the
 * shift register
 */
void sr7seg_setn(sr74hc595 sr, uint8_t data) {
    uint8_t ndata = data & 0x0F;

    sr7seg_state state;

    switch (ndata) {
    case 0x0:
        state.a  = 1;
        state.b  = 1;
        state.c  = 1;
        state.d  = 1;
        state.e  = 1;
        state.f  = 1;
        state.g  = 0;
        state.dp = 0;
        break;
    case 0x1:
        state.a  = 0;
        state.b  = 1;
        state.c  = 1;
        state.d  = 0;
        state.e  = 0;
        state.f  = 0;
        state.g  = 0;
        state.dp = 0;
        break;
    case 0x2:
        state.a  = 1;
        state.b  = 1;
        state.c  = 0;
        state.d  = 1;
        state.e  = 1;
        state.f  = 0;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0x3:
        state.a  = 1;
        state.b  = 1;
        state.c  = 1;
        state.d  = 1;
        state.e  = 0;
        state.f  = 0;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0x4:
        state.a  = 0;
        state.b  = 1;
        state.c  = 1;
        state.d  = 0;
        state.e  = 0;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0x5:
        state.a  = 1;
        state.b  = 0;
        state.c  = 1;
        state.d  = 1;
        state.e  = 0;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0x6:
        state.a  = 1;
        state.b  = 0;
        state.c  = 1;
        state.d  = 1;
        state.e  = 1;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0x7:
        state.a  = 1;
        state.b  = 1;
        state.c  = 1;
        state.d  = 0;
        state.e  = 0;
        state.f  = 0;
        state.g  = 0;
        state.dp = 0;
        break;
    case 0x8:
        state.a  = 1;
        state.b  = 1;
        state.c  = 1;
        state.d  = 1;
        state.e  = 1;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0x9:
        state.a  = 1;
        state.b  = 1;
        state.c  = 1;
        state.d  = 1;
        state.e  = 0;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0xA:
        state.a  = 1;
        state.b  = 1;
        state.c  = 1;
        state.d  = 0;
        state.e  = 1;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0xB:
        state.a  = 0;
        state.b  = 0;
        state.c  = 1;
        state.d  = 1;
        state.e  = 1;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0xC:
        state.a  = 1;
        state.b  = 0;
        state.c  = 0;
        state.d  = 1;
        state.e  = 1;
        state.f  = 1;
        state.g  = 0;
        state.dp = 0;
        break;
    case 0xD:
        state.a  = 0;
        state.b  = 1;
        state.c  = 1;
        state.d  = 1;
        state.e  = 1;
        state.f  = 0;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0xE:
        state.a  = 1;
        state.b  = 0;
        state.c  = 0;
        state.d  = 1;
        state.e  = 1;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    case 0xF:
        state.a  = 1;
        state.b  = 0;
        state.c  = 0;
        state.d  = 0;
        state.e  = 1;
        state.f  = 1;
        state.g  = 1;
        state.dp = 0;
        break;
    }

    // Shift Register Data Order: A, B, C, DP, D, E, F, G
    sr74hc595_write(sr, state.a);
    sr74hc595_write(sr, state.b);
    sr74hc595_write(sr, state.c);
    sr74hc595_write(sr, state.dp);
    sr74hc595_write(sr, state.d);
    sr74hc595_write(sr, state.e);
    sr74hc595_write(sr, state.f);
    sr74hc595_write(sr, state.g);
}

/**
 * sr7seg_setn splits the data into two nibbles and writes the data into the
 * shift registers
 */
void sr7seg_set(sr74hc595 sr, uint8_t data) {
    sr7seg_setn(sr, data << 4);
    sr7seg_setn(sr, data);
}
