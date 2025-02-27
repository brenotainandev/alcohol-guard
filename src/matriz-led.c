#include "../includes/matriz-led.h"

uint32_t retorno_rgb(double b, double r, double g)
{
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}