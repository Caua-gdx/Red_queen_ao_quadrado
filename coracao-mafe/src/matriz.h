#ifndef MATRIZ_H
#define MATRIZ_H

#include "cor.h"

#ifdef __cplusplus
extern "C" {
#endif

void matriz_iniciar(void);
void matriz_pintar(int x, int y, Cor cor);  
void matriz_mostrar(void);                  

#ifdef __cplusplus
}
#endif

#endif 
