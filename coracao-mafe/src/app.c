#include <Arduino.h>
#include <stdio.h>

#include "app.h"
#include "batimento.h"
#include "brilhos.h"
#include "config.h"
#include "cor.h"
#include "coracao.h"
#include "matriz.h"
#include "texto.h"

#define LINHA_TOPO  1
#define LINHA_BASE  (ALTURA - 3)

static unsigned long inicio = 0;

static Cor cor_do_pixel(int x, int y, float batida, float escala,
                        int linha_cheia, int letras)
{
  TipoPixel tipo = coracao_tipo(x, y, escala);

  if (tipo == PIXEL_FORA) {
    return cor_escalar(cor_rgb(COR_BRILHINHO), brilhos_intensidade(x, y));
  }

  if (tipo == PIXEL_BORDA) {
    return cor_escalar(cor_rgb(COR_BORDA), 0.75f + 0.25f * batida);
  }

  if (y < linha_cheia) {
    return cor_rgb(0, 0, 0);
  }

  if (texto_aceso(x, y, letras)) {
    return cor_escalar(cor_rgb(COR_TEXTO), 0.85f + 0.15f * batida);
  }

  if (coracao_reflexo(x, y)) {
    return cor_rgb(COR_REFLEXO);
  }

  float altura = (float)(y - LINHA_TOPO) / (LINHA_BASE - LINHA_TOPO);
  Cor recheio = cor_misturar(cor_rgb(COR_DENTRO_TOPO), cor_rgb(COR_DENTRO_BASE), altura);
  return cor_escalar(recheio, 0.6f + 0.4f * batida);
}

void app_iniciar(void)
{
  matriz_iniciar();
  inicio = millis();
  brilhos_iniciar(inicio);
  printf("Coracao da mafe2 ligado <3\n");
}

void app_atualizar(void)
{
  unsigned long agora = millis();
  unsigned long t = agora - inicio;
  unsigned long fim_letras = TEMPO_ENCHER + (unsigned long)texto_num_letras() * TEMPO_POR_LETRA;

  int linha_cheia = LINHA_TOPO;
  if (t < TEMPO_ENCHER) {
    linha_cheia = LINHA_BASE + 1 - (int)((LINHA_BASE + 1 - LINHA_TOPO) * t / TEMPO_ENCHER);
  }

  int letras = 0;
  if (t >= TEMPO_ENCHER) {
    letras = (int)((t - TEMPO_ENCHER) / TEMPO_POR_LETRA) + 1;
  }

  float batida = 0.0f;
  if (t >= fim_letras) {
    batida = batimento_intensidade(t - fim_letras);
  }
  float escala = 1.0f + BATIDA_CRESCE * batida;

  brilhos_atualizar(agora);

  for (int y = 0; y < ALTURA; y++) {
    for (int x = 0; x < LARGURA; x++) {
      matriz_pintar(x, y, cor_do_pixel(x, y, batida, escala, linha_cheia, letras));
    }
  }
  matriz_mostrar();

  unsigned long gasto = millis() - agora;
  if (gasto < PERIODO_QUADRO) {
    delay(PERIODO_QUADRO - gasto);
  }
}
