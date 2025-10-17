#include "entidade.h"

void MoverEntidade(Entidade *ent, float *cronometro, float velocidade) {
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) ent->sentido = direita;
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) ent->sentido = esquerda;
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) ent->sentido = baixo;
    else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) ent->sentido = cima;

    if (*cronometro >= velocidade){
        switch (ent->sentido)
        {
        case direita:
            ent->posicao.x += 1.0f;
            break;
        
        case esquerda:
            ent->posicao.x -= 1.0f;
            break;

        case baixo:
            ent->posicao.z += 1.0f;
            break;

        case cima:
            ent->posicao.z -= 1.0f;
            break;
        }

        *cronometro -= velocidade;
    } 

    return;
}