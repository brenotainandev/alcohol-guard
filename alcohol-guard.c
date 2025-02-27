#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "./includes/adc.h"
#include "./includes/display.h"
#include "./includes/pwm.h"
#include "./includes/entradas.h"
#include "./includes/animacoes.h"
#include "./includes/matriz-led.h"
#include "./includes/buzzer.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "alcohol_guard.pio.h"

// Define o threshold para detecção de álcool.
// Valores acima desse limite no eixo Y indicam que há álcool.
#define THRESHOLD_ALCOOL 2100

// Função para exibir a mensagem inicial melhorada (para display pequeno)
void mostrar_mensagem_inicial() {
    ssd1306_fill(&display, false);
    ssd1306_draw_string(&display, "Alcohol Guard", 0, 0);
    ssd1306_draw_string(&display, "Leitura: 10s", 0, 10);
    ssd1306_draw_string(&display, "Aguarde...", 0, 20);
    ssd1306_send_data(&display);
    sleep_ms(3000);  // Tempo para visualização inicial
}

// Função para exibir a tela inicial com o cronômetro.
// O texto "Nova leitura:" é exibido na linha 20 e o cronômetro, na linha 32.
void mostrar_tela_inicial_com_contador(int segundos_iniciais) {
    for (int i = segundos_iniciais; i > 0; i--) {
        ssd1306_fill(&display, false);
        ssd1306_draw_string(&display, "Alcohol Guard", 0, 0);
        ssd1306_draw_string(&display, "Leitura: 10s", 0, 10);
        ssd1306_draw_string(&display, "Nova leitura:", 0, 20);
        char countdown[20];
        sprintf(countdown, "%ds", i);
        ssd1306_draw_string(&display, countdown, 40, 32);
        ssd1306_send_data(&display);
        sleep_ms(1000);
    }
}

int main() {
    stdio_init_all();
    
    // Inicializa os módulos
    inicializar_pinos();     // Inicializa as entradas (ex.: botão A)
    init_buzzer();           // Inicializa o buzzer (configura o pino para PWM)
    inicializar_adc();       // Configura os pinos ADC (GP27 para eixo X e GP26 para eixo Y)
    inicializar_pwm();       // Inicializa o PWM para controle dos LEDs
    inicializar_display();   // Inicializa o display OLED
    
    // Inicializa a Matriz de LEDs WS2812
    PIO pio = pio0;
    set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(pio, &alcohol_guard_program);
    uint sm = pio_claim_unused_sm(pio, true);
    alcohol_guard_program_init(pio, sm, offset, PINO_LEDS);
    sleep_ms(100);

    // Exibe a mensagem inicial com regras
    mostrar_mensagem_inicial();
    
    // Loop principal: a cada 30 segundos inicia uma nova leitura
    while (true) {
        uint32_t ciclo_inicio = to_ms_since_boot(get_absolute_time());
        
        // Ativa o buzzer para indicar o início da leitura (toca 1 kHz)
        play_tone(1000);
        
        ssd1306_fill(&display, false);
        ssd1306_draw_string(&display, "Lendo...", 10, 10);
        ssd1306_send_data(&display);
        
        // Variável para a leitura do ADC (eixo Y, sensor de álcool)
        uint16_t valor_adc_y;
        uint32_t tempo_inicial = to_ms_since_boot(get_absolute_time());
        uint32_t tempo_atual = tempo_inicial;
        int contagem_alcool = 0;  // Conta quantas vezes o valor ultrapassa o threshold
        
        // Loop de leitura por 10 segundos
        while (tempo_atual - tempo_inicial < 10000) {
            valor_adc_y = ler_adc(0);  // Lê o ADC do eixo Y (GP26)
            
            // Exibe o valor lido no display
            char buffer[50];
            sprintf(buffer, "Y: %d", valor_adc_y);
            ssd1306_fill(&display, false);
            ssd1306_draw_string(&display, buffer, 0, 10);
            ssd1306_send_data(&display);
            
            if (valor_adc_y > THRESHOLD_ALCOOL) {
                contagem_alcool++;
            }
            
            sleep_ms(500);
            tempo_atual = to_ms_since_boot(get_absolute_time());
        }
        
        // Desliga o buzzer após a leitura
        stop_buzzer();
        
        // Exibe o resultado da leitura e animação na matriz de LEDs
        ssd1306_fill(&display, false);
        if (contagem_alcool > 0) {
            ssd1306_draw_string(&display, "Alcool detectado!", 0, 10);
            alterar_estado_pwm(false);  // Exemplo: desabilita PWM (bloqueia o carro)
            exibir_letra_x(pio, sm);      // Exibe a letra X (em vermelho) na matriz LED
        } else {
            ssd1306_draw_string(&display, "Sem alcool.", 0, 10);
            alterar_estado_pwm(true);   // Mantém o PWM ativo
            exibir_letra_o(pio, sm);      // Exibe a letra O (em verde) na matriz LED
        }
        ssd1306_send_data(&display);
        sleep_ms(3000);  // Resultado visível por 3 segundos
        
        // Calcula o tempo gasto no ciclo
        uint32_t ciclo_fim = to_ms_since_boot(get_absolute_time());
        uint32_t tempo_ciclo = ciclo_fim - ciclo_inicio;
        
        // Se o ciclo não completar 30 segundos, exibe o cronômetro na tela inicial
        if (tempo_ciclo < 30000) {
            uint32_t tempo_restante = 30000 - tempo_ciclo;
            int segundos_restantes = tempo_restante / 1000;
            mostrar_tela_inicial_com_contador(segundos_restantes);
        }
    }
    
    return 0;
}
