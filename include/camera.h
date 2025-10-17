#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include "entidade.h"


void AtualizarCam3D(
    Camera3D *camera, 
    Vector3 posInicial, 
    Entidade *alvo, 
    Vector2 mapa, 
    float tempoDelta, 
    float suavidade
);

#endif