#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definições dos pinos dos LEDs
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11

// Declaração das funções
void inicializar_leds();
void controlar_leds(uint16_t adc_x, uint16_t adc_y);

#endif
