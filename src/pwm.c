#include "../includes/pwm.h"
#include "../includes/leds.h"

static uint slice_vermelho;
static uint slice_azul;
static const uint wrap_pwm = 2048;
static const float divisor_clk = 30.0f;

void inicializar_pwm() {
    // Inicializando PWM para LED Vermelho
    gpio_set_function(LED_VERMELHO, GPIO_FUNC_PWM);
    slice_vermelho = pwm_gpio_to_slice_num(LED_VERMELHO);
    pwm_set_clkdiv(slice_vermelho, divisor_clk);
    pwm_set_wrap(slice_vermelho, wrap_pwm);
    pwm_set_enabled(slice_vermelho, true);

    // Inicializando PWM para LED Azul
    gpio_set_function(LED_AZUL, GPIO_FUNC_PWM);
    slice_azul = pwm_gpio_to_slice_num(LED_AZUL);
    pwm_set_clkdiv(slice_azul, divisor_clk);
    pwm_set_wrap(slice_azul, wrap_pwm);
    pwm_set_enabled(slice_azul, true);
}

void alterar_estado_pwm(bool estado) {
    pwm_set_enabled(slice_vermelho, estado);
    pwm_set_enabled(slice_azul, estado);
}
