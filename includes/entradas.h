#ifndef ENTRADAS_H
#define ENTRADAS_H

#include "pico/stdlib.h"

// Variáveis globais para estados que podem ser acessadas por outros módulos
extern bool estado_borda;
extern bool estado_pwm;

void inicializar_pinos();

#endif
