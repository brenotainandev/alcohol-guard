#include "../includes/entradas.h"
#include "../includes/pwm.h"

#define BOTAO_JOYSTICK 22
#define LED_VERDE 11

// Variáveis globais para controle de estados
bool estado_borda = false; // Controla o estilo da borda do display
bool estado_pwm   = true;  // Controla se o PWM (LEDs RGB) está ativo

// Callback global para as interrupções dos botões
void callback_botao(uint gpio, uint32_t eventos) {
    static absolute_time_t ultimo_tempo_A = 0;
    static absolute_time_t ultimo_tempo_J = 0;
    absolute_time_t agora = get_absolute_time();

    // Botão A: ativa/desativa os LEDs PWM
    if (gpio == BOTAO_A && absolute_time_diff_us(ultimo_tempo_A, agora) > 200000) {
        estado_pwm = !estado_pwm;
        alterar_estado_pwm(estado_pwm); // Atualiza o estado no módulo PWM
        ultimo_tempo_A = agora;
    }
    // Botão do Joystick: alterna o LED verde e o estilo da borda do display
    else if (gpio == BOTAO_JOYSTICK && absolute_time_diff_us(ultimo_tempo_J, agora) > 200000) {
        gpio_put(LED_VERDE, !gpio_get(LED_VERDE));
        estado_borda = !estado_borda;
        ultimo_tempo_J = agora;
    }
}

void inicializar_pinos() {
    // Inicializa o botão A
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    
    // Inicializa o botão do joystick
    gpio_init(BOTAO_JOYSTICK);
    gpio_set_dir(BOTAO_JOYSTICK, GPIO_IN);
    gpio_pull_up(BOTAO_JOYSTICK);
    
    // Registra o callback global para BOTAO_A
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, callback_botao);
    
    // Para o botão do joystick, apenas habilita a interrupção (o callback já foi registrado)
    gpio_set_irq_enabled(BOTAO_JOYSTICK, GPIO_IRQ_EDGE_FALL, true);
}
