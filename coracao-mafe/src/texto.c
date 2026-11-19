#include <string.h>

#include "config.h"
#include "texto.h"

#define ALTURA_LETRA 6

typedef struct {
  int         largura;
  const char *linhas[ALTURA_LETRA]; 
} Letra;


static const Letra letras[] = {
  { 5, { ".....",
         ".....",
         "##.#.",
         "#.#.#",
         "#.#.#",
         "#.#.#" } },  
  { 3, { "...",
         "...",
         ".##",
         "#.#",
         "#.#",
         ".##" } },    
  { 3, { ".##",
         "#..",
         "###",
         "#..",
         "#..",
         "#.." } },    
  { 3, { "...",
         "...",
         ".#.",
         "###",
         "#..",
         ".##" } },    
  { 3, { "##.",
         "..#",
         ".#.",
         "###",
         "...",
         "..." } },    
};
#define NUM_LETRAS ((int)(sizeof(letras) / sizeof(letras[0])))
#define ESPACO     1   

static int largura_total(void)
{
  int total = 0;
  for (int i = 0; i < NUM_LETRAS; i++) {
    total += letras[i].largura;
  }
  return total + ESPACO * (NUM_LETRAS - 1);
}

int texto_num_letras(void)
{
  return NUM_LETRAS;
}

bool texto_aceso(int x, int y, int letras_visiveis)
{
  int linha = y - TEXTO_LINHA;
  if (linha < 0 || linha >= ALTURA_LETRA) {
    return false;
  }

  int coluna = (LARGURA - largura_total() + 1) / 2;

  for (int i = 0; i < NUM_LETRAS && i < letras_visiveis; i++) {
    int dx = x - coluna;
    if (dx >= 0 && dx < letras[i].largura) {
      return letras[i].linhas[linha][dx] == '#';
    }
    coluna += letras[i].largura + ESPACO;
  }
  return false;
}
