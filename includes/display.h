#ifndef DISPLAY_H
#define DISPLAY_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "includes/ssd1306.h"

void inicializar_display();
void atualizar_display(uint16_t adc_x, uint16_t adc_y, bool estado_borda);

#endif
