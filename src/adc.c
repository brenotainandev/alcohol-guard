#include "../includes/adc.h"

void inicializar_adc() {
    adc_init();
    adc_gpio_init(27); // Eixo X
    adc_gpio_init(26); // Eixo Y
}

uint16_t ler_adc(uint8_t canal) {
    adc_select_input(canal);
    return adc_read();
}
