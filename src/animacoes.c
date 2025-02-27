#include "../includes/animacoes.h"
#include "../includes/matriz-led.h"

const int MATRIZ_ANIMACAO[2][25] = {
    {1, 0, 0, 0, 1,
     0, 1, 0, 1, 0,
     0, 0, 1, 0, 0,
     0, 1, 0, 1, 0,
     1, 0, 0, 0, 1},  // Letra X
    {0, 1, 1, 1, 0,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     0, 1, 1, 1, 0}, // Letra O
};

// Função para exibir a letra X em verde
void exibir_letra_x(PIO pio, uint sm) {
    uint32_t buffer[NUM_PIXELS];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = i * 5 + j;
            buffer[index] = MATRIZ_ANIMACAO[0][index]
                ? retorno_rgb(0.0, 0.2, 0.0)  // LED vermelho (brilho 20%)
                : retorno_rgb(0.0, 0.0, 0.0); // LED apagado
        }
    }

    // Envia o frame para os LEDs
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}

// Função para exibir a letra O em vermelho
void exibir_letra_o(PIO pio, uint sm) {
    uint32_t buffer[NUM_PIXELS];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = i * 5 + j;
            buffer[index] = MATRIZ_ANIMACAO[1][index]
                ? retorno_rgb(0.2, 0.0, 0.0)  // LED verde (brilho 20%)
                : retorno_rgb(0.0, 0.0, 0.0); // LED apagado
        }
    }

    // Envia o frame para os LEDs
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}