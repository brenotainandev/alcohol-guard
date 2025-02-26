#include "../includes/display.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO_DISPLAY 0x3C

// Definição da variável global "display"
ssd1306_t display;

void inicializar_display() {
    i2c_init(I2C_PORT, 1000 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    ssd1306_init(&display, 128, 64, false, ENDERECO_DISPLAY, I2C_PORT);
    ssd1306_config(&display);
    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);
}

void atualizar_display(uint16_t adc_x, uint16_t adc_y, bool estado_borda) {
    // Mapeamento dos valores ADC para a posição do quadrado de 8x8 pixels.
    uint8_t pos_x = (uint8_t)(adc_x * 0.0294);
    uint8_t pos_y = (uint8_t)((64 - 8) - (adc_y * 0.0137));
    
    // Limpa o display
    ssd1306_fill(&display, false);
    
    // Desenha a borda com estilo conforme o estado_borda
    if (estado_borda) {
        ssd1306_rect(&display, 1, 1, 126, 62, 1, 1); // Borda externa
        ssd1306_rect(&display, 4, 4, 120, 56, 0, 1); // Borda interna "vazia"
    } else {
        ssd1306_rect(&display, 3, 3, 122, 58, 1, 0);
    }
    
    // Desenha o quadrado (8x8 pixels) na posição mapeada
    ssd1306_rect(&display, pos_y, pos_x, 8, 8, 1, 1);
    
    // Envia os dados para atualizar o display
    ssd1306_send_data(&display);
}
