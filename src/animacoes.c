#include "../includes/animacoes.h"
#include "../includes/matriz-led.h"

// Definição dos números na matriz 5x5
const int MATRIZ_NUMEROS[10][25] = {
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Número 0

    {0, 0, 1, 0, 0,
     0, 1, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     1, 1, 1, 1, 1},  // Número 1

    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1},  // Número 2

    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Número 3

    {1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 0, 0, 0, 0},  // Número 4

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Número 5

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Número 6

    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     0, 1, 0, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 0, 1, 0},  // Número 7

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Número 8

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1}   // Número 9
};



// Função genérica para exibir um número na matriz de LEDs
void exibir_numero_na_matriz(PIO pio, uint sm, int numero) {
    if (numero < 0 || numero > 9) return;  // Garante que o número está entre 0 e 9

    uint32_t buffer[NUM_PIXELS];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = (4 - i) * 5 + j;  // Mantém a inversão de linha para alinhamento correto
            buffer[i * 5 + j] = MATRIZ_NUMEROS[numero][index]
                ? retorno_rgb(0.0, 0.2, 0.0)  // LED vermelho 20%
                : retorno_rgb(0.0, 0.0, 0.0); // LED apagado
        }
    }

    // Envia o frame para os LEDs
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}


// Funções de animação para cada número, chamando a função genérica
void animacao_numero_zero(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 0); }
void animacao_numero_um(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 1); }
void animacao_numero_dois(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 2); }
void animacao_numero_tres(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 3); }
void animacao_numero_quatro(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 4); }
void animacao_numero_cinco(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 5); }
void animacao_numero_seis(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 6); }
void animacao_numero_sete(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 7); }
void animacao_numero_oito(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 8); }
void animacao_numero_nove(PIO pio, uint sm) { exibir_numero_na_matriz(pio, sm, 9); }
