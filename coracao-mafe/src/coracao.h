#ifndef CORACAO_H
#define CORACAO_H

#include <stdbool.h>

typedef enum {
  PIXEL_FORA,
  PIXEL_BORDA,
  PIXEL_DENTRO
} TipoPixel;

TipoPixel coracao_tipo(int x, int y, float escala);

bool coracao_reflexo(int x, int y);

#endif 
