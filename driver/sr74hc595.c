/**
 * sr74hc595.c - Driver for 74HC595
 *
 * (c) 2021 Ben-Ove Pasinski - See the LICENSE file for more information
 */

#include <stdbool.h>

#include <avr/io.h>

#include "sr74hc595.h"

/**
 * sr74hc595_init sets up the ports and pins for the shift register
 */
sr74hc595 sr74hc595_init(sr74hc595_port port,
                         uint8_t        pin_ser,
                         uint8_t        pin_srclk,
                         uint8_t        pin_rclk) {
    sr74hc595 sr;
    sr.port      = port;
    sr.pin_ser   = pin_ser;
    sr.pin_srclk = pin_srclk;
    sr.pin_rclk  = pin_rclk;

    uint8_t sr_pins = pin_ser | pin_srclk | pin_rclk;

    switch (port) {
    case SR74HC595_PORTB:
        DDRB |= sr_pins;
        PORTB &= ~(sr_pins);
        break;
    case SR74HC595_PORTC:
        DDRC |= sr_pins;
        PORTC &= ~(sr_pins);
        break;
    case SR74HC595_PORTD:
        DDRD |= sr_pins;
        PORTD &= ~(sr_pins);
        break;
    }

    return sr;
}

/**
 * Utility Enum for writing to the shift register pins
 */
typedef enum {
    SR74HC595_PIN_SER,
    SR74HC595_PIN_SRCLK,
    SR74HC595_PIN_RCLK
} sr74hc595_pin;

/**
 * sr74hc595_write_data sets the given pin to HIGH or LOW depending on the data
 * parameter
 */
static void sr74hc595_write_data(sr74hc595 sr, sr74hc595_pin pin, bool data) {
    uint8_t pin_mask = 0;

    switch (pin) {
    case SR74HC595_PIN_SER:
        pin_mask = sr.pin_ser;
        break;
    case SR74HC595_PIN_SRCLK:
        pin_mask = sr.pin_srclk;
        break;
    case SR74HC595_PIN_RCLK:
        pin_mask = sr.pin_rclk;
        break;
    }

    switch (sr.port) {
    case SR74HC595_PORTB:
        PORTB &= ~(pin_mask);
        if (data != 0) {
            PORTB |= pin_mask;
        }
        break;
    case SR74HC595_PORTC:
        PORTC &= ~(pin_mask);
        if (data != 0) {
            PORTC |= pin_mask;
        }
        break;
    case SR74HC595_PORTD:
        PORTD &= ~(pin_mask);
        if (data != 0) {
            PORTD |= pin_mask;
        }
        break;
    }
}

/**
 * sr74hc595_write writes a single bit into the shift register
 */
void sr74hc595_write(sr74hc595 sr, bool data) {
    sr74hc595_write_data(sr, SR74HC595_PIN_SER, data);
    sr74hc595_write_data(sr, SR74HC595_PIN_SRCLK, 1);
    sr74hc595_write_data(sr, SR74HC595_PIN_SER, 0);
    sr74hc595_write_data(sr, SR74HC595_PIN_SRCLK, 0);
}

/**
 * sr74hc595_apply triggers the copying of the shift register's data into the
 * output register
 */
void sr74hc595_apply(sr74hc595 sr) {
    sr74hc595_write_data(sr, SR74HC595_PIN_RCLK, 1);
    sr74hc595_write_data(sr, SR74HC595_PIN_RCLK, 0);
}
