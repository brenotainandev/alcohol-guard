#ifndef BOTAO_H
#define BOTAO_H

#include "pico/stdlib.h"

// Definição dos pinos dos botões
#define BOTAO_A 5
#define BOTAO_B 6

// Declaração das funções
void configurar_botoes(void);
void tratar_interrupcao_botao(uint gpio, uint32_t eventos);

#endif // BOTAO_H
