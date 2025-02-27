#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

// Constantes
#define NUM_PIXELS 25
#define PINO_LEDS 7
#define FPS 10

// Funções gerais para LEDs
uint32_t retorno_rgb(double b, double r, double g);

#endif // LED_H
