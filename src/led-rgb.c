#include "../includes/led-rgb.h"

// Variáveis de estado do LED vermelho
static bool estado_led_vermelho = false;

// Configura os pinos do LED RGB como saída
void configurar_led_rgb(void) {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
}

// Define a cor do LED RGB (sem interferir no piscar do vermelho)
void set_led_rgb(bool red, bool green, bool blue) {
    gpio_put(LED_G, green);
    gpio_put(LED_B, blue);
}

// Função que pisca **somente** o LED vermelho
bool piscar_led_rgb_vermelho(struct repeating_timer *t) {
    estado_led_vermelho = !estado_led_vermelho;
    gpio_put(LED_R, estado_led_vermelho);
    return true;
}
