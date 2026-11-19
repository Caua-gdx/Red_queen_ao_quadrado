#include "brilhos.h"
#include "config.h"
#include "coracao.h"

typedef struct {
  int           x, y;
  unsigned long inicio;
  float         intensidade;
} Brilho;

static Brilho        brilhos[NUM_BRILHOS];
static unsigned long semente = 12345;

static unsigned int aleatorio(unsigned int max)
{
  semente = semente * 1103515245UL + 12345UL;
  return (unsigned int)((semente >> 16) % max);
}

static void sortear(Brilho *b, unsigned long agora_ms)
{
  do {
    b->x = (int)aleatorio(LARGURA);
    b->y = (int)aleatorio(ALTURA);
  } while (coracao_tipo(b->x, b->y, 1.0f + BATIDA_CRESCE + 0.1f) != PIXEL_FORA);

  b->inicio = agora_ms + aleatorio(DURACAO_BRILHO); /* espalha no tempo */
  b->intensidade = 0.0f;
}

void brilhos_iniciar(unsigned long agora_ms)
{
  for (int i = 0; i < NUM_BRILHOS; i++) {
    sortear(&brilhos[i], agora_ms);
  }
}

void brilhos_atualizar(unsigned long agora_ms)
{
  for (int i = 0; i < NUM_BRILHOS; i++) {
    Brilho *b = &brilhos[i];

    if (agora_ms < b->inicio) {
      b->intensidade = 0.0f; 
      continue;
    }

    unsigned long idade = agora_ms - b->inicio;
    if (idade >= DURACAO_BRILHO) {
      sortear(b, agora_ms);
      continue;
    }

    float fase = (float)idade / DURACAO_BRILHO;
    b->intensidade = fase < 0.5f ? fase * 2.0f : (1.0f - fase) * 2.0f;
  }
}

float brilhos_intensidade(int x, int y)
{
  float maior = 0.0f;
  for (int i = 0; i < NUM_BRILHOS; i++) {
    if (brilhos[i].x == x && brilhos[i].y == y && brilhos[i].intensidade > maior) {
      maior = brilhos[i].intensidade;
    }
  }
  return maior;
}
