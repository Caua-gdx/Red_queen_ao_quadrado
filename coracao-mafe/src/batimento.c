#include <math.h>

#include "batimento.h"
#include "config.h"

static float pulso(float t, float centro, float largura)
{
  float d = (t - centro) / largura;
  if (d < -1.0f || d > 1.0f) {
    return 0.0f;
  }
  return 0.5f * (1.0f + cosf(d * 3.14159265f));
}

float batimento_intensidade(unsigned long t_ms)
{
  float t = (float)(t_ms % PERIODO_BATIDA);

  float tum1 = pulso(t, 120.0f, 120.0f);         
  float tum2 = 0.7f * pulso(t, 380.0f, 120.0f); 
  return tum1 > tum2 ? tum1 : tum2;
}
