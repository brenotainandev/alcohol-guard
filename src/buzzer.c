#include "../includes/buzzer.h"
#include "hardware/clocks.h"

static uint slice_num;

void init_buzzer() {
    // Configura o pino do buzzer para função PWM
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_enabled(slice_num, false);
}

void play_tone(uint32_t frequency) {
    uint32_t clock = clock_get_hz(clk_sys);
    uint32_t wrap = 4095;
    float divisor = (float) clock / (frequency * (wrap + 1));
    pwm_set_clkdiv(slice_num, divisor);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_enabled(slice_num, true);
    pwm_set_gpio_level(BUZZER_PIN, wrap / 100);
}



void stop_buzzer() {
    // Desabilita o slice PWM para parar o som
    pwm_set_enabled(slice_num, false);
}
