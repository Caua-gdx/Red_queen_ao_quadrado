#ifndef COR_H
#define COR_H

#include <stdint.h>

typedef struct {
  uint8_t r, g, b;
} Cor;

static inline Cor cor_rgb(uint8_t r, uint8_t g, uint8_t b)
{
  Cor c = { r, g, b };
  return c;
}

static inline Cor cor_escalar(Cor c, float fator)
{
  if (fator < 0.0f) fator = 0.0f;
  if (fator > 1.0f) fator = 1.0f;
  return cor_rgb((uint8_t)(c.r * fator), (uint8_t)(c.g * fator), (uint8_t)(c.b * fator));
}

static inline Cor cor_misturar(Cor a, Cor b, float t)
{
  if (t < 0.0f) t = 0.0f;
  if (t > 1.0f) t = 1.0f;
  return cor_rgb((uint8_t)(a.r + (b.r - a.r) * t),
                 (uint8_t)(a.g + (b.g - a.g) * t),
                 (uint8_t)(a.b + (b.b - a.b) * t));
}

#endif
