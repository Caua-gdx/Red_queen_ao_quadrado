#include <Adafruit_NeoPixel.h>

#include "config.h"
#include "matriz.h"

static Adafruit_NeoPixel leds(LARGURA * ALTURA, PINO_MATRIZ, NEO_GRB + NEO_KHZ800);

extern "C" void matriz_iniciar(void)
{
  leds.begin();
  leds.setBrightness(BRILHO_GERAL);
  leds.clear();
  leds.show();
}

extern "C" void matriz_pintar(int x, int y, Cor cor)
{
  if (x < 0 || x >= LARGURA || y < 0 || y >= ALTURA) {
    return;
  }
  leds.setPixelColor(y * LARGURA + x, leds.Color(cor.r, cor.g, cor.b));
}

extern "C" void matriz_mostrar(void)
{
  leds.show();
}
