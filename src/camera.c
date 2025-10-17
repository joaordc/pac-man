#include "camera.h"
#include "raylib.h"
#include "raymath.h"
#include "entidade.h"

float funcSegGrauSuave(float z) {
    return ((-1.0f/32.0f) * (z * z) - (2.0f/5.0f) * z);
}

void AtualizarCam3D(Camera3D *camera, Vector3 posInicial, Entidade *alvo, Vector2 mapa, float tempoDelta, float suavidade) {
    // Target 
    Vector3 diffPacCam = Vector3Subtract(alvo->posicao, camera->target);
    camera->target.x += diffPacCam.x * tempoDelta * suavidade;
    camera->target.z += (diffPacCam.z) * tempoDelta * suavidade;

    // Eixos z e y
    Vector3 diffCamOrig = Vector3Subtract(camera->position, posInicial);

    float limiteZonaAtivaZ = mapa.y/2.0f - ((1.0f/3.0f) * mapa.y);
    
    if (alvo->posicao.z > limiteZonaAtivaZ || alvo->posicao.z < -limiteZonaAtivaZ) {
        float diffPacZona = alvo->posicao.z - limiteZonaAtivaZ;
        float z = (diffPacZona) - (diffCamOrig.z);             
        float y = (funcSegGrauSuave(diffPacZona)) - (diffCamOrig.y); 

        camera->position.z += z * tempoDelta * suavidade * 3;      
        camera->position.y += y * tempoDelta * suavidade * 3;
    } else {
        camera->position.z -= diffCamOrig.z * tempoDelta * suavidade * 3; 
        camera->position.y -= diffCamOrig.y * tempoDelta * suavidade * 3;
    }

    // Eixo x
    float x = (alvo->posicao.x/1.2f - diffCamOrig.x);
    camera->position.x += x * tempoDelta * suavidade;  
}