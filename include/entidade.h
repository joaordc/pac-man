#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "raylib.h"

typedef enum {
    cima,
    baixo,
    esquerda,
    direita
} Sentido;

typedef struct {
    Vector3 posicao;
    Color cor;
    Sentido sentido;
} Entidade;

void MoverEntidade(
    Entidade *pacman, 
    float *cronometro, 
    float velocidade
);

#endif