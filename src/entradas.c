#include "../includes/entradas.h"

// Variáveis globais para controle de estados
bool estado_borda = false; // Controla o estilo da borda do display
bool estado_pwm   = true;  // Controla se o PWM (LEDs RGB) está ativo

// Callback global para as interrupções dos botões
void callback_botao(uint gpio, uint32_t eventos) {
    static absolute_time_t ultimo_tempo_A = 0;
    static absolute_time_t ultimo_tempo_J = 0;
    absolute_time_t agora = get_absolute_time();
}

void inicializar_pinos() {
    // Inicializa o botão A
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);

    // Registra o callback global para BOTAO_A
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, callback_botao);
}
