#include "config.h"
#include "coracao.h"

static const int reflexo[][2] = { { 8, 5 }, { 7, 5 }, { 6, 6 }, { 6, 7 } };
#define NUM_REFLEXO (sizeof(reflexo) / sizeof(reflexo[0]))

static bool dentro(int x, int y, float escala)
{
  float raio = CORACAO_RAIO * escala;
  float px = (x - CORACAO_CENTRO_X) / raio;
  float py = (CORACAO_CENTRO_Y - y) / raio; 
  float a  = px * px + py * py - 1.0f;

  return a * a * a - px * px * py * py * py <= 0.0f;
}

TipoPixel coracao_tipo(int x, int y, float escala)
{
  if (!dentro(x, y, escala)) {
    return PIXEL_FORA;
  }

  if (!dentro(x + 1, y, escala) || !dentro(x - 1, y, escala) ||
      !dentro(x, y + 1, escala) || !dentro(x, y - 1, escala)) {
    return PIXEL_BORDA;
  }

  return PIXEL_DENTRO;
}

bool coracao_reflexo(int x, int y)
{
  for (unsigned int i = 0; i < NUM_REFLEXO; i++) {
    if (reflexo[i][0] == x && reflexo[i][1] == y) {
      return true;
    }
  }
  return false;
}
