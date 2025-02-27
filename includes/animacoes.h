#ifndef ANIMACOES_H
#define ANIMACOES_H

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// Declaração das funções de animações
void exibir_letra_x(PIO pio, uint sm);
void exibir_letra_o(PIO pio, uint sm);

#endif // ANIMACOES_H
