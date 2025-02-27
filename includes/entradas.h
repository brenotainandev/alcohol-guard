#ifndef ENTRADAS_H
#define ENTRADAS_H

#include "pico/stdlib.h"

#define BOTAO_A 5

// Variáveis globais para estados que podem ser acessadas por outros módulos
extern bool estado_borda;
extern bool estado_pwm;

void inicializar_pinos();

#endif
