#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "./includes/adc.h"
#include "./includes/display.h"
#include "./includes/entradas.h"
#include "./includes/animacoes.h"
#include "./includes/matriz-led.h"
#include "./includes/buzzer.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "alcohol_guard.pio.h"

// Define o threshold para detecção de álcool
#define THRESHOLD_ALCOOL 2100
#define CENTER 2000

void mostrar_mensagem_inicial() {
    ssd1306_fill(&display, false);
    ssd1306_draw_string(&display, "Alcohol Guard", 0, 0);
    ssd1306_draw_string(&display, "Leitura: 10s", 0, 10);
    ssd1306_draw_string(&display, "Aguarde...", 0, 20);
    ssd1306_send_data(&display);
    sleep_ms(3000);
}

void mostrar_tela_inicial_com_contador(int segundos) {
    for (int i = segundos; i > 0; i--) {
        if (gpio_get(BOTAO_A) == 0) break;

        ssd1306_fill(&display, false);
        ssd1306_draw_string(&display, "Alcohol Guard", 0, 0);
        ssd1306_draw_string(&display, "Leitura: 10s", 0, 10);
        ssd1306_draw_string(&display, "Nova leitura:", 0, 20);

        char countdown[10];
        sprintf(countdown, "%ds", i);
        ssd1306_draw_string(&display, countdown, 40, 32);
        ssd1306_send_data(&display);
        sleep_ms(1000);
    }
}

int main() {
    stdio_init_all();

    // Inicializa módulos
    inicializar_pinos();
    init_buzzer();
    inicializar_adc();
    inicializar_display();

    // Inicializa Matriz de LEDs WS2812 via PIO
    PIO pio = pio0;
    set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(pio, &alcohol_guard_program);
    uint sm = pio_claim_unused_sm(pio, true);
    
    if (sm == -1) {
        printf("Erro: Nenhuma state machine disponível para WS2812\n");
        return 1;
    }
    
    alcohol_guard_program_init(pio, sm, offset, PINO_LEDS);
    sleep_ms(100);

    // Mensagem inicial
    mostrar_mensagem_inicial();

    while (true) {
        uint32_t tempo_inicio = to_ms_since_boot(get_absolute_time());

        // Aguarda que o usuário comece a soprar (tempo máximo 5 segundos)
        ssd1306_fill(&display, false);
        ssd1306_draw_string(&display, "Aguardando", 0, 0);
        ssd1306_draw_string(&display, "sopro...", 0, 10);
        ssd1306_send_data(&display);
        
        uint32_t tempo_espera = to_ms_since_boot(get_absolute_time());
        while (ler_adc(0) < THRESHOLD_ALCOOL) {
            if ((to_ms_since_boot(get_absolute_time()) - tempo_espera) > 5000) {
                break; // Sai do loop após 5 segundos sem sopro
            }
            sleep_ms(100);
        }

        // Se não houve sopro, volta para o início
        if (ler_adc(0) < THRESHOLD_ALCOOL) continue;

        // Inicia medição de 10 segundos
        play_tone(1000);  
        ssd1306_fill(&display, false);
        ssd1306_draw_string(&display, "Lendo...", 10, 10);
        ssd1306_send_data(&display);

        uint16_t raw;
        uint16_t valor_adc_y;
        uint32_t tempo_medicao = to_ms_since_boot(get_absolute_time());
        int contagem_alcool = 0;
        int contagem_sem_alcool = 0;

        while ((to_ms_since_boot(get_absolute_time()) - tempo_medicao) < 10000) {
            raw = ler_adc(0);
            
            // - Se o joystick está para cima (acima de CENTER), conta como álcool.
            // - Se o joystick está para baixo (abaixo de CENTER), conta como ausência de álcool.
            valor_adc_y = raw;
            
            char buffer[20];
            sprintf(buffer, "Y: %d", valor_adc_y);
            ssd1306_fill(&display, false);
            ssd1306_draw_string(&display, buffer, 0, 10);
            ssd1306_send_data(&display);

            if (valor_adc_y > CENTER) {  
                contagem_alcool++;  // Se o valor for maior que o centro, considera álcool presente
            } else {
                contagem_sem_alcool++;  // Se for menor, conta como ausência
            }

            uint32_t elapsed = to_ms_since_boot(get_absolute_time()) - tempo_medicao;
            uint32_t remaining = (elapsed < 10000) ? (10000 - elapsed) : 0;
            sleep_ms(remaining < 500 ? remaining : 500);
        }

        stop_buzzer();

        // Exibe resultado
        ssd1306_fill(&display, false);
        if (contagem_alcool > contagem_sem_alcool) {  
            // Se houver mais leituras indicando álcool do que sem álcool
            ssd1306_draw_string(&display, "Alcool detectado!", 0, 10);
            exibir_letra_x(pio, sm);
        } else {
            ssd1306_draw_string(&display, "Sem alcool.", 0, 10);
            exibir_letra_o(pio, sm);
        }
        ssd1306_send_data(&display);
        sleep_ms(3000);

        // Aguarda 30s para nova medição (com interrupção via botão)
        mostrar_tela_inicial_com_contador(30);
    }
    
    return 0;
}
