#ifndef LED_RGB_H
#define LED_RGB_H

#include "pico/stdlib.h"

// Definição dos pinos do LED RGB
#define LED_G 11  // Verde
#define LED_B 12  // Azul
#define LED_R 13  // Vermelho

// Declaração das funções
void configurar_led_rgb(void);
void set_led_rgb(bool red, bool green, bool blue);
bool piscar_led_rgb_vermelho(struct repeating_timer *t);

#endif // LED_RGB_H
