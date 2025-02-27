#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 21  // Altere conforme o pino que você está usando

// Inicializa o buzzer (configura o pino para PWM)
void init_buzzer();

// Toca uma frequência (em Hz) com 50% de duty cycle
void play_tone(uint32_t frequency);

// Desliga o buzzer
void stop_buzzer();

#endif // BUZZER_H
