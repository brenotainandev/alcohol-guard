#ifndef PWM_H
#define PWM_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

void inicializar_pwm();
void alterar_estado_pwm(bool estado);

#endif
