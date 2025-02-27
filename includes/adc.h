#ifndef ADC_H
#define ADC_H

#include "pico/stdlib.h"
#include "hardware/adc.h"

void inicializar_adc();
uint16_t ler_adc(uint8_t canal);

#endif
