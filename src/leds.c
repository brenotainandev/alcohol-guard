#include "../includes/leds.h"
#include <stdlib.h>
#include <stdio.h>

// Inicializa os pinos dos LEDs
void inicializar_leds() {
    gpio_set_function(LED_VERMELHO, GPIO_FUNC_PWM);
    gpio_set_function(LED_AZUL, GPIO_FUNC_PWM);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
}

// Controla a intensidade dos LEDs com base no ADC
void controlar_leds(uint16_t adc_x, uint16_t adc_y) {
    uint8_t tolerancia = 100;
    
    uint16_t nivel_vermelho = (abs(adc_y - 2000) > tolerancia) ? abs(adc_y - 2000) : 0;
    uint16_t nivel_azul = (abs(adc_x - 2000) > tolerancia) ? abs(adc_x - 2000) : 0;
    
    pwm_set_gpio_level(LED_VERMELHO, nivel_vermelho);
    pwm_set_gpio_level(LED_AZUL, nivel_azul);
}
